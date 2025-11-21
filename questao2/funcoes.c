#include <stdio.h>
#include <stdlib.h>

#include "prototipos.h"

#define DISCOS 4
#define VERTICES 81
#define INFINITO 9999
#define PESO_ARESTA 1

// ========== Protótipos das funções ==========

void adicionaAresta(int verticeOrigem, int verticeDestino, ListaDeAdjacencia *grafo[VERTICES]){
    ListaDeAdjacencia *novoAdjacente = (ListaDeAdjacencia *)malloc(sizeof(ListaDeAdjacencia));
    novoAdjacente->vertice = verticeDestino;
    novoAdjacente->prox = grafo[verticeOrigem];
    grafo[verticeOrigem] = novoAdjacente;
}

void pegaConfiguracaoInicial(int configuracao[]){
    printf("Digite a configuracao inicial dos 4 discos.\n");
    printf("Tres pinos:\n0 - pino A\n1 - pino B\n2 - pino C\n");

    for(int i=0; i<DISCOS; i++){
        printf("\nDisco %d: ", i+1);
        scanf("%d", &configuracao[i]);

        while(configuracao[i] < 0 || configuracao[i] > 2){
            printf("Invalido, escolha (0, 1 ou 2): ");
            scanf("%d", &configuracao[i]);
        }
    }
}

void mostraConfiguracao(int configuracao[]){
    printf("(");
    for(int i=0; i<DISCOS; i++){
        printf(" %d ", configuracao[i]);
    }
    printf(")\n");       
}

void converteIndiceParaConfiguracao(int indice, int configuracao[]){
    for(int i=DISCOS-1; i>=0; i--){
        configuracao[i] = indice % 3;
        indice /= 3;
    }
}

int converteConfiguracaoParaIndice(int configuracao[]){
    int pesoBase3 = 1, indiceFinal = 0;
    for(int i=DISCOS-1; i>=0; i--){
        indiceFinal += configuracao[i] * pesoBase3;
        pesoBase3 *= 3;
    }
    
    return (indiceFinal);
}

int esseMovimentoEhValido(int configuracao1[], int configuracao2[]){
    int discoMovido = -1, podeMover = -1;

    for(int i=0; i<DISCOS && podeMover; i++){
        if(configuracao1[i] != configuracao2[i]){
            if(discoMovido != -1) podeMover = 0;
            discoMovido = i;
        }
    }

    if(discoMovido != -1 && podeMover){
        int pinoDeOrigem = configuracao1[discoMovido];
        int pinoDeDestino = configuracao2[discoMovido];

        for(int i=0; i<discoMovido && podeMover; i++){
            if(configuracao1[i] == pinoDeOrigem) podeMover = 0;
            if(configuracao2[i] == pinoDeDestino) podeMover = 0;
        }
    }

    return (podeMover);
}

void criaGrafo(ListaDeAdjacencia *grafo[VERTICES]){
    int configuracao1[DISCOS], configuracao2[DISCOS];

    for (int i=0; i<VERTICES; i++){
        converteIndiceParaConfiguracao(i, configuracao1);
        for(int j= i+1; j<VERTICES; j++){
            converteIndiceParaConfiguracao(j, configuracao2);

            if(esseMovimentoEhValido(configuracao1, configuracao2)){
                adicionaAresta(i, j, grafo);
                adicionaAresta(j, i, grafo);
            }
        }
    }
}

int menorDistancia(int distancia[], int visitado[]){
    int menorDistanciaAtual = INFINITO;
    int indiceComMenorDistancia = -1;

    for(int i=0; i<VERTICES; i++){
        if(!visitado[i] && distancia[i] < menorDistanciaAtual){
            menorDistanciaAtual = distancia[i];
            indiceComMenorDistancia = i;
        }
    }

    return (indiceComMenorDistancia);
}

void dijkstra(ListaDeAdjacencia *grafo[VERTICES], int origem, int destino){
    int distancia[VERTICES], visitado[VERTICES], anterior[VERTICES];

    for(int i=0; i<VERTICES; i++){
        distancia[i] = INFINITO;
        visitado[i] = 0;
        anterior[i] = -1;
    }

    distancia[origem] = 0;

    int loop = 1;
    while(loop){
        int proximoVertice = menorDistancia(distancia, visitado);

        if(proximoVertice == -1 || proximoVertice == destino) loop = 0;
        else{
            visitado[proximoVertice] = 1;

            ListaDeAdjacencia *adjacenteAtual = grafo[proximoVertice];
            while(adjacenteAtual != NULL){
                int verticeAdjacente = adjacenteAtual->vertice;

                if(!visitado[verticeAdjacente] && distancia[proximoVertice] + PESO_ARESTA < distancia[verticeAdjacente]){
                    distancia[verticeAdjacente] = distancia[proximoVertice] + PESO_ARESTA;
                    anterior[verticeAdjacente] = proximoVertice;
                }

                adjacenteAtual = adjacenteAtual->prox;
            }
        }
    }

    printf("\nMenor distancia = %d movimentos\n", distancia[destino]);
    printf("Caminho (indices): ");

    int caminho[200], tamanho = 0;
    int atual = destino;
    while (atual != -1) {
        caminho[tamanho++] = atual;
        atual = anterior[atual];
    }

    for (int i = tamanho - 1; i >= 0; i--){
        printf("Indice %d - ", caminho[i]);
        int configuracao[DISCOS];
        converteIndiceParaConfiguracao(caminho[i], configuracao);
        mostraConfiguracao(configuracao);
        printf("\n");
    }

    printf("\n");
}