#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

#define COLUNAS 8 // A a H
#define LINHAS 20 // 1 a 20
#define NUM_CELULAS (COLUNAS * LINHAS)

// Estrutura para o nó da Lista de Adjacência
typedef struct ListaDeAdjacencia {
    int indice_destino; // Índice da célula que a célula atual depende
    struct ListaDeAdjacencia *proximo;
} ListaDeAdjacencia;

// Estrutura para representar o conteúdo de uma célula
typedef struct {
    char formula[50]; // Armazena a fórmula ou o valor de entrada (ex: "10", "=B1", "@soma(A1..B2)")
    double valor;     // Valor numérico calculado da célula
    int visitado;     // Para controle de ciclo e busca (0: não visitado, 1: visitando, 2: visitado)
} Celula;

// Protótipos das funções
void inicializaPlanilha(Celula planilha[LINHAS][COLUNAS]);
int converteCoordenadaParaIndice(const char *coordenada);
void converteIndiceParaCoordenada(int indice, char *coordenada);
int processaEntrada(const char *entrada, Celula planilha[LINHAS][COLUNAS], ListaDeAdjacencia *grafo[NUM_CELULAS]);
void atualizaPlanilha(Celula planilha[LINHAS][COLUNAS], ListaDeAdjacencia *grafo[NUM_CELULAS]);
double calculaValorCelula(int linha, int coluna, Celula planilha[LINHAS][COLUNAS], ListaDeAdjacencia *grafo[NUM_CELULAS]);
void exibePlanilha(Celula planilha[LINHAS][COLUNAS]);
int buscaCiclo(int u, Celula planilha[LINHAS][COLUNAS], ListaDeAdjacencia *grafo[NUM_CELULAS]);

// Funções de manipulação da Lista de Adjacência
ListaDeAdjacencia *criaNo(int indice_destino);
void adicionaAresta(ListaDeAdjacencia *grafo[NUM_CELULAS], int origem, int destino);
void removeArestas(ListaDeAdjacencia *grafo[NUM_CELULAS], int origem);
void limpaGrafo(ListaDeAdjacencia *grafo[NUM_CELULAS]);

#endif // PROTOTIPOS_H
