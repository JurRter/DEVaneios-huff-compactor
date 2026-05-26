#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void heapify_up(MinHeap *heap, int idx) {
    int pai = (idx - 1) / 2;
    if (idx > 0 && heap->vetor[idx]->freq < heap->vetor[pai]->freq) {
        Node *temp = heap->vetor[idx];
        heap->vetor[idx] = heap->vetor[pai];
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

void heapify_down(MinHeap *heap, int idx) {
    int menor = idx;
    int esq = 2 * idx + 1;
    int dir = 2 * idx + 2;

    if (esq < heap->tam && heap->vetor[esq]->freq < heap->vetor[menor]->freq)
        menor = esq;
    if (dir < heap->tam && heap->vetor[dir]->freq < heap->vetor[menor]->freq)
        menor = dir;

    if (menor != idx) {
        Node *temp = heap->vetor[idx];
        heap->vetor[idx] = heap->vetor[menor];
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

        Node* esqn = minminheap(heap); //esqN = esquerda Nó
        Node* rgtn = minminheap(heap); //rgtN = right Nó

        Node* pai = (Node*)malloc(sizeof(Node)); 
        if (!pai) return NULL;
        pai->byte = '*'; // Placeholder para nó interno

        pai->freq = esqn->freq + rgtn->freq;

        pai->esq = esqn;
        pai->dir = rgtn;

        insertfila(heap, pai);

    }

    Node* raiz = minminheap(heap);
    free(heap->vetor);
    free(heap);
    return raiz; //no final sobra apenas a root e é retornada aq
}

void gerar_dicionario(Node *raiz, char **dicionario, char *caminho_atual, int profundidade) {
    if (!raiz) return; //se for nulo retorna
    if (!raiz->dir && !raiz->esq) { //checagem de folha
        caminho_atual[profundidade] = '\0'; // finaliza a linha e copia pro dicionario
        strcpy(dicionario[raiz->byte], caminho_atual); // se é q eu entendi oq vc quer dizer com dicionario ne, ele vai copiar a str, jogar no dicionario com a posiçao do dicionario de mesmo byte ai se eles forem iguais eles caem no mesmo lugar, pelo codigo n estar vermelho eu acho q ta funcionando maneiro
    }

    caminho_atual[profundidade] = '0';
    gerar_dicionario(raiz->esq, dicionario, caminho_atual, profundidade + 1); //desce pra esquerda e marca + 1
    caminho_atual[profundidade] = '1';
    gerar_dicionario(raiz->dir, dicionario, caminho_atual, profundidade + 1); //pro outro aldo

    // TODO: Navegar recursivamente (0 para esquerda, 1 para direita) e salvar a string na folha correspondente.
}

int calcbitslixo(unsigned int *frequencias, char **dicionario) {
    // TODO: Somar (frequencia * tamanho_do_codigo) para todos os bytes e calcular o resto da divisão por 8.
    return 0;
}

void gravar_arquivo_comprimido(const char *caminho_origem, const char *caminho_destino, 
                               unsigned int *frequencias, char **dicionario, int bits_lixo) {
    // TODO: Abrir arquivo origem (leitura) e destino (escrita binária). Gravar cabeçalho e os bits empacotados.
}


//print simples pa testar uns negocios
void imprimir_arvore(Node *raiz, int nivel) {
    if (raiz) {
        imprimir_arvore(raiz->dir, nivel + 1);
        for (int i = 0; i < nivel; i++) printf("   ");
        if (!raiz->esq && !raiz->dir)
            printf("[%c:%u]\n", raiz->byte, raiz->freq);
        else
            printf("(*:%u)\n", raiz->freq);
        imprimir_arvore(raiz->esq, nivel + 1);
    }
}

int executar_compressao(const char *arquivo_entrada, const char *arquivo_saida) {
    // TODO: Função "maestro" que chama todas as funções acima na ordem correta.
    return 0; // 0 para erro, 1 para sucesso
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