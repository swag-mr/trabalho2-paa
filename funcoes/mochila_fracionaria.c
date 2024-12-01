#include <stdio.h>
#include <stdlib.h>
#include "mochila_fracionaria.h"

int compara(Item* i1, Item* i2){
    double razao1 = (double)i1->valor / (double)i1->peso;
    double razao2 = (double)i2->valor / (double)i2->peso;

    if(razao1 > razao2)
        return 1;
    
    return 0;
}

void swap(Item** a, Item** b) {
    Item* temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Item** arr, int low, int high) {
    Item* p = arr[low];
    Item* temp = NULL;
    int i = low;
    int j = high;

    while (i < j) {

        while (compara(arr[i],p) && i <= high - 1) {
            i++;
        }

        while (!compara(arr[j], p) && j >= low + 1) {
            j--;
        }
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void quickSort(Item** arr, int low, int high) {
    if (low < high) {    
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

Resultado** mochila_fracionaria(int capacidade, Item** itens, int n){
    quickSort(itens, 0, n-1);

    Resultado** resultado = (Resultado**)malloc(sizeof(Resultado*)*n);
    for(int i=0; i < n; i++){
        resultado[i] = (Resultado*)malloc(sizeof(Resultado));
        resultado[i]->item = itens[i];
        resultado[i]->qtd = 0;
    }

    double valor_final = 0.0;

    for(int i=0; i < n; i++){
        if(itens[i]->peso <= capacidade){
            capacidade -= itens[i]->peso;
            valor_final += itens[i]->valor;

            resultado[i]->qtd += 1;
        }else{
            double qtd = (double)capacidade / (double)itens[i]->peso;
            valor_final += itens[i]->valor * qtd;
            
            resultado[i]->qtd += qtd;
            break;
        }
    }

    return resultado;
}

void imprimir_resultado_mochila_fracionaria(Resultado** resultado, int n){
    Item* item = NULL;

    double valor_final = 0.0;
    double qtd = 0.0;

    for(int i=0; i < n; i++){
        item = resultado[i]->item;
        qtd = resultado[i]->qtd;
        valor_final += qtd*item->valor;
        printf("{%d - %d}: %.2f\n", item->valor, item->peso, qtd);
    }
    printf("\nValor final: %.2f\n", valor_final);
}

/* int main(){ */
/*     int W = 50; */
/*     int N = 3; */
/*      */
/*     Item** arr = (Item**)malloc(sizeof(Item*)*N); */
/*     for(int i=0; i < N; i++){ */
/*         arr[i] = (Item*)malloc(sizeof(Item)); */
/*     } */
/*  */
/*     arr[0]->valor = 60; */
/*     arr[0]->peso = 10;  */
/*  */
/*     arr[1]->valor = 100; */
/*     arr[1]->peso = 20;  */
/*  */
/*     arr[2]->valor = 120; */
/*     arr[2]->peso = 30;  */
/*  */
/*     Resultado** resultado = mochila_fracionaria(W, arr, N); */
/*     imprimir_resultado_mochila_fracionaria(resultado, N); */
/*     return 0; */
/* } */
