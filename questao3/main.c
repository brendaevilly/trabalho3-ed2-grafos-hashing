#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipos.h"

int main() {
    Celula planilha[LINHAS][COLUNAS];
    int grafo[NUM_CELULAS][NUM_CELULAS];

    inicializaPlanilha(planilha);
    inicializarGrafo(grafo);

    char entrada[100];
    menu();
    exibePlanilha(planilha);

    int loop = 1;
    while (loop) {
        printf("\n> ");
        if(fgets(entrada, sizeof(entrada), stdin) != NULL) {
            entrada[strcspn(entrada, "\n")] = 0;

            if(strcasecmp(entrada, "sair") != 0) {
                if (processaEntrada(entrada, planilha, grafo))
                    exibePlanilha(planilha);
            }else loop = 0;
        }else loop = 0;
    }

    printf("\nEncerrando o programa.\n");
    return 0;
}