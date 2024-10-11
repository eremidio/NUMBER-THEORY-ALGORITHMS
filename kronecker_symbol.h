// VAMOS CRIAR UM PROGRAMA QUE COMPUTA OS CHAMADOS SÍMBOLOS DE KRONECKER PARA INTEIROS

/*
OS SÍMBOLOS DE KRONECKER SÃO GENERALIZAÇÕES (EXTENSÕES) DOS SÍMBOLOS DE LEGENDRE
E DE JACOBI VÁLIDOS PARA TODOS OS NÚMEROS INTEIROS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Kronecker_symbol
                          Elementary Number Theory by Edmund Landau
                          A Course In Computational Algebraic Number Theory by Henri Cohen
                          https://acadsol.eu/en/articles/25/1/2.pdf

*/

//*****************************************************************************************************************************************************************
// CABEÇALHO
#ifndef KRONECKER_SYMBOL_H
#define KRONECKER_SYMBOL_H
#include<stdbool.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdio.h>

//*****************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES

int kronecker(int64_t, int64_t);

//*****************************************************************************************************************************************************************
// FUNÇÕES

// Função que calcula o símbolo de Kronecker (a|n)
int kronecker(int64_t a, int64_t b){

  //Variável global: resultado
  int k=1;


  //Casos bases
  if(!(a&1) && !(b&1)) return 0;
  else if(b==0 && (a*a)!=1) return 0;
  else if(b==0) return 1;
  if(b==1) return k;

  if(((-1)*b)==1){
    if(a>=0) return k;
    else return ((-1)*k);
  }

  if(b==2){
    if((a%8)==1 || (a%8)==7)
      return k;
    if((a%8)==3 || (a%8)==5)
      return (-1)*k;
    else
      return 0;
  };


  //Variáveis auxiliares
  int64_t a0=a, r;

  //Procedimentos
    //Ajuste de sinais: os dois argumentos devem ser positivos
    if(a<0){
      if(b<0){
        a*=(-1); b*=(-1); k*=(-1);
      }
      else a*=(-1);
    };

    if(b<0) b*=(-1); 

    //Ajuste da paridade do segundo termo
    while(!(b&1)){

      b>>=1;
      r=(a&7);
      if(r==3 || r==5) k*=(-1);

    };

    if(a0<0 && (b&3)==3) k*=(-1);


    //Loop principal
    while(a>0){
    
      //Checando a paridade do primeiro argumento
      while(!(a&1)){
        a>>=1;
        r=(b&7);
        if(r==3 || r==5) k*=(-1);
      }

      //Condição que determina o fim do loop
      if(a==1){
        b=1;
        break;
      }

      //Redução dos argumentos da função
      if(a<b){
        r=a; a=b; b=r;
        if((a&3)==3 && (b&3)==3) k*=(-1);
      }

      a=((a-b)>>1);
      r=(b&7);
      if(r==3 || r==5) k*=(-1);

    }; //Fim do loop principal


  //Resultado
  if(b==1) return k;
  else return 0;


};

//*****************************************************************************************************************************************************************
// FIM DO HEADER
#endif
