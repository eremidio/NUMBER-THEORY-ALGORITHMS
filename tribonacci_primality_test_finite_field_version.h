//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA VERSÃO DO TESTE DE PRIMALIDADE USANDO A SEQUÊNCIA DE TRIBONACCI

/*

A SEQUÊNCIA DE TRIBONACCI PODE SER DEFINIDA PELAS RELAÇÕES RECURSIVAS T(0)=0; T(1)=1, T(2)=1 E T(n)=T(n-1)+T(n-2)+T(n-3).
UM SIMPLES TESTE DE PRIMALIDADE BASEIA-SE NA SEGUINTE PROPROSIÇÃO:  PARA n PRIMO T(n)= 0 (mod n) PARA n=1,3 (mod 8) OU
T(n)= 4 (mod n) PARA n=5,7 (mod 8), PARA n>5.

TAL TESTE PODE SER IMPLEMENTADO DE FORMAS MAIS EFICIENTES DO QUE USANDO DIRETAMENTE AS RELAÇÕES DE RECORRÊNCIA DA
DEFINIÇÃO ACIMA.

PODEMOS EMPREGAR, POR EXEMPLO, A EXPONENCIAÇÃO DE MATRIZES. DADO A MATRIZ

A=|0 3 0|, VALE AS SEGUINTES IDENTIDADES PARA UM INTEIRO n SE n FOR PRIMO:
  |0 0 3|
  |1 1 1|

A^(n-1)=|1 0 0|, SE n = 1,3 (mod 8);
        |0 1 0|
        |0 0 1|


A^(n+1)=|4 2 3|, SE n = 5,7 (mod 8);
        |1 5 3|
        |1 2 6|


USANDO CORPOS FINITOS GF(p²) CUJOS ELEMENTOS SÃO DA FORMA z=(a+b√n) (mod p), PODEMOS EXPRESSAR O TESTE ACIMA POR MEIO DAS 
IDENTIDADES: (1-√-2)^(n-1)  mod n = 1, SE n = 1,3 (mod 8); OU (1-√-2)^(n-1) mod n = 3, SE n = 5,7 (mod 8).

NÚMEROS COMPOSTOS QUE PASSAM NESTE TESTE SÃO DENOMINADOS PSEUDOPRIMOS DE TRIBONACCI. NÃO EXITEM PSEUDOPRIMOS CONHECIDOS
TAIS QUE n = 5,7 (mod 8).


TAL TESTE É UM EXEMPLO DE TESTE DE PRIMALIDADE USANDO SEQUÊNCIAS DE NÚMEROS INTEIROS COM GRAU DE RECORRÊNCIA SUPERIOR A 2
(O TESTE DE PRIMALIDADE DE WARD É OUTRO EXEMPLO QUE PODE SER INCLUSO NESSA CATEGORIA).

PARA MAIORES INFORMAÇÕES: https://trizenx.blogspot.com/2020/01/primality-testing-algorithms.html
                          https://mathworld.wolfram.com/TribonacciNumber.html

*/



//***************************************************************************************************************************
//CABEÇALHO
#ifndef TRIBONACCI_PRIMALITY_TEST_FINITE_FIELD_VERSION_H
#define TRIBONACCI_PRIMALITY_TEST_FINITE_FIELD_VERSION_H
#include"cipolla_algorithm.h"
#include<stdbool.h>


//***************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool tribonacci_primality_test_finite_field(int64_t);


//***************************************************************************************************************************
//FUNÇÕES
//Função que testa a primalidade de números inteiros usando a sequência de Tribonacci e aritmética em GF(p²)
/*
  NOTA: Usaremos a classe de números algébricos quadráticos e as rotinas de exponenciação modular disponíveis no
        arquivo cipolla_algorithm.h.

*/
bool tribonacci_primality_test_finite_field(int64_t n){

    //Teste 1: teste de Fermat para primos inferiores a 100
    int primes100[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
    for(int i=0; i<25; ++i){
      if(n==primes100[i]) return true;
      if(mod_bin_pow(primes100[i], (n-1), n)!=1) return false;
  
    }

    if(n<10000) return true;  


  //Variáveis locais
  struct algebraic_quadratic_number z, zp;
  int64_t exponent=0;
  bool flag13=false, flag57=false;

  //Procedimentos 
    //Ajuste de variáveis
    z.a=1; z.b=(-1); z.d=(-2);    
    if(n%8==1 || n%8==3){
      flag13=true;
      exponent=(n-1);
    }
    if(n%8==5 || n%8==7){
      flag57=true;
      exponent=(n+1);
    };

    //Teste 2: testando as congruências (1-√-2)^(n-1) (mod n) = 1, se n = 1,3 (mod 8); ou (1-√-2)^(n-1) (mod n) = 3, se n = 5,7 (mod 8).
    zp=algebraic_quadratic_pow_mod(z, exponent, n);

    
  //Resultado
  if(flag13==true && zp.a==1) return true;
  else if(flag57==true && zp.a==3) return true;
  else return false;

};


//***************************************************************************************************************************
//FIM DO HEADER
#endif
