//VAMOS CRIAR UM PROGRAMA QUE CALCULA A FUNÇÃO DE CONTAGEM DE PARTIÇÕES MULTIPLICATIVAS DE UM NÚMERO INTEIRO

/*

A FUNÇÃO DE CONTAGEM DE CONTAGEM DE PARTIÇÕES DE UM NÚMERO INTEIRO m(n) CONTABILIZAM DE QUANTAS FORMAS DISTINTAS
n PODE SER ESCRITA COMO UM NÚMERO INTEIRO PODE SER ESCRITO COMO O PRODUTO DE INTEIROS d≳2, DESCONSIDERANDO ORDEM
DOS FATORES. POR EXEMPLO:m(12)=4, POIS 2X2X3=2X6=3X4=12; m(30)=5, POIS 2X15=10X3=6X5=2X3X5=30.

A FUNÇÃO GERADORA DE m(n) É UMA SÉRIEDE DIRICHLET f(s)=Σm(n)/(n^s)=Π{1/[1-k^(-s)]}, COM n=1,2,... E k=2,3,...
IDENTIDADES OBTIDAS A PARTIR DA MANIPULAÇÃO FORMAL DESSA SÉRIE PERMITE CALCULAR m(n) RECURSIVAMENTE A PARTIR DOS
EXPOENTES NA DECOMPOSIÇÃO EM FATORES PRIMOS DE n.

PARA ALGUNS CASOS SIMPLES m(n) É FACILMENTE COMPUTÁVEL QUANDO n CONTÉM FATORES PRIMOS DISTINTOS m(n) É IGUAL AO 
n-ÉSIMO NÚMERO DE BELL B(n), PARA n PRIMO m(n)=1, PARA POTÊNCIAS DE NÚMEROS PRIMOS n=p^k, m(n)=p(k), ONDE p(k)
DENOTA A FUNÇÃO DE PARTIÇÃO ADITIVA USUAL.

NÃO EXISTE UM ALGORITMO EFICIENTE PARA COMPUTAR A FUNÇÃO DE CONTAGEM DE PARTIÇÕES MULTIPLICATIVAS. USAREMOS UMA 
ABORDAGEM DE FORÇA BRUTA CONSIDERANDO A LISTA COMPLETA DE DIVISORES DE UM NÚMERO E SUAS RESPECTIVAS
MULTIPLICIDADES, PARA AS FÓRMULAS PARA O CÁLCULO RECURSIVO DE m(n) VER ARTIGOS NAS REFERÊNCIAS.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Multiplicative_partition
                          https://chamberland.math.grinnell.edu/papers/multiplicative_partitions.pdf


*/ 


//*************************************************************************************************************************
//CABEÇALHO
#ifndef MULTIPLICATIVE_PARTITION_FUNCTION_H
#define MULTIPLICATIVE_PARTITION_FUNCTION_H
#include"divisors_functions.h"
#include"prime_power_detection.h"
#include"prime_decomposition.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//CONSTANTES GLOBAIS
int additive_partitions[33]={1, 1, 2, 3, 5, 7, 11, 15, 22, 30, 42, 56, 77, 101, 135, 176, 231, 297, 385, 490, 627, 792,
1002, 1255, 1575, 1958, 2436, 3010, 3718, 4565, 5604, 6842, 8349};

int64_t bell_numbers[25]={1, 1, 2, 5, 15, 52, 203, 877, 4140, 21147, 115975, 678570, 4213597, 27644437, 190899322,
  1382958545, 10480142147, 82864869804, 682076806159, 5832742205057, 51724158235372, 474869816156751, 4506715738447323,
  44152005855084346, 445958869294805289};


//*************************************************************************************************************************
//DECLARAÇÃO
bool is_square_factor_free(int64_t);
int32_t* generate_divisors_array(int32_t, int32_t*);
int64_t multiplicative_partition_function(int32_t);

//*************************************************************************************************************************
//FUNÇÕES
// Função que determina se um inteiro contém fatores primos repetidos
bool is_square_free(int64_t n) {

  // Variáveis locais
  int64_t i, limit = sqrt(n);

  // Procedimentos
    // Casos triviais
    if (n < 4) return true;

    // Fatores 2 e 3
    if ((n % 4) == 0) return false;
    if ((n % 9) == 0) return false;

    // Loop principal com otimização 6k+1
    for (i = 5; i < (limit + 2); i += 6) {
      if ((n % (i * i)) == 0) return false;
      if ((n % ((i + 2) * (i + 2))) == 0) return false;
    };

  // Caso passe nos testes acima
  return true;
};

//Função que calcula divisores de um número levando em conta a multiplicidade
int32_t* generate_divisors_array(int32_t n, int32_t* divisors_counter){

  //Variáveis locais
  int32_t* divisor_array=NULL;
  int32_t divisor_size=0, d=0;
  int step=(n&1)?2:1;
  int start=(n&1)?3:2;
  
  //Procedimentos
    //Loop principal
    for(int64_t i=start; i<n; i+=step){
      
      if(n%i==0){
        int32_t N=n;
        while(N%i==0){
          divisor_size++;
          divisor_array=(int32_t*)realloc(divisor_array, divisor_size*sizeof(int32_t));
          divisor_array[divisor_size-1]=i;
          N/=i;
        }
      }

    };

  //Resultado
  (*divisors_counter)=divisor_size; 
  return divisor_array;

};


// Função de comparação usada para ordenar as partições
int compare_ints(const void *a, const void *b) {
  return (*(int32_t*)a - *(int32_t*)b);
}

// Função que computa o número de partições multiplicativas de um inteiro
int64_t multiplicative_partition_function(int32_t n){

  // Caso base: n é primo
  if(gauss_euler_primality_test(n)) return 1;

  // Caso 2: n não contém fatores primos repetidos e possui até 24 divisores primos distintos
  if(is_square_free(n)){
    int64_t bell_index = omega_function(n);
    if(bell_index <= 24) return bell_numbers[bell_index];
  }

  // Caso 3: n é uma potência de um número primo
  int64_t prime;
  if(fast_prime_power_detection(n, &prime)){
    int p_adic_value = p_adic_valuation(n, prime);
    return additive_partitions[p_adic_value];
  }

  // Caso geral: n contém fatores primos repetidos

  // Variáveis locais
  int32_t divisor_counter = 0, t = 1, k = 1, bit_position = 0;
  int32_t* divisors_set = generate_divisors_array(n, &divisor_counter);
  uint64_t bit_setter = pow(2, divisor_counter); 
  int64_t result = 0;
  int32_t partitions[1000][divisor_counter];
  int64_t partition_count = 0;

  //Procedimnetos
    // Loop principal: iterando sobre os possíveis divisores de n
    for (uint64_t i = 0; i < bit_setter; ++i) {
   
      t = 1; k = i; bit_position = 0;
      int partition[divisor_counter]; // Array para armazenar a partição atual
      int partition_size = 0; // Tamanho da partição atual
    
      while (k > 0) {

        // Checa a paridade do bit
        if (k & 1) {
          t *= divisors_set[bit_position];
          partition[partition_size++] = divisors_set[bit_position];
        }

        // Atualiza as variáveis para a próxima iteração
        k >>= 1;
        bit_position++;        
        if (t >= n) break;
      }

      // Se o produto dos divisores for igual a n, verifica se a partição é única
      if (t == n) {

        // Ordena a partição para garantir que combinações repetidas sejam identificadas
        qsort(partition, partition_size, sizeof(int32_t), compare_ints);

        // Verifica se essa partição já existe na lista de partições
        int is_duplicate = 0;
        for (int j = 0; j < partition_count; ++j) {
          if (memcmp(partitions[j], partition, sizeof(int32_t) * partition_size) == 0) {
            is_duplicate = 1;
            break;
          }
        }

        // Se não for uma duplicata, adiciona à lista
        if (!is_duplicate) {
          memcpy(partitions[partition_count++], partition, sizeof(int32_t) * partition_size);
        }
      }
    }


    //Ajuste do resultado
    result = partition_count;

    // Libera o cache de memória
    if (divisors_set) free(divisors_set);
    divisors_set = NULL;


  // Retorna o resultado
  return result+1;

};


//*************************************************************************************************************************
//FIM DO HEADER
#endif
