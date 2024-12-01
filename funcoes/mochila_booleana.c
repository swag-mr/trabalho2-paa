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

int** tabela_mochila(int capacidade, int* pesos, int* valores, int n){
    int i, w;
    int** tabela = (int**)malloc(sizeof(int*)*(n+1));
    for(i=0; i <= n; i++){
        tabela[i] = (int*)malloc(sizeof(int)*(capacidade+1));
    }

    for(i=0; i <= n; i++){
        for(w=0; w <= capacidade; w++){
            if(i == 0 || w == 0){
                tabela[i][w] = 0;
            }else if(pesos[i-1] <= w){
                tabela[i][w] = max(valores[i-1] + tabela[i-1][w-pesos[i-1]], tabela[i-1][w]);
            }else{
                tabela[i][w] = tabela[i-1][w];
            }
        }
    }

    return tabela;
}

void itens_usados(int **tabela, int capacidade, int* pesos, int* valores, int n){
    int line = n;
    int i = capacidade;

    printf("Itens usados: ");
    while (tabela[line][i] > 0){
        printf("(%d, %d), ", valores[line-1], pesos[line-1]);
        i = i - pesos[line-1];
        line--;
    }
    printf("\n");
}

int maior_valor_mochila(int **tabela, int capacidade, int n){
    int maior = tabela[n][capacidade];
    return maior;
}
