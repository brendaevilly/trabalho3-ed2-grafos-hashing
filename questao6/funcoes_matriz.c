#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipos.h"

// =================================================================================================
// Funções de Grafo (Matriz de Adjacência)
// =================================================================================================

/**
 * @brief Inicializa o grafo com zeros.
 */
void inicializaGrafoMatriz(int grafo[NUM_CELULAS][NUM_CELULAS]) {
    for (int i = 0; i < NUM_CELULAS; i++) {
        for (int j = 0; j < NUM_CELULAS; j++) {
            grafo[i][j] = 0;
        }
    }
}

/**
 * @brief Adiciona uma aresta (origem -> destino).
 */
void adicionaArestaMatriz(int grafo[NUM_CELULAS][NUM_CELULAS], int origem, int destino) {
    if (origem >= 0 && origem < NUM_CELULAS && destino >= 0 && destino < NUM_CELULAS) {
        grafo[origem][destino] = 1;
    }
}

/**
 * @brief Remove todas as arestas de saída de um vértice.
 */
void removeArestasMatriz(int grafo[NUM_CELULAS][NUM_CELULAS], int origem) {
    if (origem >= 0 && origem < NUM_CELULAS) {
        for (int i = 0; i < NUM_CELULAS; i++) {
            grafo[origem][i] = 0;
        }
    }
}

/**
 * @brief Simula a inserção de uma aresta para fins de medição de tempo.
 * @return 1 se a inserção foi bem-sucedida, 0 caso contrário.
 */
int insereMatriz(int grafo[NUM_CELULAS][NUM_CELULAS], int origem, int destino) {
    // Simula a lógica de inserção: remove antigas e adiciona nova
    removeArestasMatriz(grafo, origem);
    adicionaArestaMatriz(grafo, origem, destino);
    return 1;
}

// =================================================================================================
// Funções de Busca (Matriz de Adjacência)
// =================================================================================================

/**
 * @brief Busca em Largura (BFS) para Matriz de Adjacência.
 * @param resultado_busca Array para armazenar a ordem de visitação.
 */
void bfsMatriz(int grafo[NUM_CELULAS][NUM_CELULAS], int inicio, int *resultado_busca) {
    int visitado[NUM_CELULAS] = {0};
    int fila[NUM_CELULAS];
    int frente = 0, tras = 0;
    int contador = 0;

    visitado[inicio] = 1;
    fila[tras++] = inicio;
    resultado_busca[contador++] = inicio;

    while (frente < tras) {
        int u = fila[frente++];
        for (int v = 0; v < NUM_CELULAS; v++) {
            if (grafo[u][v] == 1 && visitado[v] == 0) {
                visitado[v] = 1;
                fila[tras++] = v;
                resultado_busca[contador++] = v;
            }
        }
    }
}

/**
 * @brief Função auxiliar recursiva para a Busca em Profundidade (DFS).
 */
static void dfsMatrizRecursiva(int grafo[NUM_CELULAS][NUM_CELULAS], int u, int *resultado_busca, int *visitado, int *contador) {
    visitado[u] = 1;
    resultado_busca[(*contador)++] = u;

    for (int v = 0; v < NUM_CELULAS; v++) {
        if (grafo[u][v] == 1 && visitado[v] == 0) {
            dfsMatrizRecursiva(grafo, v, resultado_busca, visitado, contador);
        }
    }
}

/**
 * @brief Busca em Profundidade (DFS) para Matriz de Adjacência.
 * @param resultado_busca Array para armazenar a ordem de visitação.
 * @param visitado Array de controle de visitação (passado para manter a modularidade do protótipo).
 */
void dfsMatriz(int grafo[NUM_CELULAS][NUM_CELULAS], int inicio, int *resultado_busca, int *visitado) {
    int contador = 0;
    for (int i = 0; i < NUM_CELULAS; i++) visitado[i] = 0; // Limpa o array de visitação
    dfsMatrizRecursiva(grafo, inicio, resultado_busca, visitado, &contador);
}
