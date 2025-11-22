#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipos.h"

int main() {
    Celula planilha[LINHAS][COLUNAS];
    ListaDeAdjacencia *grafo[NUM_CELULAS];

    inicializaPlanilha(planilha);
    inicializarGrafo(grafo);
    char entrada[100];
    menu();
    exibePlanilha(planilha);

    int loop = 1;
    while (loop) {
        printf("\n> ");
        if(fgets(entrada, sizeof(entrada), stdin) != NULL){
            entrada[strcspn(entrada, "\n")] = 0;
            if (strcasecmp(entrada, "sair") != 0) {
                int verifica = processaEntrada(entrada, planilha, grafo);
                if(verifica == 0) printf("Entrada invalida. Tente novamente.\n");
                else exibePlanilha(planilha);
            }else loop = 0;
        }else loop = 0;
    }
    limpaGrafo(grafo);

    printf("\nEncerrando o programa.\n");
    return 0;
}