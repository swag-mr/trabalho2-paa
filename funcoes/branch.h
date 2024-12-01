#ifndef BRANCH_H
#define BRANCH_H

typedef struct NoBranch {
    int *atribuicoes; // Vetor indicando a tarefa atribuída a cada pessoa
    int nivel;          // Nível do nó (número de pessoas atribuídas)
    int custo;          // Custo acumulado
} NoBranch;

NoBranch *criar_no(int *atribuicoes, int n, int nivel, int custo);

void inserir_ordenado(NoBranch **fila, int *tamanho, NoBranch *novo);

int tarefa_atribuida(int *atribuicoes, int n, int tarefa);

int limite_inferior(int custo_atual, int **matriz, int n, int *atribuicoes, int nivel);

NoBranch *branch_and_bound(int **matriz, int n);

#endif
