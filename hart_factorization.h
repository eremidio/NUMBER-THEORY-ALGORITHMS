//VAMOS CRIAR UM PROGRAMA QUEEMPREGA O ALGORITMO DE FATORAÇÃO DE HART PARA FATORAR INTEIROS DE ATÉ 64 BITS

/*
O ALGORITMO DE HART É UMA APRIMORAMENTO DO ALGORTIMO DE FERMAT PARA FATORAR NÚMEROS INTEIROS.

PARA MAIORES INFORMAÇÕES: http://selmer.warwick.ac.uk/onelinefactor.pdf

*/


//***********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef HART_FACTORIZATION_H
#define HART_FACTORIZATION_H
#include<stdint.h>
#include<inttypes.h>
#include<stdbool.h>
#include<math.h>
#include<stdio.h>

//***********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t euclides_algorithm(int64_t, int64_t);
bool perfect_square_checker(int64_t);
void trial_division(int64_t*, int64_t);
void hart_factorization(int64_t);

//***********************************************************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides
int64_t euclides_algorithm(int64_t a, int64_t b){
if(b==0)
return a;
else
return euclides_algorithm(b, a%b);
                                                };

//Função que checa se um inteiro é quadrado perfeito
bool perfect_square_checker(int64_t n){
//Variáveis locais
int64_t odd=1;

//Procedimentos
//Loop principal
while(n>0){
n-=odd;
odd+=2;

//Resultado: o número não é quadrado perfeito
if(n<0)
return false;
          };

//Resultado: o número é quadrado perfeito
return true;
                                      };

//Função que performa tentativa por divisão até a raiz cúbica do número a ser fatorado
void trial_division(int64_t* n,int64_t cbrt_n){
//Variáveis locais
int64_t i;

//Procedimentos
//Fatores 2 e 3
while(((*n)%2)==0){
(*n)/=2;
printf("2, ");
                  };

while(((*n)%3)==0){
(*n)/=3;
printf("3, ");
                  };


//Loop principal
for(i=5; i<(cbrt_n+100); i+=6){
while(((*n)%i)==0){
(*n)/=i;
printf("%li, ", i);
                  };

while(((*n)%(i+2))==0){
(*n)/=(i+2);
printf("%li, ", (i+2));
                      };

                              };

                                               };

//Função que implementa o algoritmo de Hart
void hart_factorization(int64_t n){
//Variáveis locais
int64_t n_=n;
int64_t cbrt_n=cbrt(n_);
int64_t i, s, t, m, factor;

//Procedimentos
//Etapa 1: teste por divisão até a raíz cúbica do número a ser fatora do (caso o número em questão tenha mais de dois fatores primos)
trial_division(&n_, cbrt_n);

if(n_==1){
printf("...\n");
return;
         };

//Etapa 2: loop principal
for(i=1; i<n_; ++i){
s=sqrt(i*n_);
m=(s*s)%n;

if(perfect_square_checker(m)==true){
t=sqrt(m);

if(s>t){
factor = euclides_algorithm((s-t), n_);
break;
       }
else{
factor = euclides_algorithm((t-s), n_);
break;
    };
                                  };
                   };

//Printando o resultado da execução da segunda etapa do algoritmo na tela
printf("%li, %li, ...\n", factor, (n_/factor));

                                  };


//***********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
