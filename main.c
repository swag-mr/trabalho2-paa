#include <stdio.h>
#include <stdlib.h>
#include "funcoes/branch.h"
#include "funcoes/compressao.h"
#include "funcoes/lcs.h"
#include "funcoes/mochila_booleana.h"
#include "funcoes/mochila_fracionaria.h"
#include "auxiliares/auxiliares.h"

int main(){
    int opc;
    while(1){
        menuPrincipal();
        scanf("%d", &opc);

        switch(opc){
            case 1: {
                // Assignment Problem
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

                menuAssignmentProblem();
                scanf("%d", &opc);
                switch(opc){
                    case 1: {
                        // Teste com valores pré-feitos
                        printf("\nValores da matriz pré-feita:\n\n");
                        for(int i = 0; i < 4; i++) {
                            for(int j = 0; j < 4; j++) {
                                matriz[i][j] = valores[i][j];
                                printf("%d ", valores[i][j]);
                            }
                            printf("\n");
                        }   

                        NoBranch *resultado = branch_and_bound(matriz, 4);
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

                        break;
                    }
                    case 2: {
                        // Ler matriz
                        break;
                    }
                    case 0: {
                        // Sair
                        break;
                    }
                }
            }
        }
    }

    return 0;
}
