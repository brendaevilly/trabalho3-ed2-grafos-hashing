# Torre de Hanói

- 3 pinos
- 4 discos

## Problema proposto

- Criar grafo usando matriz de adjacência
- Encontrar menor caminho para o resultado final usando o
Algoritmo de Dijskstra
- Contabilizar o tempo gasto para encontrar a solução

## Representação

- **Discos e pinos correspondentes**
    - vetor de inteiros de tamanho 4, com valores posívei (1 - pino 1; 2 - pino 2; 3 - pino 3)
    - posicao 0: menor disco (topo); posicao 3: maior disco (base)
    - número de configurações possíveis = 3^4 = 81 = número de vértices do grafo = número de linhas e colunas da matriz de adjacência