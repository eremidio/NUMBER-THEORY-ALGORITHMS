//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE BAILLIE-PSW PARA TESTAR A PRIMALIDADE DE UM NÚMERO INTEIRO

/*
O TESTE DE PRIMALIDADE BAILLIE-PSW É UM DOS TESTE DE PRIMALIDADE MAIS
IMPORTANTES EM TEORIA DE NÚMEROS. É UMA MISTURA DAS ABORDAGENS DO TESTE DE
MILLER-RABIN E DO TESTE DE LUCAS PARA PROVÁVEIS PRIMOS.

PARA MAIORES INFORMAÇÕES:
https://en.wikipedia.org/wiki/Baillie–PSW_primality_test
                          https://en.wikipedia.org/wiki/Lucas_pseudoprime#Strong_Lucas_pseudoprimes
                          https://medium.com/@shruti.singh20/primality-testing-algorithms-dbea1ff9f0c7

*/

//********************************************************************************************************************
// CABEÇALHO
#ifndef BAILLIE_PSW_PRIME_TEST_H
#define BAILLIE_PSW_PRIME_TEST_H
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include "jacobi_symbol.h"
#include "mod_bin_exponentiation128.h"


//********************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool small_prime_factor_test(uint64_t , uint64_t[]);
bool lucas_lehmer_test(uint64_t);
bool baillie_test(uint64_t);
bool lucas_problable_prime_test(int64_t, int64_t, int64_t, int64_t);
bool baillie_psw_test(uint64_t);

//********************************************************************************************************************
// FUNÇÕES
// Função que testa se um número é divisível por pequenos números primos, usaremos primos até 100
bool small_prime_factor_test(uint64_t n, uint64_t prime_seed[]) {
  // Loop principal
  for (int counter = 0; counter < 25; counter++) {
    if (n % prime_seed[counter] == 0) return false;
  };

  return true;
}

// Função que realiza o teste de Lucas Lehmer para a primalidade dos chamados números de Merssene da forma 2^p-1
bool lucas_lehmer_test(uint64_t n) {
  // Parte 1: obtendo o expoente
  // Checando se o número em questão é um número de Merssene
  uint64_t p = 7;  // Expoente
  uint64_t mersenne;
  while (true) {
    mersenne = bin_pow(2, p) - 1;
    if (mersenne == n)  // Expoente encontrado
      break;
    // Recursão
    if (mersenne < n) {
      p++;
      continue;
    };
    if (mersenne > n)  // O número em questão não é um número de Mersenne
      return false;    // Vai para o próxima etapa
  };

  // Parte2: O teste de Lucas - Lehmer.
  // A sequência de Lucas Lehmer é definida como: S(0)=4 e S(N)=S(N-1)^2-2.
  // Se S(N-1)= 0 mod(N)então o número de Mersenne em questão é primo

  // Variáveis locais
  uint64_t i;  // Variáveis de iteração
  __int128_t lucas_lehmer = 4;
  // Procedimentos
  for (i = 0; i < p - 2; ++i)
    lucas_lehmer = ((lucas_lehmer * lucas_lehmer) - 2) % mersenne;

  if (lucas_lehmer == 0)
    return true;
  else
    return false;
};

// Função que realiza o teste de Baillie para testar a primalidade de um número  primo
bool baillie_test(uint64_t n) {
  // Checando se o número em questão é um quadrado perfeito
  // Variáveis locais
  double sqrt_n = sqrt(n);
  uint64_t limit = round(sqrt_n);
  // Procedimentos
  if (floor(sqrt_n) - sqrt_n >= 0) return false;

  // Checando se o número de questão pode ser escrito como a diferença de quadrados, Variáveis locais
  uint64_t i;

  for (i = 1; i < limit; ++i) {
    if (n % (limit - i) == 0) {
      uint64_t factor1 = limit - i;
      uint64_t factor2 = n / factor1;
      if (factor1 != 1 && factor2 != 1) return false;
    };
  };
  return true;
};

// Teste de Lucas usando sequências de Lucas
bool lucas_problable_prime_test(int64_t n, int64_t D, int64_t P, int64_t Q){

    //Função auxiliar usada para redução binária dos coeficientes da sequência de Lucas
    int64_t div2mod(int64_t x, int64_t n) {
        if (x & 1) {
            return ((x + n) >> 1) % n;
        } else {
            return (x >> 1) % n;
        }
    }

  

    //Variáveis locais
    int64_t U = 1;
    int64_t V = P;
    int64_t k = n + 1;
    char digits[65];
    int index = 0;


    //Procedimentos
    //Calculando string binária de (n+1)
    while (k > 0) {
        digits[index++] = (k & 1) ? '1' : '0';
        k >>= 1;
    }
    digits[index] = '\0';


    for (int i = 0; i < index / 2; i++) {
        char temp = digits[i];
        digits[i] = digits[index - i - 1];
        digits[index - i - 1] = temp;
    }

    //Cálculando o (n+1)-ésimo termo da sequência de Lucas a menos de uma relação de congruência
    for (int i = 1; i < index; i++) {
        U = (U * V) % n;
        V = div2mod((V * V) + (D * U * U), n);

        if (digits[i] == '1') {
            int64_t newU = div2mod((P * U) + V, n);
            int64_t newV = div2mod((D * U) + (P * V), n);
            U = newU;
            V = newV;
        }
    }

    //Resultado
    if( U == 0) return true; //Condição de primalidade: U(n+1)= 0 (mod n)
    else return false;


}


//Função que implementa uma versão menos robusta do teste de primalidade de Baillie-PSW
bool baillie_psw_test(uint64_t n) {
  // Caso trivial primos inferiores a 100
  if (n < 2) return false;

  uint64_t prime_seed[25] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                             43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

  for (int counter = 0; counter < 25; counter++) {
    if (n == prime_seed[counter]) return true;
  };

  // Teste1: pequenos fatores primos
  if (small_prime_factor_test(n, prime_seed) == false) return false;

  // Teste 2: Teste de Lucas-Lehmer para números de Mersenne
  else if (lucas_lehmer_test(n) == true)
    return true;

  // Teste3: Realizando o teste de Baillie
  if (n < 1e16 && baillie_test(n) == false) return false;

  // Teste 4: Realizando teste de Fermat para primos inferiores a 100
  for (int counter = 0; counter < 25; counter++) {
    if (mod_bin_pow(prime_seed[counter], (n - 1), n) != 1) return false;
  };

  // Teste 5: Calculando o símbolo de Jacobi
  if ((jacobi(2, n) * jacobi(2, n)) != 1) return true;
  if ((jacobi(3, n) * jacobi(3, n)) != 1) return true;
  if ((jacobi(5, n) * jacobi(5, n)) != 1) return true;
  if ((jacobi(7, n) * jacobi(7, n)) != 1) return true;
  if ((jacobi(11, n) * jacobi(11, n)) != 1) return true;
  if ((jacobi(13, n) * jacobi(13, n)) != 1) return true;
  if ((jacobi(17, n) * jacobi(17, n)) != 1) return true;
  if ((jacobi(19, n) * jacobi(19, n)) != 1) return true;
  if ((jacobi(23, n) * jacobi(23, n)) != 1) return true;
  if ((jacobi(29, n) * jacobi(29, n)) != 1) return true;
  if ((jacobi(31, n) * jacobi(31, n)) != 1) return true;
  if ((jacobi(37, n) * jacobi(37, n)) != 1) return true;

  //Etapa 6.1:seleção de parâmetros para o teste da sequência de Lucas
    //Variáveis locais
    int64_t D=5;
    int64_t minus_D=(-7);
    int64_t P=1, Q;

    //Ajuste do parâmetro D e Q
    while(1){
      if(jacobi(D, n)==(-1)) break;
      else D+=4;
     
      if(jacobi_symbol_extension(minus_D, n)==(-1)){
        D=minus_D;
        break;
      }
      else minus_D-=4;

    }

    Q=(1-D)/4;
  

  // Teste 6.2: Teste PSW da sequência de Lucas
  if(lucas_problable_prime_test(n, D, P, Q)==false)
    return false;

  // Caso o número passe no testes acima, um primo foi encontrado
  return true;

};

//********************************************************************************************************************
// FIM DO HEADER
#endif
