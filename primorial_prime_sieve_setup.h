//VAMOS CRIAR UM PROGRAMA QUE COMPUTA UMA SEQUÊNCIA DE INTEIROS USADAS NA GERAÇÃO DE NÚMEROS K-PRIMOS DE 64 BITS


/*

SEJA #n=Πp(i) O PRIMORIAL DE n (PRODUTO DE PRIMOS INFERIORES A n), E SEJA m E j INTEIROS TAIS QUE p(m)>j.
SEJA J(k)= #j/p(k), COM k INTEIRO E k<m. DEFINIMOS T(n, k)= J(k)*(J(k)⁻¹ mod p(k)).

UM NÚMERO n É CHAMADO DE K-PRIMO (PRIMO DE ORDEM K) SE n NÃO FOR DIVISÍVEL PELOS k-ÉSIMOS PRIMEIROS NÚMEROS PRIMOS
{p(1)=2, p(2)=3,..., p(k)=P}.

A SEGUINTE PROPOSIÇÃO É VALÍDA:
PROPOSIÇÃO: PARA UM INTEIRO r K-PRIMO TAL QUE #m<p E #(m+1)>p, VALE A IDENTIDADE r=Σ T(n, k)(r mod p(k)).

TAL PROPOSIÇÃO É EXTREMAMENTE ÚTIL PARA SE GERAR NÚMEROS K-PRIMOS EM UM DETERMINADO INTERVALO DE FORMA EFICIENTE.
NO INTERVALO [p(k)+1, p²(k)] OS NÚMEROS K-PRIMOS SÃO PRIMOS. ESTA PROPOSIÇÃO DÁ ORIGEM A UM ALGORITMO QUE É
EQUIVALENTE AO ALGORITMO DE FATORAÇÃO DE RODA, PODENDO SER ÚTIL COMO SUBROTINA EM ALGORITMOS MAIS SOFISTICADOS.


PARA MAIORES INFORMAÇÕES: https://oeis.org/A240673
                          https://arxiv.org/pdf/1404.0706
                          https://arxiv.org/pdf/1209.3165
                          https://arxiv.org/pdf/1408.1888

*/


//********************************************************************************************************************************
//CABEÇALHO
#ifndef PRIMORIAL_PRIME_SIEVE_SETUP_H
#define PRIMORIAL_PRIME_SIEVE_SETUP_H
#include"fast_modular_inverse.h"
#include<stdlib.h>


//CONSTANTES
const int small_primes[15]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
uint64_t small_primorials[15];
uint64_t Tnk_prime_generating_sequence[15][15];


//********************************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
void compute_primorial_sequence();
void compute_Tnk_prime_generating_sequence();


//********************************************************************************************************************************
//FUNÇÕES
//Função que pré-computa uma lista de primorials
void compute_primorial_sequence(){

  //Procedimentos
    //Ajuste de variáveis
    small_primorials[0]=small_primes[0];
    for(int i=1; i<15; ++i) small_primorials[i]= small_primorials[i-1]*small_primes[i];

};


//Função que pré-computa a sequência geradora de primos ordem k
void compute_Tnk_prime_generating_sequence(){

  //Procedimentos
    //Ajuste da primeira linha
    Tnk_prime_generating_sequence[0][0]=1;

    //Ajuste dos valores iniciais dos termos da sequência
    for(int i=1; i<15; ++i){
      for(int j=0; j<=i; ++j){
        Tnk_prime_generating_sequence[i][j]=small_primorials[i]/small_primes[j];
      }
    }

    //Ajuste dos valores finais dos termos da sequência
    for(int i=1; i<15; ++i){
      for(int j=0; j<=i; ++j){

        int64_t mod_inv=fast_modular_inverse(Tnk_prime_generating_sequence[i][j], small_primes[j]);
        if(mod_inv<0) mod_inv+=small_primes[j];
        Tnk_prime_generating_sequence[i][j]=Tnk_prime_generating_sequence[i][j]*mod_inv;

      }
    }

};

//********************************************************************************************************************************
//FIM DO HEADER
#endif
