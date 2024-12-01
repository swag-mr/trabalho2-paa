#ifndef MOCHILA_BOOLEANA_H
#define MOCHILA_BOOLEANA_H

int maxBooleana(int a, int b);

void destruir_matriz(int** matriz, int n, int m);

int** tabela_mochila(int capacidade, int* pesos, int* valores, int n);

void itens_usados(int **tabela, int capacidade, int* pesos, int* valores, int n);

int maior_valor_mochila(int **tabela, int capacidade, int* pesos, int* valores, int n);

#endif
