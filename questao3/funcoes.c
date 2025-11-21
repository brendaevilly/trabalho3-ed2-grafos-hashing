#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "prototipos.h"

// =================================================================================================
// Funções de Conversão e Inicialização
// =================================================================================================

/**
 * @brief Inicializa a planilha com valores 0.0 e fórmulas vazias.
 * 
 * @param planilha A matriz de células da planilha.
 */
void inicializaPlanilha(Celula planilha[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            planilha[i][j].valor = 0.0;
            planilha[i][j].formula[0] = '\0';
            planilha[i][j].visitado = 0;
        }
    }
}

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
 * @brief Converte um índice linear para uma coordenada de célula (ex: 0 -> "A1").
 * 
 * @param indice O índice linear da célula.
 * @param coordenada Buffer para armazenar a string da coordenada.
 */
void converteIndiceParaCoordenada(int indice, char *coordenada) {
    if (indice < 0 || indice >= NUM_CELULAS) {
        sprintf(coordenada, "INVALIDO");
        return;
    }
    int linha = indice / COLUNAS;
    int coluna = indice % COLUNAS;

    sprintf(coordenada, "%c%d", 'A' + coluna, linha + 1);
}

// =================================================================================================
// Funções de Grafo e Busca
// =================================================================================================

/**
 * @brief Realiza uma busca em profundidade (DFS) para detectar ciclos.
 * 
 * @param u O índice da célula atual.
 * @param planilha A matriz de células.
 * @param grafo A matriz de adjacência do grafo.
 * @return int 1 se um ciclo for detectado, 0 caso contrário.
 */
int buscaCiclo(int u, Celula planilha[LINHAS][COLUNAS], int grafo[NUM_CELULAS][NUM_CELULAS]) {
    int linha_u = u / COLUNAS;
    int coluna_u = u % COLUNAS;
    planilha[linha_u][coluna_u].visitado = 1; // Marcado como visitando

    for (int v = 0; v < NUM_CELULAS; v++) {
        if (grafo[u][v] == 1) { // Se 'u' depende de 'v'
            int linha_v = v / COLUNAS;
            int coluna_v = v % COLUNAS;

            if (planilha[linha_v][coluna_v].visitado == 1) {
                return 1; // Ciclo detectado
            }
            if (planilha[linha_v][coluna_v].visitado == 0) {
                if (buscaCiclo(v, planilha, grafo)) {
                    return 1;
                }
            }
        }
    }

    planilha[linha_u][coluna_u].visitado = 2; // Marcado como visitado
    return 0;
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

// =================================================================================================
// Funções de Cálculo e Processamento
// =================================================================================================

/**
 * @brief Analisa uma string de intervalo (ex: "B1..D2") e retorna os índices inicial e final.
 * 
 * @param range_str A string do intervalo.
 * @param start_index Ponteiro para armazenar o índice inicial.
 * @param end_index Ponteiro para armazenar o índice final.
 * @return int 1 se o intervalo for válido, 0 caso contrário.
 */
int parseRange(const char *range_str, int *start_index, int *end_index) {
    char start_coord[10], end_coord[10];
    const char *dot_dot = strstr(range_str, "..");
    if (!dot_dot) return 0;

    // Copia a coordenada inicial
    int len_start = dot_dot - range_str;
    if (len_start >= 10) return 0;
    strncpy(start_coord, range_str, len_start);
    start_coord[len_start] = '\0';

    // Copia a coordenada final
    strcpy(end_coord, dot_dot + 2);

    *start_index = converteCoordenadaParaIndice(start_coord);
    *end_index = converteCoordenadaParaIndice(end_coord);

    return (*start_index != -1 && *end_index != -1);
}

/**
 * @brief Calcula o valor de uma célula, resolvendo recursivamente suas dependências.
 * 
 * @param linha A linha da célula.
 * @param coluna A coluna da célula.
 * @param planilha A matriz de células.
 * @param grafo A matriz de adjacência do grafo.
 * @return double O valor calculado da célula.
 */
double calculaValorCelula(int linha, int coluna, Celula planilha[LINHAS][COLUNAS], int grafo[NUM_CELULAS][NUM_CELULAS]) {
    char *formula = planilha[linha][coluna].formula;
    double valor = 0.0;

    if (formula[0] == '\0') {
        // Célula vazia
        valor = 0.0;
    } else if (formula[0] == '=') {
        // Referência a outra célula (ex: =B13)
        char ref_coord[10];
        strcpy(ref_coord, formula + 1);
        int ref_indice = converteCoordenadaParaIndice(ref_coord);
        if (ref_indice != -1) {
            int ref_linha = ref_indice / COLUNAS;
            int ref_coluna = ref_indice % COLUNAS;
            // Chamada recursiva para calcular o valor da célula referenciada
            valor = calculaValorCelula(ref_linha, ref_coluna, planilha, grafo);
        } else {
            printf("ERRO: Referência de célula inválida em %c%d\n", 'A' + coluna, linha + 1);
            valor = 0.0;
        }
    } else if (formula[0] == '@') {
        // Função (ex: @soma(B1..D2))
        char func_name[10];
        char range_str[50];
        int start_index, end_index;

        // Extrai o nome da função e o intervalo
        if (sscanf(formula + 1, "%[^(](%[^)])", func_name, range_str) == 2) {
            if (parseRange(range_str, &start_index, &end_index)) {
                double *valores = (double *)malloc(NUM_CELULAS * sizeof(double));
                int count = 0;

                // Itera sobre o intervalo (assumindo que start_index < end_index para simplificar)
                for (int i = start_index; i <= end_index; i++) {
                    int r = i / COLUNAS;
                    int c = i % COLUNAS;
                    // Calcula o valor de cada célula no intervalo
                    valores[count++] = calculaValorCelula(r, c, planilha, grafo);
                }

                if (count > 0) {
                    if (strcasecmp(func_name, "soma") == 0) {
                        valor = 0.0;
                        for (int i = 0; i < count; i++) valor += valores[i];
                    } else if (strcasecmp(func_name, "max") == 0) {
                        valor = valores[0];
                        for (int i = 1; i < count; i++) if (valores[i] > valor) valor = valores[i];
                    } else if (strcasecmp(func_name, "min") == 0) {
                        valor = valores[0];
                        for (int i = 1; i < count; i++) if (valores[i] < valor) valor = valores[i];
                    } else if (strcasecmp(func_name, "media") == 0) {
                        double soma = 0.0;
                        for (int i = 0; i < count; i++) soma += valores[i];
                        valor = soma / count;
                    } else {
                        printf("ERRO: Função desconhecida '%s' em %c%d\n", func_name, 'A' + coluna, linha + 1);
                        valor = 0.0;
                    }
                }
                free(valores);
            } else {
                printf("ERRO: Intervalo de função inválido em %c%d\n", 'A' + coluna, linha + 1);
                valor = 0.0;
            }
        } else {
            printf("ERRO: Sintaxe de função inválida em %c%d\n", 'A' + coluna, linha + 1);
            valor = 0.0;
        }
    } else {
        // Valor numérico
        valor = atof(formula);
    }

    // Armazena o valor calculado na célula
    planilha[linha][coluna].valor = valor;
    return valor;
}

/**
 * @brief Atualiza todos os valores da planilha, resolvendo as dependências.
 * 
 * @param planilha A matriz de células.
 * @param grafo A matriz de adjacência do grafo.
 */
void atualizaPlanilha(Celula planilha[LINHAS][COLUNAS], int grafo[NUM_CELULAS][NUM_CELULAS]) {
    printf("\n--- Atualizando Planilha ---\n");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            // Recalcula o valor de cada célula
            calculaValorCelula(i, j, planilha, grafo);
        }
    }
    printf("--- Atualização Concluída ---\n");
}

/**
 * @brief Processa a entrada do usuário, atualiza a fórmula da célula e o grafo de dependências.
 * 
 * @param entrada A string de entrada do usuário (ex: "A1 10").
 * @param planilha A matriz de células.
 * @param grafo A matriz de adjacência do grafo.
 * @return int 1 se a entrada foi processada com sucesso, 0 caso contrário.
 */
int processaEntrada(const char *entrada, Celula planilha[LINHAS][COLUNAS], int grafo[NUM_CELULAS][NUM_CELULAS]) {
    char coord_str[10];
    char formula_str[50];
    
    // Tenta extrair a coordenada e a fórmula/valor
    if (sscanf(entrada, "%s %s", coord_str, formula_str) != 2) {
        printf("ERRO: Formato de entrada inválido. Use: COORDENADA VALOR/FORMULA (ex: A1 10 ou B2 =A1)\n");
        return 0;
    }

    int indice_u = converteCoordenadaParaIndice(coord_str);
    if (indice_u == -1) {
        printf("ERRO: Coordenada de célula inválida: %s\n", coord_str);
        return 0;
    }

    int linha_u = indice_u / COLUNAS;
    int coluna_u = indice_u % COLUNAS;

    // 1. Limpar as dependências antigas (arestas de saída) no grafo
    for (int v = 0; v < NUM_CELULAS; v++) {
        grafo[indice_u][v] = 0;
    }

    // 2. Atualizar a fórmula da célula
    strcpy(planilha[linha_u][coluna_u].formula, formula_str);

    // 3. Analisar a nova fórmula e adicionar novas dependências (arestas de saída)
    if (formula_str[0] == '=') {
        // Dependência de célula única (ex: =B13)
        char ref_coord[10];
        strcpy(ref_coord, formula_str + 1);
        int indice_v = converteCoordenadaParaIndice(ref_coord);
        if (indice_v != -1) {
            grafo[indice_u][indice_v] = 1; // u depende de v (u -> v)
        }
    } else if (formula_str[0] == '@') {
        // Dependência de intervalo de células (ex: @soma(B1..D2))
        char func_name[10];
        char range_str[50];
        int start_index, end_index;

        if (sscanf(formula_str + 1, "%[^(](%[^)])", func_name, range_str) == 2) {
            if (parseRange(range_str, &start_index, &end_index)) {
                // Adiciona dependência para todas as células no intervalo
                for (int v = start_index; v <= end_index; v++) {
                    grafo[indice_u][v] = 1; // u depende de v (u -> v)
                }
            }
        }
    }
    
    // 4. Verificar se a nova dependência cria um ciclo
    limpaVisitados(planilha);
    if (buscaCiclo(indice_u, planilha, grafo)) {
        printf("ERRO: Ciclo detectado! A operação foi desfeita.\n");
        // Desfaz a operação (limpa a fórmula e as dependências)
        planilha[linha_u][coluna_u].formula[0] = '\0';
        for (int v = 0; v < NUM_CELULAS; v++) {
            grafo[indice_u][v] = 0;
        }
        return 0;
    }

    // 5. Se não houver ciclo, recalcula a planilha
    atualizaPlanilha(planilha, grafo);

    return 1;
}

// =================================================================================================
// Funções de Exibição
// =================================================================================================

/**
 * @brief Exibe a planilha na tela com os valores calculados.
 * 
 * @param planilha A matriz de células.
 */
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
