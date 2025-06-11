//VAMOS CRIAR UM PROGRAMA QUE COMPUTA O NÚMERO DE FATORES PRIMOS DISTINTOS DE UM INTEIRO USANDO CONVOLUÇÕES DE DIRICHLET 

/*

A FUNÇÃO ω(n) COMPUTA O NÚMERO DE FATORES PRIMOS DISTINTOS DE UM INTEIRO n. TAL FUNÇÃO PODE SER COMPUTADA DE FORMA EFICIENTE
EM UM INTERVALO USANDO CONVOLUÇÕES DE DIRICHLET |μ|*1=2^ω OU EM FORMA EXPLICITA Σ|μ(d)|=2^ω(n), ONDE d DENOTA OS DIVISORES
DE n.

TAL RELAÇÃO PERMITE USAR UMA TÉCNICA SIMILAR A PENEIRA DE ERATÓSTENES PARA COMPUTAR ω(n) EM UM INTERVALO.

PARA MAIOES INFORMAÇÕES: https://en.wikipedia.org/wiki/Prime_omega_function#Example_I:_A_modified_summatory_function
                         https://en.wikipedia.org/wiki/Dirichlet_convolution

*/



//*****************************************************************************************************************************
//CABEÇALHO
#ifndef PRIME_OMEGA_FUNCTION_H
#define PRIME_OMEGA_FUNCTION_H
#include"mobius_function_lambert_series.h"
#include<math.h>


//*****************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int32_t* generate_prime_omega_function_array(int32_t);


//*****************************************************************************************************************************
//FUNÇÕES 
//Função que computa valores  da função ω(n) em um intervalo
int32_t* generate_prime_omega_function_array(int32_t n){

  //Ajuste variáveis
  n++;

  //Variáveis locais
  int32_t* prime_omega_array=(int32_t*) calloc((n+1), sizeof(int32_t));
  int8_t* mobius_array=compute_mobius_function(n);


  //Procedimentos
    //Loop principal: interando sobre o array da função de Möbius
    for(int32_t i=1; i<=n; ++i){

      //Restrição
      if(mobius_array[i]==0) continue;
      
      //Calculando 2^ω
      for(int32_t j=i; j<n; j+=i){
        prime_omega_array[j]=prime_omega_array[j]+1;
      }

    };
    
    //Ajuste do resultado
    for(int32_t k=1; k<=n; ++k) prime_omega_array[k]=floor(log2(prime_omega_array[k]));

    
    //Limpando o cachê de memória
    if(mobius_array) free(mobius_array); mobius_array=NULL;


  //Resultado
  return prime_omega_array;

};

//*****************************************************************************************************************************
//FIM DO  HEADER
#endif
