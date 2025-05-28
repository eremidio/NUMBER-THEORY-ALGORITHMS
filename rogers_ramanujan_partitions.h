//VAMOS CRIAR UM PROGRAMA PARA COMPUTAR PARTIÇÕES DE ROGER-RAMANUJAN

/*

PARA MAIORES INFORMAÇÕES:https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/rogers_ramanujan_identities.h

*/



//**********************************************************************************************************************
//CABEÇALHO
#ifndef ROGERS_RAMANUJAN_PARTITIONS_H
#define ROGERS_RAMANUJAN_PARTITIONS_H
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>


//CONSTANTES GLOBAIS
int32_t summands[100000000]={0,};
const int64_t MAX_ROGERS_RAMANUJAN=100000000;//limite superior 10^8


//**********************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void print_rogers_ramanujan_partition(int32_t);
void compute_rogers_ramanujan_partition1(int32_t, int32_t, int32_t);
void compute_rogers_ramanujan_partition2(int32_t, int32_t, int32_t);
void compute_rogers_ramanujan_partition3(int32_t, int32_t, int32_t);


//**********************************************************************************************************************
//FUNÇÕES
//Função que printa uma partição satisfazendo as identidades de Rogers-Ramanujan
void print_rogers_ramanujan_partition(int32_t index){

  //Procedimentos
  printf("{");
  for(int32_t i=0; i<index; ++i) printf("%i, ", summands[i]);
  printf("}; ");

};


//Função que calcula partições de um inteiro congruentes a 1,4 (mod 5)
void compute_rogers_ramanujan_partition1(int32_t n, int32_t start, int32_t index){


  //Caso base: n<1
  if(n==0){
    print_rogers_ramanujan_partition(index);
    return;
  }


  //Caso geral: extraindo recursivamente as parcelas de n
  for(int32_t i=start; i<=n; ++i){
    if((i%5)==1 || (i%5)==4){
      summands[index] = i;
      if(index>0 && summands[index-1]>summands[index]) continue;
      compute_rogers_ramanujan_partition1(n-i, start, index+1);
    }
  }
    

};


//Função que calcula partições de um inteiro congruentes a 2,3 (mod 5)
void compute_rogers_ramanujan_partition2(int32_t n, int32_t start, int32_t index){


  //Caso base: n<1
  if(n==0){
    print_rogers_ramanujan_partition(index);
    return;
  }


  //Caso geral: extraindo recursivamente as parcelas de n
  for(int32_t i=start; i<=n; ++i){
    if((i%5)==2 || (i%5)==3){
      summands[index] = i;
      if(index>0 && summands[index-1]>summands[index]) continue;
      compute_rogers_ramanujan_partition2(n-i, start, index+1);
    }
  }
    

};


//Função que calcula partições de um inteiro com parcelas adjacentes diferindo de no minímo 2
void compute_rogers_ramanujan_partition3(int32_t n, int32_t start, int32_t index){


  //Caso base: n<1
  if(n==0){
    print_rogers_ramanujan_partition(index);
    return;
  }


  //Caso geral: extraindo recursivamente as parcelas de n
  for(int32_t i=start; i<=n; ++i){
    summands[index] = i;
    if(index>0 && (summands[index]-summands[index-1])<2) continue;
    compute_rogers_ramanujan_partition3(n-i, start, index+1);
  }
    

};


//**********************************************************************************************************************
//FIM DO HEADER
#endif
