#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DISCOS 4
#define VERTICES 81
#define INFINITO 9999
#define PESO_ARESTA 1

// ========== Protótipos das funções ==========
void converteIndiceParaConfiguracao(int indice, int configuracao[]);
int converteConfiguracaoParaIndice(int configuracao[]);
int esseMovimentoEhValido(int configuracao1[], int configuracao2[]);
void criaGrafo(int grafo[VERTICES][VERTICES]);
int menorDistancia(int distancia[], int visitado[]);
void dijkstra(int grafo[VERTICES][VERTICES], int origem, int destino);

// ========== Função principal ==========
int main() {
    int grafo[VERTICES][VERTICES];

    criaGrafo(grafo);
    int configuracaoInicial[DISCOS];

    printf("Digite a configuracao inicial dos 4 discos.\n)");
    printf("Tres pinos:\n0 - pino A\n1 - pino B\n2 - pino C\n");

    for(int i=0; i<DISCOS; i++){
        printf("\nDisco %d: ", i+1);
        scanf("%d", &configuracaoInicial[i]);
    }

    int indiceOrigem = converteConfiguracaoParaIndice(configuracaoInicial);
    int configuracaoFinal[DISCOS] = {2, 2, 2, 2};
    int indiceDestino = converteConfiguracaoParaIndice(configuracaoFinal);

    clock_t inicio = clock();
    dijkstra(grafo, indiceOrigem, indiceDestino);
    clock_t fim = clock();

    double tempoGastoEmSegundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo gasto: %.6f segundos\n", tempoGastoEmSegundos);

    return 0;
}

// ========== Implementações das funções ==========
void converteIndiceParaConfiguracao(int indice, int configuracao[]){
    for(int i=DISCOS-1; i>=0; i--){
        configuracao[i] = indice % 3;
        indice /= 3;
    }
}

int converteConfiguracaoParaIndice(int configuracao[]){
    int indice = 0;
    for(int i=0; i<DISCOS; i++){
        indice = indice * 3 + configuracao[i];
    }

    return (indice);
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

    return (podeMover);
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

int menorDistancia(int distancia[], int visitado[]){
    int menorDistanciaAtual = INFINITO;
    int indiceComMenorDistancia = -1;

    for(int i=0; i<VERTICES; i++){
        if(!visitado[i] && distancia[i] <= menorDistanciaAtual){
            menorDistanciaAtual = distancia[i];
            indiceComMenorDistancia = i;
        }
    }

    return (indiceComMenorDistancia);
}

void dijkstra(int grafo[VERTICES][VERTICES], int origem, int destino){
    int distancia[VERTICES], visitado[VERTICES], anterior[VERTICES];

    for(int i=0; i<VERTICES; i++){
        distancia[i] = INFINITO;
        visitado[i] = 0;
        anterior[i] = -1;
    }

    distancia[origem] = 0;

    int loop = 1;
    while(loop){
        int proximoVertice = menorDistancia(distancia, visitado);

        if(proximoVertice != -1 || proximoVertice != destino){
            visitado[proximoVertice] = 1;

            for(int v=0; v<VERTICES; v++){
                if(grafo[proximoVertice][v] == 1 && distancia[proximoVertice] + PESO_ARESTA < distancia[v]){
                    distancia[v] = distancia[proximoVertice] + PESO_ARESTA;
                    anterior[v] = proximoVertice;
                }
            }
        }else loop = 0;
    }

    printf("\nMenor distancia = %d movimentos\n", distancia[destino]);
    printf("Caminho (indices): ");

    int caminho[200], tamanho = 0;
    int atual = destino;
    while (atual != -1) {
        caminho[tamanho++] = atual;
        atual = anterior[atual];
    }

    for (int i = tamanho - 1; i >= 0; i--)
        printf("%d ", caminho[i]);

    printf("\n");
}