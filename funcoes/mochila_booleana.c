#include <stdio.h>
#include <stdlib.h>
#include "mochila_booleana.h"
#include "../auxiliares/util.h"

void destruir_matriz(int** matriz, int n){
    for(int i=0; i < n; i++){
        free(matriz[i]);
    }
    free(matriz);
}

int** tabela_mochila(int capacidade, Item* itens, int n){
    int i, w;
    int** tabela = (int**)malloc(sizeof(int*)*(n+1));
    for(i=0; i <= n; i++){
        tabela[i] = (int*)malloc(sizeof(int)*(capacidade+1));
    }

    for(i=0; i <= n; i++){
        for(w=0; w <= capacidade; w++){
            if(i == 0 || w == 0){
                tabela[i][w] = 0;
            }else if(itens[i-1].peso <= w){
                tabela[i][w] = max(itens[i-1].valor + tabela[i-1][w-itens[i-1].peso], tabela[i-1][w]);
            }else{
                tabela[i][w] = tabela[i-1][w];
            }
        }
    }

    return tabela;
}

void itens_usados(int **tabela, int capacidade, Item *itens, int n){
    int line = n;
    int i = capacidade;

    printf("(valor, peso)\n\n");
    printf("Itens usados:\n");
    while (tabela[line][i] > 0){
        printf("(%d, %d), ", itens[line-1].valor, itens[line-1].peso);
        i = i - itens[line-1].peso;
        line--;
    }
    printf("\n");
}

int maior_valor_mochila(int **tabela, int capacidade, int n){
    int maior = tabela[n][capacidade];
    return maior;
}

/*
int main(){
    Item itens[] = { {11, 6}, {9, 5}, {18, 8}, {6, 2}, {7, 3}, {3, 1}};
    int W = 15; 
    int n = sizeof(itens) / sizeof(itens[0]);

    int** tabela = tabela_mochila(W, itens, n);

    itens_usados(tabela, W, itens, n);
    printf("Maior valor: %d\n", maior_valor_mochila(tabela, W, n));
    return 0;
}
*/
