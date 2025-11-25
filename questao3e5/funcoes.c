#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "prototipos.h"

void menu(){
    printf("\n--- Planilha de Calculo Rudimentar ---\n");
    printf("Colunas: A-H | Linhas: 1-20 | Total de %d celulas.\n", NUM_CELULAS);
    printf("\nComandos:\n");
    printf("  - Para inserir valor/formula: COORDENADA VALOR/FORMULA (ex: A1 10, B2 =A1, C3 @soma(A1..B2))\n");
    printf("  - Para sair: sair\n");
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

void inicializarGrafo(int grafo[NUM_CELULAS][NUM_CELULAS]) {
    for (int i = 0; i < NUM_CELULAS; i++) {
        for (int j = 0; j < NUM_CELULAS; j++) {
            grafo[i][j] = 0;
        }
    }
}

int converteCoordenadaParaIndice(const char *coordenada) {
    int valido = 0, linha, coluna;
    if (strlen(coordenada) < 2) valido = -1;
    else{
        char colChar = toupper(coordenada[0]);
        coluna = colChar - 'A';
        linha = atoi(&coordenada[1]) - 1;
        if (coluna < 0 || coluna >= COLUNAS || linha < 0 || linha >= LINHAS) valido = -1;
    }

    return ((valido == 0) ? linha * COLUNAS + coluna : -1);
}

void converteIndiceParaCoordenada(int indice, char *coordenada) {
    if (indice < 0 || indice >= NUM_CELULAS) sprintf(coordenada, "INVALIDO");
    else{
        int linha = indice / COLUNAS;
        int coluna = indice % COLUNAS;
        sprintf(coordenada, "%c%d", 'A' + coluna, linha + 1);
    }
    
}

int buscaCiclo(int indice, Celula planilha[LINHAS][COLUNAS], int grafo[NUM_CELULAS][NUM_CELULAS]) {
    int cicloDetectado = 0;
    int linha_indice = indice / COLUNAS;
    int coluna_indice = indice % COLUNAS;
    planilha[linha_indice][coluna_indice   ].visitado = 1;

    for (int v = 0; v < NUM_CELULAS && !cicloDetectado; v++) {
        if (grafo[indice][v] == 1) {
            int linha_v = v / COLUNAS;
            int coluna_v = v % COLUNAS;

            if (planilha[linha_v][coluna_v].visitado == 1) {
                cicloDetectado = 1;
            }
            if (planilha[linha_v][coluna_v].visitado == 0) {
                if (buscaCiclo(v, planilha, grafo)) {
                    cicloDetectado = 1;
                }
            }
        }
    }

    planilha[linha_indice][coluna_indice].visitado = 2;
    return (cicloDetectado);
}

void limpaVisitados(Celula planilha[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            planilha[i][j].visitado = 0;
        }
    }
}

int analisarIntervalo(const char *intervaloString, int *indiceInicio, int *indiceFim) {
    char coordenadaInicio[10], coordenadaFim[10];
    const char *pontos = strstr(intervaloString, "..");
    if (!pontos) return 0;

    int tamanhoInicio = pontos - intervaloString;
    if (tamanhoInicio >= 10) return 0;
    strncpy(coordenadaInicio, intervaloString, tamanhoInicio);
    coordenadaInicio[tamanhoInicio] = '\0';
    
    strcpy(coordenadaFim, pontos + 2);

    *indiceInicio = converteCoordenadaParaIndice(coordenadaInicio);
    *indiceFim = converteCoordenadaParaIndice(coordenadaFim);

    return (*indiceInicio != -1 && *indiceFim != -1);
}

double calculaCelulaReferencia(const char *formula, Celula planilha[LINHAS][COLUNAS], int grafo[NUM_CELULAS][NUM_CELULAS]) {
    int indice = converteCoordenadaParaIndice(formula + 1);
    double valido = 1.0;
    if (indice == -1) valido = 0.0;
    
    int linha = indice / COLUNAS;
    int coluna = indice % COLUNAS;
    return ((valido == 0.0)? valido : calculaValorCelula(linha, coluna, planilha, grafo));
}

double calculaFuncaoCelula(const char *formula, int linha, int coluna, Celula planilha[LINHAS][COLUNAS], int grafo[NUM_CELULAS][NUM_CELULAS]) {
    char nomeFuncao[10], intervaloStr[50];
    int inicio, fim;
    double resultado;

    if(sscanf(formula + 1, "%[^(](%[^)])", nomeFuncao, intervaloStr) != 2) resultado = 0.0;
    else if (!analisarIntervalo(intervaloStr, &inicio, &fim)) resultado = 0.0;
    else{
        double *valores = malloc(NUM_CELULAS * sizeof(double));
        int count = 0;
        for (int i = inicio; i <= fim; i++) {
            int r = i / COLUNAS;
            int c = i % COLUNAS;
            valores[count++] = calculaValorCelula(r, c, planilha, grafo);
        }

        resultado = 0.0;

        if(count > 0){
            if(strcasecmp(nomeFuncao, "soma") == 0){
                for (int i = 0; i < count; i++) resultado += valores[i];
            }else if(strcasecmp(nomeFuncao, "max") == 0){
                resultado = valores[0];
                for (int i = 1; i < count; i++) if (valores[i] > resultado) resultado = valores[i];
            }else if(strcasecmp(nomeFuncao, "min") == 0){
                resultado = valores[0];
                for (int i = 1; i < count; i++) if (valores[i] < resultado) resultado = valores[i];
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

double calculaValorCelula(int linha, int coluna, Celula planilha[LINHAS][COLUNAS], int grafo[NUM_CELULAS][NUM_CELULAS]) {
    char *formula = planilha[linha][coluna].formula;
    double valor = 0.0;

    if (formula[0] == '\0') valor = 0.0;
    else if (formula[0] == '=') valor = calculaCelulaReferencia(formula, planilha, grafo);
    else if (formula[0] == '@') valor = calculaFuncaoCelula(formula, linha, coluna, planilha, grafo);
    else valor = atof(formula);

    planilha[linha][coluna].valor = valor;
    return (valor);
}

void atualizaPlanilha(Celula planilha[LINHAS][COLUNAS], int grafo[NUM_CELULAS][NUM_CELULAS]) {
    printf("\n--- Atualizando Planilha ---\n");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++)
            calculaValorCelula(i, j, planilha, grafo);
    }
    printf("--- Atualização Concluída ---\n");
}

int processaEntrada(const char *entrada, Celula planilha[LINHAS][COLUNAS], int grafo[NUM_CELULAS][NUM_CELULAS]) {
    char coordenadaString[10];
    char formulaString[50];
    int retorno = 1;
    
    if (sscanf(entrada, "%s %s", coordenadaString, formulaString) != 2) retorno = 0;
    else{
        int indice = converteCoordenadaParaIndice(coordenadaString);
        if (indice == -1) retorno = 0;
        else{
            int linha = indice / COLUNAS;
            int coluna = indice % COLUNAS;

            for(int v = 0; v < NUM_CELULAS; v++) grafo[indice][v] = 0;
            strcpy(planilha[linha][coluna].formula, formulaString);
            if(formulaString[0] == '='){
                char referenciaCoordenada[10];
                strcpy(referenciaCoordenada, formulaString + 1);

                int indice_v = converteCoordenadaParaIndice(referenciaCoordenada);
                if (indice_v != -1) grafo[indice][indice_v] = 1;
            }else if(formulaString[0] == '@'){
                char nomeFuncao[10];
                char intervaloString[50];
                int indiceInicio, indiceFim;

                if (sscanf(formulaString + 1, "%[^(](%[^)])", nomeFuncao, intervaloString) == 2) {
                    if (analisarIntervalo(intervaloString, &indiceInicio, &indiceFim))
                        for (int v = indiceInicio; v <= indiceFim; v++) grafo[indice][v] = 1;
                }
            }
            
            limpaVisitados(planilha);
            if (buscaCiclo(indice, planilha, grafo)) {
                planilha[linha][coluna].formula[0] = '\0';
                for (int v = 0; v < NUM_CELULAS; v++) grafo[indice][v] = 0;
                retorno = 0;
            }

            atualizaPlanilha(planilha, grafo);
        }
    }

    return retorno;
}

void exibePlanilha(Celula planilha[LINHAS][COLUNAS]) {
    printf("\n================================================================================================\n");
    printf("  |   A    |   B    |   C    |   D    |   E    |   F    |   G    |   H    |\n");
    printf("--+--------+--------+--------+--------+--------+--------+--------+--------+\n");
    for (int i = 0; i < LINHAS; i++) {
        printf("%2d|", i + 1);
        for (int j = 0; j < COLUNAS; j++) {
            printf(" %6.2f |", planilha[i][j].valor);
        }
        printf("\n");
    }
    printf("================================================================================================\n");
}

/* DFS recursiva a partir de um nó */
void dfs_rec(int u, Celula planilha[LINHAS][COLUNAS], int grafo[NUM_CELULAS][NUM_CELULAS]) {
    int linha = u / COLUNAS;
    int coluna = u % COLUNAS;

    if(!(planilha[linha][coluna].visitado)){
        planilha[linha][coluna].visitado = 1;

        char coord[10];
        converteIndiceParaCoordenada(u, coord);
        printf("Visitando: %s\n", coord);

        for(int v=0; v<NUM_CELULAS; v++) if(grafo[u][v] == 1) dfs_rec(v, planilha, grafo);
    }
}

/* Percorre todo o grafo (somente componentes com arestas de origem) em DFS */
void buscaEmProfundidadeGrafo(int grafo[NUM_CELULAS][NUM_CELULAS], Celula planilha[LINHAS][COLUNAS]) {
    limpaVisitados(planilha);
    printf("\n--- BUSCA EM PROFUNDIDADE ---\n");

    for(int indice=0; indice<NUM_CELULAS; indice++) {
        int temAresta = 0;
        for (int v = 0; v < NUM_CELULAS && temAresta == 0; v++)
            if(grafo[indice][v] == 1) temAresta = 1;
        if (temAresta){
            int linha = indice / COLUNAS;
            int coluna = indice % COLUNAS;
            if (planilha[linha][coluna].visitado == 0) dfs_rec(indice, planilha, grafo);
        }   
    }
}

/* BFS que inicia em cada componente (somente origens com arestas) */
void buscaEmLarguraGrafo(int grafo[NUM_CELULAS][NUM_CELULAS], Celula planilha[LINHAS][COLUNAS]) {
    limpaVisitados(planilha);
    printf("\n--- BUSCA EM LARGURA ---\n");

    int fila[NUM_CELULAS];
    for(int inicio=0; inicio<NUM_CELULAS; inicio++){
        /* só inicia a BFS em nós que tenham arestas de saída */
        int temAresta = 0;
        for(int v=0; v<NUM_CELULAS && temAresta == 0; v++) 
            if(grafo[inicio][v] == 1) temAresta = 1;
        if(temAresta){
            int linha_i = inicio / COLUNAS;
            int coluna_i = inicio % COLUNAS;
            if(!(planilha[linha_i][coluna_i].visitado)){
                int ini = 0, fim = 0;
                fila[fim++] = inicio;

                while(ini < fim){
                    int u = fila[ini++];

                    int linha = u / COLUNAS;
                    int coluna = u % COLUNAS;
                    if(!(planilha[linha][coluna].visitado)){
                        planilha[linha][coluna].visitado = 1;
                        char coord[10];
                        converteIndiceParaCoordenada(u, coord);
                        printf("Visitando: %s\n", coord);

                        for(int v=0; v<NUM_CELULAS; v++)
                            if(grafo[u][v] == 1 && !planilha[v / COLUNAS][v % COLUNAS].visitado) fila[fim++] = v;
                    }
                }
            }
        }
    }
}
