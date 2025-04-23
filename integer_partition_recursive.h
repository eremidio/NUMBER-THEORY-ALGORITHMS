//VAMOS CRIAR UM PROGRAMA QUE COMPUTA PARTIÇÕES ADITIVAS DE NÚMEROS INTEIROS USANDO RECURSÃO

/*

PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/integer_partition.h

*/


//***************************************************************************************************
//CABEÇALHO 
#ifndef INTEGER_PARTITION_RECURSIVE_H
#define INTEGER_PARTITION_RECURSIVE_H
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

//CONSTANTES GLOBAIS
int summands[1000000]={0,};


//***************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void print_partition(int);
void generate_additive_partitions(int, int, int);


//***************************************************************************************************
//FUNÇÕES
//Função que printa uma partição aditiva de um inteiro
void print_partition(int index){

  //Procedimentos
  printf("{");
  for(int i=0; i<index; ++i) printf("%i, ", summands[i]);
  printf("}\n");

};


//Função que computa partições aditivas de um inteiro recursivamente
void generate_additive_partitions(int n, int start, int index){

  //Caso base: n<1
  if(n==0){
    print_partition(index);
  }


  //Caso geral: extraindo recursivamente as parcelas de n
    for(int32_t i=start; i<=n; ++i){
      summands[index]=i;
      generate_additive_partitions((n-i), i, index+1);

  }
    

};

//***************************************************************************************************
//FIM DO HEADER
#endif
