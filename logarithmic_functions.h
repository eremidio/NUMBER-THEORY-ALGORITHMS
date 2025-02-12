//VAMOS CRIAR UMA ROTINA PARA O CÁLCULO DE FUNÇÕES ARITMÉTICAS QUE ESTÃO RELACIONADAS COM A FUNÇÃO LOGARÍTMICA NATURAL

/*
PARA MAIORES REFERÊNCIAS:
https://en.wikipedia.org/wiki/Arithmetic_function
https://en.wikipedia.org/wiki/Von_Mangoldt_function
https://en.wikipedia.org/wiki/Chebyshev_function

*/

//**********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef LOGARITHMIC_FUNCTIONS_H
#define LOGARITHMIC_FUNCTIONS_H
#include"prime_power_detection.h"
#include"prime_table_reading.h"
#include<stdlib.h>


//**********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
double von_mangoldt_function(uint64_t);
double first_chebyshev_function(uint64_t, uint64_t[]);
double second_chebyshev_function(uint64_t, uint64_t[]);



//**********************************************************************************************************************************************************************
//FUNÇÕES
//Função Λ de von Mangoldt
double von_mangoldt_function(uint64_t n){

  //Variáveis locais
  int64_t prime;

  //Resultado
  if(fast_prime_power_detection(n, &prime)==false) return 0.0;
  else return log(prime);

};

//Função Θ de Chebyshev do primeiro tipo
double first_chebyshev_function(uint64_t n, uint64_t prime_list[]){


  //Variáveis locais
  double result=0.0;

  //Procedimentos
    //Loop sobre números primos estocados em uma lista
    for(int64_t i=0; prime_list[i]<=n ; ++i){
     result+=log(prime_list[i]);


    }

  //Resultado
  return result;

};

//Função ψ de Chebyshev do segundo tipo
double second_chebyshev_function(uint64_t n, uint64_t prime_list[]){

  //Variáveis locais
  double result=0.0, log_pp;
  uint64_t prime_power;


  //Procedimentos
    //Loop sobre números primos estocados em uma lista
    for(uint64_t i=0; prime_list[i]<=n ; ++i){
 
        prime_power=prime_list[i];
        log_pp=log(prime_power);

        while(prime_power<=n){
          result+=log_pp; log_pp+=log_pp;//log(x^n)=nlog(x)
          prime_power*=prime_power;
        }

    };

  //Resultado
  return result;

};


//**********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
