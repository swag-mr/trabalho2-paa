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
                do{
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
                            printf("\n");

                            NoBranch *resultado = branch_and_bound(matriz, 4);
                            if (resultado) {
                                printf("Solução ótima encontrada com custo: %d\n", resultado->custo);
                                printf("\nAtribuições:\n");
                                for (int i = 0; i < 4; i++) {
                                    printf("Pessoa %d -> Tarefa %d\n", i+1, resultado->atribuicoes[i]+1);
                                }

                                printf("\nSolução em forma de vetor: [ ");
                                for(int i = 0; i < 4; i++){
                                    if(i != 3){
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
                            int n;
                            printf("Digite o tamanho N da matriz (NxN): ");
                            scanf("%d", &n);

                            for(int i=0; i < n; i++){
                                for(int j=0; j < n; j++){
                                    printf("Digite o valor %dx%d da matriz: ", i, j);
                                    scanf("%d", &matriz[i][j]);
                                }
                            }

                            NoBranch *resultado = branch_and_bound(matriz, n);
                            if (resultado) {
                                printf("Solução ótima encontrada com custo: %d\n", resultado->custo);
                                printf("\nAtribuições:\n");
                                for (int i = 0; i < n; i++) {
                                    printf("Pessoa %d -> Tarefa %d\n", i+1, resultado->atribuicoes[i]+1);
                                }

                                printf("\nSolução em forma de vetor: [ ");
                                for(int i = 0; i < n; i++){
                                    if(i != n - 1){
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
                        case 0: {
                            // Voltar
                            printf("\nVoltando...\n");
                            break;
                        }
                        default: {
                            printf("\nSelecione uma opção válida\n");
                            break;
                        }
                    }
                    printf("\nPressione Enter para continuar...");
                    getchar();
                    getchar();
                    system("clear");
                }while(opc != 0);
                break;
            }
            case 2: {
            }
            case 3: {
            }
            case 4: {
            }
            case 5: {
            }
            case 0: {
                // Sair
                printf("\nSaindo...\n");
                return 0;
            }
        }
    }

    return 0;
}
