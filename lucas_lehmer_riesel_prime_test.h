//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE PRIMALIDADE DE LUCAS-LEHMER-RIESEL

/*
O ALGORITMO DE LUCAS-LEHMER-RIESEL É UM EFICIENTE TESTE DE PRIMALIDADE PARA NÚMEROS DA FORMA N=k(2^n)-1, COM k, n INTEIROS k<(2^n).
O TESTE ENVOLVE A SEQUÊNCIA RECURSIVA U(N)=U²(N-1)-2. SE U(N-2) = 0 (mod N) ENTÃO n É PRIMO. A DIFERENÇA DESTE TESTE PARA COM O TESTE DE 
LUCAS-LEHMER CONSISTE NA ESCOLHA DO TERMO INICIAL DA SEQUÊNCIA U(0).

PARA MAIORES REFERÊNCIAS: https://en.wikipedia.org/wiki/Lucas–Lehmer–Riesel_test
                          https://web.archive.org/web/20160306082833/http://folk.uib.no/nmaoy/papers/luc.pdf


*/ 


//**************************************************************************************************************************************************************
//CABEÇALHO
#ifndef LUCAS_LEHMER_RIESEL_PRIME_TEST_H
#define LUCAS_LEHMER_RIESEL_PRIME_TEST_H
#include"mod_bin_exponentiation128.h"
#include"jacobi_symbol.h"
#include<stdio.h>


//**************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void parameter_selection(int64_t*, int64_t);
void setup_initial_term(int64_t*, int64_t, int64_t, int64_t);
void lucas_lehmer_riesel_prime_test(int64_t, int64_t);

//**************************************************************************************************************************************************************
//FUNÇÕES

//Função que determina o parâmetro P usado para computar o termo inicial da sequência usada no algoritmo
void parameter_selection(int64_t* P, int64_t n){

 //Variáveis locais
 int64_t i;

 //Procedimentos
 for(i=4;;++i){
  if(jacobi((i-2), n)==1 && (jacobi((i+2), n)*(-1))==1)
   break;
              }


 //Resultado
 (*P)=i;

                                               };


//Função que determina o termo inicial da sequência usada no algoritmo de Lucas-Lehmer-Riesel
void setup_initial_term(int64_t* u0, int64_t P, int64_t k, int64_t N){

 //Variáveis locais
 __int128_t V0=2, V1=P, V2;
 int64_t i;

 //Procedimento

 //Loop principal
 for(i=2; i<k; ++i){

   V2=(((P*V1)%N)-(V0%N))%N;
  
   //Atualizando variáveis para a próxima iteração
   V0=(V1%N);
   V1=(V2%N);

                  };

 //Resultado
 (*u0)=V2;
                                                                     };


//Função que implementa o teste de primalidade de Lucas-Lehmer-Riesel
void lucas_lehmer_riesel_prime_test(int64_t multiplier, int64_t power){

 //Variáveis locais
 int64_t N=(multiplier*bin_pow(2, power))-1;//Número a ser testado
 int64_t P;
 int64_t u;
 int64_t i;


 //Procedimentos

 //Exibindo o número a ser testado
 printf("Número a ser testado: %li.\n", N);

 //Computado o parâmetro P
 if((multiplier%3)!=0)
  P=4;
 else
  parameter_selection(&P, N);

 //Computando o termo inicial da sequência
 if(multiplier==3 && ((power%4)==3 || (power%4)==0))
  u=5778;
 else
  setup_initial_term(&u, P, multiplier, N);

 //Loop principal
 for(i=0; i<(power-1); ++i)
   u=((u*u)-2)%N;




 //Resultado
 if(u==0)
  printf("%lu é primo.\n", N);
 else
  printf("%lu não é primo.\n", N);
                                                                      };

//**************************************************************************************************************************************************************
//FIM DO HEADER
#endif
