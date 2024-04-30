//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE PRIMALIDADE DE LUCAS PARA TESTAR A PRIMALIDADE DE INTEIROS DE 64 BITS

/*
O TESTE DE LUCAS CONSISTE EM UM ALGORITMO PARA PROVAR A PRIMALIDADE DE UM NÚMERO INTEIRO PRODUZINDO UM CERTIFICADO (CERTIFICADO DE PRATT) QUE ASSEGURA QUE O
NÚMERO EM QUESTÃO É PRIMO. O ALGORITMO SE BASEIA NA SEGUINTE PROPOSIÇÃO: DADO UM INTEIRO POSITIVO n, n É PRIMO SE E SOMENTE SE EXISTIR UM INTEIRO a, TAL QUE
1<a<n, a^(n-1)=1 (mod n) E PARA CADA FATOR PRIMO p DE (n-1) a^{(n-1)/p}≠1 (mod n).

ESTE É O MAIS SIMPLES DOS ALGORITMOS QUE SE BASEIAM NA ORDEM DE UM GRUPO PARA TESTAR A PRIMALIDADE DE UM INTEIRO E UMA VARIANTE DA SEGUINTE PROPOSIÇÃO GERAL:
DADO UM INTEIRO n E DOIS INTEIROS a, s,  TAL QUE a^s=1 (mod n) E PARA CADA DIVISOR PRIMO p DE s a^(s/p) ≠ 1 (mod n); SE s>n^(1/2) ENTÃO n É PRIMO.

ALGORITMOS MAIS MODERNOS USAM TÉCNICAS SIMILARES PARA REDUZIR A ORDEM DE GRANDEZAS DOS VALORES A SEREM TESTADOS PARA CHECAR A PRIMALIDADE DE UM NÚMERO.
ESTE É O CASO DOS ALGORITMOS DE CURVAS ELÍPTICAS E DO ALGORITMO DE POCKLINGTON (DIRETAMENTE LIGADO A ESTE PORÉM REQUERINDO APENAS UMA FATORAÇÃO PARCIAL DE
(n-1)). A PRIMALIDADE DE UM DADO INTEIRO É REDUZIDA A TESTES ENVOLVENDO NÚMEROS MENORES.

O SEGUINTE TEOREMA, UMA VARIANTE DA PROPOSIÇÃO ACIMA, PODE SER USADO PARA TESTAR DE FORMA SIMPLES A PRIMALIDADE DE UM INTEIRO n.

TEOREMA: SEJA n=2rq+1 UM INTEIRO ÍMPAR E q UM NÚMERO PRIMO. SE q≳(r-1)/2 e EXISTE UM INTEIRO a TAL QUE a^(n-1)=1 (mod n) E a^(2r) ≠ 1 (mod n), ENTÃO n É PRIMO.

O LIMITE PARA q NO TEOREMA ACIMA PODE SER REDUZIDO CONFORME A PROPOSIÇÃO ABAIXO:

TEOREMA: SEJA n=2rq+1 UM INTEIRO ÍMPAR E q UM NÚMERO PRIMO. SE q≳(r-2)/4 e EXISTE UM INTEIRO a TAL QUE a^(n-1)=1 (mod n) E a^(2r) ≠ 1 (mod n), ENTÃO: OU n É PRIMO
OU n=p² COM p=2q+1 PRIMO E a^(p-1)= 1 (mod p²).

USAREMOS O PRIMEIRO TEOREMA PARA TESTAR A PRIMALIDADE DE NÚMEROS INTEIROS SE (n-1) TIVER UM FATOR PRIMO DA ORDEM DE n^(1/2). COMBINANDO ESTE TEOREMA COM A  
PROPOSIÇÃO ORIGINAL DE LUCAS COBRE-SE TANTOS OS CASOS EM QUE (n-1) CONTÉM APENAS APENAS FATORES PRIMOS PEQUENOS, QUANTO OS CASOS EM QUE (n-1) CONTÉM UM FATOR PRIMO
SUFICIENTEMENTE GRANDE.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Pocklington_primality_test
                          https://en.wikipedia.org/wiki/Lucas_primality_test
                          Number Theoretical Algorithms in Criptography by O. N. Vasilenko
                          https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/order_primality_test.c


*/


//*********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef LUCAS_PRIMALITY_TEST_H
#define LUCAS_PRIMALITY_TEST_H
#include "mod_bin_exponentiation128.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

enum show_lucas_pratt_certificate { Verbose, Succint };



//*********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t* factor(uint64_t, uint64_t*, uint64_t*);
bool lucas_primality_test(uint64_t, enum show_lucas_pratt_certificate);

//*********************************************************************************************************************************************************************
//FUNÇÕES
//Função que aloca os fatores primos de (n-1) usando tentativa de divisão
uint64_t* factor(uint64_t n, uint64_t* factor_counter, uint64_t* prime_factor_list){

 //Variáveis locais
 uint64_t divisor_list[8]={7,11,13,17,19,23,29,31};
 uint64_t N=(n-1);
 uint64_t root=sqrt(N);
 int index=0;

 //Procedimentos

  //Busca por fatores: 2,3,5
  if((N%2)==0){

   index++;
   prime_factor_list=(uint64_t*)realloc(prime_factor_list, index*sizeof(uint64_t));
   prime_factor_list[index-1]=2;

   while((N%2)==0)
    N/=2;
   
              };

  if((N%3)==0){

   index++;
   prime_factor_list=(uint64_t*)realloc(prime_factor_list, index*sizeof(uint64_t));
   prime_factor_list[index-1]=3;

   while((N%3)==0)
    N/=3;
   
              };

  if((N%5)==0){

   index++;
   prime_factor_list=(uint64_t*)realloc(prime_factor_list, index*sizeof(uint64_t));
   prime_factor_list[index-1]=5;

   while((N%5)==0)
    N/=5;
   
              };


  //Busca por demais fatores primos até (n-1)^(1/2)
  while(1){

   for(int i=0; i<8; ++i){
    
    if((N%divisor_list[i])==0){

     index++;
     prime_factor_list=(uint64_t*)realloc(prime_factor_list, index*sizeof(uint64_t));
     prime_factor_list[index-1]=divisor_list[i];

     while((N%divisor_list[i])==0)
      N/=divisor_list[i];
   
                              };


                         };


   //Condições que determinam o fim da busca por fatores primos até (n-1)^(1/2)
   if(divisor_list[0]>root || N==1)
    break;


   //Atualizando a lista de possíveis divisores
   for(int j=0; j<8; ++j)
    divisor_list[j]=divisor_list[j]+30;

          };

  //Fatores primos superiores a (n-1)^(1/2)
  if(N>1){

   index++;
   prime_factor_list=(uint64_t*)realloc(prime_factor_list, index*sizeof(uint64_t));
   prime_factor_list[index-1]=N;

         };


  //Ajuste de variáveis
  (*factor_counter)=index;
  return prime_factor_list;

                                                                                   };




//Função que implementa o teste de primalidade de Lucas
bool lucas_primality_test(uint64_t n, enum show_lucas_pratt_certificate x){

 //Variáveis locais
 uint64_t prime_seed[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
 uint64_t* prime_factor_list=NULL;
 uint64_t* exponent_list=NULL;
 uint64_t factor_counter=0;
 uint64_t largest_prime_factor, r;
 int false_checks=0;
 bool result=false;


 //Procedimentos
  //Teste 1: busca por pequenos fatores primos
  for(int i=0; i<25; ++i){

   if(n==prime_seed[i]){
    result=true;
    goto end;
                       };


   if((n%prime_seed[i])==0){

    if(x==Verbose)
     printf("Fator de %lu encontrado: %lu\n", n, prime_seed[i]);

    goto end;
                           };

                         };


  //Etapa 2: cálculo dos fatores primos de (n-1) e dos respectivos quocientes de (n-1) por estes fatores
  prime_factor_list=factor(n, &factor_counter, prime_factor_list);

  exponent_list=(uint64_t*)realloc(exponent_list, factor_counter*sizeof(uint64_t));

  for(int j=0; j<factor_counter; ++j)
   exponent_list[j]=(n-1)/prime_factor_list[j];


  //Teste 3: Teste para casos em que (n-1)^(1/2) possui um fator primo da ordem de n^(1/2)
  largest_prime_factor=prime_factor_list[factor_counter-1];
  r=(n-1)/(2*largest_prime_factor);

  //Condição que determina a realização do teste
  if(largest_prime_factor>((r-1)/2)){
  r<<=1;
  

  for(int k=0; k<25; ++k){

   //Teste de Fermat para detecção de compostos
   if(mod_bin_pow(prime_seed[k], (n-1), n)!=1){

    if(x==Verbose)
     printf("\n%lu comprova a composição de %lu\n", prime_seed[k], n);
    goto end;

                                              };

   //Teste de primalidade envolvendo a ordem multiplicativa do grupo de inteiros a menos de uma congruência
   if(mod_bin_pow(prime_seed[k], r, n)!=1){

    result=true;
    if(x==Verbose){
     printf("\nRelatório de execução do algoritmo.\n");
     printf("%lu comprova a primalidade de %lu\n", prime_seed[k], n);
     printf("Maior fator primo de n-1=%lu: %lu\n",(n-1), largest_prime_factor);
                  };
    goto end;
                                          };

     
                         };


                                    };


  //Teste 3: teste de Lucas envolvendo a ordem multiplicativa do grupo de inteiro a menos de uma congruência se (n-1) é fatorado em pequenos fatores primos
  for(int l=0; l<25; l++){

   //Teste de Fermat para detecção de compostos
   if(mod_bin_pow(prime_seed[l], (n-1), n)!=1){

    if(x==Verbose)
     printf("\n%lu comprova a composição de %lu\n", prime_seed[l], n);
    goto end;

                                              };

   false_checks=0;//Ajuste variáveis   
    
   for(int m=0; m<factor_counter; ++m){

    if(mod_bin_pow(prime_factor_list[l], exponent_list[m], n)==1)
     false_checks++;
                                      }    
   
   //Condição de primalidade
   if(false_checks==0){

    result=true;

    if(x==Verbose){
     printf("\nRelatório de execução do algoritmo.\n");
     printf("%lu comprova a primalidade de %lu\n", prime_seed[l], n);
     printf("Lista de fatores primos de n-1=%lu: ", (n-1));
    
     for(int o=0; o<factor_counter; ++o)
      printf("%lu, ", prime_factor_list[o]);
     printf("...\n");

                  };
    goto end;

                      };


                        };

 //Resultado
 end:
  //Limpando o cachê de memória
  if(prime_factor_list)
   free(prime_factor_list);
  if(exponent_list)
   free(exponent_list);

  return result;
                                                                          };



//*********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
