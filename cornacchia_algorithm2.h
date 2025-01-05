//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA VERSÃO MODIFICADA DO ALGFORITMO DE CORNACCHIA PARA RESOLVER A EQUAÇÃO DIOFANTINA
  // x²+|D|y² =(4p) COM p PRIMO D=0,1 (mod 4), |D|<4p


/*
PARA MAIORES INFORMAÇÕES: A Course In Computational Algebraic Number Theory by Henri Cohen

*/


//******************************************************************************
//CABEÇALHO
#ifndef MODIFIED_CORNACCHIA_ALGORITHM_H
#define MODIFIED_CORNACCHIA_ALGORITHM_H
#include"cornacchia_algorithm.h"
#include<assert.h>

//******************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void modified_cornacchia_algorithm(int64_t, int64_t, int64_t*, int64_t*);



//******************************************************************************
//FUNÇÕES
//Função que implementa a versão restrita do algortimo de Cornacchia
void modified_cornacchia_algorithm(int64_t D, int64_t prime, int64_t* x, int64_t* y){


  //Caso base
  if(prime==2){
    if(D=(-4)){
      (*x)=2; (*y)=1;
      return;
    }

    (*x)=0; (*y)=0;
    return;
  };

  //Restrições
  int64_t D_=D; while(D_<0) D_+=4;
  assert(D<0 && ((D_&3)==0 || (D_&3)==1) && (D*(-1))<(prime<<2));


  //Checando se (D|p)=1
  if(binary_jacobi(D, prime)==(-1)){
    (*x)=0; (*y)=0;
    return;
  };



  //Variáveis locais
  int64_t x0=(-1), a, b, l, r, c;


  //Procedimentos
    //Etapa 1: encontrando um valor de r0 tal que r0²=-d (mod m)
    D_=D;
    while(D_<0) D_+=prime;
    x0=tonelli_shanks(D_, prime);
    if((x0&1)!=(D&1)) x0=prime-x0;


    //Etapa 2: loop euclidiano
    stage2:    
      //Ajuste de variáveis
      a=(prime<<1); b=x0;
      l=floor(sqrt(prime)*2.0);

      //Loop euclideano
      while(b>l){
        r=(a%b);
        a=b; b=r;
      }

    //Etapa 3: cálculo dos resultados
    c=((prime<<2)-(b*b)); D_=D*(-1);
    if(c%D_!=0 || fast_square_detection((c/D_), &l)==false){
      (*x)=0; (*y)=0;
      return;
    }
    else{
      (*x)=b; (*y)=l;
    }


};

//******************************************************************************
//FIM DO HEADER
#endif
