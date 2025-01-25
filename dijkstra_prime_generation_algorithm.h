// VAMOS CRIAR UM PROGRAMA QUE IMPLMENTA ALGORITMO DE DJIKSTRA PARA GERA NÚMEROS
// PRIMOS

/*
O ALGORITMO DE DIJKSTRA É UMA VARIANTE DA PENEIRA DE ERATÓSTENES USADO PARA
GERAR PRIMOS ATÉ UM DETERMINADO LIMITE.

O ALGORITMO USA UMA LISTA DE PARES ORDENADOS (p, p²) COM p PRIMO. POSSÍVEIS
CANDIDATOS A NÚMEROS PRIMOS r SÃO COMPARADOS COM O MENOR DOS VALORES DE p² QUE É
ENTÃO ATUALIZADO p²->p²+p SE r≲p², CONDIÇÃO QUE GARANTE A PRIMALIDADE DE r, O
PAR ORDENADO (r, r²) É ENTÃO ADICIONADO A LISTA. EM ESSÊNCIA ESTE ALGORITMO É
UMA REELABORAÇÃO DA PENEIRA DE ERATÓSTENES, PORÉM COM A VANTAGEM DE ECONOMIA DE
ESPAÇO.

PARA MAIORES INFORMAÇÕES:
https://wiki.tcl-lang.org/page/Dijkstra%27s+Prime+Algorithm
                          https://www.youtube.com/watch?v=fwxjMKBMR7s
                          https://mistral-7b.com/dijkstras-secret-method-for-discovering-prime-numbers/

*/

//*******************************************************************************************************************************************************************
// CABEÇALHO
#ifndef DIJKSTRA_PRIME_GENERATION_ALGORITHM_H
#define DIJKSTRA_PRIME_GENERATION_ALGORITHM_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//*******************************************************************************************************************************************************************
// ESTRTURAS USADAS NO ALGORITMO
struct prime_pair {
  int64_t prime;
  int64_t prime_square;
};

//*******************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
int64_t find_lowest_square(struct prime_pair[], int64_t);
void dijkstra_prime_generating_algorithm(int64_t);

//*******************************************************************************************************************************************************************
// FUNÇÕES
// Função que dado um valor r checa se existe algum elemento na lista de pares
// ordenados (p, p²)
int64_t find_lowest_square(struct prime_pair array[], int64_t array_size) {
  // Variáveis locais
  int64_t lowest = array[0].prime_square;
  int64_t index = 0;

  // Procedimentos
  // Loop sobre o array de primos computados
  for (int64_t i = 0; i < array_size; ++i) {
    if (array[i].prime_square < lowest) {
      lowest = array[i].prime_square;
      index = i;

      // TESTE USE UM // APÓS O MESMO
      // printf("(MENOR p²: %li)", lowest);
    };
  };

  // Resultado
  return index;
};

// Função que implementa o algoritmo de Dijkstra para gerar números primos
void dijkstra_prime_generating_algorithm(int64_t bound) {
  // Variáveis locais
  struct prime_pair* prime_pair_list = NULL;
  int64_t i, j, tester, array_size = 2;

  // Procedimentos
  // Lista de primos
  printf("Lista  de primos encontrados: 2, 3, ");

  // Adicionando os primeiros dois elementos a lista de pares ordenados
  prime_pair_list = (struct prime_pair*)realloc(prime_pair_list,
                                                2 * sizeof(struct prime_pair));
  prime_pair_list[0].prime = 2;
  prime_pair_list[0].prime_square = 4;
  prime_pair_list[1].prime = 3;
  prime_pair_list[1].prime_square = 9;

  // Loop principal
  for (i = 4; i < (bound + 1); i++) {
    tester = find_lowest_square(prime_pair_list, array_size);

    if (i == prime_pair_list[tester].prime_square) {
      for (j = 0; j < array_size; j++) {
        if (i == prime_pair_list[j].prime_square)
          prime_pair_list[j].prime_square += prime_pair_list[j].prime;
      };
    } else {
      array_size++;
      prime_pair_list = (struct prime_pair*)realloc(
          prime_pair_list, array_size * sizeof(struct prime_pair));
      prime_pair_list[array_size - 1].prime = i;
      prime_pair_list[array_size - 1].prime_square = (i * i);
      printf("%li, ", i);
    };
  };

  printf("...\n");

  // Liberando cachê de memória
  free(prime_pair_list);
};

//*******************************************************************************************************************************************************************
// FIM DO HEADER
#endif
