//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UM TESTE DE PRIMALIDADE BASEADO NO CRITÉRIO DE VANTIEGHEMS PARA INTEIROS

/*
DE ACORDO COM UM TEOREMA DEVIDO A VANTIEGHEMS UM NÚMERO PRIMO n SATISFAZ A SEGUINTE IGUALDADE
PARA k=1, ..., (n-1): Π(2^k -1) = n (mod {2^n-1}).
TAL TEOREMA FORNECE UM SIMPLES TESTE DE PRIMALIDADE.

PARA MAIORES INFORMAÇÕES:https://en.wikipedia.org/wiki/Vantieghems_theorem

*/ 


//**************************************************************************************************************************************
//CABEÇALHO
#ifndef VANTIEGHEMS_CRITERION_H
#define VANTIEGHEMS_CRITERION_H
#include<stdint.h>
#include<stdbool.h>
#include<assert.h>
#include<gmp.h>


//**************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool vantieghems_criterion(unsigned long);

//**************************************************************************************************************************************
//FUNÇÕES

//Função que determina se um inteiro ímpar é primo usando o critério de Vantieghem
bool vantieghems_criterion(unsigned long n){

  //Caso base
  if(n<2) return false;

  //Variáveis locais
  mpz_t N, p, p1, p2, p3, p4, two;


  //Procedimentos
    //Inicializando variáveis
    mpz_init(N);      
    mpz_init(p);
    mpz_init(p1);
    mpz_init(p2);
    mpz_init(p3);
    mpz_init(p4);
    mpz_init(two);

    mpz_set_ui(p, 1);
    mpz_set_ui(two, 2);
    mpz_pow_ui(p1, two, n);
    mpz_sub_ui(N, p1, 1);//N=2^n-1
    

    //Loop principal
    for(unsigned long i=2; i<n; ++i){

      mpz_pow_ui(p1, two, i);
      mpz_sub_ui(p2, p1, 1); //p2=(2^i)-1
      mpz_mul(p3, p2, p);
      mpz_mod(p4, p3, N);    
      mpz_set(p, p4);

    };
  
    mpz_mod(p1, p, N);
    unsigned long result=mpz_get_ui(p1);
      

    //Limpando cachê de memória
    mpz_clear(N);      
    mpz_clear(p);
    mpz_clear(p1);
    mpz_clear(p2);
    mpz_clear(p3);
    mpz_clear(p4);
    mpz_clear(two);


  //Resultado
  if(result==n) return true;
  else return false;


};


//**************************************************************************************************************************************
//FIM DO HEADER
#endif
