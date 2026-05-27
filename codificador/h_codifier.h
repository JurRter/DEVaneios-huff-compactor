#ifndef H_CODIFIER_H
#define H_CODIFIER_H

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

void calc_frequencias(FILE *arquivo_entrada, unsigned int *frequencias);
void heapify_up(MinHeap *heap, int index);
void insertfila(MinHeap *heap, Node *no);
MinHeap* filaprioridade(unsigned int *frequencias);
void heapify_down(MinHeap *heap, int index);
Node* minminheap(MinHeap *heap);
Node* construir_arvore_huffman(MinHeap *heap);
void gerar_dicionario(Node *raiz, char **dicionario, char *caminho_atual, int profundidade);
int calcbitslixo(unsigned int *frequencias, char **dicionario);
void gravar_arquivo_comprimido(const char *caminho_origem, const char *caminho_destino, 
                               Node *raiz, char **dicionario, int bits_lixo, unsigned int *frequencias);
void liberar_arvore(Node *raiz);
void liberar_dicionario(char **dicionario);

#endif // H_CODIFIER_H
