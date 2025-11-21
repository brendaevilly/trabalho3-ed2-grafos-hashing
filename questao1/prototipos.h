#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

#define DISCOS 4
#define VERTICES 81
#define INFINITO 9999
#define PESO_ARESTA 1

void mostraConfiguracao(int configuracao[]);
void pegaConfiguracaoInicial(int configuracao[]);
void converteIndiceParaConfiguracao(int indice, int configuracao[]);
int converteConfiguracaoParaIndice(int configuracao[]);
int esseMovimentoEhValido(int configuracao1[], int configuracao2[]);
void criaGrafo(int grafo[VERTICES][VERTICES]);
int menorDistancia(int distancia[], int visitado[]);
void dijkstra(int grafo[VERTICES][VERTICES], int origem, int destino);

#endif