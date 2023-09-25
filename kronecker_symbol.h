//VAMOS CRIAR UM PROGRAMA QUE COMPUTA OS CHAMADOS SÍMBOLOS DE KRONECKER PARA INTEIROS

/*
OS SÍMBOLOS DE KRONECKER SÃO GENERALIZAÇÕES (EXTENSÕES) DOS SÍMBOLOS DE LEGENDRE VÁLIDOS PARA TODOS OS NÚMEROS INTEIROS.
PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Kronecker_symbol

*/

//*****************************************************************************************************************************************************************
//CABEÇALHO
#ifndef KRONECKER_SYMBOL_H
#define KRONECKER_SYMBOL_H
#include"legendre_symbol.h"//Dependências necessárias estão inclusas
#include<stdio.h>

//*****************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool quick_prime_checking(int64_t);
int kronecker(int64_t, int64_t);

//*****************************************************************************************************************************************************************
//FUNÇÕES
//Função que testa se um número é primo
bool quick_prime_checking(int64_t n){
//Casos triviais
if(n<2)
return false;
if(n==2 || n==3)
return true;
if((n%2)==0 || (n%3)==0)
return false;

//Variáveis locais
uint64_t i, limit=sqrt(n);

//Procedimentos
//Loop principal com otimização 6k+1
for(i=5; i<limit; i+=6){
if((n%i)==0 || (n%(i+2))==0)
return false;
                       };

return true;
                                    };

//Função que calcula o símbolo de Kronecker (a|n)
int kronecker(int64_t a, int64_t n){
//Variáveis locais
int result=1;

//Casos triviais
//Números não relativamente primos
if(euclides_algorithm(a, n)>1)
return 0;

//n=2
if(n==2){
if((a%8)==1 || (a%8)==7)
return result;
if((a%8)==3 || (a%8)==5)
return (-1)*result;
        };

//n=0, 1, -1
if(n==0){
if((a*a)==1)
return result;
else
return 0;
        };

if(n==1)
return result;

if(n==(-1)){
if(a<0)
return (-1)*result;
else
return result;
           };

//n é primo
if(a>0 && n>0 && quick_prime_checking(n)==true)
return legendre((uint64_t)a, (uint64_t)n);

//Caso ambos sejam negativos
if(a<0 && n<0)
return (-1)*kronecker((-1)*a, (-1)*n);

//Caso a ou n negativo
if(a<0 && n>=0)
return kronecker((-1)*a, n);
if(a>=0 && n<0)
return kronecker(a, (-1)*n);

//Caso geral n é composto
if(quick_prime_checking(n)==false){
//Variáveis locais
int64_t n_=n;
int64_t i;
int64_t limit=sqrt(n);
int result=1;

//Procedimentos

//Fatores 2
while((n_%2)==0){
result*=kronecker(a, 2);
n_/=2;
                };

//Fatores ímpares
for(i=3; i<=limit; i+=2){
while((n_%i)==0){
result*=kronecker(a, i);
n_/=i;
                };

                            };

//Resultado
if(n_<=1)
return result;

//Caso o número em questão tenha um fator primo maior que n^(1/2)
if(n_>1)
return result*legendre(a, n_);

                                  };


                                       };

//*****************************************************************************************************************************************************************
//FIM DO HEADER
#endif
