#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipos.h"

void rotacionaDireita5(char matricula[]) {
    char temp = matricula[4];
    for(int i = 4; i > 0; i--) matricula[i] = matricula[i - 1];
    matricula[0] = temp;
}

int hashA(char matricula[], int tamanhoTabela) {
    char m[12];
    strcpy(m, matricula);

    rotacionaDireita5(m);
    int dig2 = m[1] - '0';
    int dig4 = m[3] - '0';
    int dig5 = m[4] - '0';

    int valor = dig2 * 100 + dig4 * 10 + dig5;

    return (valor % tamanhoTabela);
}

int colisaoA(char matricula[]) {
    char m[12];
    strcpy(m, matricula);
    rotacionaDireita5(m);
    return (m[0] - '0');
}

int hashB(char matricula[], int tamanhoTabela) {
    char m[12];
    strcpy(m, matricula);

    int g1 = ((m[5] - '0') * 100) + ((m[6] - '0') * 10) + (m[10] - '0');
    int g2 = ((m[7] - '0') * 100) + ((m[8] - '0') * 10) + (m[9] - '0');

    int soma = g1 + g2;

    return (soma % tamanhoTabela);
}

int colisaoB(char matricula[]) {
    int dig6 = matricula[5] - '0';
    int dig11 = matricula[10] - '0';

    return ((dig6 * 10) + dig11);
}

void inserir(Aluno tabela[], int tamanho, Aluno aluno, int (*hfunc)(char*, int), int (*cfunc)(char*), int *colisoes) {
    int pos = hfunc(aluno.matricula, tamanho);

    int incremento = cfunc(aluno.matricula);
    if (incremento == 0) incremento = 1;

    int tentativas = 0;
    int primeiraPosicaoOcupada = -1;

    int inserido = 0;
    while(tentativas < tamanho && !inserido){
        if(!tabela[pos].ocupado){
            tabela[pos] = aluno;
            tabela[pos].ocupado = 1;
            inserido = 1;
        }else{
            if(primeiraPosicaoOcupada == -1)
                primeiraPosicaoOcupada = pos;

            (*colisoes)++;

            pos = (pos + incremento) % tamanho;
            tentativas++;
        }
    }
    if(!inserido && primeiraPosicaoOcupada != -1) {
        tabela[primeiraPosicaoOcupada] = aluno;
        tabela[primeiraPosicaoOcupada].ocupado = 1;
    }
}

void inicializa(Aluno tabela[], int tamanho) {
    for (int i = 0; i < tamanho; i++)
        tabela[i].ocupado = 0;
}