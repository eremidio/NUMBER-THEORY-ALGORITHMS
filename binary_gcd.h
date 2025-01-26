//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UM ALGORITMO DE EUCLIDES USANDO OPERADORES BITWISE  

/*
O ALGORITMO DE EUCLIDES PODE SER OTIMIZADO BASEANDO-SE NAS SEGUINTES PROPOSIÇÕES FACILMENTE DEMONSTRÁVEIS:
1. SE a E b SÃO AMBOS PARES mdc(a, b) = 2.mdc(a/2, b/2)
2. SE a FOR ÍMPAR E b FOR PAR mdc(a, b) = mdc(a, b/2)
3. SE a E b SÃO AMBOS ÍMPARES mdc(a, b) = mdc((a-b)/2, b)

PARA MAIORES INFORMAÇÕES: https://bjpcjp.github.io/pdfs/math/number-theory-ITA.pdf

*/


//*************************************************************************************************************************
//CABEÇALHO
#ifndef BINARY_GCD_H
#define BINARY_GCD_H
#include<stdint.h>

//*************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t fast_euclides_algorithm(uint64_t , uint64_t);

//*************************************************************************************************************************
//FUNÇÕES
//Algoritmo de euclides usando operações binárias
uint64_t fast_euclides_algorithm(uint64_t a, uint64_t b){
  
  //Variáveis locais
  int bit_shift=0;

  //Procedimentos
    //Caso trivial
    if(b==a || b==0)
      return a;
    if(a==0)
      return b;


    //Invertendo os argumentos da função se a<b
    if(a<b){
      uint64_t t= b;
      b=a; a=t;
    }

    //Removendo fatores 2 em comum
    while(!(a&1) && !(b&1)){
      a>>=1; b>>=1;
      bit_shift++;
    }

    //Removendo demais fatores 2;
     while(!(a&1)) a>>=1;
     while(!(b&1)) b>>=1;

    //Loop principal
    while(a>b || a<b){

      if(a>b){
        a-=b;
        while(!(a&1)) a>>=1;
      }

      if(a<b){
        b-=a;
        while(!(b&1)) b>>=1;
      }

    }

  //Em caso de falha
  return (b<<bit_shift);

};


//*************************************************************************************************************************
//FIM DO HEADER
#endif 
