//VAMOS CRIAR UM PROGRAMA QUE CALCULA O PRIMORIAL DE UM NÚMERO INTEIRO 

/*
O PRIMORIAL DE UM NÚMERO p, DENOTADOPOR #p É DEFINIDO COMO O PRODUTÓRIO DE TODOS OS NÚMEROS PRIMOS NO INTERVALO 1, ..., p.
O PRIMORIAL DE UM NÚMERO É DEFINIDO POR MEIO DAS SEGUINTES RELAÇÕES:
    { 1 SE p=0,1
p# ={ (p-1)#.p SE, p FOR PRIMO
    { (p-1)#, SE p FOR UM NÚMERO COMPOSTO

A FUNÇÃO PRIMORIAL APARECE EM IMPORTANTES IDENTIDADES ENVOVENDO OUTRAS FUNÇÕES IMPORTANTES EM TEORIA DE NÚMEROS COMO A FUNÇÃO
ZETA DE RIEMANN.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Primorial

*/


//***************************************************************************************************************
//CABEÇALHO
#ifndef PRIMORIAL_H
#define PRIMORIAL_H
#include<stdint.h>
#include<stdbool.h>
#include<math.h>

//***************************************************************************************************************
//FUNÇÕES
//Função que determina se um número é primo
bool is_prime(uint64_t n){
//Casos triviais
if(n<2)
return false;
if(n==2 || n==3)
return true;
if(n%2==0 || n%3==0)
return false;

//Loop principal
for(uint64_t i=5; i<sqrt(n); i+=6){
if((n%i)==0 || (n%(i+2))==0)
return false;
                                  };
return true;

                         };

//Função que calcula o primorial de um número
uint64_t primorial(uint64_t n){
//Caso trivial: 
if(n==0 || n==1)
return 1;

//Caso 1: n é primo
if(is_prime(n)==true)
return n*primorial(n-1);

//Caso 2: n não é primo
else
return primorial(n-1);
                              };

//***************************************************************************************************************
//FIM DO HEADER
#endif
