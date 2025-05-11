//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ROTINAS PARA COMPUTAR A DECOMPOSIÇÃO ZECKENDORF DE NÚMEROS INTEIROS DE 64 BITS


/*

O TEOREMA DE ZECKERDOF-LEKKERKERKER AFIRMA QUE TODO NATURAL PODE SER EXPRESSO DE MANEIRA ÚNICA COMO A SOMA DE NÚMEROS
DE FIBONACCI. TAL DECOMPOISIÇÃO É ÚNICA A MENOS DA ORDEM DOS FATORES.

A REPRESENTAÇÃO DE ZECKENDORF PERMITE DEFINIR A OPERAÇÃO DE MULTIPLICAÇÃO DE FIBONACCI DEFINIDA PARA DOIS INTEIROS.
SEJA DOIS INTEIROS a,b TAIS QUE a=ΣF(k), b=ΣF(l), ONDE k, l SÃO ÍNDICES INTEIROS, DEFINIMOS a°b=ΣF(k+l), ONDE A SOMA
É REALIZADA SOBRE TODOS OS POSSÍVEIS PARES ORDERNADOS (k, l). TAL OPERAÇÃO É COMUTATIVA E ASSOCIATIVA.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Zeckendorf%27s_theorem


*/


//*************************************************************************************************************************
//CABEÇALHO
#ifndef ZECKENDORF_DECOMPOSITION_H
#define ZECKENDORF_DECOMPOSITION_H
#include"int128.h"


//CONSTANTES GLOBAIS USADAS NO CÁLCULO
__int128_t fibonacci_buffer[185];/*F(184)<(2^127)-1 de forma que todo o intervalo de inteiros de 128 bits é contemplado*/


//*************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void fill_fibonacci_buffer();
int* zeckendorf_decomposition(uint64_t);
__int128_t fibonacci_multiplication(int[], int[], int, int);

//*************************************************************************************************************************
//FUNÇÕES
//Função que preenche um buffer de números de Fibbonacci
void fill_fibonacci_buffer(){

  //Procedimentos
    //Ajuste dos termos iniciais da sequência
    fibonacci_buffer[0]=0; fibonacci_buffer[1]=1; 

    //Loop principal
    for(int k=2; k<185; ++k) fibonacci_buffer[k]=fibonacci_buffer[k-1]+fibonacci_buffer[k-2];
    
};


//Função que calcula a decomposição Zeckendorf de um número inteiro
int* zeckendorf_decomposition(uint64_t n){

  //Variáveis locais
  int* fib_index_array=NULL;
  int index=0, k;


  //Procedimentos
    //Loop principal
    while(n>0){

      //Calculando um index k tal que F(k) entra na decomposição de n      
      for(k=2; k<185; ++k){
        if(fibonacci_buffer[k]>=n){
          index++;
          if(fibonacci_buffer[k]>n) k--;
          n-=fibonacci_buffer[k];
          break;
        }
      }

      //Adicionando um elemento a lista de indexes
      fib_index_array=(int*)realloc(fib_index_array, index*sizeof(int));
      fib_index_array[index-1]=k;
      if(n==0) break;

    };//Fim do loop principal
  

  //Resultado 
  return fib_index_array;

};


//Função que calcula o produto de Fibonacci de dois inteiros
__int128_t fibonacci_multiplication(int a_fib_array[], int b_fib_array[], int a_fib_size, int b_fib_size){

  //Variáveis locais
  __int128_t result=0;
  
  //Procedimentos
    //Ajuste de variáveis
    if(a_fib_array[a_fib_size-1]==0) a_fib_size--;
    if(b_fib_array[b_fib_size-1]==0) b_fib_size--;

    //Loop principal
    for(int i=0; i<a_fib_size; ++i){
      for(int j=0; j<b_fib_size; ++j){

      result=result+fibonacci_buffer[a_fib_array[i]+b_fib_array[j]];

      }
    };


  //Resultado
  return result;

};


//*************************************************************************************************************************
//FIM DO HEADER
#endif
