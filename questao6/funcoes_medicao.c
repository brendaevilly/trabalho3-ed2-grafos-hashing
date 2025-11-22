#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "prototipos.h"


double medeTempoInsercaoMatriz(int grafo[NUM_CELULAS][NUM_CELULAS], int num_arestas) {
    clock_t inicio, fim;
    double tempo_total = 0.0;
    int origem, destino;

    for (int i = 0; i < NUM_TESTES; i++) {
        // Reinicializa o grafo para cada teste
        inicializaGrafoMatriz(grafo);
        
        inicio = clock();
        for (int j = 0; j < num_arestas; j++) {
            // Gera arestas aleatórias
            origem = rand() % NUM_CELULAS;
            destino = rand() % NUM_CELULAS;
            insereMatriz(grafo, origem, destino);
        }
        fim = clock();
        tempo_total += (double)(fim - inicio) / CLOCKS_PER_SEC;
    }

    return tempo_total / NUM_TESTES;
}

double medeTempoBuscaMatriz(int grafo[NUM_CELULAS][NUM_CELULAS], void (*funcao_busca)(int[NUM_CELULAS][NUM_CELULAS], int, int*)) {
    clock_t inicio, fim;
    double tempo_total = 0.0;
    int resultado_busca[NUM_CELULAS];
    int visitado[NUM_CELULAS]; // Apenas para DFS

    // Preenche o grafo com algumas arestas para que a busca não seja trivial (ex: 10% de densidade)
    inicializaGrafoMatriz(grafo);
    for (int i = 0; i < NUM_CELULAS; i++) {
        for (int j = 0; j < NUM_CELULAS; j++) {
            if (rand() % 10 == 0) { // 10% de chance de ter uma aresta
                adicionaArestaMatriz(grafo, i, j);
            }
        }
    }

    for (int i = 0; i < NUM_TESTES; i++) {
        int no_inicial = rand() % NUM_CELULAS;
        
        inicio = clock();
        // A função de busca é chamada. O array 'visitado' é usado apenas para a DFS
        if (funcao_busca == (void (*)(int[NUM_CELULAS][NUM_CELULAS], int, int*))dfsMatriz) {
            dfsMatriz(grafo, no_inicial, resultado_busca, visitado);
        } else {
            bfsMatriz(grafo, no_inicial, resultado_busca);
        }
        fim = clock();
        tempo_total += (double)(fim - inicio) / CLOCKS_PER_SEC;
    }

    return tempo_total / NUM_TESTES;
}

double medeTempoInsercaoLista(ListaDeAdjacencia *grafo[NUM_CELULAS], int num_arestas) {
    clock_t inicio, fim;
    double tempo_total = 0.0;
    int origem, destino;

    for (int i = 0; i < NUM_TESTES; i++) {
        // Reinicializa o grafo para cada teste
        limpaGrafoLista(grafo);
        inicializaGrafoLista(grafo);
        
        inicio = clock();
        for (int j = 0; j < num_arestas; j++) {
            // Gera arestas aleatórias
            origem = rand() % NUM_CELULAS;
            destino = rand() % NUM_CELULAS;
            insereLista(grafo, origem, destino);
        }
        fim = clock();
        tempo_total += (double)(fim - inicio) / CLOCKS_PER_SEC;
    }
    
    // Limpa o grafo após o último teste
    limpaGrafoLista(grafo);

    return tempo_total / NUM_TESTES;
}


double medeTempoBuscaLista(ListaDeAdjacencia *grafo[NUM_CELULAS], void (*funcao_busca)(ListaDeAdjacencia*[NUM_CELULAS], int, int*)) {
    clock_t inicio, fim;
    double tempo_total = 0.0;
    int resultado_busca[NUM_CELULAS];
    int visitado[NUM_CELULAS]; // Apenas para DFS

    // Preenche o grafo com algumas arestas para que a busca não seja trivial (ex: 10% de densidade)
    inicializaGrafoLista(grafo);
    for (int i = 0; i < NUM_CELULAS; i++) {
        for (int j = 0; j < NUM_CELULAS; j++) {
            if (rand() % 10 == 0) { // 10% de chance de ter uma aresta
                adicionaArestaLista(grafo, i, j);
            }
        }
    }

    for (int i = 0; i < NUM_TESTES; i++) {
        int no_inicial = rand() % NUM_CELULAS;
        
        inicio = clock();
        // A função de busca é chamada. O array 'visitado' é usado apenas para a DFS
        if (funcao_busca == (void (*)(ListaDeAdjacencia*[NUM_CELULAS], int, int*))dfsLista) {
            dfsLista(grafo, no_inicial, resultado_busca, visitado);
        } else {
            bfsLista(grafo, no_inicial, resultado_busca);
        }
        fim = clock();
        tempo_total += (double)(fim - inicio) / CLOCKS_PER_SEC;
    }
    
    // Limpa o grafo após o último teste
    limpaGrafoLista(grafo);

    return tempo_total / NUM_TESTES;
}
