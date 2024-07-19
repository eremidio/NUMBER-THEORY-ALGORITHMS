//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ROTINAS PARA SE CALCULAR RAÍZES PRIMITIVAS DE UM NÚMERO INTEIRO n VIA TENTATIVA E ERRO

/*
NA PRESENTE VERSÃO USAREMOS ROTINAS EXPONENCIAÇÃO E FORÇA BRUTA PARA CHECAR AS CONDIÇÕES NECESSÁRIA 
POR RAÍZES PRIMITIVAS MÓDULO UM INTEIRO.

PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/primitive_root.h
*/

//*************************************************************************************************************************
//CABEÇALHO
#ifndef PRIMITIVE_ROOT_RAW_H
#define PRIMITIVE_ROOT_RAW_H
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include<math.h>
#include"mod_bin_exponentiation128.h"
#include"euler_totient_function.h"

//*************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool primitive_root_checker(uint64_t);
void primitive_root(uint64_t);

//*************************************************************************************************************************
//FUNÇÕES
// Função que checa se um inteiro posui raízes primitivas
bool primitive_root_checker(uint64_t n){

  //Casos triviais
  if(n == 1 || n == 2 || n == 4) return true;
  if((n % 8) == 0) return false;

  //Caso geral: n é da forma 2(p^k) ou p^k
    //Variáveis locais
    uint64_t prime;


    //Procedimentos
      //Eliminando o fator 2
      if (!(n&1)) n>>=1;
      if(!(n&1)) return false;

    // Testando por fatores primos ímpares (um número não pode ser divisível por dois ímpares diferentes)
    if(fast_prime_power_detection(n, &prime)==true) return true;
    else return false;

};

//Função que calcula as raízes primitivas de um número inteiro
void primitive_root(uint64_t n){

  //Checando se o número em questão possui raízes primitivas
  bool check=primitive_root_checker(n);
  if(check==false){
    printf("O número em questão não possui raízes primitivas!\n");
    return;
  };


  //Variáveis locais 
  uint64_t validator = euler_totient_function(n);
  uint64_t i, j;//Variável de iteração
  uint64_t root_number=0;
  uint64_t* primitive_root_array=NULL;

  //Procedimentos
    //iterando sobre possíveis candidatos (usaremos o algoritmo de Euclides definido em euler_totient_function.h)
    for(i=1; i<n; ++i){

    //Apenas números coprimos podem ser raízes primitivas
    if(gcd_euclides(i, n)>1) continue;

    //Testando possíveis candidatos
    for(j=1; j<(validator+2); ++j){
      if(mod_bin_pow(i, j, n)==1) break;
                              };
    
      if(j==validator){
        root_number++;
        primitive_root_array=(uint64_t*)realloc(primitive_root_array, root_number*sizeof(uint64_t));
        primitive_root_array[root_number-1]=i;
      };

    };


    //Exibindo as raízes primitivas encontradas
      printf("Raízes primitivas de %lu: ", n);
      for(uint64_t k=0; k<root_number; ++k)
        printf("%lu, ", primitive_root_array[k]);
        printf("...\n");

    //Limpando o cachê de memoria
    free(primitive_root_array);                                     

};

//*************************************************************************************************************************
//FIM DO HEADER
#endif
