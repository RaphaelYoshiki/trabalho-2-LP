/* coletor.h*/
#include <stdio.h>
#include <stdlib.h>

#define TAM_HEAP 512

typedef struct structObj {
    int marcado;
    struct structObj *prox;
    int valor;
} Objeto;

typedef struct {
    Objeto *heap[TAM_HEAP];
    int tam_heap;

    Objeto *primeiro;
    int qtdObj;
    int maxObj;
} Heap;

Heap *criaHeap();

void pushObj(Heap *heap, Objeto *obj);

Objeto *pop(Heap *heap);

void mark(Objeto *obj);

void mark_heap(Heap *heap);

void sweep(Heap *heap);

void coletor(Heap *heap);

Objeto *criaObj(Heap *heap);

void push(Heap *heap, int val);

void freeheap(Heap *heap);