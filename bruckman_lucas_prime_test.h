//VAMOS CRIAR UM PROGRAMA PARA TESTAR A PRIMALIDADE USANDO A SEQUÊNCIA DOS NÚMEROS DE LUCAS

/*

A SEGUINTE IDENTIDADE É SATISFEITAS POR NÚMEROS NÚMEROS PRIMOS: L(n)=1 (mod n).
L(n) DENOTA O n-ÉSIMO TERMO DA SEQUÊNCIAS DE NÚMEROS DE LUCAS DEFINIDOS PELAS
RELAÇÕES RECURSIVAS: L(n)=L(n-1)+L(n-2) COM L(1)=1, L(2)=3.

PARA MAIORES INFORMAÇÕES: https://mathworld.wolfram.com/LucasNumber.html
                          https://mathworld.wolfram.com/LucasPseudoprime.html
                          https://www.fq.math.ca/Scanned/32-2/bruckman2.pdf


*/


//********************************************************************************************
//CABEÇALHO
#ifndef BRUCKMAN_LUCAS_PRIME_TEST_H
#define BRUCKMAN_LUCAS_PRIME_TEST_H
#include"mod_bin_exponentiation128.h"
#include"fast_lucas_sequence.h"
#include<stdbool.h>


//********************************************************************************************
//DECALARAÇÃO DE FUNÇÕES
bool bruckman_lucas_prime_test(int64_t);


//********************************************************************************************
//FUNÇÕES 
//Função que testa a primalidade de um inteiro usando a sequência de números de Lucas
bool bruckman_lucas_prime_test(int64_t n){

  //Casos bases:
  if(n<2) return false;
  if(n==2 || n==3 || n==5) return true;
  if(!(n&1) || (n%3)==0 ||  (n%5)==0) return false;


  //Variáveis locais
  __int128_t Un, Vn;


  //Procedimentos
    //Teste de Fermat na base 2
    if(mod_bin_pow(2, (n-1), n)!=1) return false;

    //Testando a relação de congruência  L(n)=1 (mod n)
    fast_modular_lucas_sequence(1, (-1), n, n, &Un, &Vn);


    //Resultado
    if(Vn==1) return true;
    else return false;

};



//********************************************************************************************
//FIM DO HEADER
#endif
