//VAMOS CRIAR UM PROGRAMA QUE RESOLVE EQUAÇÕES DIONFANTINAS SOBRE O CORPO DOS NÚMEROS INTEIROS PARA DUAS E TRÊS VARIÁVEIS

/*

EQUAÇÕES DIOFANTINAS LINEARES TEM A FORMA: Σa(i)x(i)=b, COM b, a INTEIROS E i=1,2,3,...
DE GRANDE INTERESSE TEÓRICO É O CÁLCULO DE SOLUÇÕES INTEIRAS PARA EQUAÇÕES DESTE TIPO.

*/


//******************************************************************************************************************************
//CABEÇALHO
#ifndef LINEAR_DIOFANTINE_EQUATION_H
#define LINEAR_DIOFANTINE_EQUATION_H
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>
#include<stdio.h>

//******************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void linear_diofantine_equation(int64_t, int64_t, int64_t);
void linear_diofantine_equation2(int64_t, int64_t, int64_t, int64_t);

//******************************************************************************************************************************
//FUNÇÕES
//Função que resolve equações diofantinas lineares sobre os inteiros em duas variáveis ax+by=c
void linear_diofantine_equation(int64_t a, int64_t b, int64_t c){

  //Ajuste dos coeficientes da equação
  if(b>a){
    int64_t temp=a;
    a=b;
    b=temp;
         };

  //Variáveis locais
  int64_t x, y, diff=0, counter=0;


  //Procedimentos 
    //Exibindo a equação a ser resolvida
    printf("Soluções inteiras da equação: %lix+%liy=%li: \n", a, b,c);

    //Loop principal
    for(x=1; (a*x)<=c; ++x){
    
      diff=(c-(a*x));
      if(diff%b==0 && diff>=0){
        y=diff/b;
        counter++;
        printf("x=%li, y=%li\n", x, y);
                              };

                           };



   //Resultado de execução do algoritmo caso não haja soluções
   if(counter==0)
    printf("Não existe solução inteiras para a equação: %lix+%liy=%li: \n", a, b, c);

    printf("+++++++++++++++++++++++++++++++++\n");
                                                                };

//Função que calcula soluções da equação diofantina linear em três variáveis ax+by+cz=d
void linear_diofantine_equation2(int64_t a, int64_t b, int64_t c, int64_t d){

  //Variáveis locais
  int64_t z;



  //Procedimentos 
    //Exibindo a equação a ser resolvida
    printf("Soluções inteiras da equação: %lix+%liy+%liz=%li: \n", a, b, c, d);

    //Redução da equação em três variáveis para uma equação de duas variáveis
    for(z=1; (c*z)<=d; ++z){
      printf("z=%li ------> redução da equação original:\n", z);
      linear_diofantine_equation(a, b, (d-(c*z)));


                           };

    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
                                                                            };

/*
NOTA: O PROCEDIMENTO ACIMA PODE SER GENERALIZADO PARA N VARIÁVEIS, BASTA DEFINIR UM ARRAY DE VARIÁVEIS x[0], x[1], ETC E 
      REDUZIR A EQUAÇÃO EM UMA VARIÁVEL ATÉ OBTER O CASO MAIS SIMPLES ILUSTRADO ACIMA DE DUAS OU TRÊS VARIÁVEIS.

*/



//******************************************************************************************************************************
//FIM DO HEADER
#endif
