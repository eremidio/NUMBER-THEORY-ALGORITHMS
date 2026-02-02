//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA EFICIENTES ROTINAS PARA O CÁLCULO DE EXPONENCIAIS MODULARES DE INTEIROS DE 64 BITS

/*

SUBROTINA ÚTIL EM OUTROS ALGORITMOS MAIS COMPLEXOS QUE REQUER MÚLTIPLOS CÁLCULOS DE EXPONENCIAIS A MENOS DE UMA RELAÇÃO DE 
CONGRUÊNCIA. 

PARA MAIORES INFORMAÇÕES: https://math.mit.edu/classes/18.783/2017/LectureNotes4.pdf
                          https://cs.au.dk/~ivan/FastExpproject.pdf

*/


//*******************************************************************************************************************************************
//CABEÇALHO
#ifndef BINARY_WINDOW_EXPONENTATION_H
#define BINARY_WINDOW_EXPONENTATION_H
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include<assert.h>
#include<stdio.h>


//CONSTANTES GLOBAIS
const int buffer_size_array[11]={1,2,4,8,16,32,64,128,256,512,1024};


//*******************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t* fill_pow2_buffer(uint64_t, uint64_t, size_t);
uint64_t pow_mod_window(uint64_t, uint64_t, uint64_t, size_t);


//*******************************************************************************************************************************************
//FUNÇÕES
//Função que preenche um buffer de números usados no cálculo da exponencial modular
uint64_t* fill_pow2_buffer(uint64_t a, uint64_t m, size_t buffsize){

  //Variáveis locais
  __int128_t buff=1;  
  uint64_t* buffer=(uint64_t*)malloc(buffsize*sizeof(uint64_t));

  
  //Procedimento
    //Preecherdo o buffer de números usados no cálculo
    buffer[0]=1;
    for(size_t i=1; i<buffsize; ++i){
      buff=(a*buff)%m;
      buffer[i]=buff;
    }
   

  //Resultado
  return buffer;
  
};


//Função que computa uma exponencial modular usando janelas de bits de tamanho 2^k 
uint64_t pow_mod_window(uint64_t a, uint64_t b, uint64_t m, size_t k) {

  //Restrição (memória)
  assert(k > 0 && k <=10);

  //Variáveis locais
  size_t buffsize = buffer_size_array[k], mask=buffsize-1, t=0;
  uint64_t* buffer = fill_pow2_buffer(a, m, buffsize); //Pré-computando
  __int128_t r = 1;
  

  
  //Procedimentos
    //Computando o número de janelas de 2^k-bits do expoenete
    uint64_t tmp = b;
    while (tmp >>= k) ++t;


    //Loop principal (left-to-right)
    for(int i=t; i>=0; --i){

        //Duplicando o resultado r=r^(2^k)
        for(size_t j=0; j<k; ++j)
            r = (r*r)%m;

        //Computa o é-simo digito do expoente ma base 2^k
        uint64_t d = (b>>(i*k))&mask;

        //Checando o é-simo (2^k)-dígito do expoente
        r=(r*buffer[d]) % m;

    }

    //Limpando o cachê de memória
    if(buffer) free(buffer); buffer = NULL;


  //Resultado
  uint64_t result=r;
  return result;

}


//*******************************************************************************************************************************************
//FIM DO HEADER
#endif
