#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "prototipos.h"


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


void inicializaPlanilha(Celula planilha[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            planilha[i][j].visitado = 0;
        }
    }
}


void limpaVisitados(Celula planilha[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            planilha[i][j].visitado = 0;
        }
    }
}
