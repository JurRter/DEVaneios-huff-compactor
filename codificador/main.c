#include <stdio.h>
#include <stdlib.h>
#include "h_codifier.h"

int main(int argc, char *argv[]) {
    char *caminho_entrada = (argc > 1) ? argv[1] : "arquivos_txt/domcasmurro.txt";
    char *caminho_saida = (argc > 2) ? argv[2] : "saida.huff";

    printf("comprimindo: %s \n", caminho_entrada);
    
    unsigned int frequencias[256] = {0};
    FILE *f_entrada = fopen(caminho_entrada, "rb");
    if (!f_entrada) {
        printf("erro na abertura\n");
        return 1;
    }
    calc_frequencias(f_entrada, frequencias);
    fclose(f_entrada);

    MinHeap *heap = filaprioridade(frequencias);
    Node *raiz = construir_arvore_huffman(heap);
    if (!raiz) {
        printf("erro na construção.\n");
        return 1;
    }

    char **dicionario = malloc(256 * sizeof(char *));
    for (int i = 0; i < 256; i++) dicionario[i] = calloc(256, sizeof(char));
    char caminho[256];
    gerar_dicionario(raiz, dicionario, caminho, 0);

    int bits_lixo = calcbitslixo(frequencias, dicionario);
    gravar_arquivo_comprimido(caminho_entrada, caminho_saida, raiz, dicionario, bits_lixo, frequencias);

    liberar_dicionario(dicionario);
    liberar_arvore(raiz);

    printf("comprimiu: %s\n", caminho_saida);

    return 0;
}
