//VAMOS CRIAR UM PROGRAMA PARA COMPUTAR OPERAÇÕES EM CÍRCULOS UNITÁRIOS EM CORPOS FINITOS DO PRIMEIRO TIPO 

/*
O GRUPO DE CÍRCULO UNITÁRIO, ORIGINALEMENTE DEFINIDO SOBRE OS REAIS CONSISTE NO CONJUNTO DE PONTOS NO PLANO
CARTESIANO P=(x,y) TAIS QUE x²+y²=1. PODEMOS RESTRINGIR GRUPO EM QUESTÃO A GRUPOS FINITOS DO PRIMEIRO TIPO
TOMANDO C={P=(x,y) | x²+y²=1 (mod p)} E DEFININDO A OPERAÇÃO DE ADIÇÃO DE PONTOS DE SIMILAR A OPERAÇÃO NO
GRUPO DO CÍRCULO UNITÁRIO (QUE É ISOMÓRFICO A U(1), NÚMEROS COMPLEXOS DE NORMA 1), ISTO É, DADOS DOIS
PONTOS P=(x,y) E Q=(u,v), P+Q=(xu-yv, xv+yu) (mod p). A ORDEM DO GRUPO ASSIM DEFINIDO É DADO POR
#C(p)=p-((-1)|p) (ONDE (|) DENOTA O SÍMBOLO DE KRONECKER/JACOBI).

GENERALIZAÇÕES DESTE GRUPO PARA ESFERAS DE DIMENSÃO 3 (HIPERESFERA) É POSSÍVEL E NESTE CASO DEFINIMOS
H={P=(x,y,z,w) | x²+y²+z²+w²=1 (mod p)}, A ORDEM DESSE GRUPO É #H=p³-p. A OPERAÇÃO DE MULTIPLICAÇÃO É
SIMILAR A MULTPLICAÇÃO DE QUATERNIÕES NESTE CASO.

PARA MAIORES INFORMAÇÕES: Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance


*/


//********************************************************************************************************
//CABEÇALHO
#ifndef CIRCLE_GROUP_H
#define CIRCLE_GROUP_H
#include"binary_jacobi_symbol.h"
#include"tonelli_shanks.h"
#include<stdlib.h>
#include<time.h>


//********************************************************************************************************
//ESTRUTURAS
struct circle_point{
  int64_t x;
  int64_t y;
  int64_t p;
};


//********************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
struct circle_point circle_pointwise_addition(struct circle_point, struct circle_point);
struct circle_point circle_pointwise_doubling(struct circle_point);
struct circle_point circle_pointwise_scalar_multiplication(struct circle_point, int64_t);
struct circle_point set_unitary_circle_point(int64_t);
int64_t unitary_circle_group_order(int64_t);

//********************************************************************************************************
//FUNÇÕES 
//Função que adiciona dois pontos em um círculo 
struct circle_point circle_pointwise_addition(struct circle_point p1, struct circle_point p2){

  //Variáveis locais
  struct circle_point p3;
  __int128_t t;

    //Procedimentos
      //Cálculo do resultado
      p3.p=p1.p;
      t=((p1.x*p2.x)%p3.p)-((p1.y*p2.y)%p3.p);  p3.x=t;
      t=((p1.x*p2.y)%p3.p)+((p1.y*p2.x)%p3.p);  p3.y=t;

  //Resultado
  return p3;
  
};


//Função que duplica um ponto

struct circle_point circle_pointwise_doubling(struct circle_point p1){

  //Variáveis locais
  struct circle_point p2= circle_pointwise_addition(p1, p1);

  //Resultado
  return p2;

};

//Função que computa um múltiplo escalar de um ponto no círculo
struct circle_point circle_pointwise_scalar_multiplication(struct circle_point p1, int64_t n){

  //Caso base: n<3
  if(n==0){
    struct circle_point p2;
    p2.x=0; p2.y=0; p2.p=p1.p;
    return p2;
  }

  if(n==1) return p1;
  
  if(n==2){
    struct circle_point p2= circle_pointwise_addition(p1, p1);
    return p2;
  }
    

  //Variáveis locais
  struct circle_point p3={0, 0, p1.p}, Q=p1, temp;

    //Procedimentos
      //Cálculo do resultado
      while(n>0){
      
        //Checando a paridade de n
        if(n&1){
          p3=circle_pointwise_addition(p1, Q);
        }
  
        //Atualizando variáveis para a próxima iteração
        temp=circle_pointwise_doubling(Q);
        Q=temp;
        n>>=1;

      }
  
  //Resultado
  return p3;

};

//Função que gera um ponto não trivial no círculo unitário
struct circle_point set_unitary_circle_point(int64_t prime){
  
  //Semente para geração de números aleatórios
  srand(time(NULL));

  //Variáveis locais
  struct circle_point p1;
  __int128_t t;
  int64_t x=0, y=0, y_squared;


  //Procedimentos
    //Calculando valores de x e y satisfazendo x²+y²=1
    while(y==0){

      x=rand()%prime;

      t=1-(x*x); 
      t+=(prime*prime);
      t%=prime;
      
      y_squared=t;
      y=tonelli_shanks(y_squared, prime);

    }


    //Ajuste do resultado final
    p1.x=x;
    p1.y=y;
    p1.p=prime;

  //Resultado
  return p1;

};


//Função que calcula o número de pontos no círculo
int64_t unitary_circle_group_order(int64_t prime){
  return (prime-binary_jacobi((-1), prime));
};

//********************************************************************************************************
//FIM DO HEADER
#endif
