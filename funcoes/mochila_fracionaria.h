#ifndef MOCHILA_FRACIONARIA_H
#define MOCHILA_FRACIONARIA_H

#include "../auxiliares/structs.h"

typedef struct resultado{
    Item* item;
    double qtd;
}Resultado;

int compara(Item* i1, Item* i2);

void swap(Item** a, Item** b);

int partition(Item** arr, int low, int high);

void quickSort(Item** arr, int low, int high);

Resultado** mochila_fracionaria(int capacidade, Item** itens, int n);

void imprimir_resultado_mochila_fracionaria(Resultado** resultado, int n);

#endif
