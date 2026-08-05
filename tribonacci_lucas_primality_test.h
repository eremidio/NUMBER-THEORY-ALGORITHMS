//VAMOS CRIAR UM PROGRAMA PARA TESTAR A PRIMALIDADE DE NÚMEROS INTEIROS DE 64 BITS USANDO A SEQUÊNCIA DE TRIBONACCI-LUCAS

/*

SEJA T(n) A SEQUÊNCIA DE TRIBONACCI QUE PODE SER DEFINIDA POR MEIO DAS RELAÇÕES RECURSIVAS: T(0)=0; T(1)=0, T(2)=9 E T(n)=T(n-1)+3T(n-2)+9T(n-3).
A SEQUÊNCIA DE TRIBONACCI-LUCAS Q(n) É DEFINIDA PELA RELAÇÃO Q(n) = T(n+2)+T(n)+2T(n-1). ESTA SEQUÊNCIA PODE SER COMPUTADA DE FORMA RÁPIDA
USANDO-SE A SEGUINTE PROPOSIÇÃO: SEJA A MATRIZ q=|1 1 1| PARA n INTEIRO TEMOS QUE q^n=|T(n+2) T(n+1)+T(n)   T(n+1)| SE Tr DENOTA O TRAÇO DE UMA
                                                 |1 0 0|                              |T(n+1) T(n)+T(n-1)   T(n)  |
                                                 |0 1 0|                              |T(n)   T(n-1)+T(n-2) T(n-1)|
MATRIZ ENTÃO TEMOS QUE Q(n)=Tr(q^n), DESTA FORMA TERMOS DESTA SEQUÊNCIA PODEM SER COMPUTADOS EM TEMPO POLINOMIAL.

ESTA SEQUÊNCIA EM PARTICULAR É DE GRANDE INTERESSE EM TEORIA DOS NÚMEROS POR CONTA DA SEGUINTE PROPOSIÇÃO: PARA p PRIMO VALE A SEGUINTE RELAÇÃO
DE CONGRUÊNCIA Q(p)= 1 (mod p). ESTA RELAÇÃO FORNECE UM IMPORTANTE DE TESTE DE PSEUDOPRIMALIDADE DE UM NÚMERO INTEIRO. O TESTE É EXTREMAMENTE
EFICAZ PARA RÁPIDA DETECÇÃO DE NÚMEROS COMPOSTOS, ATÉ 10^7 APENAS 12 PSEUDOPRIMOS PASSAM PELO TESTE. EFICIENTES TESTE DE PRIMALIDADE PODEM SER
OBTIDOS COMBINANDO-SE OUTROS TESTE DE PRIMALIDADE COM O TESTE DA SEQUÊNCIA TRIBONACCI-LUCAS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Generalizations_of_Fibonacci_numbers#Tribonacci_numbers


*/


//*************************************************************************************************************************************************
//CABEÇALHO
#ifndef TRIBONACCI_LUCAS_PRIMALITY_TEST_H
#define TRIBONACCI_LUCAS_PRIMALITY_TEST_H
#include"matrix_exponentiation.h"
#include"matrix_modular_reduction.h"
#include"mod_bin_exponentiation128.h"
#include<stdint.h>
 

//*************************************************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
template<typename T>
Matrix<T> modular_tribonacci_lucas_matrix(T);
bool tribonacci_lucas_primality_test(uint64_t);


//*************************************************************************************************************************************************
//FUNÇÕES 
//Função que computa uma matriz contendo diversos elementos da sequência de Tribonacci e cujo traço é um elemento da sequência de Tribonacci-Lucas
template<typename T>
Matrix<T> modular_tribonacci_lucas_matrix(T n){

  //Variáveis locais
  Matrix<T> coefficients_matrix;


  //Procedimentos
    //Inicializando a matriz q
    coefficients_matrix.reshape(3,3);
    coefficients_matrix.matrix[0][0]=1; coefficients_matrix.matrix[0][1]=1; coefficients_matrix.matrix[0][2]=1; 
    coefficients_matrix.matrix[1][0]=1; coefficients_matrix.matrix[1][1]=0; coefficients_matrix.matrix[1][2]=0; 
    coefficients_matrix.matrix[2][0]=0; coefficients_matrix.matrix[2][1]=1; coefficients_matrix.matrix[2][2]=0; 


    //Calculando o resultado q^n
    Matrix<T> tribonacci_matrix=matrix_powmod<T, T>(coefficients_matrix, n, n);


  //Resultado
  return tribonacci_matrix;

};


//Função que executa um teste de primalidade usando a sequência de Tribonacci-Lucas
bool tribonacci_lucas_primality_test(uint64_t n){

//Casos bases:
if(n<2) return false;
if(n==2) return true;

//Teste 1: teste de Fermat na base 2 para rápida detecção de compostos
if(mod_bin_pow(2, (n-1), n)!=1)
  return false;


//Variáveis locais
Matrix<__int128_t> Qn_matrix = modular_tribonacci_lucas_matrix<__int128_t>(static_cast<__int128_t>(n));
__int128_t tester = (Qn_matrix.matrix[0][0]+Qn_matrix.matrix[1][1]+Qn_matrix.matrix[2][2])%n;

//Resultado: checando a relação de congruência do teste da sequência de Tribonacci-Lucas
if(tester==1) return true;
else return false;

};


//*************************************************************************************************************************************************
//FIM DO HEADER
#endif
