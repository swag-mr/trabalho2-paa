#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes/branch.h"
#include "funcoes/compressao.h"
#include "funcoes/lcs.h"
#include "funcoes/mochila_booleana.h"
#include "funcoes/mochila_fracionaria.h"
#include "auxiliares/auxiliares.h"

int main(int argc, char* argv[]){
    if(argc > 1){
        if(strcmp(argv[1], "teste_assignment") == 0){
            //teste assignment problem

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

            printf("\nValores da matriz pré-programada:\n\n");
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

            return 0;
        }
        if(strcmp(argv[1], "teste_huffman") == 0){
            //teste codificação de huffman

            printf("\nString pré-programada: controle remoto\n");

            char texto[MAX_CHARS];
            int frequencias[MAX_CHARS] = {0};

            strcpy(texto, "controle remoto");

            int n = strlen(texto) - 1;
            for (int i = 0; i < n; i++)
                frequencias[(unsigned char)texto[i]]++;

            char caracteres[MAX_CHARS];
            int freq[MAX_CHARS], index = 0;

            for (int i = 0; i < MAX_CHARS; i++) {
                if (frequencias[i] > 0) {
                    caracteres[index] = (char)i;
                    freq[index] = frequencias[i];
                    index++;
                }
            }
            printf("\nCódigos de Huffman:\n");
            char* tabela[MAX_CHARS] = {0};
            codificarHuffman(caracteres, freq, index, tabela);

            printf("\nTexto codificado: ");
            for (int i = 0; i < n; i++) {
                printf("%s", tabela[(unsigned char)texto[i]]);
            }
            printf("\n");

            printf("\nTamanho da string não comprimida (em bits): %d\n", 8 * n);

            int tamanho_codificado = 0;
            for (int i = 0; i < n; i++) {
                tamanho_codificado += strlen(tabela[(unsigned char)texto[i]]);
            }
            printf("\nTamanho da string comprimida (em bits): %d\n", tamanho_codificado);

            double taxa_compressao = ((double)tamanho_codificado / (8.0 * n)) * 100.0;
            double taxa_reducao = 100.0 - taxa_compressao;
            printf("\nTaxa de redução (em %%): %.2f\n", taxa_reducao);

            return 0;
        }
        if(strcmp(argv[1], "teste_fractional_knapsack") == 0){
            //teste fractional knapsack problem

            return 0;
        }
        if(strcmp(argv[1], "teste_knapsack") == 0){
            //teste knapsack problem
            int weight[] = { 6, 5, 8, 2, 3, 1 };
            int profit[] = { 11, 9, 18, 6, 7, 3};
            int W = 15;
            int n = sizeof(profit) / sizeof(profit[0]);
            
            printf("\nCapacidade da mochila: %d\n", W);
            printf("Quantidade de itens: %d\n", n);
            printf("Peso dos itens: ");
            for(int i=0; i < n; i ++){
                printf("%d ", weight[i]);
            }
            printf("\n");
            printf("Valores dos itens: ");
            for(int i=0; i < n; i ++){
                printf("%d ", profit[i]);
            }
            printf("\n\n");

            int** tabela = tabela_mochila(W, weight, profit, n);

            itens_usados(tabela, W, weight, profit, n);
            printf("Maior valor: %d\n", maior_valor_mochila(tabela, W, n));

            return 0;
        }
        if(strcmp(argv[1], "teste_lcs") == 0){
            //teste longest common subsequence

            return 0;
        }
    }

    int opc;
    while(1){
        menuPrincipal();
        scanf("%d", &opc);

        switch(opc){
            case 1: {
                // Assignment Problem

                // Ler matriz
                int n;
                printf("Digite o tamanho N da matriz (NxN): ");
                scanf("%d", &n);

                int **matriz = (int**) malloc(n * sizeof(int*));
                for(int i=0; i < n; i++){
                    matriz[i] = (int*) malloc(n * sizeof(int));
                }

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

                printf("\nPressione Enter para continuar...");
                getchar();
                getchar();
                system("clear");
                break;
            }
            case 2: {
                // Codificação de Huffman
                getchar();
                // Ler String
                char texto[MAX_CHARS];
                int frequencias[MAX_CHARS] = {0};

                printf("Digite um texto: ");
                fgets(texto, MAX_CHARS, stdin);

                int n = strlen(texto) - 1;
                for (int i = 0; i < n; i++)
                    frequencias[(unsigned char)texto[i]]++;

                char caracteres[MAX_CHARS];
                int freq[MAX_CHARS], index = 0;

                for (int i = 0; i < MAX_CHARS; i++) {
                    if (frequencias[i] > 0) {
                        caracteres[index] = (char)i;
                        freq[index] = frequencias[i];
                        index++;
                    }
                }
                printf("\nCódigos de Huffman:\n");
                char* tabela[MAX_CHARS] = {0};
                codificarHuffman(caracteres, freq, index, tabela);

                printf("\nTexto codificado: ");
                for (int i = 0; i < n; i++) {
                    printf("%s", tabela[(unsigned char)texto[i]]);
                }
                printf("\n");

                printf("\nTamanho da string não comprimida (em bits): %d\n", 8 * n);

                int tamanho_codificado = 0;
                for (int i = 0; i < n; i++) {
                    tamanho_codificado += strlen(tabela[(unsigned char)texto[i]]);
                }
                printf("\nTamanho da string comprimida (em bits): %d\n", tamanho_codificado);

                double taxa_compressao = ((double)tamanho_codificado / (8.0 * n)) * 100.0;
                double taxa_reducao = 100.0 - taxa_compressao;
                printf("\nTaxa de redução (em %%): %.2f\n", taxa_reducao);

                printf("\nPressione Enter para continuar...");
                getchar();
                system("clear");
                break;
            }
            case 3: {
                // Fractional Knapsack Problem
                break;
            }
            case 4: {
                // Knapsack Problem
                int n, W;

                printf("Digite o número de itens: ");
                scanf("%d", &n);

                int* weight = (int*)malloc(n * sizeof(int));
                int* profit = (int*)malloc(n * sizeof(int));

                printf("Digite os pesos dos itens:\n");
                for(int i = 0; i < n; i++){
                    printf("Peso do item %d: ", i + 1);
                    scanf("%d", &weight[i]);
                }

                printf("Digite os valores dos itens:\n");
                for(int i = 0; i < n; i++){
                    printf("Valor do item %d: ", i + 1);
                    scanf("%d", &profit[i]);
                }

                printf("Digite a capacidade da mochila: ");
                scanf("%d", &W);
                printf("\n");

                int** tabela = tabela_mochila(W, weight, profit, n);

                itens_usados(tabela, W, weight, profit, n);
                printf("Maior valor: %d\n", maior_valor_mochila(tabela, W, n));

                destruir_matriz(tabela, n+1);
                free(weight);
                free(profit);
                break;
            }
            case 5: {
                // Longest Common Subsequence
                break;
            }
            case 0: {
                // Sair
                printf("\nSaindo...\n");
                return 0;
            }
            default: {
                printf("\nSelecione uma opção válida\n");
                break;
            }
        }
    };

    return 0;
}
