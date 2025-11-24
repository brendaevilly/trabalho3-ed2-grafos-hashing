#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

#define MAX_ALUNOS 4000
#define TAM_MATRICULA 12

struct Aluno;
typedef struct aluno{
    char matricula[TAM_MATRICULA];
    char nome[50];
    char curso[50];
    int periodo;
    int anoIngresso;
    int ocupado;
}Aluno;

void rotacionaDireita5(char matricula[]);
int hashA(char matricula[], int tamanhoTabela);
int colisaoA(char matricula[]);
int hashB(char matricula[], int tamanhoTabela);
int colisaoB(char matricula[]);
void inserir(Aluno tabela[], int tamanho, Aluno aluno, int (*hfunc)(char*, int), int (*cfunc)(char*), int *colisoes);
void inicializa(Aluno tabela[], int tamanho);

#endif