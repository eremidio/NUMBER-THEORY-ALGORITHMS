//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE EULER PARA FATORAR NÚMEROS INTEIROS


/*
O ALGORITMO DE EULER É UM ALGORITMO QUE PERMITE FATORAR NÚMEROS INTEIROS PROVIDO QUE PELO
DUAS REPRESENTAÇÕES VIA FORMAS QUADRÁTICAS DO TIPO n=x²+Dy², COM D>0 E mdc(D,n) SEJA 
POSSÍVEL. SUPONHA QUE (a,b) E (c,d) SEJAM DOIS PARES SATISFAZENDO A RELAÇÃO ACIMA PARA 
n=pq, COM p E q PRIMOS, ISTO É, n=a²+Db²=c²+Dd². TEMOS ENTÃO QUE OS FATORES PRIMOS DE n
SÃO DADOS POR mdc(n, ad+bc) E mdc(n, ad-bc).

O ALGORITMO BASEIA-SE NO FATO DE QUE É POSSÍVEL DEMONSTRAR QUE PRODUTOS DE NÚMEROS DA
FORMA r²+Ds², PODEM SER REESCRITOS NESSA FORMA POR MEIO DE UM REARRANJO NOS TERMOS DO 
PRODUTO. O ALGORITMO REQUER QUE O NÚMERO A SER FATORADO ADMITA DUAS REPRESENTAÇÕES DESSE
TIPO, O QUE NÃO É APLICÁVEL A TODO NÚMERO INTEIRO. UMA CONDIÇÃO NECESSÁRIA,PORÉM NÃO
SUFICIENTE PARA TAL, É QUE OS FATORES PRIMOS DE n COM EXPOENTE ÍMPAR SEJAM CLASSES 
RESIDUAIS QUADRÁTICAS MÓDULO -D.

PARA MAIORES INFORMAÇÕES: Prime Numbers And Computer Methods For Factorization, by Hans Riesel



*/

//**********************************************************************************************
//CABEÇALHO
#ifndef EULER_FACTORIZATION_METHOD_H
#define EULER_FACTORIZATION_METHOD_H
#include"prime_power_detection.h"
#include<stdio.h>

//**********************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t gcd_s64(int64_t, int64_t);
bool find_number_representatives(int64_t*, int64_t*, int64_t*, int64_t*, int64_t, int64_t);
void euler_factorization_method(int64_t);

//**********************************************************************************************
//FUNÇÕES 
//Função que implementa o algoritmo de Euclides para inteiros de 64 bits
int64_t gcd_s64(int64_t a, int64_t b){

  if(b==0) return a;
  else return gcd_s64(b, (a%b));

};


//Função que calcula os valores a, b, c, d que permitem escrever n=a²+Db²=c²+Dd²
bool find_number_representatives(int64_t* a, int64_t* b, int64_t* c, int64_t* d, int64_t n, int64_t D){

  //Variáveis locais
  bool first=false, second=false;
  int64_t x, y, x_square;


  //Procedimentos
    //Loop principal
    for(y=1; (y*y*D)<n; ++y){
      x_square=n-(D*y*y);
  
      if(fast_square_detection(x_square, &x)==true){
        if(first==false){
          (*a)=x; (*b)=y;
          first=true;
          continue;
                        }

        if(second==false){
          (*c)=x; (*d)=y;
          second=true;
          return true;
                         }
      }    

    }

  //Resultado
  return false;

};


//Função que implementa o algoritmo de Euler para fatorar números inteiros
void euler_factorization_method(int64_t n){

  //Variáveis locais
  int64_t D, a, b, c, d;
  int64_t factor1, factor2;


  //Procedimentos
    //Loop principal
    for (D=1; D<100; ++D){
      if(find_number_representatives(&a, &b, &c, &d, n, D)==true) break;
    }  

    //Caĺculo dos fatores primos
    factor1=gcd_s64(((a*d)-(b*c)), n);
    if(factor1==1 && factor1==n) factor1=gcd_s64(((a*d)+(b*c)), n);
    factor2=(n/factor1);
    
    printf("Fatores primos de %li encontrados: %li e %li\n", n, factor1, factor2);


};


//**********************************************************************************************
//FIM DO HEADER
#endif
