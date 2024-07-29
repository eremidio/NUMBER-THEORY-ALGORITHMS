//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA AS  FUNÇÕES TOTIENTE DE JORDAN E DE CARMICHAEL

/*
A FUNÇÃO TOTIENTE DE JORDAN E A FUNÇÃO TOTIENTE DE CARMICHAEL SÃO GENERALIZAÇÕES DA FUNÇÃO TOTIENTE DE EULER.

A FUNÇÃO λ DE CARMICHAEL OU FUNÇÃO TOTIENTE REDUZIDA É DEFINIDA COMO O MENOR INTEIRO λ(n) TAL QUE TODOS OS
NÚMEROS COPRIMOS a COM n NO INTERVALO 2,..., (n-1); SATISFAZEM
A RELAÇÃO a^λ(n)=1 (mod n). 

O TEOREMA DE CARMICHAEL AFIRMA QUE PARA n= 8, 16, 32, 64, ..., (2^r) COM r>3 λ(n)=(1/2)φ(n). SE n=2, 4 OU
p^r COM p PRIMO E λ(n)=φ(n). SE n PUDER SER DECOMPOSTO EM FATORES PRIMOS DESTA NATUREZA
n=(p(1)^r(1))...(p(k)^r(k)), ENTÃO λ(n)=mmc(λ(p(1)^r(1)), ..., λ(p(n)^r(n))).

A FUNÇÃO TOTIENTE DE JORDAN É DEFINIDA PELA RELAÇÃO J(k, n)=(n^k)Π(1-(1/(p^k))).
A FUNÇÃO TOTIENTE DE JORDAN É UMA FUNÇÃO MULTIPLICATIVA DADO m E n COPRIMOS J(k, mn)=J(k, m)J(k, n).


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Carmichael_function
                          https://en.wikipedia.org/wiki/Dedekind_psi_function
                          https://en.wikipedia.org/wiki/Jordan%27s_totient_function

*/


//***********************************************************************************************************************
//CABEÇALHO
#ifndef TOTIENT_FUNCTIONS_H
#define TOTIENT_FUNCTIONS_H
#include"euler_totient_function.h"
#include<math.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

//***********************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
uint64_t carmichael_function(uint64_t);
uint64_t jordan_totient_function(uint64_t, uint64_t);
long double dedekind_psi_function(uint64_t, uint64_t);


//***********************************************************************************************************************
//FUNÇÕES
/*NOTA: Usaremos a função gcd_euclides definida no arquivo euler_totient_function.h*/
//Função totiente reduzida ou função λ de Carmichael
//NOTA: usaremos a função gcd_euclides definida no arquivo euler_totient_function.h
uint64_t carmichael_function(uint64_t n){

  //Caso trivial
  if(gauss_euler_primality_test(n)==true)
    return(n-1);

  //Caso geral
  //Variáveis locais
  uint64_t* coprime_array=NULL;
  uint64_t counter=0, i=1, j=0;
  uint64_t tester, exponent;
  uint64_t limit=sqrt(n);


  //Procedimentos
    //Calculando números coprimos com n
    for(tester=2; tester<n; ++tester){
      if(gcd_euclides(tester, n)==1){
        counter++;
        coprime_array=(uint64_t*)realloc(coprime_array, counter*sizeof(uint64_t));
          coprime_array[counter-1]=tester;

      };
    };



    //Calculando o expoente que satisfaz a definição da função λ
    for(; i<n; ++i){
      if(mod_bin_pow(coprime_array[0], i, n)==1){
        exponent=i;
        break;
      };
    };



    //Testando se o expoente encontrado satisfaz as relações de congruência
    pick:
      for(j=0; j<counter; j++){
        if(mod_pow(coprime_array[j], exponent, n)!=1){
          exponent++;
          goto pick;
        };
      };


  //Limpando o cachê de memória e  retornando um resultado
  free(coprime_array);
  return exponent;

                                        };

//Função totiente de Jordan J(k, n)
uint64_t jordan_totient_function(uint64_t k, uint64_t n){

  //Caso trivial:
  if(k==1) return euler_totient_function(n);

  //Chamada recursiva do algoritmo
  if(n>10000){

    //Variáveis locais
    uint64_t limit=sqrt(n), factor1=0, factor2=0;

    //Procedimentos
    factor1=limit;
    for(;factor1<n; factor1++){
      if((n%factor1)==0){
        factor2=n/factor1;
        if(gcd_euclides(factor1,factor2)==1)
      break;
    };
                          };

    //Resultado
    return jordan_totient_function(k, factor1)*jordan_totient_function(k, factor2);
  };


  //Caso base n<=10000
  //Variáveis locais
  __int128_t result=round(pow(n, k));
  uint64_t i=0;
 
  //Procedimentos
    //Cálculo do resultado
    if((n%2)==0){
      result*=round(pow(2, k)-1);
      result/=pow(2, k);
    };



    for(i=3; i<n; i+=2){
      if((n%i)==0){
        result*=round(pow(i, k)-1);
        result/=pow(i, k);
      };
    };


  //Resultado
  return result;

};

//Função Ψ de Dedekind
long double dedekind_psi_function(uint64_t k, uint64_t n){
  return jordan_totient_function((2*k),n)/(jordan_totient_function(k,n)*1.0);
};

//***********************************************************************************************************************
//FIM DO HEADER
#endif
