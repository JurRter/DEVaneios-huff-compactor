#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    unsigned char byte;          
    unsigned int frequencia;     
    struct Node *esquerda;       
    struct Node *direita;        
} Node;

typedef struct MinHeap {
    unsigned int tamanho_atual;  
    unsigned int capacidade;     
    Node **vetor_de_nos;        
} MinHeap;

void calc_frequencias(FILE *arquivo_entrada, unsigned int *frequencias) {
    //TODO
}

MinHeap* filaprioridade(unsigned int *frequencias) {
    // TODO
    return NULL;
}

void insertfila(MinHeap *heap, Node *no) {
    // TODO
}

Node* minminheap(MinHeap *heap) {
    // TODO extrair o minimo
    return NULL;
}

Node* construir_arvore_huffman(MinHeap *heap) {
    // TODO: Fazer um loop extraindo os 2 menores, criando um pai e inserindo de volta, até restar 1 nó.
    return NULL;
}

void gerar_dicionario(Node *raiz, char **dicionario, char *caminho_atual, int profundidade) {
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