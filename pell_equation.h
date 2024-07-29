//VAMOS CRIAR UM PROGRAMA QUE CALCULA A SOLUÇÃO FUNDAMENTAL DA EQUAÇÃO DE PELL USANDO FRAÇÕES CONTINUADAS

/*
USANDO CONVERGENTES DE EXPANSÃO EM FRAÇÕES CONTINUADAS DE √n É POSSÍVEL CALCULAR A SOLUÇÃO
FUNDAMENTAL DA EQUAÇÃO DE PELL x²-ny²=1, ISTO É, OS MENOS VALORES DE x, y QUE SATISFAZEM 
ESTA EQUAÇÃO.

TAL ALGORITMO É BASEADO NA SEGUINTE PROPOSIÇÃO: SEJA f(x,y)=x²-ny², COM n, x, y INTEIROS,
SE √n FOR IRRACIONAL, f(x,y)=0 SOMENTE SE (x, y)=(0,0).

PARA MAIORES INFORMAÇÕES: Introduction to Modern Number Theory, by Yuri I. Manin and Alexei A. Panchishkin
                          Prime numbers and computer methods for factorization,by Hans Riesel.

*/ 


//********************************************************************************************************
//CABEÇALHO
#ifndef PELL_EQUATION_H
#define PELL_EQUATION_H
#include<math.h>
#include<stdint.h>
#include<stdlib.h>
#include<inttypes.h>
#include<stdio.h>

//********************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void pell_equation(int64_t);

//********************************************************************************************************
//FUNÇÕES
//Função que calcula a solução fundamental da equação de Pell usando convergentes da fração continuada de √n
void pell_equation(int64_t n){

  //Variáveis locais
  int64_t A0, A1, A2;
  int64_t B0, B1, B2;
  int64_t Q0, Q1, R0, R1, P0, P1, a;
  int64_t root=(int64_t)sqrt(n);
  //Procedimentos
    //Caso trivial: n é quadrado perfeito
    if(root*root==n){
      printf("\n\n Solução fundamental da equação x²-%liy²=1: x=0, y=0\n", n);
      return;
    }

    //Ajuste inicial de variáveis
    A0=0; A1=1; B0=1; B1=0;
    R0=0; P0=0; Q0=1;

    //------------------------------------------
    printf("i                    A(i)                    B(i)\n");
    printf("-------------------------------------------------\n");

  
    //Loop principal
    for(int64_t i=0; ; ++i){
      //Cálculo dos convergentes de √n
      if(i==0) P1=0;
      else P1=root-R0;
      if(i==0) Q1=1;
      else Q1=(n-P1*P1)/Q0;
      a=(P1+root)/Q1;

      A2=a*A1+A0;
      B2=a*B1+B0;
      if(i==0) R1=0;
      else R1=(P1+root)%Q1;

      //Teste se uma solução da equação fundamental foi encontrada
      if((A2*A2-n*B2*B2)==1) goto show_result;
      if(A2<0 || B2<0){
        printf("O algoritmo falhou\n");
        return;
      }
      
      //Exibindo o resultado
      printf("%li                            %li                              %li\n", i, A2, B2);




      //Atualizando variáveis para a próxima iteração
      A0=A1; A1=A2; B0=B1; B1=B2;
      Q0=Q1; R0=R1; 


    }

  
  //Resultado da execução do algoritmo
  show_result:
  printf("\n\n Solução fundamental da equação x²-%liy²=1: x=%li, y=%li\n", n, A2, B2);


};


//********************************************************************************************************
//FIM DO HEADER
#endif
