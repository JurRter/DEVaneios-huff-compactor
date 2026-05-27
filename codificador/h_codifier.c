#include "h_codifier.h"
#include <stdlib.h>
#include <string.h>


void calc_frequencias(FILE *arquivo_entrada, unsigned int *frequencias) {
    if (!arquivo_entrada) return;
    unsigned char buf[1024];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), arquivo_entrada)) > 0) {
        for (size_t i = 0; i < n; i++) {
            frequencias[buf[i]]++;
        }
    }
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

MinHeap* filaprioridade(unsigned int *frequencias) {
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
    heap->tam--; //manobra de substituição

    heapify_down(heap, 0); //agora checa o no de menor frequencia

    return raiz;
}

Node* construir_arvore_huffman(MinHeap *heap) {
    if(!heap || heap->tam == 0) return NULL;

    while (heap->tam > 1){

        Node* esq = minminheap(heap);
        Node* rit = minminheap(heap);

        Node* pai = (Node*)malloc(sizeof(Node)); 
        if (!pai) return NULL;
        pai->byte = '*'; // Placeholder para nó interno

        pai->freq = esq->freq + rit->freq;

        pai->esq = esq;
        pai->dir = rit;

        insertfila(heap, pai);

    }

    Node* raiz = minminheap(heap);
    free(heap->vetor);
    free(heap);
    return raiz; //no final sobra apenas a root e é retornada aq
}

void gerar_dicionario(Node *raiz, char **dicionario, char *caminho_atual, int profundidade) {
    if (!raiz) return;
    if (!raiz->dir && !raiz->esq) {
        caminho_atual[profundidade] = '\0';
        strcpy(dicionario[raiz->byte], caminho_atual);
    } else {
        caminho_atual[profundidade] = '0';
        gerar_dicionario(raiz->esq, dicionario, caminho_atual, profundidade + 1);
        caminho_atual[profundidade] = '1';
        gerar_dicionario(raiz->dir, dicionario, caminho_atual, profundidade + 1);
    }
}

void serial_tree(Node *raiz, FILE *saida, unsigned short *tam_arvore) {
    if (!raiz) return;
    (*tam_arvore)++;
    if (!raiz->esq && !raiz->dir) {
        if (raiz->byte == '*' || raiz->byte == '\\') {
            unsigned char escape = '\\';
            fwrite(&escape, 1, 1, saida);
            (*tam_arvore)++;
        }
        fwrite(&(raiz->byte), 1, 1, saida);
    } else {
        unsigned char byte = '*';
        fwrite(&byte, 1, 1, saida);
        serial_tree(raiz->esq, saida, tam_arvore);
        serial_tree(raiz->dir, saida, tam_arvore);
    }
}

int calcbitslixo(unsigned int *frequencias, char **dicionario) {
    unsigned long long total_bits = 0;
    for (int i = 0; i < 256; i++) {
        if (frequencias[i] > 0) {
            total_bits += (unsigned long long)frequencias[i] * strlen(dicionario[i]);
        }
    }
    int lixo = 8 - (total_bits % 8);
    return (lixo == 8) ? 0 : lixo;
}

void gravar_arquivo_comprimido(const char *caminho_origem, const char *caminho_destino, 
                               Node *raiz, char **dicionario, int bits_lixo, unsigned int *frequencias) {
    FILE *origem = fopen(caminho_origem, "rb");
    FILE *destino = fopen(caminho_destino, "wb");
    if (!origem || !destino) return;

    // 1. Contagem (4 bytes): Quantidade de bytes únicos
    int contagem = 0;
    for (int i = 0; i < 256; i++) {
        if (frequencias[i] > 0) contagem++;
    }
    fwrite(&contagem, sizeof(int), 1, destino);

    // 2. Tabela: Sequência de pares [Byte (1 byte) | Frequencia (4 bytes)]
    for (int i = 0; i < 256; i++) {
        if (frequencias[i] > 0) {
            unsigned char b = (unsigned char)i;
            fwrite(&b, 1, 1, destino);
            fwrite(&frequencias[i], sizeof(unsigned int), 1, destino);
        }
    }

    // 3. Lixo (1 byte)
    unsigned char lixo = (unsigned char)bits_lixo;
    fwrite(&lixo, 1, 1, destino);

    // 4. Payload: Dados codificados
    unsigned char buffer_in[1024];
    unsigned char byte_out = 0;
    int bit_count = 0;
    size_t n;

    while ((n = fread(buffer_in, 1, sizeof(buffer_in), origem)) > 0) {
        for (size_t i = 0; i < n; i++) {
            char *codigo = dicionario[buffer_in[i]];
            for (int j = 0; codigo[j] != '\0'; j++) {
                if (codigo[j] == '1') {
                    byte_out = byte_out | (1 << (7 - bit_count));
                }
                bit_count++;
                if (bit_count == 8) {
                    fwrite(&byte_out, 1, 1, destino);
                    byte_out = 0;
                    bit_count = 0;
                }
            }
        }
    }
    if (bit_count > 0) {
        fwrite(&byte_out, 1, 1, destino);
    }

    fclose(origem);
    fclose(destino);
}

void liberar_arvore(Node *raiz) {
    if (!raiz) return;
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
}

void liberar_dicionario(char **dicionario) {
    if (!dicionario) return;
    for (int i = 0; i < 256; i++) {
        if (dicionario[i]) free(dicionario[i]);
    }
    free(dicionario);
}
