#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lcs.h"
#include "util.h"

int tam_lcs(char *s1, char *s2, int m, int n){
    if(m == 0 || n == 0)
        return 0;
    
    if(s1[m-1] == s2[n-1])
        return 1 + tam_lcs(s1, s2, m - 1, n - 1);
    else
        return max(tam_lcs(s1, s2, m, n - 1), tam_lcs(s1, s2, m - 1, n));
}

int proxy_tam_lcs(char* s1, char* s2){
    int m = strlen(s1);
    int n = strlen(s2);

    return tam_lcs(s1, s2, m, n);
}

Cell** tabela_lcs(char* s1, char* s2){
    int i, j;
    int m = strlen(s1);
    int n = strlen(s2);

    Cell** tabela = (Cell**)malloc(sizeof(Cell*)*(m+1));
    for(i=0; i <= m; i++){
        tabela[i] = (Cell*)malloc(sizeof(Cell)*(n+1));
    }

    for(i = 0; i <= m; i++){
        tabela[i][0].valor = 0;
        tabela[i][0].dir = 0;
    }

    for(j = 0; j <= n; j++){
        tabela[0][j].valor = 0;
        tabela[0][j].dir = 0;
    }

    for(i = 1; i <= m; i++){
        for(j = 1; j <= n; j++){
            if(s1[i-1] == s2[j-1]){
                tabela[i][j].valor = tabela[i - 1][j - 1].valor + 1;
                tabela[i][j].dir = '\\';
            }else if(tabela[i - 1][j].valor >= tabela[i][j - 1].valor){
                tabela[i][j].valor = tabela[i - 1][j].valor;
                tabela[i][j].dir = '|';
            }else{
                tabela[i][j].valor = tabela[i][j - 1].valor;
                tabela[i][j].dir = '-';
            }
        }
    }

   

    return tabela;
}

void print_lcs(Cell** tabela, char *s1, int i, int j){
    if(i == 0 || j == 0)
        return;

    if(tabela[i][j].dir == '\\'){
        print_lcs(tabela, s1, i-1, j-1);
        printf("%c", s1[i-1]);
    }else if(tabela[i][j].dir == '|'){
        print_lcs(tabela, s1, i-1, j);
    }else{
        print_lcs(tabela, s1, i, j-1);
    }
}

void proxy_print_lcs(char *s1, char *s2){
    Cell** tabela = tabela_lcs(s1, s2);

    int m = strlen(s1);
    int n = strlen(s2);

    print_lcs(tabela, s1, m, n);
}

void print_tabela(Cell** tabela, int m, int n){
    int i,j;
    for(i=0; i <= m; i++){
        for(j=0; j <= n; j++){
            printf("(%d,%c) ", tabela[i][j].valor, tabela[i][j].dir);
        }
        printf("\n");
    }
}

/* int main(){ */
/*     char *s1 = (char*)malloc(sizeof(char)*MAX); */
/*     char *s2 = (char*)malloc(sizeof(char)*MAX); */
/*     int res = 0; */

/*
    printf("Digite a primeira sequência de caracteres: ");
    gets(s1);

    printf("Digite a segunda sequência de caracteres: ");
    gets(s2);

    res = proxy_lcs(s1, s2);

    printf("Tamanho da maior subsequência: %d\n", res);
*/
/*     char* s3 = "ABCBDAB"; */
/*     char* s4 = "BDCABA"; */
/*  */
/*     proxy_print_lcs(s3, s4); */
/*     return 0; */
/* } */
