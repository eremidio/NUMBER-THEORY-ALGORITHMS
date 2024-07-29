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
#include<stdlib.h>


//**********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
double von_mangoldt_function(int64_t);
double first_chebyshev_function(int64_t);
double second_chebyshev_function(int64_t);
double pi_weight_function(int64_t);

//**********************************************************************************************************************************************************************
//FUNÇÕES
//Função Λ de von Mangoldt
double von_mangoldt_function(int64_t n){

  //Variáveis locais
  int64_t prime;

  //Resultado
  if(fast_prime_power_detection(n, &prime)==false) return 0.0;
  else return log(prime);

};

//Função Θ de Chebyshev do primeiro tipo
double first_chebyshev_function(int64_t n){


  //Variáveis locais
  int64_t i=0;
  double result=0.0;

  //Procedimentos
  for(i=2; i<=n; ++i){
    if(baillie_psw_test(i)==true) result+=log(i);
  };

  //Resultado
  return result;
};

//Função ψ de Chebyshev do segundo tipo
double second_chebyshev_function(int64_t n){

  //Variáveis locais
  int64_t i,prime;
  double result=0.0;

  //Procedimentos
    //Loop principal
    for(i=2; i<=n; ++i){
      if(fast_prime_power_detection(i, &prime)==false) continue;
      else result+=log(prime);
    }

  //Resultado
  return result;

};


//Função Π de contagem de primos de Riemann
double pi_weight_function(int64_t n){

  //Variáveis locais
  int64_t i, prime, power;
  double sum=0.0;

  //Procedimentos


  
    //Loop principal
    for(i=2; i<=n; i++){

      //Checando se o número em questão é potência de um primo
      if(fast_prime_power_detection(i, &prime)==true){
        power=0;
        while(i>=2){
          i/=prime;
          power++;
        }
        sum+=(1.0/power);

      }

    }

  //Resultado
  return sum;


};

//**********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
