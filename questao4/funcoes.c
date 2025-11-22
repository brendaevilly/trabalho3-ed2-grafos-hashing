#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "prototipos.h"

void menu(){
    printf("\n--- Planilha de Calculo Rudimentar (Lista de Adjacencia) ---\n");
    printf("Colunas: A-H | Linhas: 1-20 | Total de %d celulas.\n", NUM_CELULAS);
    printf("\nComandos:\n");
    printf("  - Para inserir valor/formula: COORDENADA VALOR/FORMULA (ex: A1 10, B2 =A1, C3 @soma(A1..B2))\n");
    printf("  - Para sair: sair\n");
}

ListaDeAdjacencia *criaNo(int indice_destino) {
    ListaDeAdjacencia *novoNo = (ListaDeAdjacencia *)malloc(sizeof(ListaDeAdjacencia));
    if(novoNo != NULL){
        novoNo->indice_destino = indice_destino;
        novoNo->proximo = NULL;
    }

    return (novoNo);
}

void adicionaAresta(ListaDeAdjacencia *grafo[NUM_CELULAS], int origem, int destino) {
    ListaDeAdjacencia *novoNo = criaNo(destino);
    novoNo->proximo = grafo[origem];
    grafo[origem] = novoNo;
}

void removeArestas(ListaDeAdjacencia *grafo[NUM_CELULAS], int origem) {
    ListaDeAdjacencia *atual = grafo[origem];
    ListaDeAdjacencia *proximo;
    while(atual != NULL){
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    grafo[origem] = NULL;
}

void limpaGrafo(ListaDeAdjacencia *grafo[NUM_CELULAS]) {
    for (int i = 0; i < NUM_CELULAS; i++) removeArestas(grafo, i);
}

void inicializaPlanilha(Celula planilha[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            planilha[i][j].valor = 0.0;
            planilha[i][j].formula[0] = '\0';
            planilha[i][j].visitado = 0;
        }
    }
}

void inicializarGrafo(ListaDeAdjacencia *grafo[NUM_CELULAS]){
    for (int i = 0; i < NUM_CELULAS; i++) {
        grafo[i] = NULL;
    }
}

int converteCoordenadaParaIndice(const char *coordenada) {
    int verifica = 1, coluna, linha;
    if(strlen(coordenada) < 2) verifica = -1;
    else{
        char colChar = toupper(coordenada[0]);
        coluna = colChar - 'A';
        linha = atoi(&coordenada[1]) - 1;
        if(coluna < 0 || coluna >= COLUNAS || linha < 0 || linha >= LINHAS) verifica = -1;
    }

    return ((verifica == 1) ? (linha * COLUNAS + coluna) : verifica);
}

void converteIndiceParaCoordenada(int indice, char *coordenada) {
    int linha, coluna;
    if (indice < 0 || indice >= NUM_CELULAS) sprintf(coordenada, "INVALIDO");
    else{
        linha = indice / COLUNAS;
        coluna = indice % COLUNAS;
        sprintf(coordenada, "%c%d", 'A' + coluna, linha + 1);
    }
}

int buscaCiclo(int u, Celula planilha[LINHAS][COLUNAS], ListaDeAdjacencia *grafo[NUM_CELULAS]) {
    int ciclo = 0;
    int linha_u = u / COLUNAS;
    int coluna_u = u % COLUNAS;
    planilha[linha_u][coluna_u].visitado = 1;

    ListaDeAdjacencia *temp = grafo[u];
    while (temp != NULL && !ciclo) {
        int v = temp->indice_destino;
        int linha_v = v / COLUNAS;
        int coluna_v = v % COLUNAS;

        if (planilha[linha_v][coluna_v].visitado == 1) ciclo = 1;
        if (planilha[linha_v][coluna_v].visitado == 0) {
            if (buscaCiclo(v, planilha, grafo)) ciclo = 1;
        }
        temp = temp->proximo;
    }

    planilha[linha_u][coluna_u].visitado = 2;
    return ciclo;
}

void limpaVisitados(Celula planilha[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++) planilha[i][j].visitado = 0;
}

int analisarIntervalo(const char *intervaloString, int *IndiceInicio, int *IndiceFim) {
    char coordenadaInicio[10], coordenadaFim[10];
    const char *pontos = strstr(intervaloString, "..");
    if (!pontos) return 0;

    int tamanhoInicio = pontos - intervaloString;
    if (tamanhoInicio >= 10) return 0;
    strncpy(coordenadaInicio, intervaloString, tamanhoInicio);
    coordenadaInicio[tamanhoInicio] = '\0';

    strcpy(coordenadaFim, pontos + 2);

    *IndiceInicio = converteCoordenadaParaIndice(coordenadaInicio);
    *IndiceFim = converteCoordenadaParaIndice(coordenadaFim);

    return (*IndiceInicio != -1 && *IndiceFim != -1);
}

double calculaReferenciaCelula(const char *formula, Celula planilha[LINHAS][COLUNAS], ListaDeAdjacencia *grafo[NUM_CELULAS]) {
    double verifica = 1.0;
    char coordenadaReferencia[10];
    strcpy(coordenadaReferencia, formula + 1);
    int linha, coluna;

    int indice = converteCoordenadaParaIndice(coordenadaReferencia);
    if (indice == -1) verifica = 0.0;
    else{
        linha = indice / COLUNAS;
        coluna = indice % COLUNAS;
    }

    return ((verifica == 1.0) ? calculaValorCelula(linha, coluna, planilha, grafo) : verifica);
}

double calculaFuncao(const char *formula, int linha, int coluna, Celula planilha[LINHAS][COLUNAS], ListaDeAdjacencia *grafo[NUM_CELULAS]) {
    char nomeFuncao[10], intervaloStr[50];
    int inicio, fim;
    double resultado = 1.0;

    if(sscanf(formula + 1, "%[^(](%[^)])", nomeFuncao, intervaloStr) != 2) resultado = 0.0;
    else if(!analisarIntervalo(intervaloStr, &inicio, &fim)) resultado = 0.0;
    else{
        double *valores = malloc(NUM_CELULAS * sizeof(double));
        int count = 0;

        for(int i = inicio; i <= fim; i++){
            int r = i / COLUNAS;
            int c = i % COLUNAS;
            valores[count++] = calculaValorCelula(r, c, planilha, grafo);
        }

        resultado = 0.0;
        if(count > 0){
            if(strcasecmp(nomeFuncao, "soma") == 0) for (int i = 0; i < count; i++) resultado += valores[i];
            else if(strcasecmp(nomeFuncao, "max") == 0){
                resultado = valores[0];
                for (int i = 1; i < count; i++) 
                    if (valores[i] > resultado) resultado = valores[i];
            }else if(strcasecmp(nomeFuncao, "min") == 0){
                resultado = valores[0];
                for (int i = 1; i < count; i++)
                    if (valores[i] < resultado) resultado = valores[i];
            }else if(strcasecmp(nomeFuncao, "media") == 0){
                double soma = 0.0;
                for (int i = 0; i < count; i++) soma += valores[i];
                resultado = soma / count;
            }else resultado = 0.0;
        }

        free(valores);
    }
    
    return (resultado);
}

double calculaValorCelula(int linha, int coluna, Celula planilha[LINHAS][COLUNAS], ListaDeAdjacencia *grafo[NUM_CELULAS]){
    char *formula = planilha[linha][coluna].formula;
    double valor = 0.0;

    if (formula[0] == '\0') valor = 0.0;
    else if(formula[0] == '=') valor = calculaReferenciaCelula(formula, planilha, grafo);
    else if(formula[0] == '@') valor = calculaFuncao(formula, linha, coluna, planilha, grafo);
    else valor = atof(formula);

    planilha[linha][coluna].valor = valor;
    return (valor);
}

void atualizaPlanilha(Celula planilha[LINHAS][COLUNAS], ListaDeAdjacencia *grafo[NUM_CELULAS]) {
    printf("\n--- Atualizando Planilha ---\n");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) calculaValorCelula(i, j, planilha, grafo);
    }
    printf("--- Atualizacao Concluida ---\n");
}

int processaEntrada(const char *entrada, Celula planilha[LINHAS][COLUNAS], ListaDeAdjacencia *grafo[NUM_CELULAS]) {
    int verifica = 1;
    char coordenadaString[10];
    char formulaString[50];
    
    if(sscanf(entrada, "%s %s", coordenadaString, formulaString) != 2) verifica = 0;
    else{
        int indice_u = converteCoordenadaParaIndice(coordenadaString);
        if(indice_u == -1) verifica = 0;
        else{
            int linha_u = indice_u / COLUNAS;
            int coluna_u = indice_u % COLUNAS;

            removeArestas(grafo, indice_u);
            char formula_antiga[50];
            strcpy(formula_antiga, planilha[linha_u][coluna_u].formula);
            strcpy(planilha[linha_u][coluna_u].formula, formulaString);

            if(formulaString[0] == '=') {
                char coordenadaReferencia[10];
                strcpy(coordenadaReferencia, formulaString + 1);
                int indice_v = converteCoordenadaParaIndice(coordenadaReferencia);
                if(indice_v != -1) adicionaAresta(grafo, indice_u, indice_v);
            }else if(formulaString[0] == '@') {
                char nomeFuncao[10];
                char intervaloString[50];
                int indiceInicio, indiceFim;

                if(sscanf(formulaString + 1, "%[^(](%[^)])", nomeFuncao, intervaloString) == 2) {
                    if (analisarIntervalo(intervaloString, &indiceInicio, &indiceFim))
                        for(int v = indiceInicio; v <= indiceFim; v++) adicionaAresta(grafo, indice_u, v);
                }
            }

            limpaVisitados(planilha);
            if(buscaCiclo(indice_u, planilha, grafo)){
                removeArestas(grafo, indice_u);
                strcpy(planilha[linha_u][coluna_u].formula, formula_antiga);
                atualizaPlanilha(planilha, grafo); 
                verifica = 0;
            }
            atualizaPlanilha(planilha, grafo);
        }
    }

    return (verifica);
}

void exibePlanilha(Celula planilha[LINHAS][COLUNAS]) {
    printf("\n================================================================================================\n");
    printf("  |   A    |   B    |   C    |   D    |   E    |   F    |   G    |   H    |\n");
    printf("--+--------+--------+--------+--------+--------+--------+--------+--------+\n");
    for (int i = 0; i < LINHAS; i++) {
        printf("%2d|", i + 1);
        for (int j = 0; j < COLUNAS; j++) printf(" %6.2f |", planilha[i][j].valor);
        printf("\n");
    }
    printf("================================================================================================\n");
}