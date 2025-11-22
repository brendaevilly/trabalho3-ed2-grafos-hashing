#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "prototipos.h"

// Constantes de densidade para o teste de inserção
#define NUM_ARESTAS_ESPARSO (NUM_CELULAS * 2) // 2 arestas por nó em média
#define NUM_ARESTAS_DENSO (NUM_CELULAS * NUM_CELULAS / 10) // 10% de densidade

int main() {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Variáveis para Matriz de Adjacência
    int grafo_matriz[NUM_CELULAS][NUM_CELULAS];
    double tempo_insercao_matriz, tempo_bfs_matriz, tempo_dfs_matriz;

    // Variáveis para Lista de Adjacência
    ListaDeAdjacencia *grafo_lista[NUM_CELULAS];
    double tempo_insercao_lista, tempo_bfs_lista, tempo_dfs_lista;

    printf("==================================================================\n");
    printf("  Questão 6: Medição de Tempo de Execução (N=%d, Testes=%d)\n", NUM_CELULAS, NUM_TESTES);
    printf("==================================================================\n");

    // -------------------------------------------------------------------------
    // Testes com Matriz de Adjacência
    // -------------------------------------------------------------------------
    printf("\n--- Matriz de Adjacência ---\n");

    // (a) Inserção de Dados no Grafo (Simulando um grafo esparso)
    tempo_insercao_matriz = medeTempoInsercaoMatriz(grafo_matriz, NUM_ARESTAS_ESPARSO);
    printf("Tempo Médio de Inserção (%d arestas): %.10f segundos\n", NUM_ARESTAS_ESPARSO, tempo_insercao_matriz);

    // (b) Busca em Largura (BFS)
    tempo_bfs_matriz = medeTempoBuscaMatriz(grafo_matriz, (void (*)(int[NUM_CELULAS][NUM_CELULAS], int, int*))bfsMatriz);
    printf("Tempo Médio de Busca em Largura (BFS): %.10f segundos\n", tempo_bfs_matriz);

    // (c) Busca em Profundidade (DFS)
    tempo_dfs_matriz = medeTempoBuscaMatriz(grafo_matriz, (void (*)(int[NUM_CELULAS][NUM_CELULAS], int, int*))dfsMatriz);
    printf("Tempo Médio de Busca em Profundidade (DFS): %.10f segundos\n", tempo_dfs_matriz);


    // -------------------------------------------------------------------------
    // Testes com Lista de Adjacência
    // -------------------------------------------------------------------------
    printf("\n--- Lista de Adjacência ---\n");

    // (a) Inserção de Dados no Grafo (Simulando um grafo esparso)
    tempo_insercao_lista = medeTempoInsercaoLista(grafo_lista, NUM_ARESTAS_ESPARSO);
    printf("Tempo Médio de Inserção (%d arestas): %.10f segundos\n", NUM_ARESTAS_ESPARSO, tempo_insercao_lista);

    // (b) Busca em Largura (BFS)
    tempo_bfs_lista = medeTempoBuscaLista(grafo_lista, (void (*)(ListaDeAdjacencia*[NUM_CELULAS], int, int*))bfsLista);
    printf("Tempo Médio de Busca em Largura (BFS): %.10f segundos\n", tempo_bfs_lista);

    // (c) Busca em Profundidade (DFS)
    tempo_dfs_lista = medeTempoBuscaLista(grafo_lista, (void (*)(ListaDeAdjacencia*[NUM_CELULAS], int, int*))dfsLista);
    printf("Tempo Médio de Busca em Profundidade (DFS): %.10f segundos\n", tempo_dfs_lista);

    printf("==================================================================\n");

    return 0;
}
