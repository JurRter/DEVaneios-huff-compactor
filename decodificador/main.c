#include <stdio.h>
#include <stdlib.h>
#include "h_decodifier.h"

int main(int argc, char *argv[]) {
    char *arquivo_entrada = (argc > 1) ? argv[1] : "saida.huff";
    char *arquivo_saida = (argc > 2) ? argv[2] : "saida_descompactada.txt";

    printf("descomprimindo %s \n", arquivo_entrada);

    FILE *entrada = fopen(arquivo_entrada, "rb");
    if (!entrada) {
        printf("erro na abertura.\n");
        return 1;
    }

    int contagem;
    if (fread(&contagem, sizeof(int), 1, entrada) != 1) {
        printf("erro na leitura da contagem\n");
        fclose(entrada);
        return 1;
    }

    unsigned int frequencias[256] = {0};
    for (int i = 0; i < contagem; i++) {
        unsigned char b;
        unsigned int f;
        if (fread(&b, 1, 1, entrada) != 1 || fread(&f, sizeof(unsigned int), 1, entrada) != 1) {
            printf("erro na leitura da tabela\n");
            fclose(entrada);
            return 1;
        }
        frequencias[b] = f;
    }

    unsigned char lixo_byte;
    if (fread(&lixo_byte, 1, 1, entrada) != 1) {
        printf("erro na leitura do lixo\n");
        fclose(entrada);
        return 1;
    }
    int bits_lixo = (int)lixo_byte;

    MinHeap *heap = filaprioridade_dec(frequencias);
    Node *raiz = construir_arvore_huffman_dec(heap);
    
    FILE *saida = fopen(arquivo_saida, "wb");
    if (!saida) {
        printf("erro ao descomprimir.\n");
        liberar_arvore_dec(raiz);
        fclose(entrada);
        return 1;
    }

    decodificar_arquivo(entrada, saida, raiz, bits_lixo);

    fclose(entrada);
    fclose(saida);
    liberar_arvore_dec(raiz);

    printf("descomprimiu: %s\n", arquivo_saida);

    return 0;
}
