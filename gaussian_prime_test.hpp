//VAMOS CRIAR UM PROGRAMA PARA TESTAR A PRIMALIDADE DOS INTEIROS GAUSSIANOS

/*
OS INTEIROS GAUSSIANOS SÃO NUMEROS COMPLEXOS DA FORMA z=a+bi COM a, b INTEIROS. A NORMA DE UM INTEIRO GAUSSIANO É DEFINIDA COMO N(z)= a²+b². A NORMA É UMA FUNÇÃO
MULTIPLICATIVA, ISTO É, N(zw) = N(z)N(w). ELES FORMAM UM ANEL TAL QUAL O CONJUNTO DOS INTEIROS. MUITOS CONCEITOS E TEOREMAS DESENVOLVIDOS NO CONTEXTO DO CONUNTO DOS
NÚMEROS  INTEIROS PODEM SER GENERALIZADOS PARA O CONJUNTO DOS INTEIROS GAUSSIANOS.

USANDO A PROPRIEDADE MULTIPLICATIVA DA NORMA EXTENDER MUITOS DOS ALGORITMOS VÁLIDOS PARA NÚMEROS INTEIROS PARA O CONJUNTO DOS INTEIROS GAUSSIANOS COMO O ALGORITMO DE 
EUCLIDES.

UM INTEIRO GAUSSIANO É DITO SER PRIMO SE ELE NÃO PUDER SER EXPRESSO COMO O PRODUTO DE DOIS OU MAIS INTEIROS NÃO INCLUSO 1,-1, i, -i.
UM INTEIRO GAUSSIANO z=a+bi É PRIMO SE E SOMENTE UMA DAS SEGUINTES CONDIÇÕES FOR SATISFEITAS:
(i) SE a=0 OU b=0 ENTÃO SUA NORMA DEVE UM PRIMO p DA FORMA p = 3 (mod 4).
(ii) CASO  a E b SEJAM DIFRENTES DE 0, ENTÃO SUA NORMA DEVE SER UM PRIMO DA FORMA p = 1 (mod 4).

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Gaussian_integer


*/


//********************************************************************************************************************************************************
//CABEÇALHO
#ifndef GAUSSIAN_PRIME_TEST_H
#define GAUSSIAN_PRIME_TEST_H
#include"complex_numbers.hpp"
#include<stdint.h>
#include<cmath>

//********************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool gaussian_prime_test(complex<int64_t>);
bool is_integer_prime(int64_t);


//********************************************************************************************************************************************************
//FUNÇÕES
//Função que testa a primalidade de um númeiro inteiro
bool is_integer_prime(int64_t n){
  //Casos triviais
  if(n<2) return false;
  if(n==2 || n==3) return true;
  if((n%2)==0 || (n%3)==0)  return false;

  //Variáveis locais
  int64_t i, limit=std::sqrt(n);

  //Loop principal 
  for(i=5; i<limit; i+=6){
    if((n%i)==0 || (n%(i+2))==0)
      return false;
  };

  return true;
};


//Função que testa a primalidade de um inteiro Gaussiano
bool gaussian_prime_test(complex<int64_t> z){

  //Variáveis locais 
  int64_t gaussian_norm=(z.real*z.real)+(z.imag*z.imag);

  //Caso trivial: 2=(i-i)(i+i)= i(1-i)²
  if(z.real==2 && z.imag==0) return true;

  //Caso 1: o número em questão tem a parte real ou imaginária nula
  if(z.real==0 || z.imag==0){
    if(is_integer_prime(gaussian_norm)==true && (gaussian_norm%4)==3)
      return true;    
    else return false;
  }


  //Caso 2: as partes real e imaiginária são ambas não nulas
  else{
    if(is_integer_prime(gaussian_norm)==true && (gaussian_norm%4)==1)
      return true;
    else return false;
  };

};

//********************************************************************************************************************************************************
//FIM DO HEADER
#endif
