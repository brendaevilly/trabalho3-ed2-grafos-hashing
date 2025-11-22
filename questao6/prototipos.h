#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

#include <time.h>

#define COLUNAS 8 // A a H
#define LINHAS 20 // 1 a 20
#define NUM_CELULAS (COLUNAS * LINHAS)
#define NUM_TESTES 30

// Estruturas Comuns

// Estrutura para representar o conteúdo de uma célula
typedef struct {
    char formula[50]; // Armazena a fórmula ou o valor de entrada
    double valor;     // Valor numérico calculado da célula
    int visitado;     // Para controle de busca (0: não visitado, 1: visitando, 2: visitado)
} Celula;

// Estrutura para o nó da Lista de Adjacência
typedef struct ListaDeAdjacencia {
    int indice_destino; // Índice da célula que a célula atual depende
    struct ListaDeAdjacencia *proximo;
} ListaDeAdjacencia;

// Protótipos Comuns (Conversão, Inicialização)

int converteCoordenadaParaIndice(const char *coordenada);
void inicializaPlanilha(Celula planilha[LINHAS][COLUNAS]);
void limpaVisitados(Celula planilha[LINHAS][COLUNAS]);

// Protótipos para Matriz de Adjacência (Questão 3)


// Operações de Grafo
void inicializaGrafoMatriz(int grafo[NUM_CELULAS][NUM_CELULAS]);
void adicionaArestaMatriz(int grafo[NUM_CELULAS][NUM_CELULAS], int origem, int destino);
void removeArestasMatriz(int grafo[NUM_CELULAS][NUM_CELULAS], int origem);

// Operações de Busca
void bfsMatriz(int grafo[NUM_CELULAS][NUM_CELULAS], int inicio, int *resultado_busca);
void dfsMatriz(int grafo[NUM_CELULAS][NUM_CELULAS], int inicio, int *resultado_busca, int *visitado);

// Operação de Inserção (simplificada para teste de tempo)
int insereMatriz(int grafo[NUM_CELULAS][NUM_CELULAS], int origem, int destino);

// Protótipos para Lista de Adjacência (Questão 4)

// Operações de Grafo
void inicializaGrafoLista(ListaDeAdjacencia *grafo[NUM_CELULAS]);
void adicionaArestaLista(ListaDeAdjacencia *grafo[NUM_CELULAS], int origem, int destino);
void removeArestasLista(ListaDeAdjacencia *grafo[NUM_CELULAS], int origem);
void limpaGrafoLista(ListaDeAdjacencia *grafo[NUM_CELULAS]);

// Operações de Busca
void bfsLista(ListaDeAdjacencia *grafo[NUM_CELULAS], int inicio, int *resultado_busca);
void dfsLista(ListaDeAdjacencia *grafo[NUM_CELULAS], int inicio, int *resultado_busca, int *visitado);

// Operação de Inserção (simplificada para teste de tempo)
int insereLista(ListaDeAdjacencia *grafo[NUM_CELULAS], int origem, int destino);

// Protótipos de Medição de Tempo (Questão 6)

double medeTempoInsercaoMatriz(int grafo[NUM_CELULAS][NUM_CELULAS], int num_arestas);
double medeTempoBuscaMatriz(int grafo[NUM_CELULAS][NUM_CELULAS], void (*funcao_busca)(int[NUM_CELULAS][NUM_CELULAS], int, int*));

double medeTempoInsercaoLista(ListaDeAdjacencia *grafo[NUM_CELULAS], int num_arestas);
double medeTempoBuscaLista(ListaDeAdjacencia *grafo[NUM_CELULAS], void (*funcao_busca)(ListaDeAdjacencia*[NUM_CELULAS], int, int*));

#endif // PROTOTIPOS_H
