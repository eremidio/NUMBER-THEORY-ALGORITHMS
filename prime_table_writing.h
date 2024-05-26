//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ROTINAS PARA CRIAR UM ARQUIVO PARA ESTOCAR NÚMEROS PRIMOS ÍMPARES DE UMA FORMA COMPACTA

/*
NOTA: PARA COMPACTAR A TABELA USAMOS UMA STRING BINÁRIA,CADA INTEIRO ÍMPAR É RESGISTRADO COMO UM CARACTÉRE 0 OU 1 (TIPO char EM C/C++). 

*/

//***********************************************************************************************************************************************************
//CABEÇALHO
#ifndef PRIME_TABLE_WRITING_H
#define PRIME_TABLE_WRITING_H
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdbool.h>
#include<math.h>
#include"mod_bin_exponentiation128.h"

//***********************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool fast_prime_checking(uint64_t);
void generate_prime_table(uint64_t, char[]);

//***********************************************************************************************************************************************************
//FUNÇÕES
//Função que determina se um número é primo ou não
bool fast_prime_checking(uint64_t n){

  //Caso base primos inferiores a 120
    //Variáveis locais
    int prime_seed[30]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113};

    //Procedimentos: teste de divisibilidade por primos inferiores a 100
    for(int i=1; i<30; ++i){
      if(n==prime_seed[i])
        return true;
      if((n%prime_seed[i])==0)
        return false;
                           };

  //Teste de Fermat na base 2 para rápida detecção de compostos
  if(mod_bin_pow(2,(n-1), n)!=1)
    return false;


  //Caso geral: busca por fatores primos até n^(1/2)
    //Variáveis locais
    int residue_class[8]={1,7,11,13,17,19,23,29};
    uint64_t sqrt_n=sqrt(n), divisor;

    //Procedimentos
    for(uint64_t j=3; ;++j){

      for(int k=0; k<8; ++k){
  
        divisor=30*j+residue_class[k];
        if(n%divisor==0)
          return false;  
                            };

        if(divisor>sqrt_n);
          break;

                           };

  //Resultado caso o número passe nos testes acima
  return true;
   
                                    };


//Função que gera uma tabela de números primos ímpares usando uma notação compacta
void generate_prime_table(uint64_t limit, char filename[]){

  //Variáveis locais
  FILE* prime_table_file;
  uint64_t n=3;
  char zero_bit='0';
  char one_bit='1';


  //Procedimentos
    //Abrindo o arquivo para escrita de números
    prime_table_file=fopen(filename, "w");

    //Loop principal: peneirando os primos ímpares e registrando os resultados no arquivo aberto como bits 1 e os não primos como bits 0.
    while(n<limit){
      if(fast_prime_checking(n)==true){
        int c=fputc(one_bit, prime_table_file);
        n+=2;
                                      }
      else{
        int c=fputc(zero_bit, prime_table_file);
        n+=2;
          };
                  };



      //Fechando o arquivo aberto
      fclose(prime_table_file);
 

                                                          };




//***********************************************************************************************************************************************************
//FIM DO HEADER
#endif
