//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE CIPOLLA PARA CONGRUENTES QUE SÃO POTÊNCIAS DE NÚMEROS PRIMOS

/*

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Cipolla%27s_algorithm

*/


//******************************************************************************************
//CABEÇALHO
#ifndef CIPOLLA_ALGORITHM_EXTENDED_H
#define CIPOLLA_ALGORITHM_EXTENDED_H
#include"cipolla_algorithm.h"

//******************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t cipolla_algorithm_extended(int64_t, int64_t, int64_t);


//******************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de cipolla para potências de números primos
int64_t cipolla_algorithm_extended(int64_t n, int64_t prime, int64_t power){

  //Caso base
  if(power==1) return cipolla_algorithm(n, prime);



  //Variáveis locais
  struct algebraic_quadratic_number z, z1, z2, zp, zp1, zp2;
  int64_t prime_power=bin_pow(prime, power);
  int64_t s= (prime_power+ (prime_power/prime))/2;
  int64_t t=(prime_power-(2*(prime_power/prime))+1)/2;
  int64_t q=mod_bin_pow(n, t, prime_power);

  int64_t a=2, root;
  int64_t result;

  //Procedimentos
    //Seleção do parâmetro tal que (a²-n|p)=(-1)
    while(1){
      root=(a*a)-n;
      if(kronecker(root, prime)==(-1)) break;  
      else a++;
  
    }; 

    //Ajuste de variáveis
    q>>=1;
    z1.a=a; z1.b=1; z1.d=root;
    z2.a=a; z2.b=(-1); z2.d=root;

    zp1=algebraic_quadratic_pow_mod(z1, s, prime_power);
    zp2=algebraic_quadratic_pow_mod(z2, s, prime_power);

    zp.d=zp1.d;
    zp.a=(zp1.a+zp2.a); zp.a=(zp.a*q)%prime_power;
    zp.b=(zp1.b+zp2.b); zp.b=(zp.b*q)%prime_power;

    
  //Resultado
  result=zp.a;
  return result;

};


//******************************************************************************************
//FIM DO HEADER
#endif
