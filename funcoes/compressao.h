#ifndef COMPRESSAO_H
#define COMPRESSAO_H

#define MAX_CHARS 256

// Estrutura para o nó da árvore de Huffman
typedef struct No {
    char caractere;
    int frequencia;
    struct No *esquerda, *direita;
} No;

// Estrutura para a fila de prioridade (min heap)
typedef struct MinHeap {
    int tamanho;
    int capacidade;
    No** array;
} MinHeap;

No* criarNo(char caractere, int frequencia);

MinHeap* criarMinHeap(int capacidade);

void trocarNos(No** a, No** b);

void heapify(MinHeap* minHeap, int idx);

void inserirMinHeap(MinHeap* minHeap, No* no);

No* extrairMinimo(MinHeap* minHeap);

No* construirArvoreHuffman(char caracteres[], int frequencias[], int tamanho);

void imprimirCodigos(No* raiz, int arr[], int topo, char* tabela[MAX_CHARS]);

void codificarHuffman(char caracteres[], int frequencias[], int tamanho, char* tabela[MAX_CHARS]);

#endif
