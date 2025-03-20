//VAMOS CRIAR UM PROGRAMA QUE COMPUTA PARTIÇÕES MULTIPLICATIVAS DE INTEIROS

/*

PARTIÇÕES MULTIPLICATIVAS SÃO DIFERENTES COMBINAÇÕES DO FATORES PRIMOS DE UM NÚMERO INTEIRO TAL QUE CADA
FATOR NÃO NECESSARIAMENTE DISTINTO APARECE EM APENAS UMA PARCELA. AS PARTIÇÕES MULTIPLICATTIVAS DE n=30
SÃO 30=15X2=3X10=5X6=2X3X5, PARA N=250 TEMOS 250=2X125=10X25=10X5X5=50X5=2X5X25=2X5X5X5, ONDE 30=2X3X5 E
250=2X5³.

PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/multiplicative_partition_function.h


*/


//********************************************************************************************************
//CABEÇALHO
#ifndef MULTIPLICATIVE_PARTITION_H
#define MULTIPLICATIVE_PARTITION_H
#include"multiplicative_partition_function.h"


//********************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t* generate_multiplicative_partitions(int32_t, int32_t[], int32_t, uint64_t*);
void print_multiplicative_partition(int32_t[], uint64_t);
void multiplicative_partitions(int32_t);

//********************************************************************************************************
//FUNÇÕES


//Função que gera partições multiplicativas para números que possuem fatores primos repetidos
uint64_t* generate_multiplicative_partitions(int32_t n, int32_t divisors_array[], int32_t divisors_size, uint64_t* mp_array_size){

  //Variáveis locais
  uint64_t double_check_array[1000000]={0};
  uint64_t* multiplicative_partition_array=NULL;
  uint64_t bit_setter=pow(2,  divisors_size), mp_size=0, k=0, l=0;
  int32_t t=0, double_check_index=0;
  int32_t bit_position=0;



  //Procedimentos
    //Loop sobre possíveis combinações de fatores primos
    for(uint64_t  i=1; i<bit_setter; ++i){

      k=i; t=1; bit_position=0; double_check_index=0;
      while(k>0){

        if(k&1){
          t*=divisors_array[bit_position];
          if(divisors_array[bit_position]>=3) double_check_index+=divisors_array[bit_position];
        }
        k>>=1;
        bit_position++;
        if(t>=n) break;
      };

      if(t==n){
        //Checando se uma partição repetida foi determinada
        bool is_duplicate=false;
        for(uint64_t j=0; j<l; ++j){
          if(double_check_index==double_check_array[j]){
            is_duplicate=true; break;
          }
        };

        if(is_duplicate==true) continue;
        else{
          double_check_array[l]=double_check_index;
          ++l;
        };

        //Reajustando o array de valores
        mp_size++;
        multiplicative_partition_array=(uint64_t*)realloc(multiplicative_partition_array, mp_size*sizeof(uint64_t));
        multiplicative_partition_array[mp_size-1]=i;
      }

    };//Fim do loop principal

  //Resultado
  (*mp_array_size)=mp_size;
  return multiplicative_partition_array; 

};


//Função que printa uma partição multiplicativa
void print_multiplicative_partition(int32_t divisors_array[], uint64_t partition_index){

  //Variáveis locais
  int bit_position=0;

  //Procedimentos
    //Iterando sobre os bits da partição
    printf("{");
    while(partition_index>0){
      if(partition_index&1) printf("%i, ",  divisors_array[bit_position]);
  
      partition_index>>=1;
      bit_position++;

    };
    printf("}\n");

};

//Função que gera as partições multiplicativas de um númerom inteiro
void multiplicative_partitions(int32_t n){

  //Caso base: n é primo
  printf("{%i, }\n", n);
  if(gauss_euler_primality_test(n)) return;
  

  //Variáveis locais
  int32_t divisors_size;
  int32_t * divisors_array=generate_divisors_array(n, &divisors_size);//Lista de divisores
  uint64_t multiplicative_partition_size;
  uint64_t* multiplicative_partition_array=NULL;
  bool is_squarefree_n=is_square_free(n);


  //Procedimentos
    //Gerando um array de indexes de partições multiplicativas
    multiplicative_partition_array = generate_multiplicative_partitions(n,
                        divisors_array, divisors_size, &multiplicative_partition_size);


    //Printando as partições multiplicativas
    for(uint64_t i=0; i<multiplicative_partition_size; ++i)
      print_multiplicative_partition(divisors_array, multiplicative_partition_array[i]);

    //Limpando o cachê de memória
    if(divisors_array) free(divisors_array); divisors_array=NULL;
    if(multiplicative_partition_array) free(multiplicative_partition_array); multiplicative_partition_array=NULL;

};


//********************************************************************************************************
//FIM DO HEADER
#endif
