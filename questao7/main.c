#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prototipos.h"

int main() {
    int TAM1 = 1211;
    int TAM2 = 1280;

    Aluno tabelaA1[TAM1], tabelaA2[TAM2];
    Aluno tabelaB1[TAM1], tabelaB2[TAM2];

    int colisoesA1 = 0, colisoesA2 = 0;
    int colisoesB1 = 0, colisoesB2 = 0;

    inicializa(tabelaA1, TAM1);
    inicializa(tabelaA2, TAM2);
    inicializa(tabelaB1, TAM1);
    inicializa(tabelaB2, TAM2);

    for(int i=0; i<MAX_ALUNOS; i++){
        Aluno aluno;

        int ano = rand() % 10 + 2015;
        int numeroCurso = rand() % 10;
        int numeroAluno = (rand() % 900000) + 100000;

        int matriculaNum = ano * 10000000 + numeroCurso * 1000000 + numeroAluno;

        sprintf(aluno.matricula, "%04d%d%06d", ano, numeroCurso, numeroAluno);
        sprintf(aluno.nome, "Aluno %d", i);
        strcpy(aluno.curso, "Sistemas");
        aluno.periodo = 1 + (i % 8);
        aluno.anoIngresso = ano;
        aluno.ocupado = 0;

        inserir(tabelaA1, TAM1, aluno, hashA, colisaoA, &colisoesA1);
        inserir(tabelaA2, TAM2, aluno, hashA, colisaoA, &colisoesA2);
        inserir(tabelaB1, TAM1, aluno, hashB, colisaoB, &colisoesB1);
        inserir(tabelaB2, TAM2, aluno, hashB, colisaoB, &colisoesB2);
    }

    printf("\n========= RESULTADOS =========\n");

    printf("\n(a) Metodo A - Tabela 1211: %d colisoes", colisoesA1);
    printf("\n(a) Metodo A - Tabela 1280: %d colisoes", colisoesA2);

    printf("\n(b) Metodo B - Tabela 1211: %d colisoes", colisoesB1);
    printf("\n(b) Metodo B - Tabela 1280: %d colisoes\n", colisoesB2);

    return 0;
}
