//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE LUCAS-LEHMER PARA TESTAR A PRIMALIDADE DE NÚMEROS DE MERSENNE

/*

NÚMEROS DE MERSENNE SÃO NÚMEROS DA FORMA M(n)=(2^n)-1. PARA QUE M(n) SEJA PRIMO n TAMBÉM DEVE SER. 
O TESTE DE LUCAS-LEHMER É UM CASO PARTICULAR DO TESTE (n+1) QUE TESTA A PRIMALIDADE DE UM INTEIRO
USANDO SEQUÊNCIAS DE LUCAS.

PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/n_plus_one_primality_test.h
                          https://en.m.wikipedia.org/wiki/Mersenne_prime
                          https://t5k.org/mersenne/

*/


//****************************************************************************************************************
//CABEÇALHO
#ifndef MERSENNE_PRIME_H
#define MERSENNE_PRIME_H
#include<gmp.h>
#include"baillie_psw_prime_test.h"

//****************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void get_mersenne_number(mpz_t, uint64_t);
bool is_mersenne_prime(uint64_t, mpz_t);


//****************************************************************************************************************
//FUNÇÕES
//Função que calcula um número de Mersenne
void get_mersenne_number(mpz_t M, uint64_t n){

  //Variáveis locais
  mpz_t power, two, one;
  
  //Procedimento
    //Inicializando variáveis locais
    mpz_init(power);
    mpz_init(one);
    mpz_init(two);
  
    //Calculando o número de Mersenne
    mpz_set_ui(two, 2);
    mpz_set_ui(one, 1);
    mpz_pow_ui(power, two, n);
    mpz_sub(M, power, one);


    //Limpando o cachê de memória
    mpz_clear(power);
    mpz_clear(one);
    mpz_clear(two);

};


//Função que testa a primalidade de um número de Mersenne usando o teste de Lucas-Lehmer
bool is_mersenne_prime(uint64_t n, mpz_t M){

  //Teste 1: testando a primalidade de n
  if(baillie_psw_test(n)==false) return false;

  //Variáveis locais
  mpz_t temp1, temp2, s, two;


  //Procedimentos
    //Inicializando variáveis 
    mpz_init(temp1);
    mpz_init(temp2);
    mpz_init(s);
    mpz_init(two); 

    mpz_set_ui(two, 2);
    mpz_set_ui(s, 4);


    //Loop principal
    for(uint64_t p=3; p<=n; p++){
      
      mpz_mul(temp1, s, s);
      mpz_sub(temp2, temp1, two);
      mpz_mod(temp1, temp2, M);

      mpz_set(s, temp1);

    };

    uint64_t tester=mpz_get_ui(s);
    

    //Limpeza do cachê de memória
    mpz_clear(temp1);
    mpz_clear(temp2);
    mpz_clear(s);
    mpz_clear(two);  


  //Resultado
  if(tester==0) return true;
  else return false;  

};


//****************************************************************************************************************
//FIM DO HEADER
#endif
