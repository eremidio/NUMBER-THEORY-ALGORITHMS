//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UM TESTE DE PRIMALIDADE BASEADO NO CRITÉRIO DE VANTIEGHEMS PARA INTEIROS PEQUENOS (ATÉ 31)

/*
DE ACORDO COM UM TEOREMA DEVIDO A VANTIEGHEMS UM NÚMERO PRIMO n SATISFAZ A SEGUINTE IGUALDADE PARA k=1, ..., (n-1): Π(2^k -1) = n (mod {2^n-1}).
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

//**************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
__int128_t generate_vantieghems_factor(int);
bool vantieghems_criterion(int);

//**************************************************************************************************************************************
//FUNÇÕES
//Função que determina 2^n-1 provido o valor de n
__int128_t generate_vantieghems_factor(int n){

 //Resultado
 return (2<<(n-1))-1;
                                             };

//Função que determina se um inteiro ímpar é primo usando o critério de Vantieghem
bool vantieghems_criterion(int n){
 //RESTRIÇÃO
 assert(n<=31);

 //Variáveis locais
 __int128_t modulus=generate_vantieghems_factor(n), tester=1, multiplier;
 int k;

 //Procedimentos
  //Loop principal
  for(int k=1; k<n; k++){

   multiplier=generate_vantieghems_factor(k);
   tester=(multiplier*tester)%modulus;

                        };


  //Resultado
  if(tester==n)
   return true;
  else
   return false;

                                 };


//**************************************************************************************************************************************
//FIM DO HEADER
#endif
