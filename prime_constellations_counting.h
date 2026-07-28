//VAMOS CRIAR UM PROGRAMA QUE COMPUTA O NÚMERO DE OCORRÊNCIAS DE CONSTELAÇÕES DE NÚMEROS PRIMOS

/*

PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/prime_constellations.h

*/


//**********************************************************************************************************************************************
//CABEÇALHO
#ifndef PRIME_CONSTELLATION_COUNTING_H
#define PRIME_CONSTELLATION_COUNTING_H
#include"logarithmic_integral_continued_fraction.h"
#include<stdint.h>
#include<inttypes.h>
#include<stdio.h>


//CONSTANTES GLOBAIS
int32_t PRIME_ARRAY[664579];//Lista de primos até 10^7


//**********************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
long double factorial_db(int);
long double logarithm_negative_power_integral(long double, int);
void fill_prime_buffer();
int32_t small_prime_residual_class_counting(int32_t, int[], int);
long double compute_hardy_littlewood_constant(int[], int);
long double prime_constellation_counting(int[], int, long double);


//**********************************************************************************************************************************************
//FUNÇÕES
//Função que calcula o fatorial de um inteiro
long double factorial_db(int n){

  //Variáveis locais
  long double result=1.0;


  //Procedimentos: loop principal
  while(n>1){
    result*=n;
    --n;
  }
  
  
  //Resultado
  return result;

};


//Função que computa a integral definida de 2 a x da função f(x)=ln(x)^{-N} com N inteiro
long double logarithm_negative_power_integral(long double x, int N){

  //Variáveis locais
  long double fact1 = factorial_db(N-1), fact2 = 0;
  long double ln_x = log(x), ln_2 = log(2), log_power = 0.0;
  long double result = logarithmic_integral_continued_fraction(x); 


  //Procedimento: loop principal
  for(int k=0; k<=(N-2); ++k){

    fact2 = factorial_db(k);

    log_power = pow(ln_2, (k+1));
    result = result+((2*fact2)/log_power);

    log_power = pow(ln_x, (k+1));
    result = result-((x*fact2)/log_power);

  }


  //Resultado
  result/=fact1;
  return result;

};


//Função que preenche um buffer de primos até 10^7
void fill_prime_buffer(){

  //Variáveis locais
  FILE* primefile;
  int32_t p=0, counter=0;

  
  //Procedimentos 
    //Abrindo o arquivo para leituta
    primefile=fopen("prime_list.txt", "r");
    
    //Lendo o conteúdo do arquivo estocando os primos em um array
    while(fscanf(primefile, "%i", &p)==1){
      PRIME_ARRAY[counter]=p;
      counter++;
    }

    //Fechando o arquivo
    fclose(primefile);

};


//Função que computa o número de classes residuais não ocupadas módulo um número primo pequeno
int32_t small_prime_residual_class_counting(int32_t p, int ktuple[], int N){

  //Variáveis locais
  int* residual_class = (int*)malloc(p*sizeof(int));
  int hits = 0, r=0;


  //Procedimentos
    //Ajuste de variáveis 
    for(int32_t i=0; i<p; ++i) residual_class[i]=0;

    //Computando as classes residuais
    for(int k=0; k<N; ++k){
      r=(ktuple[k]%p);
  
      if(residual_class[r]<1){
        hits++;
        residual_class[r]=1;
      }

    }

    //Limpando ocachê de memória
    if(residual_class) free(residual_class);
    residual_class=NULL;


  //Resultado
  return (p-hits);

};


//Função que computa as constantes de Hardy-Littlewood
long double compute_hardy_littlewood_constant(int ktuple[], int N){

  //Pré-computação: preenchendo um buffer de números primos
  fill_prime_buffer();


  //Variáveis locais
  long double prime_power=0, prime_minus_one_power=0;
  long double result = 1.0;
  int32_t w=0;
  int maximum=0;


  //Procedimentos
    //Determinando o elemento máximo da enupla
    for(int i=0; i<N; ++i){
      if(ktuple[i]>maximum) maximum = ktuple[i];
    }

    //Loop principal: sobre o buffer de primos até 10^7
    for(int32_t k=0; k<664579/* π(10^7) */; ++k){

      prime_minus_one_power = pow((long double)(PRIME_ARRAY[k]-1), N);
      prime_power           = pow((long double)PRIME_ARRAY[k], N-1);

      //Computando o número de classes residuais livres
      if(PRIME_ARRAY[k]>maximum){
        w = PRIME_ARRAY[k]-N;
      }
      else{
        w = small_prime_residual_class_counting(PRIME_ARRAY[k], ktuple, N);
      }


      result *= ((long double)w * prime_power);
      result /= prime_minus_one_power;

    }


  //Resultado
  return result;

};


//Função que computa o número de ocorrências de constelações de primos
long double prime_constellation_counting(int ktuple[], int N, long double x){

  //Variáveis locais
  long double parcel1 = logarithm_negative_power_integral(x, N);
  long double parcel2 = compute_hardy_littlewood_constant(ktuple, N);


  //Resultado
  return (parcel1*parcel2);

};

//**********************************************************************************************************************************************
//FIM DO HEADER
#endif
