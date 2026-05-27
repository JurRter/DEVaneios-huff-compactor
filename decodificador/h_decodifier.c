#include "h_decodifier.h"
#include <stdlib.h>
#include <string.h>

Node* criar_no(unsigned char byte) {
    Node* novo = (Node*)malloc(sizeof(Node));
    if (novo) {
        novo->byte = byte;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

void heapify_up(MinHeap *heap, int index) {
    int pai = (index - 1) / 2;
    if (index > 0 && heap->vetor[index]->freq < heap->vetor[pai]->freq) {
        Node *temp = heap->vetor[index];
        heap->vetor[index] = heap->vetor[pai];
        heap->vetor[pai] = temp;
        heapify_up(heap, pai);
    }
}

void insertfila(MinHeap *heap, Node *no) {
    if (heap->tam == heap->cap) return;
    heap->vetor[heap->tam] = no;
    heapify_up(heap, heap->tam);
    heap->tam++;
}

MinHeap* filaprioridade_dec(unsigned int *frequencias) {
    MinHeap* heap = malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    heap->tam = 0;
    heap->cap = 256;
    heap->vetor = malloc(heap->cap * sizeof(Node*));
    if (!heap->vetor) return NULL;
    for (int i = 0; i < 256; i++) {
        if (frequencias[i] > 0) {
            Node* no = (Node*)malloc(sizeof(Node));
            if (!no) return NULL;
            no->byte = (unsigned char)i;
            no->freq = frequencias[i];
            no->esq = no->dir = NULL;
            insertfila(heap, no);
        }
    }
    return heap;
}

void heapify_down(MinHeap *heap, int index) {
    int menor = index;
    int esq = 2 * index + 1;
    int dir = 2 * index + 2;

    if (esq < heap->tam && heap->vetor[esq]->freq < heap->vetor[menor]->freq)
        menor = esq;
    if (dir < heap->tam && heap->vetor[dir]->freq < heap->vetor[menor]->freq)
        menor = dir;

    if (menor != index) {
        Node *temp = heap->vetor[index];
        heap->vetor[index] = heap->vetor[menor];
        heap->vetor[menor] = temp;
        heapify_down(heap, menor);
    }
}

Node* minminheap(MinHeap *heap) {
    if(heap->tam == 0) return NULL;
    Node* raiz = heap->vetor[0];
    heap->vetor[0] = heap->vetor[heap->tam - 1];
    heap->tam--;
    heapify_down(heap, 0);
    return raiz;
}

Node* construir_arvore_huffman_dec(MinHeap *heap) {
    if(!heap || heap->tam == 0) return NULL;
    while (heap->tam > 1){
        Node* esq = minminheap(heap);
        Node* rit = minminheap(heap);
        Node* pai = (Node*)malloc(sizeof(Node)); 
        if (!pai) return NULL;
        pai->byte = '*';
        pai->freq = esq->freq + rit->freq;
        pai->esq = esq;
        pai->dir = rit;
        insertfila(heap, pai);
    }
    Node* raiz = minminheap(heap);
    free(heap->vetor);
    free(heap);
    return raiz;
}

void decodificar_arquivo(FILE *entrada, FILE *saida, Node *raiz, int bits_lixo) {
    Node *atual = raiz;
    unsigned char byte;
    unsigned char proximo_byte;
    
    if (fread(&byte, 1, 1, entrada) != 1) return;

    while (fread(&proximo_byte, 1, 1, entrada) == 1) {
        for (int i = 7; i >= 0; i--) {
            if ((byte >> i) & 1) {
                atual = atual->dir;
            } else {
                atual = atual->esq;
            }

            if (!atual->esq && !atual->dir) {
                fwrite(&(atual->byte), 1, 1, saida);
                atual = raiz;
            }
        }
        byte = proximo_byte;
    }

    // Trata o último byte considerando o lixo
    for (int i = 7; i >= bits_lixo; i--) {
        if ((byte >> i) & 1) {
            atual = atual->dir;
        } else {
            atual = atual->esq;
        }

        if (!atual->esq && !atual->dir) {
            fwrite(&(atual->byte), 1, 1, saida);
            atual = raiz;
        }
    }
}

void liberar_arvore_dec(Node *raiz) {
    if (!raiz) return;
    liberar_arvore_dec(raiz->esq);
    liberar_arvore_dec(raiz->dir);
    free(raiz);
}

