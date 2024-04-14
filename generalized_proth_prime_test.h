//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE PROTH GENERALIZADO

/*
NÚMEROS DE PROTH TEM A FORMA n=k(2^r)+1, COM k ÍMPAR, r, k<(2^r) INTEIROS.
NÚMEROS DE PROTH GENERALIZADOS TEM A FORMA n=k(p^r)+1, COM p PRIMO.

O ALGORITMO IMPLEMENTADO AQUI ESTÁ DETALHADO NO ARTIGO: https://arxiv.org/pdf/1011.4836.pdf

O ALGORITMO EM QUESTÃO UTILIZA POLINÔMIOS CICLOTÔMICOS QUE PARA UM PRIMO p ASSUME UMA FORMA SIMPLES, O p-ÉSIMO POLINÔMIO CICLOTÔMICO É DADO POR:
Φ(p, x)=x^(p-1)+x^(p-2)+...+x^2+x

PARA MAIORES REFERÊNCIAS: https://en.wikipedia.org/wiki/Cyclotomic_polynomial

*/

//****************************************************************************************************************************************************
//CABEÇALHO
#if !defined GENERALIZED_PROTH_PRIME_TEST_H
#define GENERALIZED_PROTH_PRIME_TEST_H
#include"mod_bin_exponentiation128.h"
#include<stdbool.h>
#include<stdio.h>
#include<math.h>


//****************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t modular_prime_cyclotomic_polynomial(uint64_t , uint64_t, uint64_t);
void generalized_proth_prime_test(uint64_t, uint64_t, uint64_t, uint64_t);

//****************************************************************************************************************************************************
//FUNÇÕES

//Função que cálcula o p-ésimo polinômio ciclotômico a menos de uma congruência
uint64_t modular_prime_cyclotomic_polynomial(uint64_t prime, uint64_t number, uint64_t modulus){

 //Variáveis locais
 uint64_t result=0;
 uint64_t i;

 //Procedimentos

 //Loop principal
 for(i=(prime-1); i>=1; --i){
  uint64_t parcel=mod_bin_pow(number, i, modulus);
  result+=parcel;
                            };

 //Resultado
 return (result+1);
                                                                                               };


//Função que implementa o teste de primalidade para números de Proth generalizados
void generalized_proth_prime_test(uint64_t odd_k, uint64_t prime, uint64_t power, uint64_t witness){

 //Variáveis locais
 uint64_t N = (odd_k*bin_pow(prime, power))+1;//Número a ser testado
 uint64_t i, j;
 __int128_t S0, S1;

 //Procedimentos

 //Exibindo o número a ser testado
 printf("Número cuja primalidade: %lu\n", N);

 //Teste 1: checando se N é um possível pseudo primo para a base escolhida
 if((N%witness)==0){
  printf("%lu é composto.\n", N);
  return;
                   };

 S0=bin_pow(witness, odd_k);

 if((S0%N)==1){
  printf("%lu é forte candidato a primo em relação a base %lu\n", N, witness);
  return;
              };

 //Loop principal
 for(i=1; i<=power; ++i){

  S1=mod_bin_pow(S0, prime, N);

  if((S1%N)==1 && modular_prime_cyclotomic_polynomial(prime, (uint64_t)(S0), N)==0){
   j=i;
   goto prime_result;
                                                                                   };

  if((S1%N)==1 && modular_prime_cyclotomic_polynomial(prime, (uint64_t)(S0), N)!=0){
   printf("%lu é composto.\n", N);
   return;
                                                                                   };

  //Atualizando variáveis para próxima iteração
  S0=S1;


                        };


 //Resultado
 printf("%lu é composto.\n", N);
 return;


 //Resultado se primo:
 prime_result:
  if((2*j)<=((log(odd_k)/log(prime))+power)){
   printf("%lu é forte candidato a primo em relação a base %lu\n", N, witness);
   return;
                                            };

  if((2*j)>((log(odd_k)/log(prime))+power)){
   printf("%lu é primo.\n", N);
   return; 
                                           };
        
                                                                                                   };


//****************************************************************************************************************************************************
//FIM DO HEADER
#endif
