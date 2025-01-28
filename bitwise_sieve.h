//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA PENEIRA DE ERATÓSTENES COM OTIMIZAÇÃO ESPACIAL

/*
ESTOCANDO-SE INTEIROS DE UM TAMANHO EM BITS MÚLTIPLO DE 2 SUPORTADO POR UMA DETERMINADA ARQUITETURA
É POSSÍVEL REDUZIR O ESPAÇO REQUERIDO PARA ALOCAR NÚMEROS PRIMOS AO SE USAR A PENEIRA DE ERATÓSTENES.

NO PRESENTE ALGORITMO USAREMOS INTEIROS DE 8 BITS PARA ALOCAR NÚMEROS INTEIROS USANDO O ALGORITMO
TRADICIONAL DA PENEIRA DE ERATÓSTENES.

PARA MAIORES INFORMAÇÕES: https://www.geeksforgeeks.org/bitwise-sieve/

*/
 

//*************************************************************************************************
//CABEÇALHO
#ifndef BITWISE_SIEVE_H
#define BITWISE_SIEVE_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include<math.h>

//CONSTANTES GLOBAIS
const int first_entry=252; //Binário 11111100
const int table_entry=255; //Binário 11111111


//*************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void start_sieving_array(uint8_t[], uint64_t);
bool prime_checking(uint8_t[], uint64_t);
void mark_non_prime(uint8_t[], uint64_t);
void bitwise_sieve(uint64_t);

//*************************************************************************************************
//FUNÇÕES
//Função que inicializa o array de inteiros de 8 bits
void start_sieving_array(uint8_t bit8_array[], uint64_t array_size){

  //Procedimentos
    //Inicializando o primeiro elemento do array
    bit8_array[0]=252;

    //Inicializando os demais elementos do array
    for(uint64_t i=1; i<array_size; ++i) bit8_array[i]=255;

};


//Função que checa se um dado número é primo
bool prime_checking(uint8_t bit8_array[], uint64_t n){

  //Variaveis locais
  uint64_t slot=(n>>3);// div 8
  int bit_slot=(n&7); // mod 8
  uint8_t mask=(1<<bit_slot);


  //Resultado
  if((bit8_array[slot]&mask)>0) return true;
  else return false;

};


//Função que marca um inteiro como não primo
void mark_non_prime(uint8_t bit8_array[], uint64_t n){

  //Variaveis locais
  uint64_t slot=(n>>3);// div 8
  int bit_slot=(n&7); // mod 8
  uint8_t mask=~(1<<bit_slot);

  //Procedimentos
    //Modificando o n-ésimo bit para zero: contagem da direita para a esquerda
    bit8_array[slot]&=mask;


};

//Função que implementa uma peneira de Eratóstenes com otimização espacial usando manipulações de bits
void bitwise_sieve(uint64_t limit){

  //Variáveis
  uint8_t* bit8_array=NULL;
  uint64_t array_size=ceil(limit/8)+1;


  //Procedimentos
    //Inicializando o array de inteiros de 8 bits
    bit8_array=(uint8_t*)realloc(bit8_array, array_size*sizeof(uint8_t));
    start_sieving_array(bit8_array, array_size);


    //Loop principal: marcando não primos
    for(uint64_t prime=2; prime*prime<=limit; prime++){
        if(prime_checking(bit8_array, prime)){

          for(uint64_t x=(prime*prime); x<=limit; x+=prime)
          mark_non_prime(bit8_array, x);
   

        }

    }


  //Printando números primos na tela
  printf("2, ");
  for(uint64_t j=3; j<=limit; j+=2){
    if(prime_checking(bit8_array, j))
    printf("%lu, ",j);
  }
  printf("...\n");
  
    

  //Limpando o cachê de mémoria
  if(bit8_array) free(bit8_array);

};

//*************************************************************************************************
//FIM DO HEADER
#endif
