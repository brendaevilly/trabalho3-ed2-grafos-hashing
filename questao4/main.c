#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipos.h"

// ========== Função principal ==========
int main() {
    // Planilha e Grafo de Dependências (Lista de Adjacência)
    Celula planilha[LINHAS][COLUNAS];
    ListaDeAdjacencia *grafo[NUM_CELULAS]; // array de ponteiros para as listas de adjacência

    // Inicialização
    inicializaPlanilha(planilha);
    for (int i = 0; i < NUM_CELULAS; i++) {
        grafo[i] = NULL;
    }

    char entrada[100];
    printf("--- Planilha de Cálculo Rudimentar (Lista de Adjacência) ---\n");
    printf("Colunas: A-H, Linhas: 1-20. Total de %d células.\n", NUM_CELULAS);
    printf("Comandos:\n");
    printf("  - Para inserir valor/fórmula: COORDENADA VALOR/FORMULA (ex: A1 10, B2 =A1, C3 @soma(A1..B2))\n");
    printf("  - Para sair: sair\n");
    
    exibePlanilha(planilha);

    while (1) {
        printf("\n> ");
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            break;
        }
        // Remove a quebra de linha
        entrada[strcspn(entrada, "\n")] = 0;

        if (strcasecmp(entrada, "sair") == 0) {
            break;
        }

        processaEntrada(entrada, planilha, grafo);
        exibePlanilha(planilha);
    }

    // Libera a memória do grafo
    limpaGrafo(grafo);

    printf("\nEncerrando o programa.\n");
    return 0;
}
