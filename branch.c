#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "branch.h"

// Função para criar um novo nó
No *criar_no(int *atribuicoes, int n, int nivel, int custo) {
    No *novo = (No *)malloc(sizeof(No));
    novo->atribuicoes = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        novo->atribuicoes[i] = atribuicoes[i];
    }
    novo->nivel = nivel;
    novo->custo = custo;
    return novo;
}

// Função para inserir um nó na fila ordenada por custo
void inserir_ordenado(No **fila, int *tamanho, No *novo) {
    fila[*tamanho] = novo;
    (*tamanho)++;
    for (int i = *tamanho - 1; i > 0 && fila[i]->custo < fila[i - 1]->custo; i--) {
        No *temp = fila[i];
        fila[i] = fila[i - 1];
        fila[i - 1] = temp;
    }
}

// Função para verificar se uma tarefa já foi atribuída
int tarefa_atribuida(int *atribuicoes, int n, int tarefa) {
    for (int i = 0; i < n; i++) {
        if (atribuicoes[i] == tarefa) {
            return 1; // Tarefa já atribuída
        }
    }
    return 0; // Tarefa disponível
}

// Função para calcular o limite inferior
int limite_inferior(int custo_atual, int **matriz, int n, int *atribuicoes, int nivel) {
    int custo_estimado = custo_atual;
    for (int i = nivel; i < n; i++) {
        int min_custo = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (!tarefa_atribuida(atribuicoes, n, j) && matriz[i][j] < min_custo) {
                min_custo = matriz[i][j];
            }
        }
        custo_estimado += min_custo;
    }
    return custo_estimado;
}

// Função principal de Branch-and-Bound
No *branch_and_bound(int **matriz, int n) {
    int atribuicoes[n];
    for (int i = 0; i < n; i++) atribuicoes[i] = -1;

    No *fila[100]; // Fila de nós
    int tamanho_fila = 0;

    inserir_ordenado(fila, &tamanho_fila, criar_no(atribuicoes, n, 0, 0));

    No *melhor_solucao = NULL;
    int melhor_custo = INT_MAX;

    while (tamanho_fila > 0) {
        No *atual = fila[--tamanho_fila];

        if (atual->nivel == n) {
            if (atual->custo < melhor_custo) {
                melhor_custo = atual->custo;
                if (melhor_solucao) free(melhor_solucao);
                melhor_solucao = atual;
            }
            continue;
        }

        for (int j = 0; j < n; j++) {
            if (!tarefa_atribuida(atual->atribuicoes, n, j)) {
                int custo_atual = atual->custo + matriz[atual->nivel][j];
                if (custo_atual >= melhor_custo) continue;

                int nova_atribuicao[n];
                for (int k = 0; k < n; k++) nova_atribuicao[k] = atual->atribuicoes[k];
                nova_atribuicao[atual->nivel] = j;

                int estimativa = limite_inferior(custo_atual, matriz, n, nova_atribuicao, atual->nivel + 1);
                if (estimativa < melhor_custo) {
                    inserir_ordenado(fila, &tamanho_fila, criar_no(nova_atribuicao, n, atual->nivel + 1, custo_atual));
                }
            }
        }
        free(atual);
    }
    return melhor_solucao;
}

int main() {
    int **matriz = (int**) malloc(4 * sizeof(int*));
    for(int i=0; i < 4; i++){
        matriz[i] = (int*) malloc(4 * sizeof(int));
    }

    int valores[4][4] = {
        {5, 5, 6, 9},
        {3, 1, 4, 4},
        {3, 5, 13, 3},
        {3, 9, 14, 10}
    };

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            matriz[i][j] = valores[i][j];
        }
    }   

    No *resultado = branch_and_bound(matriz, 4);
    if (resultado) {
        printf("Solução ótima encontrada com custo: %d\n", resultado->custo);
        printf("\nAtribuições:\n");
        for (int i = 0; i < 4; i++) {
            printf("Pessoa %d -> Tarefa %d\n", i+1, resultado->atribuicoes[i]+1);
        }

        printf("\nSolução em forma de vetor: [ ");
        for(int i = 0; i < 4; i++){
            if(i != 3){ // 3 = n - 1
                printf("%d, ", resultado->atribuicoes[i]);
            }else{
                printf("%d ", resultado->atribuicoes[i]);
            }
        }
        printf("]\n");

        free(resultado);
    } else {
        printf("Nenhuma solução encontrada.\n");
    }
    return 0;
}

