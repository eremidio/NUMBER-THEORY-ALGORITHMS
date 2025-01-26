//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA  ROTINAS EFICIENTES PARA CALCULAR INVERSOS MODULARES

/*
OS SEGUINTES ALGORITMOS SÃO UMA ALTERNATIVA AO ALGORITMO DE EUCLIDES ESTENDIDO.

PARA MAIORES INFORMAÇÕES: Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance


*/


//**********************************************************************************************
//CABEÇALHO
#ifndef FAST_MODULAR_INVERSION_H
#define FAST_MODULAR_INVERSION_H
#include"mod_bin_exponentiation128.h"
#include<stdbool.h>
#include<math.h>

//**********************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t fast_modular_inverse(int64_t, int64_t);
__int128_t fast_modular_inverse_mersenne_prime(__int128_t, __int128_t);


//**********************************************************************************************
//FUNÇÕES



//Função que calcula inversos modulares a menos de uma relação de congruência
int64_t fast_modular_inverse(int64_t n, int64_t p){

  //Variáveis locais
  int64_t z=(n>p)?(n%p):n;
  __int128_t a=1;


  //Procedimentos
    //Loop principal
    while(z!=1){
  
      int64_t q = -floor(p/z);
      z=p+(q*z);
      a=(a*q)%p;

    }

  //Resultado 
  return ((int64_t)(a));

};


//Função que calcula inversos modulares a menos de uma relação de congruência de primos de Mersenne
__int128_t fast_modular_inverse_mersenne_prime(__int128_t n, __int128_t p){

  
  //Variáveis locais
  __int128_t a=1, b=0, y=n, z=p;
  int q=0;

  //Procedimentos
    //Calculando a potência q p=2^q-1
    __int128_t p_=p+1;
    while(p_>1){
      p_>>=1;
      q++;
    }


    //Loop principal
    while(1){

      //Calculando o parâmetro e tal que 2^e divide n
      int e=0;
      while(!(y&1)){
        y>>=1;
        e++;
      };

      //Redução euclidiana
      a=(mod_bin_pow(2, (q-e), p)*a)%p;
      if(y==1) break;

      a=(a+b); b=a;
      y=(y+z); z=y;
      

  };//Fim do loop principal


  //Resultado
  return a;

};


//**********************************************************************************************
//FIM DO HEADER
#endif
