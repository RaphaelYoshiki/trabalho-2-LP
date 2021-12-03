//VSCode não consegue rodar programas com bibliotecas criadas pelo usuário
//por algum motivo

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_HEAP 512
#define TAM_MAX_HEAP 64

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

Heap *criaHeap() {
    Heap *heap = malloc(sizeof(Heap));
    heap->tam_heap = 0;
    heap->primeiro = NULL;
    heap->qtdObj = 0;
    heap->maxObj = TAM_MAX_HEAP;
    return heap;
}

void pushObj(Heap *heap, Objeto *obj) { //Armazena o objeto no heap e incrementa o tam_heap
    heap->heap[heap->tam_heap] = obj;
    heap->tam_heap++;
    //printf("Push!\n");
}

Objeto *pop(Heap *heap) { //Diminui o tam_ heap e retorna o heap
    heap->tam_heap--;
    //printf("Pop!\n");
    return heap->heap[heap->tam_heap];
}

void mark(Objeto *obj) { //Marca o objeto, a menos que ele já esteja marcado
    if (obj->marcado) {
        return;
    }
    else {
        obj->marcado = 1;
    }
}

void mark_heap(Heap *heap) { //Itera pelo heap inteiro e marca tudo
    for (int i = 0; i < heap->tam_heap; i++) {
        mark(heap->heap[i]);
        //printf("Marcado.\n");
    }
}

void sweep(Heap *heap) { //Varredura do heap
    Objeto **obj = &heap->primeiro; //Ponteiro para Objeto *primeiro (outro ponteiro) -> Primeiro elemento do heap
    while (*obj) { //Enquanto o endereço de memória de "obj" existir
        if (!(*obj)->marcado) { //-> Objeto não foi alcançado, deve ser removido
            Objeto *temp = *obj;
            *obj = temp->prox;
            free(temp);
            //printf("Varrido.\n");
            heap->qtdObj--;
        }
        else { //-> Objeto foi alcançado, marcar para o próximo ciclo e pular para o próximo
            (*obj)->marcado = 0;
            obj = &(*obj)->prox;
        }
    }    
}

void coletor(Heap *heap) {
    int qtdObj = heap->qtdObj;

    mark_heap(heap);
    sweep(heap);

    if (heap->qtdObj == 0) {
        heap->maxObj = TAM_MAX_HEAP; //TAM_MAX_HEAP foi o valor que escolhi como máximo de objetos para o heap
    }
    else {
        heap->maxObj = heap->qtdObj * 2; //Dobra a capacidade do heap se o número de objetos ultrapassar TAM_MAX_HEAP
        //Se o heap passar de TAM_HEAP ocorre stack overflow
    }

    printf("%d objetos coletados, restam %d.\n", qtdObj - heap->qtdObj, heap->qtdObj);
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
    
    printf("heap->tam_heap = %d\nheap->qtdObj = %d\nheap->maxObj = %d\n\n", heap->tam_heap, heap->qtdObj, heap->maxObj);
}

void freeheap(Heap *heap) { //Libera a memória do heap inteiro
    heap->tam_heap = 0;
    coletor(heap);
    free(heap);
}

int main () {
    puts("Compilou!\n");
    Heap* heap = criaHeap();

    time_t t;
    srand((unsigned) time(&t));
    
    int input;
    int escolha;
    printf("Qtos?\n");
    scanf("%d", &input);

    printf("Push(1) ou pop(2)?  --Primeira vez deve ser push--\n");
    scanf("%d", &escolha);

    while (input >= 0) {
        if (escolha == 1) {
            for(int i = 0 ; i < input ; i++) {
                push(heap, rand() % 100);
            }
        }
        else if (escolha == 2) {
            for(int i = 0 ; i < input ; i++) {
                pop(heap);
            }
        }        
        printf("Qtos?\n");
        scanf("%d", &input);
        printf("Push(1) ou pop(2)?\n");
        scanf("%d", &escolha);
    }

    coletor(heap);
    freeheap(heap);
    return 0;
}