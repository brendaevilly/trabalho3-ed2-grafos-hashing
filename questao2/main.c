#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "prototipos.h"

#define DISCOS 4
#define VERTICES 81

int main(){
    ListaDeAdjacencia *grafo[VERTICES];

    for (int i = 0; i < VERTICES; i++) grafo[i] = NULL;

    criaGrafo(grafo);
    int configuracaoInicial[DISCOS];
    pegaConfiguracaoInicial(configuracaoInicial);

    printf("Configuracao inicial escolhida:\n");
    mostraConfiguracao(configuracaoInicial);

    int indiceOrigem = converteConfiguracaoParaIndice(configuracaoInicial);

    int configuracaoFinal[DISCOS] = {2, 2, 2, 2};
    printf("Configuracao final desejada:\n");
    mostraConfiguracao(configuracaoFinal);

    int indiceDestino = converteConfiguracaoParaIndice(configuracaoFinal);

    clock_t inicio = clock();
    dijkstra(grafo, indiceOrigem, indiceDestino);
    clock_t fim = clock();

    double tempoGastoEmSegundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo gasto: %.6f segundos\n", tempoGastoEmSegundos);

    return 0;
}