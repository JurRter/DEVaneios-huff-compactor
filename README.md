# DEVaneios-huff-compactor
Trabalho de pesquisa da disciplina de Estrutura de Dados 2.

Este projeto implementa um **Compactador e Descompactador** de arquivos baseado no algoritmo de **Codificação de Huffman**.

## 📁 Estrutura do Projeto

- `codificador/`: Contém o código-fonte responsável por ler um arquivo e aplicar a compressão (`h_codifier.c`).
- `decodificador/`: Contém o código-fonte responsável por ler um arquivo comprimido e restaurar seu conteúdo original (`h_decodifier.c`).
- `arquivos_txt/`: Arquivos de texto de exemplo para realizar testes de desempenho e compressão (ex: `codigo_red_dead_redemption_2.txt` e `domcasmurro.txt`).

## 🛠️ Como Compilar

Para compilar os programas, certifique-se de ter um compilador de C instalado (como o `gcc`). No terminal, rode os comandos:

**Compilar o Codificador:**
```bash
gcc codificador/h_codifier.c -o codificador/h_codifier
```

**Compilar o Decodificador:**
```bash
gcc decodificador/h_decodifier.c -o decodificador/h_decodifier
```

## 🚀 Como Usar (Exemplo)

*(Nota: Adapte essa seção de acordo com os parâmetros que os seus códigos aceitam no `main`)*

**1. Compactando um arquivo texto:**
```bash
./codificador/h_codifier arquivos_txt/domcasmurro.txt domcasmurro.huff
```

**2. Descompactando o arquivo:**
```bash
./decodificador/h_decodifier domcasmurro.huff domcasmurro_restaurado.txt
```

## 👥 Equipe DEVaneios
- Brendo, Samir e Tiago

