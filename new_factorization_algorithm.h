//VAMOS IMPLEMENTAR UM ALGORITMO PARA FATORAR NÚMEROS INTEIROS USANDO UM MÉTODO SIMILAR AO MÉTODO DE STRASSEN-POLLARD PARA INTEIROS DE 64 BITS

/*
AO QUE CONSTA O PRESENTE ALGORITMO É UMA CONTRIBUIÇÃO ORIGINAL A TEORIA DOS NÚMEROS COMPUTACIONAL.
GENTILEZA INFORMAR CASO CONTRÁRIO.

O PRESENTE ALGORITMO É UMA VARIANTE DO ALGORTIMO PRESENTE NO ARTIGOS:
https://www.researchgate.net/publication/238519187_Carmichael_numbers_and_a_new_primality_test
https://ieeexplore.ieee.org/document/5662138/authors#authors

O ALGORITMO DESCRITO NOS ARTIGOS ORIGINALMENTE SE DESTINA A TESTAR A PRIMALIDADE DE UM INTEIRO,
DETECTANDO OS CHAMADOS NÚMEROS DE CARMICHAEL (PSEUDOPRIMOS NO TESTE DE FERMAT). O ALGORITMO EM 
QUESTÃO É UMA ADAPATAÇÃO DO ALGORITMO ORIGINAL AO PROBLEMA DE COMPUTAR FATORES PRIMOS DE UM
INTEIRO.

O ALGORITMO POSSUI SIMILAR AO ALGORITMO DE STRASSEN-POLLARD: PARA b VARIANDO DE n^(1/2) A 2
OS PRODUTOS [b^(n) (mod (b-1)n)] (mod n) SÃO ACUMULADOS. TOMANDO-SE O mdc DO PRODUTO COM O 
NÚMERO A SER FATORADO, UM FATOR PRIMO DO NÚMERO EM QUESTÃO É REVELADO. A COMPLEXIDADE DO
ALGORITMO É LIMITADA PELO MENOR FATOR PRIMO DO NÚMERO EM QUESTÃO. TEMPO DE EXECUÇÃO
RAZOÁVEIS SÃO OBTIDOS NO TESTE COM SEMIPRIMOS DA ORDEM DE 50 BITS. O ALGORITMO É ÚTIL PARA
REMOVER PEQUENOS FATORES PRIMOS (DA ORDEM DE 10^8) DE INTEIROS COMPOSTOS.

*/ 


//************************************************************************************************
//CABEÇALHO
#ifndef NEW_FACTORIZATION_ALGORITHM_H
#define NEW_FACTORIZATION_ALGORITHM_H
#include"mod_bin_exponentiation128.h"
#include<math.h>
#include<stdio.h>


//************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t gcd_u64(uint64_t, uint64_t);
void new_factorization_algorithm(uint64_t);

//************************************************************************************************
//FUNÇÕES
//Função que implkementa o algoritmo de Euclides
uint64_t gcd_u64(uint64_t a, uint64_t b){

  if(b==0) return a;
  else return gcd_u64(b, (a%b));

};



//Função que implementa um teste de primalidade similar ao teste de Strassen-Pollard para fatorar números inteiros
void new_factorization_algorithm(uint64_t n){

  //Variáveis locais
  __int128_t temp=1;
  uint64_t max_mod=sqrt(n);
  uint64_t factor=1, cofactor=1,  b=0, low=0;
  


  //Procedimentos
    //Loop principal
    for(uint64_t b=max_mod; b>2; --b){
      low++;
      __int128_t mod=(b-1)*n;
      __int128_t temp1=mod_bin_pow(b, n, mod);
      __int128_t temp2=mod_bin_pow((2+low-1), n, mod);
      temp=(temp*temp1)%n; temp=(temp*temp2)%n;

      //Computando fatores primos do número a ser fatorado
      uint64_t tester= temp;

      if(n<1e15) factor=gcd_u64(tester, n);
      if(n>1e15 && (low%1000)==0) factor=gcd_u64(tester, n);

      if(factor>1 && factor<n){
        cofactor=n/factor;  
        break;
                              }
    
    }

  //Resultado da execução do algoritmo
  if(factor==1 || cofactor==1)
    printf("O algoritmo não encontrou fatores primos do número em questão.\n");
  else
    printf("Fatores primos de %lu encontrados: %lu e %lu\n", n, factor,cofactor);


};



//************************************************************************************************
//FIM DO HEADER
#endif
