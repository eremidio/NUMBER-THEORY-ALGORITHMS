//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA VERSÃO DO ALGORITMO EXTENDIDO DE EUCLIDES USANDO OPERAÇÕES DE MANIPULAÇÃO DE BITS 

/*
PARA MAIORES INFORMAÇÕES: A Course In Computational Algebraic Number Theory by Henri Cohen
                          Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance

*/


//*******************************************************************************************************************************************
//CABEÇALHO
#ifndef BINARY_EXTENDED_GCD_H
#define BINARY_EXTENDED_GCD_H
#include<stdint.h>
#include<inttypes.h>
#include<stdbool.h>


//*******************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void binary_extended_gcd(int64_t*, int64_t*, int64_t*, int64_t, int64_t);


//*******************************************************************************************************************************************
//FUNÇÕES
//Função que implementa uma versão binária do algoritmo de Euclides extendido
void binary_extended_gcd(int64_t* a, int64_t* b, int64_t* gcd, int64_t x, int64_t y){

  //Variáveis locais
  int64_t a_, b_, h=0;
  int64_t t1, t2, t3;
  int64_t v1, v2, v3;
  int bit_shift=0;


  //Procedimentos
    //Removendo fatores 2 comuns
    while(!(x&1) && !(y&1)){
      x>>=1; y>>=1;
      bit_shift++;

    }

    //Inicializando variáveis
    a_=1; b_=0; h=x; 
    v1=y; v2=(1-x); v3=y;

    if(!(x&1)){
      t1=1; t2=0; t3=x;
    }
    else{
      t1=0; t2=(-1); t3=(-1)*y;
    };


    goto even_check;

    //Loop principal
    while(1){

      //Checando a paridade dos parâmetros t1, t2, t3
      if(!(t1&1) && !(t2&1)){
        t1>>=1; t2>>=1; t3>>=1;
      }
      else{
        t1+=y; t2-=x;
        t1>>=1; t2>>=1; t3>>=1;
      }  

      even_check:
      if(!(t3&1)) continue;   

      //Ajuste de variáveis
      if(t3>0){
        a_=t1; b_=t2; h=t3;    
      }
      else{
        v1=y-t1;  v2=(-1)*x-t2; v3=(-1)*t3;
      };

      //Redução euclidiana
      t1=(a_)-v2; t2=(b_)-v2; t3=h-v3;
      if(t1<0){
        t1+=y; t2-=x;
      }

      //Condição que determina o fim do loop
      if(t3==0) break;
      

    };//Fim  do loop principal


    //Ajuste fino do resultado
    if(bit_shift>0) (*gcd)=(h<<bit_shift);
    else (*gcd)=h;
    (*a)=a_; (*b)=b_;


};

//*******************************************************************************************************************************************
//FIM DO HEADER
#endif
