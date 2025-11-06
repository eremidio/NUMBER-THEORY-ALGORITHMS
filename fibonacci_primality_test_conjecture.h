//VAMOS CRIAR UM PROGRAMA QUE TESTA A PRIMALIDADE DE UM INTEIRO USANDO A SEQUÊNCIA DE FIBONACCI

/*

A SEGUINTE CONJECTURA PODE SER USADA PARA TESTAR A PRIMALIDADE DE NÚMEROS INTEIROS.

CONJECTURA: SEJA F(n) O N-ÉSIMO TERMO DA SEQUÊNCIA DE FIBONACCI, PARA n PRIMO E n>5 UMA DAS SEGUINTES IDENTIDADES
RELAÇÕES DE CONGRUÊNCIA É VÁLIDA PARA n NÃO DIVISÍVEL POR 2 OU 3: SE n=1,9 (mod 10) ENTÃO F(n)= 1 (mod n), SE
SE n=3,7 (mod 10) ENTÃO F(n)= (-1) (mod n).

PARA MAIORES INFORMAÇÕES: https://vixra.org/pdf/1909.0461v1.pdf

*/


//************************************************************************************************************
//CABEÇALHO
#ifndef FIBONACCI_PRIMALITY_TEST_CONJECTURE_H
#define FIBONACCI_PRIMALITY_TEST_CONJECTURE_H
#include"fast_lucas_sequence.h"
#include<stdbool.h>


//************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool fibonacci_primality_test_conjecture(int64_t);


//************************************************************************************************************
//FUNÇÕES
//Função que testa a primalidade de um inteiro usando a sequência de Fibonacci
bool fibonacci_primality_test_conjecture(int64_t n){

  //Casos bases:
  if(n<2) return false;
  if(n==2 || n==3 || n==5) return true;
  if(!(n&1) || n%3==0 || n%5==0) return false;

  //Variáveois locais
  __int128_t Un=0, Vn=0;


  //Procedimentos: compuntando o n-ésimo termo da sequência de Fibonacci
  fast_modular_lucas_sequence(1, (-1), n, n, &Un, &Vn);
  if(Un<0) Un+=n;

  
  //Resultado
  if(Un==1){
    int mod=n%10;
    if(mod==1 || mod==9) return true;
  };
  if(Un==(n-1)){
    int mod=n%10;
    if(mod==3 || mod==7) return true;
  };
  return false;

};


//************************************************************************************************************
//FIM DO HEADER
#endif
