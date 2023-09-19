//VAMOS CRIAR ROTINAS PARA O CÁLCULO DE ALGUMAS FUNÇÕES ARITMÉTICAS RELACIONDAS A DECOMPOSIÇÃO DE UM NÚMERO EM FATORES PRIMOS

/*
FUNÇÕES ARITMÉTICAS SÃO FUNÇÕES DEFINIDAS NO CONJUNTO DOS NÚMEROS INTEIROS E QUE TEM COMO CONJUNTO IMAGEM UM SUBCONJUNTO DOS NÚMEROS COMPLEXOS.
FUNÇÕES MULTIPLICATIVAS E ADITIVAS POSSUEM A SEGUINTE PROPRIEDADES: DADO m E n RELATIVAMENTE PRIMOS, ISTO É, mmc(m,n)=1, f(mn)=f(m)f(n) OU f(mn)=f(m)+f(n) 
RESPECTIVAMENTE. SE A RESTRIÇÃO DE QUE m E n SEJAM COPRIMOS NÃO FOR NECESSÁRIA ENTÃO A FUNÇÃO f É CHAMADA DE COMPLETAMENTE ADITIVA E COMPLETAMENTE MULTIPLICATUVA.

FUNÇÕES ARITMÉTICA SÃO DE GRANDE IMPORTÂNCIA EM TEORIA DE NÚMEROS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Arithmetic_function


*/

//****************************************************************************************************************************************************************
//CABEÇALHO
#ifndef PRIME_DECOMPOSITION_H
#define PRIME_DECOMPOSITION_H
#include"euler_totient_function.h"
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>

//CONSTANTE GLOBAIS
#define ARITHMETIC_MAX 100000

//****************************************************************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
int64_t euclides_algorithm(int64_t, int64_t);
bool is_integer_prime(int64_t);
int64_t omega_function(int64_t);
int64_t capital_omega_function(int64_t);
int64_t p_adic_valuation(int64_t, int64_t);
int64_t arithmetic_derivative(int64_t);
double logarithmic_derivative(int64_t);
int64_t liouville_function(int64_t);

//****************************************************************************************************************************************************************
//FUNÇÕES

//********************************
//Funções auxiliares

//Função que implementa o algoritmo de Euclides
int64_t euclides_algorithm(int64_t a, int64_t b){
return gcd_euclides((uint64_t)a, (uint64_t)b);
                                                };

//Função que testa a primalidade de um númeiro inteiro
bool is_integer_prime(int64_t n){
//Casos triviais
if(n<2)
return false;
if(n==2 || n==3)
return true;
if((n%2)==0 || (n%3)==0)
return false;

//Variáveis locais
int64_t i, limit=sqrt(n);

//Loop principal 
for(i=5; i<limit; i+=6){
if((n%i)==0 || (n%(i+2))==0)
return false;
                       };
return true;
                                };


//********************************
//Funções de decomposição em fatores primos
//Função de contagem de fatores primos distintos (função ω)
int64_t omega_function(int64_t n){
//Caso trivial:
if(is_integer_prime(n))
return 1;

//Variáveis locais
int64_t limit=sqrt(n);
int64_t i=0, counter=0;
int64_t factor1=0, factor2=0;
//Procedimentos
//Caso base:
if(n<=ARITHMETIC_MAX){
//Contando fatores 2
if((n%2)==0)
counter++;

while((n%2)==0)
n/=2;

//Contando fatores ímpares
for(i=3; i<n; i+=2){
if((n%i)==0)
counter++;

while((n%i)==0)
n/=i;

if(n==1)
break;
                       };

//Resultado
return counter+1;
                     }

else{
factor1=limit;
for(;factor1<n; factor1++){
if((n%factor1)==0){
factor2=n/factor1;
if(euclides_algorithm(factor1,factor2)==1)
break;
                  };

                          };
//Resultado
return omega_function(factor1)+omega_function(factor2);

    };
                                 };

//Função de contagem de fatores primos (função Ω) 
int64_t capital_omega_function(int64_t n){
//Caso trivial:
if(is_integer_prime(n))
return 1;
//Variáveis locais
int64_t limit=sqrt(n);
int64_t i=0, counter=0;
int64_t factor1=0, factor2=0;
//Procedimentos
//Caso base:
if(n<=ARITHMETIC_MAX){
//Contando fatores 2
while((n%2)==0){
counter++;
n/=2;
               };

//Contando fatores ímpares
for(i=3; i<n; i+=2){
while((n%i)==0){
counter++;
n/=i;
               };
if(n==1)
break;
                       };

//Resultado
return counter+1;
                     }
else{
factor1=limit;
for(;factor1<n; factor1++){
if((n%factor1)==0){
factor2=n/factor1;
break;
                  };

                          };
//Resultado
return capital_omega_function(factor1)+capital_omega_function(factor2);
    };
                                         };

//Função que calcula o máximo expoente o qual um fator primo divide um número inteiro ν(p,n)
int64_t p_adic_valuation(int64_t n, int64_t prime){
//Variáveis locais
int64_t power_counter=0;
//Procedimento
while((n%prime)==0){
power_counter++;
n/=prime;
                   };
//Resultado
return power_counter;
                                                  };


//Derivada aritmética
int64_t arithmetic_derivative(int64_t n){
//Caso base
if(is_integer_prime(n)==true)
return 1;

//Chamada recursiva da função
//Variáveis locais
int64_t factor1=sqrt(n), factor2=0;

//Procedimentos
//Cálculo de fatores do número em questão
for(; factor1<n; factor1++){
if((n%factor1)==0){
factor2=n/factor1;
break;
                  };

                           };
//Resultado
return (factor1*arithmetic_derivative(factor2))+(factor2*arithmetic_derivative(factor1));
                                        };
//Derivada logarítmica
double logarithmic_derivative(int64_t n){
return (arithmetic_derivative(n)/n);
                                        };

//Função de Liouville λ
int64_t liouville_function(int64_t n){
//Variáveis locais
int64_t result=1;
//Resultado
if(capital_omega_function(n)&1)
return result*(-1);
else
return result;
                                     };


//****************************************************************************************************************************************************************
//FIM DO HEADER
#endif
