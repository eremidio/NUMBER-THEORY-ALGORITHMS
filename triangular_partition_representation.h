//VAMOS CRIAR UM PROGRAMA QUE CALCULA PARTOIÇÕES DE INTEIROS EM PARTIÇÕES TRIANGULARES 

/*

PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/triangular_partition_representation_generating_function.h

*/



//**************************************************************************************************
//CABEÇALHO
#ifndef TRIANGULAR_PARTITION_REPRESENTATION_H
#define TRIANGULAR_PARTITION_REPRESENTATION_H
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>

//CONSTANTES GLOBAIS
int64_t summands[100000000]={0,};
const int64_t MAX_TRIANGULAR=100000000000000;


//**************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void print_triangular_partition(int64_t);
void generate_triangular_partitions(int64_t, int64_t, int64_t);


//**************************************************************************************************
//FUNÇÕES
//Função que computa um array de números triangulares
int64_t* generate_triangular_number_array(int64_t n, int64_t* triangular_size){

  //Variáveis locais
  int64_t* triangular_array=NULL;
  int64_t s=0, t=0;


  //Procedimentos
    //Loop principal
    for(int64_t i=0; ; ++i){
      t=(i*(i+1))/2;
      if(t>n) break;
      s++;
      triangular_array=(int64_t*) realloc(triangular_array, s*sizeof(int64_t));
      triangular_array[s-1]=t;
    }


  //Resultado
  (*triangular_size)=s;
  return triangular_array;

};

//Função que printa uma partição triangular de um inteiro
void print_triangular_partition(int64_t index){

  //Procedimentos
  printf("{");
  for(int64_t i=0; i<index; ++i) printf("%li, ", summands[i]);
  printf("}\n");

};



//Função que computa partições triangulares de um inteiro recursivamente
void generate_triangular_partitions(int64_t n, int64_t start, int64_t index){

  //Caso base: n<1
  if(n==0){
    print_triangular_partition(index);
  }


  //Caso geral: extraindo recursivamente as parcelas de n
    for(int32_t i=start; i<=n; ++i){
      int64_t t=(i*(i+1))/2;
      summands[index]=t;
      generate_triangular_partitions((n-t), i, index+1);

  }
    

};


//**************************************************************************************************
//FIM DO HEADER
#endif
