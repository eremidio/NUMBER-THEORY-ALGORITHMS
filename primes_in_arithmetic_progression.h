//VAMOS CRIAR UM PROGRAMA PARA CALCULAR A FUNÇÃO DE CONTAGEM DE PRIMOS EM PROGRESSÕES ARITMÉTICAS π(a, b; x)

/*

A FUNÇÃO π(a, b; x) COMPUTA O NÚMERO DE PRIMOS INFERIORES A x QUE SATISFAZEM A RELAÇÃO DE CONGRUÊNCIA p = a (mod b). UM TEOREMA PROVADO POR
DIRICHLET (E GENERALIZAÇÕES DESTE COMO O TEORIEMA DE SIEGEL-WALFIZS) AFIRMA QUE SE mdc(a, b)=1, HÁ INFINITOS NÚMEROS PRIMOS SATISFAZENDO A
RELAÇÃO DE CONGRUÊNCIA ACIMA. O TEOREMA DE DIRICHLET PROVÊ A SEGUINTE FÓRMULA ASSINTÓTICA PARA A FUNÇÃO MODULAR DE CONTAGEM DE NÚMEROS
PRIMOS: π(a, b; x) ~ x/[ln(x)φ(b)] ONDE φ(b) É A FUNÇÃO TOTIENTE DE EULER.


PARA MAIORES REFERÊNCIAS: https://en.wikipedia.org/wiki/Dirichlet%27s_theorem_on_arithmetic_progressions
                          https://en.wikipedia.org/wiki/Bombieri%E2%80%93Vinogradov_theorem
                          https://en.wikipedia.org/wiki/Siegel%E2%80%93Walfisz_theorem
                          https://math.stackexchange.com/questions/2841676/asymptotic-formula-of-modular-prime-counting-function
                          https://en.wikipedia.org/wiki/Green%E2%80%93Tao_theorem
                          https://mathworld.wolfram.com/ModularPrimeCountingFunction.html
                          https://arxiv.org/html/2412.14594v2#S10
                          https://empslocal.ex.ac.uk/people/staff/mrwatkin/zeta/sousa_2020_sigma.pdf
                          https://mathworld.wolfram.com/PrimeQuadraticEffect.html
                          https://mathworld.wolfram.com/ChebyshevBias.html

*/


//************************************************************************************************************************************************
//CABEÇALHO
#ifndef PRIMES_IN_ARITHMETIC_PROGRESSION_H
#define PRIMES_IN_ARITHMETIC_PROGRESSION_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include"euler_totient_function.h"


//************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool* fill_prime_array_sieve(int64_t);
double modular_prime_function_approximation(int64_t, int64_t);
int64_t modular_prime_function_exact(int64_t, int64_t, int64_t, bool[]);


//************************************************************************************************************************************************
//FUNÇÕES
//Função que computa um array de números primos usando o crivo de Eratóstenes
bool* fill_prime_array_sieve(int64_t n){

  //Variáveis locais
  int64_t x = 0, y = 0, marker = 0;
  const int prime_seed[10] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29}; //Primos inferiores a 30
  const int remainder_seed[8] = {1,  7,  11, 13, 17, 19, 23, 29}; //Possíveis resíduos módulo 30 de um número primo superior a 30
  bool* number_array = (bool*)calloc((n + 1), sizeof(bool));

  //Procedimentos
    //Marcando os primos na lista inferiores a 30
    for (x = 0; x < 10; x++) {
      marker = prime_seed[x];
      number_array[marker] = true;
    };

    //Inicializando os membros da lista usando uma roda 30k+r:
    for (x = 1;; x++) {
      for (y = 0; y < 8; y++) {
        marker = 30 * x + remainder_seed[y];
        number_array[marker] = true;
        if (marker > n) break;
      };

      if (marker > n) break;
    };

    //Descartando múltiplos de primos até a raíz quadrada do limite superior
    for (x = 7; (x * x) <= n; x += 2) {
      if (number_array[x] == true) {
        for (y = (x * x); y <= n; y += x) number_array[y] = false;
      };
    };


  //Resultado
  return number_array;

};


//Função que computa um valor aproximado da função modular de contagem de primos π(a, b; x)
double modular_prime_function_approximation(int64_t x, int64_t b){

  //Resultado
  return (x*1.0)/(log(x)*euler_totient_function(b));

};


//Função que computa um valor exato da função modular de contagem de primos π(a, b; x)

/*

  NOTA: Usaremos a peneira de Eratóstenes para computar números primos até um determinado limite.

*/
int64_t modular_prime_function_exact(int64_t n, int64_t a, int64_t b, bool prime_array[]){

  //Restrição: a, b devem ser coprimos
  if(gcd_euclides(a, b)>1)
    return 0;


  //Variáveis locais
  int counter=0;

  
  //Procedimento
    //Loop principal
    for(int64_t i=a; i<=n; i+=b){
      if(prime_array[i]==true)
        counter++;
    }


  //Resultado
  return counter;

};


//************************************************************************************************************************************************
//FIM DO HEADER 
#endif

