#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main() {
    char texto[MAX_CHARS];
    int frequencias[MAX_CHARS] = {0};

    printf("Digite um texto: ");
    fgets(texto, MAX_CHARS, stdin);

    int n = strlen(texto) - 1;
    for (int i = 0; i < n; i++)
        frequencias[(unsigned char)texto[i]]++;

    char caracteres[MAX_CHARS];
    int freq[MAX_CHARS], index = 0;

    for (int i = 0; i < MAX_CHARS; i++) {
        if (frequencias[i] > 0) {
            caracteres[index] = (char)i;
            freq[index] = frequencias[i];
            index++;
        }
    }
    printf("\nCódigos de Huffman:\n");
    char* tabela[MAX_CHARS] = {0};
    codificarHuffman(caracteres, freq, index, tabela);

    printf("\nTexto codificado: ");
    for (int i = 0; i < n; i++) {
        printf("%s", tabela[(unsigned char)texto[i]]);
    }
    printf("\n");

    printf("\nTamanho da string não comprimida (em bits): %d\n", 8 * n);

    int tamanho_codificado = 0;
    for (int i = 0; i < n; i++) {
        tamanho_codificado += strlen(tabela[(unsigned char)texto[i]]);
    }
    printf("\nTamanho da string comprimida (em bits): %d\n", tamanho_codificado);

    double taxa_compressao = ((double)tamanho_codificado / (8.0 * n)) * 100.0;
    double taxa_reducao = 100.0 - taxa_compressao;
    printf("\nTaxa de redução (em %%): %.2f\n", taxa_reducao);

    return 0;
}

