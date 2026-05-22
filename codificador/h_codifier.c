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
    if (!arquivo_entrada || !frequencias)return; // checa se a frequencia e o arquivo de entrada e null.
    unsigned char buf [4096];
    size_t n;
    while ((n = fread(buf,1,sizeof(buf), arquivo_entrada))>0) {
        for (size_t i = 0; i < n; i++) {
            frequencias[buf[i]]++; //vai checar o byte(vulgo o simbolo e adicionar na lista de frequencia dele) adicionar nas frequencias
        }
    }
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

        }
    }
    return heap;
}

void insertfila(MinHeap *heap, Node *no) {
    // TODO
}

Node* minminheap(MinHeap *heap) {
    // TODO extrair o minimo
    return NULL;
}

Node* construir_arvore_huffman(MinHeap *heap) {
    for (int i = 0; i < 256; i++) {

    }

    // TODO: Fazer um loop extraindo os 2 menores, criando um pai e inserindo de volta, até restar 1 nó.
    return NULL;
}

void gerar_dicionario(Node *raiz, char **dicionario, char *caminho_atual, int profundidade) {
    if (!raiz) return; //se for nulo retorna
    if (!raiz->dir && !raiz->esq) { //checagem de folha
        caminho_atual[profundidade] = '\0'; // finaliza a linha e copia pro dicionario
        strcpy(dicionario[raiz->byte], caminho_atual); // se é q eu entendi oq vc quer dizer com dicionario ne, ele vai copiar a str, jogar no dicionario com a posiçao do dicionario de mesmo byte ai se eles forem iguais eles caem no mesmo lugar, pelo codigo n estar vermelho eu acho q ta funcionando maneiro
    }



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

int executar_compressao(const char *arquivo_entrada, const char *arquivo_saida) {
    // TODO: Função "maestro" que chama todas as funções acima na ordem correta.
    return 0; // 0 para erro, 1 para sucesso
}

/*void liberar_arvore(Node *raiz) {
    // TODO: Percorrer em pós-ordem dando free() nos filhos da esquerda, direita e depois na raiz.
}

void liberar_dicionario(char **dicionario) {
    // TODO: Fazer um loop de 0 a 255 dando free() nas strings alocadas.
} aqui viria alguma de limpeza de memoria, veja ai se quer fazer essa parada*/