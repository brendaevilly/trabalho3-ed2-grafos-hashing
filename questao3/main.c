#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipos.h"

// ========== Função principal ==========
int main() {
    // Planilha e Grafo de Dependências (Matriz de Adjacência)
    Celula planilha[LINHAS][COLUNAS];
    int grafo[NUM_CELULAS][NUM_CELULAS]; // grafo[u][v] = 1 significa que a célula u depende da célula v

    // Inicialização
    inicializaPlanilha(planilha);
    for (int i = 0; i < NUM_CELULAS; i++) {
        for (int j = 0; j < NUM_CELULAS; j++) {
            grafo[i][j] = 0;
        }
    }

    char entrada[100];
    printf("--- Planilha de Cálculo Rudimentar ---\n");
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

        if (processaEntrada(entrada, planilha, grafo)) {
            exibePlanilha(planilha);
        }
    }

    printf("\nEncerrando o programa.\n");
    return 0;
}
