//VAMOS CRIAR UM PROGRAMA PARA ESTOCAR DIFERENÇAS DE NÚMEROS PRIMOS 

/*

SUBROTINA ÚTIL EM ALGUNS ALGORITMOS. ESTOCANDO-SE APENAS AS DIFERENÇAS ENTRE PRIMOS CONSECUTIVOS, A SEQUÊNCIAS DE PRIMOS
PODE SER RECUPERADA SOMANDO-SE AS DIFERENÇAS INICIANDO-SE A SEQUÊNCIA A PARTIR DE 2 (PRIMEIRO NÚMERO PRIMO).

*/


//*****************************************************************************************************
//CABEÇALHO
#ifndef COMPACT_PRIME_TABLE_READING_H
#define COMPACT_PRIME_TABLE_READING_H
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>


//*****************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint8_t* read_prime_table_difference(char[], size_t*);


//*****************************************************************************************************
//FUNÇÕES
//Função que aloca uma lista de diferenças entre números primos consecutivos estocadas
uint8_t* read_prime_table_difference(char file_name[], size_t* prime_diff_size){

  //Variáveis locais
  FILE* prime_table_file;
  uint8_t* prime_difference_array=NULL;
  size_t array_size=0;
  uint8_t prime_difference=0;


  //Procedimentos
    //Abrindo arquivo parea leitura
    prime_table_file = fopen(file_name, "r");

    //Lendo as entradas do arquivo
    while(fscanf(prime_table_file, "%hhu\n", &prime_difference)==1){

      array_size=array_size+1;
      prime_difference_array=(uint8_t*)realloc(prime_difference_array, array_size*sizeof(uint8_t));
      prime_difference_array[array_size-1]=prime_difference;

    }


    //Fechandoo arquivo de leitura
    fclose(prime_table_file);

  //Resultado
  (*prime_diff_size)=array_size;
  return prime_difference_array;

};

//*****************************************************************************************************
//FIM DO HEADER
#endif
