//VAMOS CRIAR UM PROGRAMA QUE COMPUTA PARTIÇÕES MULTIPLICATVAS USANDO RECURSÃO

/*

PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/multiplicative_partition_function.h
                          https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/multiplicative_partition.h
                          https://github.com/eremidio/COMBINATORICS---STATISTICS---PROBABILITY/blob/main/set_partition.h

*/


//**********************************************************************************************
//CABEÇALHO
#ifndef MULTIPLICATVE_PARTITION_RECURSIVE_H
#define MULTIPLICATVE_PARTITION_RECURSIVE_H
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

//CONSTANTES GLOBAIS
int32_t divisors[100]={0,};


//**********************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void print_multiplicative_partition(int);
void generate_multiplicative_partitions(int32_t, int32_t, int);


//**********************************************************************************************
//FUNÇÕES
//Função que printa uma partição multiplicativa de um inteiro
void print_partition(int index){
  
  //Procedimentos
  printf("{");
  for(int i =0; i<=index; ++i) printf("%i, ", divisors[i]);
  printf("}\n");

};


//Função que computa partições multiplicativas de inteiros de forma recursiva
void generate_multiplicative_partitions(int32_t n, int32_t start, int index){

  //Caso base: n está completamente fatorado (não necessariamente em fatores primos)
  if(n==1){
    print_partition(index-1);
    return;
  }


  //Caso geral: extraindo recursivamente os divisores (não necessariamente primos) de n
  for(int32_t i=start; i<=n; ++i){
    if(n%i==0){
      divisors[index]=i;
      generate_multiplicative_partitions((n/i), i, index+1);
    }
  }
    

};

//**********************************************************************************************
//FIM DO HEADER
#endif
