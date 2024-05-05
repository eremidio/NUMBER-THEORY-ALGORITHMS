//VAMOS ESCREVER UM PROGRAMA PARA COMPUTAR A FUNÇÃO TOTIENTE DE EULER TAMBÉM CONHECIDA COMO FUNÇÃO φ DE EULER

/*
PARA UM ARGUMENTO n A FUNÇÃO φ(n) CONTABALIZA QUANTOS INTEIROS NO INTERVALO [1, 2, ..., n] SÃO RELATIVAMENTE PRIMOS COM n.
ISTO É, DADO UM NÚMERO a NO INTERVALO 1, 2,..., n, φ(n) CONTABILIZA QUANTOS NÚMEROS SATISFAZEM A CONDIÇÃO mdc(a, n)=1.

A FUNÇÃO φ(n) É MULTIPLICATIVA: φ(n)φ(m)=φ(nm) SE n E m FOREM  RELATIVAMENTE PRIMOS.
PARA UM NÚMERO PRIMO p: φ(p)=p-1 (APENAS 1 É RELATIVAMENTE PRIMO COM n).

ESTA FUNÇÃO PODE SER DETERMINADA POR MEIO DE CONTAGEM DIRETA USANDO O ALGORITMO DE EUCLIDES OU USANDO-SE A FÓRMULA DE EULER, QUE FAZ USO DE UM PRODUTÓRIO ENVOLVENDO FATORES PRIMOS DE n.

PARA MAIORES INFORMAÇÕES:https://en.wikipedia.org/wiki/Euler%27s_totient_function

*/

//*************************************************************************************************************************
//CABEÇALHO
#ifndef EULER_TOTIENT_FUNCTION_H
#define EULER_TOTIENT_FUNCTION_H
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<math.h>

#define PHI_MAX 500000

//Limite máximo: 9223372036854775807

//*************************************************************************************************************************
//FUNÇÕES

//Função que implementa o algoritmo de Euclides para se calcular o mdc de dois inteiros
uint64_t gcd_euclides(uint64_t a, uint64_t b){
if(b==0)
return a;
else
return gcd_euclides(b, a%b);
                                             };

//Função que detecta se um número é quadrado perfeito
bool perfect_square(uint64_t n){
return floor(sqrt(n))-sqrt(n)>=0;
                               };

//Função que calcula se um número é primo ou não
bool is_prime(uint64_t n){

 //Casos triviais
  //0,1
  if(n<=1)
   return false;

  //Primos menores que 100
  uint64_t prime_seed[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
  
  for(int p=1; p<25; ++p){

    if(n==prime_seed[p])
     return true;
    if((n%prime_seed[p])==0)
     return false;

                         };

  
 //Caso geral:
  //Variáveis locais
  uint64_t sqrt_n =sqrt(n);

  //Procedimento: loop sobre possíveis divisores usando uma otimização 30k+1

  for(uint64_t i=30; i<(sqrt_n+1); i+=30){

    if((n%(i+1))==0 || (n%(i+7))==0 || (n%(i+11))==0 || (n%(i+13))==0 || (n%(i+17))==0 || (n%(i+19))==0 || (n%(i+23))==0 || (n%(i+29))==0)
     return false;

                                        };

  return true;
                         };


//Função totiente para pequenos inteiros ≲250000
uint64_t totient_function_small_numbers(uint64_t n){

 //Variáveis locais
 uint64_t counter=0;
 uint64_t i;//Variável de iteração


 //Procedimentos: contagem de direta de números coprimos usando o algoritmo de Euclides
 for(i=1; i<n; ++i){
  if(gcd_euclides(i, n)==1)
  ++counter;
                  };

 return counter;
                                                  };


//Função totiente de Euler para números grandes (usamos a propriedade multiplicativa da função φ para ≲250000²)
uint64_t totient_function_large_numbers(uint64_t n){


 //Variáveis locais
 uint64_t factor1, factor2;
 uint64_t limit=sqrt(n);
 uint64_t i;//Variável de iteração

 //Procedimentos
  //Caso 1: quadrados perfeitos
  if(perfect_square(n)==true)
   return totient_function_large_numbers(limit)*limit;

  //Caso 2: Números primos
  if(is_prime(n))
   return (n-1);
 

  //Caso 3: Encontrando fatores relativamente primos de um dado número
  for(i=2; i<limit; ++i){

   if(n%(limit-i)==0){

    factor1=limit-i;
    factor2=n/factor1;
   if(gcd_euclides(factor1, factor2)==1)
    break;

                   };

   if(n%i==0){
    factor1=i;
    factor2=n/factor1;
   if(gcd_euclides(factor1, factor2)==1)
    break;
             };


                      };


 //Resultado
 if(factor1>PHI_MAX && factor2<=PHI_MAX)
  return totient_function_large_numbers(factor1)*totient_function_small_numbers(factor2);
 if(factor2>PHI_MAX && factor1<=PHI_MAX)
  return totient_function_large_numbers(factor2)*totient_function_small_numbers(factor1);
 else
  return totient_function_small_numbers(factor2)*totient_function_small_numbers(factor1);
                                                   };


//Função totiente de Euler
uint64_t euler_totient_function(uint64_t n){

 if(n>PHI_MAX)
  return totient_function_large_numbers(n);
 else
  return totient_function_small_numbers(n);
                                           };

//*************************************************************************************************************************
//FIM DO HEADER
#endif
