//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO CANGURU (λ) DE POLLARD PARA O CÁLCULO DE LOGARITMO DISCRETO

/*
O ALGORITMO CANGURU (λ) DE POLLARD PARA O CÁLCULO DE LOGARITMO DISCRETO USA DUAS SUBSEQUÊNCIAS {x(0), ..., x(N)} E {y(0), y(1), ...} PARA O CÁLCULO DO
LOGARITMO DISCRETO. DADO UM GRUPO CÍCLICO G DE ORDEM n, COM UM GERADOR g E UM ELEMENTO h O OBJETIVO É DETERMINAR UM x TAL QUE g^x=g*...*g=h. 

O ALGORITMO USA UMA FUNÇÃO QUE GERA NÚMEROS PSEUDOALETÓRIOS f:G->S, ONDE S É UM CONJUNTO PRÉ-DEFINIDO PARA DETERMINAR UMA RELAÇÃO DO TIPO g^a=h(g^b) QUE
IMPLICA NA RELAÇÃO h=g^(b-a), UMA DAS SEQUÊNCIAS É INICIALIZADA COM O VALOR y(0)=h. ESTE ALGORITMO É PARTICULARMENTE ÚTIL PARA SE DETERMINAR LOGARITMOS 
DISCRETOS EM UM DADO INTERVALO [a, (a+1), ... , (b-1), b], INCLUINDO O INTEVALO {0, 1, ..., (n-1)} QUE ABRANGE OS POSSIVEIS VALORES.

PARA MAIORES INFORMAÇÕES: https://link.springer.com/content/pdf/10.1007/s001450010010.pdf
                          https://en.wikipedia.org/wiki/Pollard%27s_kangaroo_algorithm#

*/

//********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef POLLARD_KANGAROO_LOGARITHM_H
#define POLLARD_KANGAROO_LOGARITHM_H
#include"mod_bin_exponentiation128.h"
#include<stdbool.h>
#include<stdio.h>

//********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t pseudo_randomwalk(int64_t, int64_t, int64_t, int64_t);
int64_t pollard_kangaroo_logarithm(int64_t, int64_t, int64_t);

//********************************************************************************************************************************************************************
//FUNÇÕES
//Função que gera uma sequência de números pseudoaleatórias
int64_t pseudo_randomwalk(int64_t x, int64_t g, int64_t h, int64_t N){

 //Variáveis locais
 int64_t remainder=(x%3);
 __int128_t result;

 //Resultado
 switch(remainder){
  case 0:
   result =((x*x)%N);
   break;

  case 1:
   result =((x*g)%N);
   break;
 case 2:
   result=((x*h)%N);
   break;
                 };

  return result;
                                                                     };


//Função que implementa o algoritmo Canguru (λ) de Pollard
int64_t pollard_kangaroo_logarithm(int64_t g, int64_t h, int64_t N){


 //Variáveis locais
 int64_t result;
 int64_t x0=mod_bin_pow(g, (N-1), N);
 int64_t d=pseudo_randomwalk(x0, g, h, N);
 int64_t n=h*100;
 int64_t x1, x2, xn;
 int64_t y0=h;
 int64_t ds=pseudo_randomwalk(y0, g, h, N);
 int64_t y1, y2;


 //Procedimentos
 //Cálculo da sequência  {x(0), ..., x(N)} (Canguru domesticado)
  //1ª iteração
  x1=x0;
  x2=((x1%N)*mod_bin_pow(g, pseudo_randomwalk(x1, g, h, N), N))%N;
  d+=pseudo_randomwalk(x2, g, h, N);
  x1=x2;//Atualização das variáveis para a próxima iteração


  //Demais iterações
  for(int64_t i=1; i<n; ++i){
   x2=((x1%N)*mod_bin_pow(g, pseudo_randomwalk(x1, g, h, N), N))%N;
   d+=pseudo_randomwalk(x2, g, h, N);
   x1=x2;//Atualização das variáveis para a próxima iteração
                          };


 //Ajuste de variável de controle
 xn=mod_bin_pow(g, (d+N-1), N);
 y0=h;
 ds=0;
 y1=y0;



  //Loop principal

   //Cálculo da sequência  {y(0), y(1), ...} (Canguru selvagem)
   while(true){

  //Condições que determinam o fim do loop principal do algoritmo
  //Caso de falha
  if(ds>(N-1+d)){
   printf("O algoritmo não encontrou o logaritmo de %li (mod %li) na base %li\n", h, g, N);
   return (-1);
                } ;

  //Caso de sucesso na execução do algoritmo
  if(y2==xn){
   result=(N-1+d-ds);
   break;
            };


   //Cálculo dos elementos na sequência
   y2=((y1%N)*mod_bin_pow(g, pseudo_randomwalk(y1, g, h, N), N))%N;
   ds+=pseudo_randomwalk(y1, g, h, N);
   y1=y2;//Atualização das variáveis para a próxima iteração
  
          };


 //Resultado
 return result;
                                                                   };

//********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
