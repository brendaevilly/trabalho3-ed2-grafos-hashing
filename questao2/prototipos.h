#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

#define DISCOS 4
#define VERTICES 81
#define INFINITO 9999
#define PESO_ARESTA 1

struct listaDeAdjacencia;
typedef struct listaDeAdjacencia{
    int vertice;
    struct listaDeAdjacencia *prox;
} ListaDeAdjacencia;

void adicionaAresta(int verticeOrigem, int verticeDestino, ListaDeAdjacencia *grafo[VERTICES]);
void pegaConfiguracaoInicial(int configuracao[]);
void mostraConfiguracao(int configuracao[]);
void converteIndiceParaConfiguracao(int indice, int configuracao[]);
int converteConfiguracaoParaIndice(int configuracao[]);
int esseMovimentoEhValido(int configuracao1[], int configuracao2[]);
void criaGrafo(ListaDeAdjacencia *grafo[VERTICES]);
int menorDistancia(int distancia[], int visitado[]);
void dijkstra(ListaDeAdjacencia *grafo[VERTICES], int origem, int destino);

#endif