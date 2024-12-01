#ifndef MOCHILA_BOOLEANA_H
#define MOCHILA_BOOLEANA_H

#include "../auxiliares/structs.h"

void destruir_matriz(int** matriz, int n);

int** tabela_mochila(int capacidade, Item* itens, int n);

void itens_usados(int **tabela, int capacidade, Item* itens, int n);

int maior_valor_mochila(int **tabela, int capacidade, int n);

#endif
