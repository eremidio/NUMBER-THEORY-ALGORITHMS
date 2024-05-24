//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA AS FUNÇÕES DE CONTAGEM E DE SOMA DE DIVISORES DE UM INTEIRO

/*
AS FUNÇÕES τ(n) E σ(n) QUE COMPUTAM RESPECTIVAMENTE O NÚMERO E A SOMA DOS DIVISORES DE UM INTEIRO SÃO FUNÇÕES ARITMÉTICAS
MULTIPLICATIVAS (ISTO É F(mn)=F(m)F(n), SE mdc(m,n)=1) DE GRANDE INTERESSE PRÁTICO EM TEORIA DOS NÚMEROS.

SEJA n= Π{p(i)^e(i)} A EXPANSÃO DE UM INTEIRO n EM FATORES PRIMOS. AS FUNÇÕES τ(n) E σ(n) PODEM SER FACILMENTE COMPUTADA PELAS
SEGUINTES FÓRMULAS:

τ(n) = Π{e(i)+1}.

σ(n)=Π{ {p(i)^[e(i)+1]} -1}/{p(i)-1}.

NESTAS FÓRMULAS i=1,2,... É O INDEX CORRESPODENTE A DISTINTOS FATORES PRIMOS DE n.

DE GRANDE INTERESSE TEÓRICO SÃO OS CHAMADOS NÚMEROS PERFEITOS, INTEIROS n TAIS QUE σ(n)=2n. DE ACORDO COM UMA PROPOSIÇÃO DE 
EUCLIDES SE (2^n)-1 FOR PRIMO (PRIMOS DE MERSENNE), ENTÃO [(2^n)-1](2^(n-1)) É UM NÚMERO PERFEITO.

PARA MAIORES INFORMAÇÕES: https://undergraduatemaths.wordpress.com/wp-content/uploads/2017/12/david_m-_burton_elementary_number_theory_seventbook4you.pdf
                          https://en.wikipedia.org/wiki/Perfect_number

*/


//******************************************************************************************************************
//CABEÇALHO
#ifndef DIVISORS_FUNCTIONS_H
#define DIVISORS_FUNCTIONS_H
#include"gauss_euler_primality_test.h"
#include<stdbool.h>
#include<math.h>
#include<stdio.h>


//******************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
int64_t gcd_df(int64_t, int64_t);
int64_t divisors_counting(int64_t);
int64_t sum_of_divisors(int64_t);
bool is_perfect_number(int64_t);

//******************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides
int64_t gcd_df(int64_t a, int64_t b){

  if(b==0)
    return a;
  else
    return gcd_df(b, (a%b));
                                    };

//Função que calcula a contagem de divisores de um inteiro
int64_t divisors_counting(int64_t n){

  //Casos triviais: n<3 ou n é primo
  if(n<=0)
    return (-1);//Erro
  if(n==1)
    return 1;
  if(n==2 || gauss_euler_primality_test(n)==true)
    return 2;


  //Caso geral
    //Variáveis locais
    int64_t factor1, factor2, i, limit=sqrt(n);
    int64_t result=0;

    //Procedimentos
      //Caso 1: n<5000
      if(n<5000){
      for(i=1; i<=n; ++i){
        if((n%i)==0)
         result++;
                         };
  
      //Resultado
      return result;
                };

      //Caso 2:n>5000
        //Encontrando fatores relativamente primos de um dado número
        for(i=2; i<limit; ++i){

        if(n%(limit-i)==0){

          factor1=limit-i;
          factor2=n/factor1;
          if(gcd_df(factor1, factor2)==1)
            break;

                         };

       if(n%i==0){
        factor1=i;
        factor2=n/factor1;
        if(gcd_df(factor1, factor2)==1)
          break;
                 };

                             };


      //Chamada recursiva da função
      return divisors_counting(factor1)*divisors_counting(factor2);


                                    };

//Função que calcula a soma de divisores de um inteiro
int64_t sum_of_divisors(int64_t n){

  //Casos triviais: n<3 ou n é primo
  if(n<=0)
    return (-1);
  if(n==1)
    return 1;
  if(n==2)
    return 3;
  if(gauss_euler_primality_test(n)==true)
    return (n+1);



  //Caso geral
    //Variáveis locais
    int64_t factor1, factor2, i, limit=sqrt(n);
    int64_t result=0;

    //Procedimentos
      //Caso 1: n<5000
      if(n<5000){
      for(i=1; i<=n; ++i){
        if((n%i)==0)
         result+=i;
                         };
  
      //Resultado
      return result;
                };

      //Caso 2:n>5000
        //Encontrando fatores relativamente primos de um dado número
        for(i=2; i<limit; ++i){

        if(n%(limit-i)==0){

          factor1=limit-i;
          factor2=n/factor1;
          if(gcd_df(factor1, factor2)==1)
            break;

                         };

       if(n%i==0){
        factor1=i;
        factor2=n/factor1;
        if(gcd_df(factor1, factor2)==1)
          break;
                 };

                             };


      //Chamada recursiva da função
      return sum_of_divisors(factor1)*sum_of_divisors(factor2);


                                  };


//Função que determina se um número é perfeito ou não
bool is_perfect_number(int64_t n){

  //Resultado
  if(sum_of_divisors(n)==(2*n))
    return true;
  else
    return false;
                                 };


//******************************************************************************************************************
//FIM DO HEADER
#endif
