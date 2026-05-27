# DEVaneios-huff-compactor

Este projeto implementa um utilitário de linha de comando para **compactação e descompactação de arquivos** utilizando o **Algoritmo de Huffman**. Desenvolvido como trabalho prático para a disciplina de **Estrutura de Dados 2**, o software aplica conceitos de Árvores Binárias, Filas de Prioridade (Min-Heaps) e Tabelas de Frequência.

- LINK DO SLIDE: https://www.canva.com/design/DAHK4pHGYCY/zRnonBUnxSvnT7_EK_sYyw/edit
## Estrutura do Projeto

- `codificador/`: Implementação do compressor.
- `decodificador/`: Implementação do decompressor.
- `arquivos_txt/`: Exemplos de arquivos para teste.
- `README.md`: Documentação principal.


## Funcionamento e Algoritmo

O algoritmo de Huffman é uma técnica de compressão sem perdas baseada na frequência de ocorrência de símbolos (bytes).
1. **Frequência**: O arquivo é lido byte a byte para contar as ocorrências de cada um dos 256 valores possíveis.
2. **Árvore de Huffman**: Uma árvore binária é construída usando uma fila de prioridade (Min-Heap), onde os bytes menos frequentes ficam nas folhas mais profundas.
3. **Dicionário**: A árvore é percorrida para gerar códigos binários variáveis (bits) para cada byte.
4. **Codificação**: O arquivo original é reescrito substituindo os bytes pelos seus respectivos códigos binários.

## Formato do Arquivo `.huff`

O cabeçalho do arquivo compactado segue o layout abaixo:

| Campo | Tamanho | Descrição |
| :--- | :--- | :--- |
| **Contagem** | 4 bytes (int) | Quantidade de bytes únicos presentes na tabela de frequências. |
| **Tabela** | Variável | Sequência de pares `[Byte (1 byte) + Frequência (4 bytes)]`. |
| **Lixo** | 1 byte | Inteiro (0 a 7) indicando bits a descartar no último byte. |
| **Payload** | Variável | Bloco de dados codificado. |

## Como Compilar

Certifique-se de ter o `gcc` instalado.

### Via GCC diretamente:
```bash
# Compilar Codificador
gcc codificador/*.c -o huff_compressor
ou 
gcc codificador/main.c codificador/h_codifier -o huff_compressor

# Compilar Decodificador
gcc decodificador/*.c -o huff_decompressor
ou
gcc codificador/main.c codificador/h_decodifier -o huff_compressor
```

## Como Usar

O programa opera via Interface de Linha de Comando (CLI).

### 1. Compactar (Codificador)
```bash
./huff_compressor.exe <caminho_entrada> <caminho_saida.huff>
```
Exemplo: `./huff_compressor.exe arquivos_txt/domcasmurro.txt saida.huff`

### 2. Descompactar (Decodificador)
```bash
./huff_decompressor.exe <caminho_entrada.huff> <caminho_saida_original.txt>
```
Exemplo: `./huff_decompressor.exe saida.huff recuperado.txt`

## Resultados e Performance

Testes realizados com os arquivos presentes na pasta `arquivos_txt/`:

| Arquivo Original | Tamanho Original | Tamanho Comprimido | Redução (%) |
| :--- | :--- |:-------------------|:------------|
| `domcasmurro.txt` | 390.272 bytes | 229.058 bytes      | **41,3%*    |
| `lorem_ipsum.txt` | 2.839 bytes | 1.713 bytes        | **39,7%**   |
| `MEGAZORD_huffman.txt`| 1.020.000 bytes | 466.430 bytes      | **54,3%**   |

| Arquivo Original | Tamanho Original | Tamanho Comprimido | Acrescimo (%) |
| :--- | :--- |:-------------------|:--------------|
| `key_red_dead...txt`| 29 bytes | 147 bytes          | **406,9%**    |

*Em arquivos extremamente pequenos, a compressão teve um efeito negativo.*

## 👥 Equipe DEVaneios
- Brendo
- Samir
- Tiago

