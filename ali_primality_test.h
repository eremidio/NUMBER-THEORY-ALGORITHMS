//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UM ALGORITMO DE TESTAGEM DE PRIMALIDADE SIMILAR AO TESTE DE MILLER-RABIN

/*
O PRESENTE PROGRAMA PROGRAMA CONTÉM UM TESTE DE PRIMALIDADE SIMILAR AO TESTE DE MILLER-RABIN.
O TESTE EM QUESTÃO É PROBABILÍSTICO TAL COMO O TESTE DE MILLER-RABIN.

ARITGO DISPONÍVEL EM: https://eprints.qut.edu.au/16142/1/Yousef_Bani_Hammad_Thesis.pdf

*/ 


//***********************************************************************************************************************************
//CABEÇALHO
#ifndef ALI_PRIMALITY_TEST_H
#define ALI_PRIMALITY_TEST_H
#include"mod_bin_exponentiation128.h"
#include<stdbool.h>
#include<stdio.h>

//CONSTANTES
int primes_under100[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};

//***********************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t gcd_ali(uint64_t, uint64_t);
bool ali_primality_test(uint64_t);

//***********************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides
uint64_t gcd_ali(uint64_t a, uint64_t b){
  
  if(b==0) return a;
  else return gcd_ali(b, (a%b));

};

//Função que implementa o teste de primalidade de Ali
bool ali_primality_test(uint64_t n){

  //Casos triviais: n é par ou inferior a 2, primos inferiores a 100
  if(n<2) return false;
  if(n==2) return true;
  if(!(n&1)) return false;

  //Primos inferiores a 100
  for(int i=0; i<25; ++i){

    if(n==primes_under100[i]) return true;

    if(n%primes_under100[i]==0){
      printf("Fator de %lu encontrado: %i\n", n, primes_under100[i]);
      return false;
                               };
  }



//FASE 1: précomputação/detecção de compostos usando testes nas bases 2 e 4

  //Variáveis locais
  uint64_t x=(n-1);
  uint64_t b=4, tester;

  //Procedimentos
    //Teste de Fermat na base 2
    if(mod_bin_pow(2, x, n)!=1) return false;

    //Teste na base b=4
    while(!(x&1) && mod_bin_pow(b, x, n)==1) x>>=1;
    if(mod_bin_pow(b, x, n)!=1) x<<=1;

    
//FASE 2: DETECÇÃO DE FATORES PRIMOS USANDO CLASSES RESIDUAIS mod n

  //Variáveis locais
  uint64_t c, base, factor=1;
  
  //Procedimentos
    //Loop principal
    for(int i=0; i<25; ++i){

      base=primes_under100[i];
      c=mod_bin_pow(base, x , n);

      if(c==1 || c==(n-1)) continue;
      factor=gcd_ali(n, (c-1));
      if(factor>1 && factor<n) break;
      factor=gcd_ali(n, (c+1));
      if(factor>1 && factor<n) break;
        

    }



  //Caso passe nos testes acima um provável primo foi encontrado
  if(factor==1) return true;
  else{
    printf("Fator de %lu encontrado: %lu\n", n, factor);
    return false;
  }

};


//***********************************************************************************************************************************
//FIM DO HEADER
#endif
