//VAMOS CRIAR UM PROGRAMA QUE COMPUTA O SÍMBOLO DE JACOBI USANDO OPERAÇÕES DE MANIPULAÇÃO DE BITS E REDUÇÕES MODULARES

/*
O ALGORITMO PRESENTE PERMITE COMPUTAR O SÍMBOLO DE JACOBI (QUE É O IGUAL AO SÍMBOLO DE LEGENDRE
QUANDO O SEGUNDO ARGUMENTO É UM NÚMERO PRIMO) USANDO APENAS MANIPULAÇÃO DE BITS, REDUÇÕES
MODULARES E INVERSÕES DE SINAL. O ALGORITMO PODE SER IMPLEMENTADO RECURSIVAMENTE.

PARA MAIORES REFERÊNCIAS: http://www.mat.uniroma3.it/users/pappa/missions/slides/NEPAL2010_1.pdf

*/


//****************************************************************************************************
//CABEÇALHO
#ifndef BINARY_JACOBI_SYMBOL_H
#define BINARY_JACOBI_SYMBOL_H
#include<stdint.h>
#include<inttypes.h>
#include<assert.h>


//CONSTANTES  GLOBAIS
int tab8[8]={0, 1, 0, (-1), 0, (-1), 0, 1};

//****************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int binary_jacobi(int64_t, int64_t);

//****************************************************************************************************
//FUNÇÕES
//Função que calcula o símbolo de Jacobi
int binary_jacobi(int64_t a, int64_t b){

  //Restrição
  assert((b&1)==1); //O segundo termo deve ser ímpar

  //Variáveis locais
  int64_t x=a, y=b, z=1;
  int64_t t;


  //Procedimento
    //Loop principal
    while(1){

      //Resultado
      if(x==0 || x==1) return (x*z);
  
      //Checando o sinal do primeiro argumento
      if(x<0){
        x*=(-1);
        t=((y-1)>>1);//(-1)^[y-1]/2
        if(t&1) z*=(-1);
        continue;
      }

      //Reduzindo os coeficientes
      if(x>=y){
        x%=y;
        continue;
      }
 
      //Checando a paridade do primeiro termo
      if(!(x&1)){
        x>>=1;
        t=tab8[y&7];//(-1)^[y²-1]/8
        z*=t;
        continue;
      }
      
      if((x&1)){

        t=(((x-1)>>1)&1)*(((y-1)>>1)&1);//(-1)^[(x-1)(y-1)]/4
        int64_t temp=x;

        x=(y%x);
        y=temp;
        if(t&1) z*=(-1);  

      }
      

    };//Fim do loop principal
    

  //Em caso de erro
  return 0; 

};



//****************************************************************************************************
//FIM DO HEADER
#endif
