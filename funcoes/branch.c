#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "branch.h"

// Função para criar um novo nó
NoBranch *criar_no(int *atribuicoes, int n, int nivel, int custo) {
    NoBranch *novo = (NoBranch *)malloc(sizeof(NoBranch));
    novo->atribuicoes = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        novo->atribuicoes[i] = atribuicoes[i];
    }
    novo->nivel = nivel;
    novo->custo = custo;
    return novo;
}

// Função para inserir um nó na fila ordenada por custo
void inserir_ordenado(NoBranch **fila, int *tamanho, NoBranch *novo) {
    fila[*tamanho] = novo;
    (*tamanho)++;
    for (int i = *tamanho - 1; i > 0 && fila[i]->custo < fila[i - 1]->custo; i--) {
        NoBranch *temp = fila[i];
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
NoBranch *branch_and_bound(int **matriz, int n) {
    int atribuicoes[n];
    for (int i = 0; i < n; i++) atribuicoes[i] = -1;

    NoBranch *fila[100]; // Fila de nós
    int tamanho_fila = 0;

    inserir_ordenado(fila, &tamanho_fila, criar_no(atribuicoes, n, 0, 0));

    NoBranch *melhor_solucao = NULL;
    int melhor_custo = INT_MAX;

    while (tamanho_fila > 0) {
        NoBranch *atual = fila[--tamanho_fila];

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
