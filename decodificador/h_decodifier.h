#ifndef H_DECODIFIER_H
#define H_DECODIFIER_H

#include <stdio.h>

typedef struct Node {
    unsigned char byte;
    unsigned int freq;
    struct Node *esq;
    struct Node *dir;
} Node;

typedef struct MinHeap {
    unsigned int tam;
    unsigned int cap;
    Node **vetor;
} MinHeap;

Node* criar_no(unsigned char byte);
void heapify_up(MinHeap *heap, int index);
void insertfila(MinHeap *heap, Node *no);
MinHeap* filaprioridade_dec(unsigned int *frequencias);
void heapify_down(MinHeap *heap, int index);
Node* minminheap(MinHeap *heap);
Node* construir_arvore_huffman_dec(MinHeap *heap);
void decodificar_arquivo(FILE *entrada, FILE *saida, Node *raiz, int bits_lixo);
void liberar_arvore_dec(Node *raiz);

#endif // H_DECODIFIER_H
