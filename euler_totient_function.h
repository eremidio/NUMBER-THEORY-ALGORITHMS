// VAMOS ESCREVER UM PROGRAMA PARA COMPUTAR A FUNÇÃO TOTIENTE DE EULER TAMBÉM
// CONHECIDA COMO FUNÇÃO φ DE EULER

/*
PARA UM ARGUMENTO n A FUNÇÃO φ(n) CONTABALIZA QUANTOS INTEIROS NO INTERVALO [1,
2, ..., n] SÃO RELATIVAMENTE PRIMOS COM n. ISTO É, DADO UM NÚMERO a NO INTERVALO
1, 2,..., n, φ(n) CONTABILIZA QUANTOS NÚMEROS SATISFAZEM A CONDIÇÃO mdc(a, n)=1.

A FUNÇÃO φ(n) É MULTIPLICATIVA: φ(n)φ(m)=φ(nm) SE n E m FOREM  RELATIVAMENTE
PRIMOS. PARA UM NÚMERO PRIMO p: φ(p)=p-1 (APENAS 1 É RELATIVAMENTE PRIMO COM n).

ESTA FUNÇÃO PODE SER DETERMINADA POR MEIO DE CONTAGEM DIRETA USANDO O ALGORITMO
DE EUCLIDES OU USANDO-SE A FÓRMULA DE EULER, QUE FAZ USO DE UM PRODUTÓRIO
ENVOLVENDO FATORES PRIMOS DE n.

PARA MAIORES
INFORMAÇÕES:https://en.wikipedia.org/wiki/Euler%27s_totient_function

*/

//*************************************************************************************************************************
// CABEÇALHO
#ifndef EULER_TOTIENT_FUNCTION_H
#define EULER_TOTIENT_FUNCTION_H
#include"gauss_euler_primality_test.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define PHI_MAX 250000


//*************************************************************************************************************************
// FUNÇÕES

// Função que implementa o algoritmo de Euclides para se calcular o mdc de dois
// inteiros
uint64_t gcd_euclides(uint64_t a, uint64_t b) {
  if (b == 0)
    return a;
  else
    return gcd_euclides(b, a % b);
};

// Função que detecta se um número é quadrado perfeito
bool perfect_square(uint64_t n) { return floor(sqrt(n)) - sqrt(n) >= 0; };

// Função que calcula um fator primo de um inteiro de 64 bits usando o algoritmo de Pollard-rho
uint64_t pollard_rho(uint64_t n){

  //Variáveis locais
  uint64_t remainder=1;
  uint64_t a=1, counter=0;
  uint64_t x=2, y=2;


  //Procedimentos
    //Testando inicialmente com x=2, y=2
    restart:
    while(remainder==1){
      x=((x*x+a)%n);
      y=((y*y+a)%n);
      y=((y*y+a)%n);

      if(x>y)
        remainder=gcd_euclides((x-y), n);
      if(x<y)
        remainder=gcd_euclides((y-x), n);

      if(remainder>1 && remainder<n) return remainder;


    //Atualizando variáveis
    counter++;
    if(counter>1e6){
      counter=0;
      a++;
                  };


    };

  return 0;//Caso de falha do algoritmo
                        
};

//Função que checa se um inteiro é da forma p^k com p primo e k inteiro
bool power_prime_detection(uint64_t n, uint64_t* prime,  uint64_t* power){


 //Variáveis locais
 uint64_t sqrt_n=sqrt(n); 

  //Procedimentos 
    //Caso particular números da forma 2^k e 3^k
    if(n%2==0){

      (*power)=0;
      while(n%2==0){
        n/=2;
        (*power)++;
                   }

      if(n==1){
        (*prime)=2;
        return true;
              }
      else
        return false;

    };

    if(n%3==0){

      (*power)=0;
      while(n%3==0){
        n/=3;
        (*power)++;
                   }

      if(n==1){
        (*prime)=3;
        return true;
              }
      else
        return false;

    };


    //Loop principal
    for(uint64_t i=5; i<=sqrt_n; i+=6){

      if(n%i==0){
        (*power)=0;
        while(n%i==0){
          n/=i;
          (*power)++;
                     }

          if(n==1){
            (*prime)=i;
            return true;
                  }
          else
            return false;
       };


    if((n%(i+2))==0){

        (*power)=0;
        while(n%(i+2)==0){
          n/=(i+2);
          (*power)++;
                         }

      if(n==1){
        (*prime)=(i+2);
        return true;
              }
      else
        return false;

    };
 
                                  };

 //Resultado
 return false;
  

};

// Função totiente para pequenos inteiros ≲250000
uint64_t totient_function_small_numbers(uint64_t n) {
  // Variáveis locais
  uint64_t counter = 0;
  uint64_t i;  // Variável de iteração

  // Procedimentos: contagem de direta de números coprimos usando o algoritmo de
  // Euclides
  for (i = 1; i < n; ++i) {
    if (gcd_euclides(i, n) == 1) ++counter;
  };

  return counter;
};

// Função totiente de Euler para números grandes (usamos a propriedade
// multiplicativa da função φ para ≲250000²)
uint64_t totient_function_large_numbers(uint64_t n) {
  // Variáveis locais
  uint64_t factor1, factor2, common;
  uint64_t limit = sqrt(n), prime, power;
  uint64_t i;  // Variável de iteração

  // Procedimentos
  // Caso 1: quadrados perfeitos
  if (perfect_square(n) == true)
    return totient_function_large_numbers(limit) * limit;

  // Caso 2: Números primos
  if (gauss_euler_primality_test(n)) return (n - 1);

  //Caso 3: potências de números primos
  if (power_prime_detection(n, &prime, &power)) return ( (prime-1) * bin_pow(prime,(power - 1) ) );

  // Caso 4: Encontrando fatores relativamente primos de um dado número
  factoring:
    factor1=pollard_rho(n);
    factor2=n/factor1;

    //Ajuste de fatores
    common=gcd_euclides(factor1, factor2);
    if(common>1){
      factor2/=common;
      factor1*=common;

    }    
    

  // Resultado
  if (factor1 > PHI_MAX && factor2 <= PHI_MAX)
    return totient_function_large_numbers(factor1) *
           totient_function_small_numbers(factor2);
  if (factor2 > PHI_MAX && factor1 <= PHI_MAX)
    return totient_function_large_numbers(factor2) *
           totient_function_small_numbers(factor1);
  if (factor2 < PHI_MAX && factor1 < PHI_MAX)
    return totient_function_small_numbers(factor2) *
           totient_function_small_numbers(factor1);
  else
    return totient_function_large_numbers(factor2) *
           totient_function_large_numbers(factor1);
};

// Função totiente de Euler
uint64_t euler_totient_function(uint64_t n) {
  if (n > PHI_MAX)
    return totient_function_large_numbers(n);
  else
    return totient_function_small_numbers(n);
};

//*************************************************************************************************************************
// FIM DO HEADER
#endif
