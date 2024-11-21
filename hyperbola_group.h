//VAMOS CRIAR UM PROBLEMA QUE IMPLEMENTA ROTINAS PARA O CÁLCULO DE PONTOS RACIONAIS EM UMA HIPÉRBOLE

/*
UMA HIPÉRBOLE UNITÁRIA É DEFINIDA PELA EQUAÇÃO x²-y²=1. QUANDO DEFINIDA NOM CONJUNTO DOS REAIS
ELA PODE SER PARAMETRIZADA PELA IDENTIDADES x=cosh(θ) E  y=senh(θ).

PODEMOS DEFINIR O GRUPO DE PONTOS COM COODERNADAS INTEIRAS DEFINIDAS SOBRE UMA HIPÉRBOLE 
QUALQUER USANDO O CONJUNTO DOS NÚMEROS PERPLEXOS: z=(x, y) OU EM NOTAÇÃO ALGÉBRICA z= x+yj,
ONDE j É A UNIDADE HIPERBÓLICA IMAGINÁRIA j²=1. A MULTIPLICAÇÃO DE DOIS INTEIROS É DEFINIDA
POR MEIO DA RELAÇÃO: (x, y) × (u, v) =(xu+yv, xv+yu) OU (x+yj)×(u+vj)=(xu+yv)+(xv+yu)j.

PARA FINS DE APLICAÇÕES NOS RESTRIGIREMOS A CORPOS FINITOS DO PRIMEIRO TIPO, INTEIROS A MENOS
DE UMA RELAÇÃO DE CONGRUÊNCIA.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Split-complex_number
                          https://en.wikipedia.org/wiki/Unit_hyperbola

*/



//*****************************************************************************************************************
//CABEÇALHO
#ifndef HYPERBOLA_GROUP_H
#define HYPERBOLA_GROUP_H
#include"tonelli_shanks.h"
#include<stdlib.h>
#include<time.h>

//*****************************************************************************************************************
//ESTRUTURAS USADAS 
struct hyperbola_point{
  
  int64_t x;
  int64_t y;
  int64_t p;

};


//*****************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
struct hyperbola_point hyperbola_pointwise_addition(struct hyperbola_point, struct hyperbola_point);
struct hyperbola_point hyperbola_pointwise_doubling(struct hyperbola_point);
struct hyperbola_point hyperbola_pointwise_scalar_multiplication(struct hyperbola_point, int64_t);
struct hyperbola_point set_unitary_hyperbola_point(int64_t);

//*****************************************************************************************************************
//FUNÇÕES
//Função que adiciona dois pontos em uma hipérbole unitária
struct hyperbola_point hyperbola_pointwise_addition(struct hyperbola_point p1, struct hyperbola_point p2){

  //Variáveis locais
  struct hyperbola_point p3;
  __int128_t t;

    //Procedimentos
      //Cálculo do resultado
      p3.p=p1.p;
      t=((p1.x*p2.x)%p3.p)+((p1.y*p2.y)%p3.p);  p3.x=t%p3.p;
      t=((p1.x*p2.y)%p3.p)+((p1.y*p2.x)%p3.p);  p3.y=t%p3.p;

  //Resultado
  return p3;

};


//Função queduplica um ponto em uma hipérbole unitária
struct hyperbola_point hyperbola_pointwise_doubling(struct hyperbola_point p1){

  //Variáveis locais
  struct hyperbola_point p2= hyperbola_pointwise_addition(p1, p1);

  //Resultado
  return p2;

};


//Função que calcula um múltiplo escalar de um ponto na hipébole unitária
struct hyperbola_point hyperbola_pointwise_scalar_multiplication(struct hyperbola_point p1, int64_t n){


  //Caso base: n<3
  if(n==0){
    struct hyperbola_point p2;
    p2.x=0; p2.y=0; p2.p=p1.p;
    return p2;
  }

  if(n==1) return p1;
  
  if(n==2){
    struct hyperbola_point p2= hyperbola_pointwise_doubling(p1);
    return p2;
  }
    

  //Variáveis locais
  struct hyperbola_point p3={0, 0, p1.p}, Q=p1, temp;

    //Procedimentos
      //Cálculo do resultado
      while(n>0){
      
        //Checando a paridade de n
        if(n&1){
          p3=hyperbola_pointwise_addition(p1, Q);
        }
  
        //Atualizando variáveis para a próxima iteração
        temp=hyperbola_pointwise_doubling(Q);
        Q=temp;
        n>>=1;

      }
  
  //Resultado
  return p3;

};


//Função que calcula um ponto não trivial em uma hipérbole unitária
struct hyperbola_point set_unitary_hyperbola_point(int64_t prime){
  
  //Semente para geração de números aleatórios
  srand(time(NULL));

  //Variáveis locais
  struct hyperbola_point p1;
  __int128_t t;
  int64_t x=0, y=0, x_squared;


  //Procedimentos
    //Calculando valores de x e y satisfazendo x²+y²=1
    while(y==0){

      y=rand()%prime;

      t=1+(y*y); 
      t%=prime;
      
      x_squared=t;
      x=tonelli_shanks(x_squared, prime);

    }


    //Ajuste do resultado final
    p1.x=x;
    p1.y=y;
    p1.p=prime;

  //Resultado
  return p1;

};

//*****************************************************************************************************************
//FIM DO HEADER
#endif
