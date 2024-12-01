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

            int W = 50;
            int N = 3;

            Item** arr = (Item**)malloc(sizeof(Item*) * N);
            for (int i = 0; i < N; i++) {
                arr[i] = (Item*)malloc(sizeof(Item));
            }

            arr[0]->valor = 60;
            arr[0]->peso = 10; 
            arr[1]->valor = 100;
            arr[1]->peso = 20; 
            arr[2]->valor = 120;
            arr[2]->peso = 30; 

            printf("\nCapacidade da mochila: %d\n", W);
            printf("Quantidade de itens: %d\n", N);
            for(int i=0; i < N; i++){
                printf("Valor do item %d: %d\n", i+1, arr[i]->valor);
                printf("Peso do item %d: %d\n", i+1, arr[i]->peso);
            }
            printf("\n");

            Resultado** resultado = mochila_fracionaria(W, arr, N);
            imprimir_resultado_mochila_fracionaria(resultado, N);

            return 0;
        }
        if(strcmp(argv[1], "teste_knapsack") == 0){
            //teste knapsack problem

            Item itens[] = { {11, 6}, {9, 5}, {18, 8}, {6, 2}, {7, 3}, {3, 1} };
            int W = 15;
            int n = sizeof(itens) / sizeof(itens[0]);
            
            printf("\nCapacidade da mochila: %d\n", W);
            printf("Quantidade de itens: %d\n", n);
            for(int i=0; i < n; i++){
                printf("Valor do item %d: %d\n", i+1, itens[i].valor);
                printf("Peso do item %d: %d\n", i+1, itens[i].peso);
            }
            printf("\n");

            int** tabela = tabela_mochila(W, itens, n);

            itens_usados(tabela, W, itens, n);
            printf("Maior valor: %d\n", maior_valor_mochila(tabela, W, n));

            return 0;
        }
        if(strcmp(argv[1], "teste_lcs") == 0){
            //teste longest common subsequence

            char* s3 = "ABCBDAB";
            char* s4 = "BDCABA";

            printf("Strings: '%s' e '%s'\n", s3, s4);
            printf("Maior subsequência comum: ");
            proxy_print_lcs(s3, s4);
            printf("\n");

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
                printf("\nDigite o tamanho N da matriz (NxN): ");
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

                printf("\nDigite um texto: ");
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

                int capacidade, n;

                printf("Digite a capacidade da mochila: ");
                scanf("%d", &capacidade);

                printf("Digite o número de itens: ");
                scanf("%d", &n);

                Item** itens = (Item**)malloc(sizeof(Item*) * n);
                for (int i = 0; i < n; i++) {
                    itens[i] = (Item*)malloc(sizeof(Item));
                    printf("Digite o valor do item %d: ", i + 1);
                    scanf("%d", &itens[i]->valor);
                    printf("Digite o peso do item %d: ", i + 1);
                    scanf("%d", &itens[i]->peso);
                }
                printf("\n");

                Resultado** resultado = mochila_fracionaria(capacidade, itens, n);
                imprimir_resultado_mochila_fracionaria(resultado, n);
                break;
            }
            case 4: {
                // Knapsack Problem

                int capacidade, n;

                printf("Digite a capacidade da mochila: ");
                scanf("%d", &capacidade);

                printf("Digite o número de itens: ");
                scanf("%d", &n);

                Item* itens = (Item*)malloc(sizeof(Item) * n);
                for (int i = 0; i < n; i++) {
                    printf("Digite o valor do item %d: ", i + 1);
                    scanf("%d", &itens[i].valor);
                    printf("Digite o peso do item %d: ", i + 1);
                    scanf("%d", &itens[i].peso);
                }
                printf("\n");

                int** tabela = tabela_mochila(capacidade, itens, n);

                itens_usados(tabela, capacidade, itens, n);
                printf("Maior valor: %d\n", maior_valor_mochila(tabela, capacidade, n));

                destruir_matriz(tabela, n + 1);
                free(itens);
                break;
            }
            case 5: {
                // Longest Common Subsequence

                getchar();
                char s1[MAX];
                char s2[MAX];

                printf("\nDigite a primeira sequência de caracteres: ");
                fgets(s1, MAX, stdin);
                s1[strcspn(s1, "\n")] = '\0'; // Remove o \n do final

                printf("Digite a segunda sequência de caracteres: ");
                fgets(s2, MAX, stdin);
                s2[strcspn(s2, "\n")] = '\0';

                printf("\nMaior subsequência comum: ");
                proxy_print_lcs(s1, s2);
                printf("\n");
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
