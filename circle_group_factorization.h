//VAMOS CRIAR UM PROGRAMA PARA FATORAR INTEIROS DE 64 BITS USANDO O GRUPO DO CÍRCULO UNITÁRIO EM CORPOS FINITOS DO PRIMEIRO TIPO

/*
O PRESENTE ALGORITMO FUNCIONADE MODO SIMILAR AO ALGORITMO DE FATORAÇÃO DE CURVAS ELÍPTICAS,
COMPUTANDO MÚLTIPLOS DE PONTOS EM UM CÍRCULO UNITÁRIO.

PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/circle_group.h
                          https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/elliptic_curve_factorization.hpp

*/


//*******************************************************************************************
//CABEÇALHO
#ifndef CIRCLE_GROUP_FACTORIZATION_H
#define CIRCLE_GROUP_FACTORIZATION_H
#include"circle_group.h"
#include"prime_power_detection.h"
#include<stdio.h>


//*******************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t gcd_s64(int64_t, int64_t);
struct circle_point set_initial_point(int64_t);
void circle_group_factorization(int64_t, int64_t);

//*******************************************************************************************
//FUNÇÕES
//Função que calcula omdc de dois inteiros de 64 bits
int64_t gcd_s64(int64_t a, int64_t  b){

  if(b==0) return a;
  else return gcd_s64(b, (a%b));

};


//Função que calcula um ponto no círculo unitário
struct circle_point set_initial_point(int64_t n){

  //Semente parageração de nmúmeros
  srand(time(NULL));
  
  //Variáveis locais
  struct circle_point p1;
  __int128_t t;
  int64_t x=0, y=0, y_squared;
  int64_t root=sqrt(n);

  //Procedimentos
    //Gerando valores x e y que satifazem a relação x²+y²=1 (mod n)
      x=2+rand()%n;
      if(x>n) x%=n;
  
      //Loop  principal
        while(1){
          t=1-(x*x); t+=(n*n); t%=n;
          y_squared=t;
          if(fast_square_detection(y_squared, &y)==true) break;
          else x++;
          if(x==n) break;
          
        }

    //Ajuste do resultado final
    p1.x=x;
    p1.y=y;
    p1.p=n;

  //Resultado
  return p1;

};


//Função que fatora número inteiro usando o grupo de círculo unitário
void circle_group_factorization(int64_t n, int64_t ord){

  
  //Variáveis locais
  struct circle_point p1, p2;
  __int128_t t1=1, t2=1, t3=1;
  int64_t factor=1, xn=1, yn=1, zn=1;
  int trials=0;

  //Procedimento
    //Selecionando um ponto inicial no círculo unitário
    restart:
    p1=set_initial_point(n);

    //Cálculando múltiplos deste pontos
    for(int64_t i=1; i<=ord; ++i){

      p2=circle_pointwise_scalar_multiplication(p1, i);
      t1=(t1*p2.x)%n; t1--; xn=t1;
      t2=(t2*p2.y)%n; t2--; yn=t2;
  
      factor=gcd_s64(n, xn);
      if(factor>1 &&  factor<n) break;
      factor=gcd_s64(n, yn);
      if(factor>1 &&  factor<n) break;

    }  

    //Resultado da execução do algoritmo
    if(factor>1 &&  factor<n){
      printf("Fatores de %li encontrados: %li e %li\n", n,  factor, (n/factor));
      return;
    }
    else printf("O algoritmo falhou!\n");

};


//*******************************************************************************************
//FIM DO HEADER
#endif
