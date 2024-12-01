#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 4 // Número de tarefas e pessoas

typedef struct {
    int atribuicoes[N]; // Vetor indicando a tarefa atribuída a cada pessoa
    int nivel;          // Nível do nó (número de pessoas atribuídas)
    int custo;          // Custo acumulado
} No;

// Função para criar um novo nó
No *criar_no(int atribuicoes[N], int nivel, int custo) {
    No *novo = (No *)malloc(sizeof(No));
    for (int i = 0; i < N; i++) {
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
int tarefa_atribuida(int atribuicoes[N], int tarefa) {
    for (int i = 0; i < N; i++) {
        if (atribuicoes[i] == tarefa) {
            return 1; // Tarefa já atribuída
        }
    }
    return 0; // Tarefa disponível
}

// Função para calcular o limite inferior
int limite_inferior(int custo_atual, int matriz[N][N], int atribuicoes[N], int nivel) {
    int custo_estimado = custo_atual;
    for (int i = nivel; i < N; i++) {
        int min_custo = INT_MAX;
        for (int j = 0; j < N; j++) {
            if (!tarefa_atribuida(atribuicoes, j) && matriz[i][j] < min_custo) {
                min_custo = matriz[i][j];
            }
        }
        custo_estimado += min_custo;
    }
    return custo_estimado;
}

// Função principal de Branch-and-Bound
No *branch_and_bound(int matriz[N][N]) {
    int atribuicoes[N];
    for (int i = 0; i < N; i++) atribuicoes[i] = -1;

    No *fila[100]; // Fila de nós
    int tamanho_fila = 0;

    inserir_ordenado(fila, &tamanho_fila, criar_no(atribuicoes, 0, 0));

    No *melhor_solucao = NULL;
    int melhor_custo = INT_MAX;

    while (tamanho_fila > 0) {
        No *atual = fila[--tamanho_fila];

        if (atual->nivel == N) {
            if (atual->custo < melhor_custo) {
                melhor_custo = atual->custo;
                if (melhor_solucao) free(melhor_solucao);
                melhor_solucao = atual;
            }
            continue;
        }

        for (int j = 0; j < N; j++) {
            if (!tarefa_atribuida(atual->atribuicoes, j)) {
                int custo_atual = atual->custo + matriz[atual->nivel][j];
                if (custo_atual >= melhor_custo) continue;

                int nova_atribuicao[N];
                for (int k = 0; k < N; k++) nova_atribuicao[k] = atual->atribuicoes[k];
                nova_atribuicao[atual->nivel] = j;

                int estimativa = limite_inferior(custo_atual, matriz, nova_atribuicao, atual->nivel + 1);
                if (estimativa < melhor_custo) {
                    inserir_ordenado(fila, &tamanho_fila, criar_no(nova_atribuicao, atual->nivel + 1, custo_atual));
                }
            }
        }
        free(atual);
    }
    return melhor_solucao;
}

int main() {
    int matriz[N][N] = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };

    No *resultado = branch_and_bound(matriz);
    if (resultado) {
        printf("Solução ótima encontrada com custo: %d\n", resultado->custo);
        printf("Atribuições:\n");
        for (int i = 0; i < N; i++) {
            printf("Pessoa %d -> Tarefa %d\n", i, resultado->atribuicoes[i]);
        }
        free(resultado);
    } else {
        printf("Nenhuma solução encontrada.\n");
    }
    return 0;
}

