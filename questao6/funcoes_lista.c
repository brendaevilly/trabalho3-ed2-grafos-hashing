#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipos.h"

// Funções de Grafo (Lista de Adjacência)

ListaDeAdjacencia *criaNo(int indice_destino) {
    ListaDeAdjacencia *novoNo = (ListaDeAdjacencia *)malloc(sizeof(ListaDeAdjacencia));
    if (novoNo == NULL) {
        // Em funções que não são void e não devem ter print, o tratamento de erro é via retorno
        // Neste caso, retornamos NULL para indicar falha na alocação.
        return NULL;
    }
    novoNo->indice_destino = indice_destino;
    novoNo->proximo = NULL;
    return novoNo;
}


void inicializaGrafoLista(ListaDeAdjacencia *grafo[NUM_CELULAS]) {
    for (int i = 0; i < NUM_CELULAS; i++) {
        grafo[i] = NULL;
    }
}


void adicionaArestaLista(ListaDeAdjacencia *grafo[NUM_CELULAS], int origem, int destino) {
    ListaDeAdjacencia *novoNo = criaNo(destino);
    if (novoNo != NULL) {
        novoNo->proximo = grafo[origem];
        grafo[origem] = novoNo;
    }
}


void removeArestasLista(ListaDeAdjacencia *grafo[NUM_CELULAS], int origem) {
    ListaDeAdjacencia *atual = grafo[origem];
    ListaDeAdjacencia *proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    grafo[origem] = NULL;
}


void limpaGrafoLista(ListaDeAdjacencia *grafo[NUM_CELULAS]) {
    for (int i = 0; i < NUM_CELULAS; i++) {
        removeArestasLista(grafo, i);
    }
}


int insereLista(ListaDeAdjacencia *grafo[NUM_CELULAS], int origem, int destino) {
    // Simula a lógica de inserção: remove antigas e adiciona nova
    removeArestasLista(grafo, origem);
    adicionaArestaLista(grafo, origem, destino);
    return 1;
}

// Funções de Busca (Lista de Adjacência)


void bfsLista(ListaDeAdjacencia *grafo[NUM_CELULAS], int inicio, int *resultado_busca) {
    int visitado[NUM_CELULAS] = {0};
    int fila[NUM_CELULAS];
    int frente = 0, tras = 0;
    int contador = 0;

    visitado[inicio] = 1;
    fila[tras++] = inicio;
    resultado_busca[contador++] = inicio;

    while (frente < tras) {
        int u = fila[frente++];
        ListaDeAdjacencia *temp = grafo[u];
        while (temp != NULL) {
            int v = temp->indice_destino;
            if (visitado[v] == 0) {
                visitado[v] = 1;
                fila[tras++] = v;
                resultado_busca[contador++] = v;
            }
            temp = temp->proximo;
        }
    }
}


static void dfsListaRecursiva(ListaDeAdjacencia *grafo[NUM_CELULAS], int u, int *resultado_busca, int *visitado, int *contador) {
    visitado[u] = 1;
    resultado_busca[(*contador)++] = u;

    ListaDeAdjacencia *temp = grafo[u];
    while (temp != NULL) {
        int v = temp->indice_destino;
        if (visitado[v] == 0) {
            dfsListaRecursiva(grafo, v, resultado_busca, visitado, contador);
        }
        temp = temp->proximo;
    }
}


void dfsLista(ListaDeAdjacencia *grafo[NUM_CELULAS], int inicio, int *resultado_busca, int *visitado) {
    int contador = 0;
    for (int i = 0; i < NUM_CELULAS; i++) visitado[i] = 0; // Limpa o array de visitação
    dfsListaRecursiva(grafo, inicio, resultado_busca, visitado, &contador);
}
