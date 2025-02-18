//VAMOS CRIAR UM PROGRAMA QUIE IMPLEMENTA UMA VERSÃO SIMPLIFICADA DO TESTE DE PRIMALIDADE DE FRÖBENIUS

/*
O SEGUINTE TEOREMA PODE SER USADO PARA DEFINIR UM PSEUDOPRIMO DE FRÖBENIUS: SEJA c UM INTEIRO PRIMO ÍMPAR
TAL QUE (c|n)=(-1), ENTÃO n É UM PSEUDO PRIMO DE FRÖBENIUS SE E SOMENTE (1+√c)^n = (1-√c) mod n.

O TEOREMA ACIMA PODE SER REFORMULADO EM TERMOS DO NÚMERO ALGÉBRICO (a+b√c) COM mdc(ab, n)=1 E c NÃO TENDO
FATORES PRIMOS REPETIDOS.

O SEGUINTE TEOREMA PODE SER USADO PARA OBTER UM FATOR DE n CASO n SEJA UM PSEUDOPRIMO DE FRÖBENIUS NA
DEFINIÇÃO DO TEOREMA ANTERIOR: SEJA n=pq UM PSEUDOPRIMO DE FRÖBENIUS COM p, q PRIMOS EM RELAÇÃO AOS
PARÂMETROS (a, b, c). ENTÃO SE (c|p)=(-1) E (c|q)= 1, ENTÃO p É UM DOS FATORES PRIMOS DE 
mdc(a(q-1)-1, b(q-1)); CASO (c|p)=1 E (c|q)=(-1) ENTÃO p É UM DOS FATORES PRIMOS DE
mdc(a(q+1)-N, b(q+1)) COM N=(a²-b²c).

TAIS TEOREMAS PROVIDO DE ALGUMAS PROPOSIÇÕES ADICIONAIS PERMITEM ELABORAR UM SIMPLES E DETERMINÍSTICO
TESTE DE PRIMALIDADE PARA INTEIROS DE 64 BITS (COM MARGEM DE ERRO EXTREMAMENTE BAIXA PARA n<(2^64),
PARA 2^60 NÃO EXISTEM PSEUDOPRIMOS).

PARA MAIORES INFORMAÇÕES: https://ar5iv.labs.arxiv.org/html/1307.7920


*/


//****************************************************************************************************
//CABEÇALHO
#ifndef QUADRATIC_FROBENIUS_FINITE_FIELD_VERSION_H
#define QUADRATIC_FROBENIUS_FINITE_FIELD_VERSION_H
#include"cipolla_algorithm.h"
#include"prime_power_detection.h"
#include<stdbool.h>

//****************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool quadratic_frobenius_test_finite_field(int64_t);

//****************************************************************************************************
//FUNÇÕES
//Função que implementa uma versão simplicada do teste de primalidade de Fröbenius
/*
  NOTA: usaremos a rotina de exponenciação modular em GF(p²) disponível no arquivo
        cipolla_algorithm.h
*/

bool quadratic_frobenius_test_finite_field(int64_t n){

  //Variáveis locais
  int primes500[95]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
    149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317,
    331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499};
  struct algebraic_quadratic_number z, zp;
  int64_t c;


  //Procedimentos
    //Teste 1: descartando quadrados perfeitos
    if(fast_square_detection(n, &c) == true) return false;

    //Teste 2: divisão por pequenos primos
    for(int i=0; i<95; ++i){
      if(n==primes500[i]) return true;
      else if(n%primes500[i]==0) return false;
    };
    if(n<(primes500[94]*primes500[94])) return true;//n<499² condição suficiente de primalidade


    //Etapa 2: calculando o menor c primo ímpar tal que (c|n)==(-1)
    for(int j=0; j<95; ++j){
      c=primes500[j];
      if(kronecker(c, n)==(-1)) break;
    }


    //Teste 3: checando a relação de congruência  (1+√c)^n = (1-√c) mod n
    z.a=1; z.b=1; z.d=c;
    zp=algebraic_quadratic_pow_mod(z, n, n);
    if(zp.b<0) zp.b+=n;

    if(zp.a==1 && zp.b==(n-1)) return true;
    else return false;

   
};

//****************************************************************************************************
//FIM DO HEADER
#endif
