# torre de hanói

- 3 pinos
- 4 discos

## problema proposto

- criar grafo usando matriz de adjacência
- encontrar menor caminho para o resultado final usando o
algoritmo de dijskstra
- contabilizar o tempo gasto para encontrar a solução

## representação

- matriz com 3^4 posições = 81 posições = 81 configurações possíveis para a torre de hanói = 81 vértices no grafo
- cada vértice, posição da matriz, vai ter uma configuração representada por um vetor de 4 posições
    - indices = discos | valores de 0 à 2 = pinos