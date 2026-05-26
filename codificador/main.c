#include <stdio.h>
#include <stdlib.h>
#include "h_codifier.c"

int main() {
    char *caminho_entrada = "arquivos_txt/trabalho_ed2.txt";
    FILE *arquivo = fopen(caminho_entrada, "rb");
    if (!arquivo) {
        printf("erro ao abrir arquivo %s\n", caminho_entrada);
        return 1;
    }

    unsigned int frequencias[256] = {0};
    calc_frequencias(arquivo, frequencias);
    fclose(arquivo);

    printf("fila\n");
    MinHeap *heap = filaprioridade(frequencias);
    
    printf("arvore\n");
    Node *raiz = construir_arvore_huffman(heap);

    if (raiz) {
        printf("boa\n");
        imprimir_arvore(raiz, 0);
        
        liberar_arvore(raiz);
    } else {
        printf("erro em construir\n");
    }

    return 0;
}
