#include <stdlib.h>
#include <stdio.h>


int leitor(FILE *f) {
    *f = fopen("Entrada.bin", "rb");
    if (!f) {
        perror("fopen"); return 1;
    }
    int c;
    while ((c = fgetc(f)) != EOF) {
        unsigned char b = (unsigned char)c;
    }
}
