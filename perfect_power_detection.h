//VAMOS CRIAR UM PROGRAMA PARA DETECTAR POTÊNCIAS DE NÚMEROS INTEIROS ATÉ 64 BITS

/*

UM ALGORITMO EXTREMAMENTE SIMPLES É OBTIDO PARA DETECTAR POTÊNCIAS DE NÚMEROS INTEIROS AO SE APLICAR O MÉTODO DE APROXIMAÇÃO
DE NEWTON-RAPHSON A FUNÇÃO f(x)=x^k-n COM n, k INTEIROS.

PARA MAIORES INFORMAÇÕES: Computational Number Theory by Abhijit Das

*/


//******************************************************************************************************************************
//CABEÇALHO
#ifndef PERFECT_POWER_DETECTION_H
#define PERFECT_POWER_DETECTION_H
#include"mod_bin_exponentiation128.h"
#include<stdbool.h>
#include<math.h>


//******************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool is_perfect_k_power(uint64_t, int);
bool perfect_power_detection(uint64_t, int*);


//******************************************************************************************************************************
//FUNÇÕES
//Função que detecta números inteiros que são potências de números inteiros com um dado expoente k
bool is_perfect_k_power(uint64_t n, int k){

  //Caso base:
  if(n==1) return true;


  //Variáveis locais
  uint64_t a=0, b=0;
  int l=(int)(log2(n)+1);


  //Procedimentos
    //Ajuste de variáveis
    a=bin_pow(2, ceil(l/k));
    if(a==1) return false;


    //Loop principal: iteração do método de Newton
    while(1){

      uint64_t t=bin_pow(a, (k-1));
      b=floor((((k-1)*a*t)+n)/(k*t));

      if(b>=a) break;
      else a=b;

    };


  //Resultado
  uint64_t u=bin_pow(a, k);
  if(u==n) return true;
  else return false;

};


//Função que detecta inteiros que são potências de números primos de até 64 bits
bool perfect_power_detection(uint64_t n, int* exponent){

  //Variáveis locais
  int max_power= (int)(log2(n)+1);

  //Procedimentos
    //Loop principal
    for(int e=2; e<=max_power; ++e){
      if(is_perfect_k_power(n, e)==true){
        (*exponent)=e;
        return true;      
      }
    };


  //Resultado
  return false;

};


//******************************************************************************************************************************
//FIM DO HEADER
#endif
