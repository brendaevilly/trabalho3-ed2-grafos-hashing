#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

#define COLUNAS 8
#define LINHAS 20 
#define NUM_CELULAS (COLUNAS * LINHAS)

struct Celula;
typedef struct {
    char formula[50];
    double valor;   
    int visitado;    
} Celula;

void menu();
void inicializaPlanilha(Celula planilha[LINHAS][COLUNAS]);
void inicializarGrafo(int grafo[NUM_CELULAS][NUM_CELULAS]);
int converteCoordenadaParaIndice(const char *coordenada);
void converteIndiceParaCoordenada(int indice, char *coordenada);
int buscaCiclo(int indice, Celula planilha[LINHAS][COLUNAS], int grafo[NUM_CELULAS][NUM_CELULAS]);
void limpaVisitados(Celula planilha[LINHAS][COLUNAS]);
int analisarIntervalo(const char *intervaloString, int *indiceInicio, int *indiceFim);
double calculaCelulaReferencia(const char *formula, Celula planilha[LINHAS][COLUNAS], int grafo[NUM_CELULAS][NUM_CELULAS]);
double calculaFuncaoCelula(const char *formula, int linha, int coluna, Celula planilha[LINHAS][COLUNAS], int grafo[NUM_CELULAS][NUM_CELULAS]);
double calculaValorCelula(int linha, int coluna, Celula planilha[LINHAS][COLUNAS], int grafo[NUM_CELULAS][NUM_CELULAS]);
void atualizaPlanilha(Celula planilha[LINHAS][COLUNAS], int grafo[NUM_CELULAS][NUM_CELULAS]);
int processaEntrada(const char *entrada, Celula planilha[LINHAS][COLUNAS], int grafo[NUM_CELULAS][NUM_CELULAS]);
void exibePlanilha(Celula planilha[LINHAS][COLUNAS]);

#endif