cmake_minimum_required(VERSION 4.2)
project(DEVaneios_huff_compactor C)

set(CMAKE_C_STANDARD 11)

add_executable(Codifier
        "codificador/h_codifier.c"
        codificador/main.c
)

add_executable(Decodifier
        "decodificador/h_decodifier.c"
)