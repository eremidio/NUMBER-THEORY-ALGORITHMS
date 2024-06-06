//VAMOS CRIAR UM PROGRAMA QUE GERA UMA TABELA DE FATORES PRIMOS E SUAS RESPECTIVAS MULTIPLICIDADES PARA INTEIROS DE 64 BITS

/*
NOTA: ESSA ROTINA SERÁ USADA COMO SUBROTINA EM ALGORITMOS COMO O ALGORITMO DE POHLIG-HELLMAN, CÁLCULO DE ORDENS
MULTIPLICATIVAS, ENTRE OUTROS QUE REQUER UMA LISTA DE FATORES PRIMOS E SUAS RESPECTIVAS MULTIPLICIDADES.

USAREMOS TENTATIVA POR DIVISÃO E ERRO COM ALGUMAS OTIMIZAÇÕES COMO FATORAÇÃO DE RODA E ABORTAGEM PREMATURA QUANDO UMA
FATORAÇÃO COMPLETA FOR ATIGINDA.

*/ 



//***************************************************************************************************************************************
//CABEÇALHO
#ifndef FACTORIZATION_MAP_H
#define FACTORIZATION_MAP_H
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>


//***************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void factorization_map(uint64_t, uint64_t[], int[]);


//***************************************************************************************************************************************
//FUNÇÕES
//Função que fatora um número e cria um array de fatores primos e suas respectivas multiplicidades
void factorization_map(uint64_t n, uint64_t factor_array[], int multiplicity_array[]){

  //Variáveis locais
  const static int prime_seed[10]={2,3,5,7,11,13,17,19,23,29};
  const static int residue_class[8]={1,7,11,13,17,19,23,29};
  uint64_t sqrt_n=sqrt(n), cbrt_n=cbrt(n), divisor=0, multiplicity=0, index=0;


  //Procedimentos
    //Testes por fatores primos inferiores a 30
    for(int i=0; i<10; ++i){

      if((n%prime_seed[i])==0){

        multiplicity=0;
        while((n%prime_seed[i])==0){
          n/=prime_seed[i];
          multiplicity++;
                                   };

        factor_array[index]=prime_seed[i];
        multiplicity_array[index]=multiplicity;
        index++;
        
                               }

    };


  //Loop principal: teste até fatores n^(1/2)
  for(int j=1;;j++){

    for(int k=1; k<8; ++k){
      divisor=(30*j)+residue_class[k];

      //Abortagem 1: limite superior a n^(1/2)
      if(divisor>(sqrt_n+1) || n==1)
        goto end;


      //Divisor encontrado
      if((n%divisor)==0){

        multiplicity=0;
        while((n%divisor)==0){
          n/=divisor;
          multiplicity++;
                             };

        factor_array[index]=divisor;
        multiplicity_array[index]=multiplicity;
        index++;


      //Abortagem 2: o fator encontrado está entre os limites n^(1/3) e n^(1/2) neste intervalo o número em questão possuí no máximo dois fatores primos
      if(divisor>(2*cbrt_n))
        goto end;
        
                        }


      };

  };


    //Fatores primos superiores a raíz quadrada do número em questão
    end:
    if(n==1)
      return;

    if(n>1){
      factor_array[index]=n;
      multiplicity_array[index]=1;
      index++;
           };
  


                                                                                     };


//***************************************************************************************************************************************
//FIM DO HEADER
#endif
