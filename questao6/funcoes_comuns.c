#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "prototipos.h"

/**
 * @brief Converte uma coordenada de célula (ex: "A1", "H20") para um índice linear (0 a NUM_CELULAS-1).
 * 
 * @param coordenada A string da coordenada da célula.
 * @return int O índice linear da célula, ou -1 se a coordenada for inválida.
 */
int converteCoordenadaParaIndice(const char *coordenada) {
    if (strlen(coordenada) < 2) return -1;

    char colChar = toupper(coordenada[0]);
    int coluna = colChar - 'A';
    int linha = atoi(&coordenada[1]) - 1;

    if (coluna < 0 || coluna >= COLUNAS || linha < 0 || linha >= LINHAS) {
        return -1;
    }

    return linha * COLUNAS + coluna;
}

/**
 * @brief Inicializa a planilha (apenas a parte de controle de visitação).
 * 
 * @param planilha A matriz de células da planilha.
 */
void inicializaPlanilha(Celula planilha[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            planilha[i][j].visitado = 0;
        }
    }
}

/**
 * @brief Limpa os estados de visitação da planilha.
 * 
 * @param planilha A matriz de células.
 */
void limpaVisitados(Celula planilha[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            planilha[i][j].visitado = 0;
        }
    }
}
