#include <stdio.h>
#include <stdlib.h>
#include "coletor.h"

Heap *criaHeap() {
    Heap *heap = malloc(sizeof(Heap));
    heap->tam_heap = 0;
    heap->primeiro = NULL;
    heap->qtdObj = 0;
    heap->maxObj = 10;
    return heap;
}

void pushObj(Heap *heap, Objeto *obj) {
    heap->heap[heap->tam_heap++] = obj;
}

Objeto *pop(Heap *heap) {
    return heap->heap[heap->tam_heap--];
}

void mark(Objeto *obj) {
    if (obj->marcado) {
        return;
    }
    else {
        obj->marcado = 1;
    }
}

void mark_heap(Heap *heap) {
    for (int i = 0; i < heap->tam_heap; i++) {
        mark(heap->heap[i]);
    }
}

void sweep(Heap *heap) {
    Objeto **obj = &heap->primeiro; //Ponteiro para Objeto *primeiro (outro ponteiro)
    while (*obj) { //Enquanto o endereço de memória de "obj" existir
        if ((*obj)->marcado == 0) {
            Objeto *temp = *obj;
            *obj = temp->prox;
            free(temp);
            heap->qtdObj--;
        }
        else {
            (*obj)->marcado = 0;
            obj = &(*obj)->prox;
        }
    }    
}

void coletor(Heap *heap) {
    mark_heap(heap);
    sweep(heap);

    if (heap->qtdObj == 0) {
        heap->maxObj = 10; //10 foi o valor que escolhi como máximo de objetos para o heap
    }
    else {
        heap->maxObj = heap->qtdObj * 2;
    }
}

Objeto *criaObj(Heap *heap) {
    if (heap->qtdObj >= heap->maxObj) { //Se o heap passar do limite ativa o coletor de lixo
        coletor(heap);
    }

    Objeto *obj = malloc(sizeof(Objeto));
    obj->prox = heap->primeiro;
    heap->primeiro = obj;
    obj->marcado = 0;
    heap->qtdObj++;

    return obj;
}

void push(Heap *heap, int val) {
    Objeto *obj = criaObj(heap);
    obj->valor = val;
    pushObj(heap, obj);
}

void freeheap(Heap *heap) {
    heap->tam_heap = 0;
    coletor(heap);
    free(heap);
}