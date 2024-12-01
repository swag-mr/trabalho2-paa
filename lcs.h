#ifndef LCS_H
#define LCS_H

#define MAX 1000

typedef struct cell{
    int valor;
    char dir; // (-) aponta para esq; (|) aponta para cima; (\) aponta esq+cima
} Cell;

int max(int a, int b);

int tam_lcs(char *s1, char *s2, int m, int n);

int proxy_tam_lcs(char* s1, char* s2);

Cell** tabela_lcs(char* s1, char* s2);

void print_lcs(Cell** tabela, char *s1, int i, int j);

void proxy_print_lcs(char *s1, char *s2);

void print_tabela(Cell** tabela, int m, int n);

#endif
