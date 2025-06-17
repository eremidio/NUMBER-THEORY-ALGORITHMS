//VAMOS CRIARUM PROGRAMA QUE COMPUTA A FUNÇÃO DE CONTAGEM DE FATORES PRIMOS NÃO NECESSARIAMENTE DISTINTOS DE UM INTEIRO

/*

A FUNÇÃO Ω(n) É UMA FUNÇÃO ARITMÉTICA MULTIPLICATIVA QUE COMPUTA OS NÚMEROS DE FATORES PRIMOS NÃO NECESSARIAMANETE DISTINTOS
DE UM INTEIRO n.

TAL FUNÇÃO SATIFAZ A IDENTIDADE ENVOLVENDO CONVOLUÇÃO DE DIRICHLET Ω*μ=1{p^k}, ONDE 1{p^k} É A FUNÇÃO CARACTERÍSTICA DE
POTÊNCIAS DE NÚMEROS PRIMOS. USANDO A FÓRMULA DE INVERSÃO DE DIRICHLET PODEMOS REESCREVER A FÓRMULA ACIMA COMO 
Ω(n)= Σ 1{p^k}(d), ONDE A SOMA É FEITA SOBRE TODOS OS DIVISORES DE n. DESTA FORMA PODEMOS COMPUTAR A FUNÇÃO Ω(n) POR MEIO
DE UMA VARIANTE DA PENEIRA DE ERATÓSTENES.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Dirichlet_convolution#Dirichlet_inverse
                          https://en.wikipedia.org/wiki/Möbius_inversion_formula#Statement_of_the_formula
                          https://en.wikipedia.org/wiki/Prime_omega_function


*/


//*********************************************************************************************************************
//CABEÇALHO
#ifndef BIG_PRIME_OMEGA_FUNCTION_H
#define BIG_PRIME_OMEGA_FUNCTION_H
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>


//*********************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool* compute_prime_power_characteristic_function(int32_t);
int32_t* compute_capital_omega_function(int32_t);


//*********************************************************************************************************************
//FUNÇÕES
//Função que computa a função característica de potências de números primos em um intervalo
bool* compute_prime_power_characteristic_function(int32_t n){

  //Variáveis locais
  bool* prime_power_array = (bool*) calloc((n+1), sizeof(bool));


  //Procedimentos
    //Ajuste do array de valores
    prime_power_array[2]=true; prime_power_array[3]=true;
    for(int32_t i=5; i<=n; i+=6){
      prime_power_array[i]=true;
      prime_power_array[i+2]=true;
    };

    //Computando números primos
    for(int32_t i=2; (i*i)<=n; i++){
      if(prime_power_array[i]){
        for(int32_t j=(2*i); j<=n; j+=i){
          if(prime_power_array[j]==true) prime_power_array[j]=false;
        }
      }
    };

    //Computando potências de números primos
    for(int32_t k=2; (k*k)<=n; ++k){

      if(prime_power_array[k]){
        int32_t l=k;
        while(l<=n){
          prime_power_array[l]=true;
          l*=k;
        }
      }
    };  


  //Resultado
  return prime_power_array;
  
};


//Função que computa a função Ω(n) em um intervalo
int32_t* compute_capital_omega_function(int32_t n){

  //Variáveis locais
  bool* prime_power_array = compute_prime_power_characteristic_function(n);
  int32_t * big_prime_omega_array = (int32_t*) calloc((n+1), sizeof(int32_t));

  
  //Procedimentos
    //Loop principal: iterando sobre potências de números primos
    for(int32_t i=2; i<=n; ++i){
      if(prime_power_array[i]){
        for(int32_t j=i; j<=n; j+=i) big_prime_omega_array[j]=big_prime_omega_array[j]+1;
      }
    }

    //Limpando o cachê de memória
    if(prime_power_array) free(prime_power_array); prime_power_array=NULL;
  
  //Resultado
  return big_prime_omega_array;

};


//*********************************************************************************************************************
//FIM DO HEADER
#endif
