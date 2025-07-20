//VAMOS CRIAR UM PROGRAMA QUE COMPUTA PARTIÇÕES POLIGINAIS DE UM INTEIRO 

/*

PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/COMBINATORICS---STATISTICS---PROBABILITY/blob/main/polygonal_numbers_generating_function.h

*/


//*****************************************************************************************************************
//CABEÇALHO
#ifndef POLYGONAL_PARTITIONS_H
#define POLYGONAL_PARTITIONS_H
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

//CONSTANTES GLOBAIS
int64_t summands[1000000]={0,};


//*****************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t polygonal_number(int64_t, int);
void print_polygonal_partition(int64_t);
void generate_polygonal_partitions(int64_t, int64_t, int64_t, int);


//*****************************************************************************************************************
//FUNÇÕES
//Função que computa o n-ésimo número poligonal P(n, s)
int64_t polygonal_number(int64_t n, int s){

  //Variáveis locais
  int64_t val1=(s-2)*n*n;
  int64_t val2=(s-4)*n;

  //Resultado
  return ((val1-val2)/2);

};


//Função que printa uma partição aditiva de um inteiro
void print_polygonal_partition(int64_t index){

  //Procedimentos
  printf("{");
  for(int64_t i=0; i<index; ++i) printf("%li, ", summands[i]);
  printf("}\n");

};


//Função que gera partições poligonais de um inteiro de 64 bits
void generate_polygonal_partitions(int64_t n, int64_t start, int64_t index, int s){

  //Caso base: n<1
  if(n==0){
    print_polygonal_partition(index);
    return;
  };

  //Loop principal:chamada recursiva do algoritmo
  for(int64_t i=start; i<=n; ++i){
    int64_t P_sn=polygonal_number(i, s);
    summands[index]=P_sn;
    generate_polygonal_partitions((n-P_sn), i, index+1, s);
  }
    
};

//*****************************************************************************************************************
//FIM DO HEADER
#endif
