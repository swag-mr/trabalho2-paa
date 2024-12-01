#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compressao.h"

// Função para criar um novo nó da árvore
No* criarNo(char caractere, int frequencia) {
    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->caractere = caractere;
    novoNo->frequencia = frequencia;
    novoNo->esquerda = novoNo->direita = NULL;
    return novoNo;
}

// Função para criar a fila de prioridade (min heap)
MinHeap* criarMinHeap(int capacidade) {
    MinHeap* minHeap = (MinHeap*) malloc(sizeof(MinHeap));
    minHeap->tamanho = 0;
    minHeap->capacidade = capacidade;
    minHeap->array = (No**) malloc(minHeap->capacidade * sizeof(No*));
    return minHeap;
}

// Função para trocar dois nós
void trocarNos(No** a, No** b) {
    No* temp = *a;
    *a = *b;
    *b = temp;
}

// Função para fazer o heapify (ajustar a heap)
void heapify(MinHeap* minHeap, int idx) {
    int menor = idx;
    int esquerda = 2 * idx + 1;
    int direita = 2 * idx + 2;

    if (esquerda < minHeap->tamanho && minHeap->array[esquerda]->frequencia < minHeap->array[menor]->frequencia)
        menor = esquerda;

    if (direita < minHeap->tamanho && minHeap->array[direita]->frequencia < minHeap->array[menor]->frequencia)
        menor = direita;

    if (menor != idx) {
        trocarNos(&minHeap->array[menor], &minHeap->array[idx]);
        heapify(minHeap, menor);
    }
}

// Função para inserir um nó na heap
void inserirMinHeap(MinHeap* minHeap, No* no) {
    minHeap->array[minHeap->tamanho] = no;
    int i = minHeap->tamanho;
    minHeap->tamanho++;

    while (i && minHeap->array[i]->frequencia < minHeap->array[(i - 1) / 2]->frequencia) {
        trocarNos(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Função para extrair o nó com a menor frequência
No* extrairMinimo(MinHeap* minHeap) {
    No* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->tamanho - 1];
    minHeap->tamanho--;
    heapify(minHeap, 0);
    return temp;
}

// Função para construir a árvore de Huffman
No* construirArvoreHuffman(char caracteres[], int frequencias[], int tamanho) {
    MinHeap* minHeap = criarMinHeap(tamanho);

    for (int i = 0; i < tamanho; i++)
        inserirMinHeap(minHeap, criarNo(caracteres[i], frequencias[i]));

    while (minHeap->tamanho != 1) {
        No* esquerda = extrairMinimo(minHeap);
        No* direita = extrairMinimo(minHeap);

        No* somarNo = criarNo('$', esquerda->frequencia + direita->frequencia);
        somarNo->esquerda = esquerda;
        somarNo->direita = direita;
        inserirMinHeap(minHeap, somarNo);
    }

    return extrairMinimo(minHeap);
}

// Função para imprimir os códigos de Huffman e armazená-los
void imprimirCodigos(No* raiz, int arr[], int topo, char* tabela[MAX_CHARS]) {
    if (raiz->esquerda) {
        arr[topo] = 0;
        imprimirCodigos(raiz->esquerda, arr, topo + 1, tabela);
    }

    if (raiz->direita) {
        arr[topo] = 1;
        imprimirCodigos(raiz->direita, arr, topo + 1, tabela);
    }

    if (!(raiz->esquerda) && !(raiz->direita)) {
        printf("%c: ", raiz->caractere);
        tabela[(unsigned char)raiz->caractere] = (char*)malloc(topo + 1);
        for (int i = 0; i < topo; i++) {
            printf("%d", arr[i]);
            tabela[(unsigned char)raiz->caractere][i] = arr[i] + '0';
        }
        tabela[(unsigned char)raiz->caractere][topo] = '\0';
        printf("\n");
    }
}

// Função principal
void codificarHuffman(char caracteres[], int frequencias[], int tamanho, char* tabela[MAX_CHARS]) {
    No* raiz = construirArvoreHuffman(caracteres, frequencias, tamanho);
    int arr[MAX_CHARS], topo = 0;
    imprimirCodigos(raiz, arr, topo, tabela);
}
