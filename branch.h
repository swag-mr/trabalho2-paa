#ifndef BRANCH_H
#define BRANCH_H

typedef struct {
    int *atribuicoes; // Vetor indicando a tarefa atribuída a cada pessoa
    int nivel;          // Nível do nó (número de pessoas atribuídas)
    int custo;          // Custo acumulado
} No;

No *criar_no(int *atribuicoes, int n, int nivel, int custo);

void inserir_ordenado(No **fila, int *tamanho, No *novo);

int tarefa_atribuida(int *atribuicoes, int n, int tarefa);

int limite_inferior(int custo_atual, int **matriz, int n, int *atribuicoes, int nivel);

No *branch_and_bound(int **matriz, int n);

#endif
