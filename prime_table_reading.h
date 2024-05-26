//VAMOS CRIAR UM PROGRAMA PARA LER UMA TABELA DE NÚMEROS PRIMOS ÍMPARES USANDO UMA NOTAÇÃO COMPACTA CONFORME AS ROTINAS DO ARQUIVO prime_table_writing.h

/*
NOTA: A LEITURA DO ARQUIVO ALOCA A LISTA DE PRIMOS EM UM ARRAY, UM PONTEIRO PARA ALOCAR INTEIROS DE 64 BITS. A MEMÓRIA USADA DEVE SER MANUALMENTE
DEALOCADA PELA FUNÇÃO QUE USA ESSA SUBROTINA.

*/

//***********************************************************************************************************************************************************
//CABEÇALHO
#ifndef PRIME_TABLE_READING_H
#define PRIME_TABLE_READING_H
#include"prime_table_writing.h"

//***********************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t * read_prime_table(char[], uint64_t*,  uint64_t*);

//***********************************************************************************************************************************************************
//FUNÇÕES

//Função que retorna um array de inteiros de 64 bits alocados de forma compacta em uma tabela de números primos
uint64_t * read_prime_table(char filename[], uint64_t* prime_array ,uint64_t* prime_table_size){

  //Variáveis locais
  FILE* prime_table_file;
  uint64_t prime_index=0;
  uint64_t n=3;
  char one_bit='1';
  char zero_bit='0';
  register int c;   
  
  //Procedimentos
    //Abrindo o arquivo contendo a lista de números primos compactada
    prime_table_file=fopen(filename, "r");


    //Adicionando o número 2 (único primo par) à lista de primos
    prime_index++;
    prime_array=(uint64_t*)realloc(prime_array, prime_index*sizeof(uint64_t));
    prime_array[prime_index-1]=2;

  //Loop principal: coletando os números primos alocados
  while((c=fgetc(prime_table_file))!=EOF){
    if(c==one_bit){
      prime_index++;
      prime_array=(uint64_t*)realloc(prime_array, prime_index*sizeof(uint64_t));
      prime_array[prime_index-1]=n;
      n+=2;     
                  }
    else
      n+=2;

                                            };

    
    

    //Fechando o arquivo
    fclose(prime_table_file);

  //Resultado da execução do algoritmo
  (*prime_table_size)=prime_index;
  return prime_array;
  
                                                                        };

//***********************************************************************************************************************************************************
//FIM DO HEADER
#endif
