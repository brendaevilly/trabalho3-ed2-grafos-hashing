#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

#define COLUNAS 8
#define LINHAS 20
#define NUM_CELULAS (COLUNAS * LINHAS)

struct ListaDeAdjacencia;
struct Celula;

typedef struct ListaDeAdjacencia {
    int indice_destino;
    struct ListaDeAdjacencia *proximo;
} ListaDeAdjacencia;

typedef struct {
    char formula[50];
    double valor;
    int visitado;
} Celula;

void menu();
ListaDeAdjacencia *criaNo(int indice_destino);
void adicionaAresta(ListaDeAdjacencia *grafo[NUM_CELULAS], int origem, int destino);
void removeArestas(ListaDeAdjacencia *grafo[NUM_CELULAS], int origem);
void limpaGrafo(ListaDeAdjacencia *grafo[NUM_CELULAS]);
void inicializaPlanilha(Celula planilha[LINHAS][COLUNAS]);
void inicializarGrafo(ListaDeAdjacencia *grafo[NUM_CELULAS]);
int converteCoordenadaParaIndice(const char *coordenada);
void converteIndiceParaCoordenada(int indice, char *coordenada);
int buscaCiclo(int u, Celula planilha[LINHAS][COLUNAS], ListaDeAdjacencia *grafo[NUM_CELULAS]);
void limpaVisitados(Celula planilha[LINHAS][COLUNAS]);
double calculaReferenciaCelula(const char *formula, Celula planilha[LINHAS][COLUNAS], ListaDeAdjacencia *grafo[NUM_CELULAS]);
double calculaFuncao(const char *formula, int linha, int coluna, Celula planilha[LINHAS][COLUNAS], ListaDeAdjacencia *grafo[NUM_CELULAS]);
double calculaValorCelula(int linha, int coluna, Celula planilha[LINHAS][COLUNAS], ListaDeAdjacencia *grafo[NUM_CELULAS]);
int processaEntrada(const char *entrada, Celula planilha[LINHAS][COLUNAS], ListaDeAdjacencia *grafo[NUM_CELULAS]);
void exibePlanilha(Celula planilha[LINHAS][COLUNAS]);

#endif