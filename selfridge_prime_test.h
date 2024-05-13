//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE SELFRIDGE PARA TESTAR SE UM NÚMERO É PRIMO OU NÃO


/*
O TESTE DE SELFRIDGE É BASEADO EM UMA CONJECTURA QUE AFIRMA QUE UM NÚMERO p = 2,3 (mod 5)É PRIMO SE E SOMENTE SE:
1. f(p+1) = 0 mod(p). ONDE f(p+1) É O (p+1)-ÉSIMO NÚMERO NA SEQUÊNCIA DE FIBONACCI.
2. 2^(p-1)= 1 mod(p).

ESTE É UM REASULTADO AINDA NÃO COMPROVADO, EMBORA FUNCIONE RAZOALMENTE BEM EM CÁLCULOS PRÁTICOS, SENDO
RAZOÁVEL PARA GERAÇÃO DE NÚMEROS PRIMOS ELEVADOS DA ORDEM 10^100.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Primality_test#Heuristic_tests

*/


//****************************************************************************************************************************************************************
//CABEÇALHO
#ifndef SELFRIDGE_PRIME_TEST_H
#define SELFRIDGE_PRIME_TEST_H
#include"mod_bin_exponentiation128.h"
#include<stdbool.h>

//****************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void modular_fibonacci_number(uint64_t, uint64_t, uint64_t*, uint64_t*);
bool selfridge_prime_test(uint64_t);


//****************************************************************************************************************************************************************
//FUNÇÕES
//Função que calcula o n-ésimo número de Fibonacci a menos de uma relação de congruência
void modular_fibonacci_number(uint64_t n, uint64_t m, uint64_t* fn, uint64_t* fn1){

 //Caso base: n==0
 if(n==0){

  (*fn)=0;
  (*fn1)=1;
  return;

         };

 //Caso geral:n>0
  //Variáveis locais
  __int128_t a, b, c, d;
  
  //Procedimentos
   //Execução recursiva do algoritmo
   modular_fibonacci_number((n>>1), m, fn, fn1); 

   //Calculando os termos da sequência usando a fórmula de duplicação
   a=(*fn);
   b=(*fn1);

   c=(a*((b*2)-a))%m;
   d=(((a*a)%m)*((b*b)%m))%m;

   //Resultado da execução do algoritmo
   if(!(n&1)){

    (*fn)=c;
    (*fn1)=d;

               }

   else{
    (*fn)=d%n;
    (*fn1)=(c+d)%n;   
       };

                                                                                  };



//Função que executao teste de primalidade de Selfridge
bool selfridge_prime_test(uint64_t n){
  
 //Variáveis locais
 uint64_t mod_fibn, mod_fibn1;

 //Procedimentos
  //Teste 1: teste de Fermat na base 2
  if(mod_bin_pow(2, (n-1), n)!=1)
   return false;

  //Teste 2: teste da sequência de Fibonacci
  modular_fibonacci_number((n+1), n, &mod_fibn, &mod_fibn1);
  if(mod_fibn1>0)
    return false;

 //Caso passe nos testes acima um primo foi encontrado
 return true;
 
                                     };







//****************************************************************************************************************************************************************
//FIM DO HEADER
#endif
