#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DISCOS 4
#define VERTICES 81

// ========== Protótipos das funções ==========
void converteIndiceParaConfiguracao(int indice, int configuracao[]);
int esseMovimentoEhValido(int configuracao1[], int configuracao2[]);
void criaGrafo(int grafo[VERTICES][VERTICES]);

// ========== Função principal ==========
int main() {
    int grafo[VERTICES][VERTICES];

    clock_t inicio = clock();

    clock_t fim = clock();

    return 0;
}

// ========== Implementações das funções ==========
void converteIndiceParaConfiguracao(int indice, int configuracao[]){
    for(int i=DISCOS-1; i>=0; i--){
        configuracao[i] = indice % 3;
        indice /= 3;
    }
}

int esseMovimentoEhValido(int configuracao1[], int configuracao2[]){
    int discoMovido = -1, podeMover = 1;

    for(int i=0; i<DISCOS && podeMover; i++){
        if(configuracao1[i] != configuracao2[i]){ 
            if(discoMovido != -1) podeMover = 0;
            discoMovido = i;
        }
    }

    if(discoMovido != -1 && podeMover){
        int pinoDeOrigem = configuracao1[discoMovido];
        int pinoDeDestino = configuracao2[discoMovido];

        for(int i=0; i<discoMovido && podeMover; i++){
            if(configuracao1[i] == pinoDeOrigem) podeMover = 0;
            if(configuracao2[i] == pinoDeDestino) podeMover = 0;
        }
    }

    return podeMover;
}

void criaGrafo(int grafo[VERTICES][VERTICES]){
    int configuracao1[DISCOS], configuracao2[DISCOS];

    for(int i=0; i<VERTICES; i++){
        for(int j=0; j<VERTICES; j++){
            if(i != j){
                converteIndiceParaConfiguracao(i, configuracao1);
                converteIndiceParaConfiguracao(j, configuracao2);

                if(esseMovimentoEhValido(configuracao1, configuracao2)) grafo[i][j] = 1;
                else grafo[i][j] = 0;
            }else grafo[i][j] = 0;
        }
    }
}