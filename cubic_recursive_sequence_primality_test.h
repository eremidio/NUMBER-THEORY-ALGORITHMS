//VAMOS CRIAR UM TESTE DE PRIMALIDADE USANDO SEQUÊNCIAS RECURSIVAS DE ORDEM 3 PARA INTEIROS DE 64 BITS

/*

CERTAS SEQUÊNCIAS RECURSIVAS DE ORDEM 3 (SEQUÊNCIAS DEFINIDAS POR RELAÇÕES ALGÉBRICAS QUE ASSOCIAM OS TERMOS DE ORDEM n COM OS TERMOS
DE ORDEM (n-3)) SATISFAZEM O CHAMADO CRITÉRIO DE FERMAT, ISTO É, PARA UM INTEIRO n PRIMO, O ENÉSIMO TERMO DA SEQUÊNCIA SATISFAZ ALGUM
CRITÉRIO DE DIVISIBLIDADE DO TIPO [S(n)-a]=0 (mod n), PARA a INTEIRO. EXEMPLOS TÍPICOS INCLUEM A SEQUÊNCIA DE NARAYANA N(n), A
SEQUÊNCIA DE VAN DER LAAN S(n), A SEQUÊNCIA DE PERRIN P(n), ENTRE OUTRAS.

TAIS SEQUÊNCIAS PODEM SER COMPUTADAS EM TEMPO O(log(n)) USANDO-SE CERTAS MATRIZES 3X3 CUJOS AUTOVALORES REAIS SÃO CONSTANTES COMO A
(SUPER) RAZÃO DE OURO/PRATA, A CONSTANTE PLÁSTICA, QUE SÃO SOLUÇÕES DOS RESPECTIVOS POLINÔMIOS CARACTERÍSTICOS DAS MATRIZES. AO PASSO
QUE PARA CADA RELAÇÃO DE CONGRUÊNCIA EXISTEM VÁRIOS PSEUDOPRIMOS, QUANDO COMBINADOS TEM-SE UM TESTE DE PRIMALIDADE ROBUSTO
(POSSIVELMENTE DETERMINÍSTICO) QUE PODE SER EMPREGADO PARA FILTRAR POSSÍVEIS CANDIDATOS A PRIMOS ANTES DE SE APLICAR UM TESTE COMO O
TESTE DE CURVAS ELIPTÍCAS OU O TESTE APR-CL.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Plastic_ratio#Van_der_Laan_sequence
                          https://en.wikipedia.org/wiki/Supergolden_ratio#
                          https://en.wikipedia.org/wiki/Supersilver_ratio#
                          https://en.wikipedia.org/wiki/Pell_number#Pell_numbers
                          https://oeis.org/A000129
                          https://oeis.org/A001609
                          https://oeis.org/A332647

*/


//**********************************************************************************************************************************
//CABEÇALHO
#ifndef CUBIC_RECURSIVE_SEQUENCE_PRIMALITY_TEST_H
#define CUBIC_RECURSIVE_SEQUENCE_PRIMALITY_TEST_H
#include"mod_bin_exponentiation128.h"
#include"matrix_exponentiation.h"
#include"matrix_modular_reduction.h"


//**********************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool narayana_primality_test(int64_t);
bool third_order_pell_primality_test(int64_t);
bool cubic_recursive_sequence_primality_test(int64_t);


//**********************************************************************************************************************************
//FUNÇÕES
//Função que checa a primalidade de um inteiro usando a sequência de Narayana
/*

NOTA: A sequência de Narayana é definida por N(0)=N(1)=N(2)=1, N(n)= N(n-1)+N(n-3).
      Para n primo seja A(n)=N(n)+2N(n-3), então A(n) = 1 (mod n).
      Para Q=|1 0 1| temos que Q^n= |N(n)   N(n-2) N(n-1)|
             |1 0 0|                |N(n-1) N(n-3) N(n-2)| 
             |0 1 0|                |N(n-2) N(n-4) N(n-3)| 
      A(n) é o traço da matriz Q^n.

*/
bool narayana_primality_test(int64_t n){

  //Variáveis locais
  Matrix<__int128_t> narayana_matrix(3);
  
  
  //Procedimento
    //Definindo as entradas da matriz de Narayana
    narayana_matrix.matrix[0][0]=1; narayana_matrix.matrix[0][1]=0; narayana_matrix.matrix[0][2]=1; 
    narayana_matrix.matrix[1][0]=1; narayana_matrix.matrix[1][1]=0; narayana_matrix.matrix[1][2]=0; 
    narayana_matrix.matrix[2][0]=0; narayana_matrix.matrix[2][1]=1; narayana_matrix.matrix[2][2]=0; 
  
    //Computando a matriz Q^n mod(n)
    Matrix<__int128_t> Qn_mod_matrix=matrix_powmod<__int128_t, int64_t>(narayana_matrix, n, n);

    //Checando a condição de primalidade
    __int128_t result=(Qn_mod_matrix.matrix[0][0]+Qn_mod_matrix.matrix[1][1]+Qn_mod_matrix.matrix[2][2])%n;
    if(result<0) result=(result+n);


  //Resultado
  if(result==1) return true;
  else return false;    

};


//Função que checa a primalidade de um inteiro usando a sequência de Pell de ordem 3
/*

NOTA: A sequência de Pell de ordem 3 é definida por S(0)=1, S(1)=2, S(2)=4, S(n)= 2S(n-1)+S(n-3).
      Para n primo seja A(n)=S(n)+2S(n-3), então A(n) = 2 (mod n).
      Para Q=|2 0 1| temos que Q^n= |S(n)   S(n-2) S(n-1)|
             |1 0 0|                |S(n-1) S(n-3) S(n-2)| 
             |0 1 0|                |S(n-2) S(n-4) S(n-3)| 
      A(n) é o traço da matriz Q^n.

*/
bool third_order_pell_primality_test(int64_t n){

  //Variáveis locais
  Matrix<__int128_t> pell_matrix(3);
  
  
  //Procedimento
    //Definindo as entradas da matriz de Pell
    pell_matrix.matrix[0][0]=2; pell_matrix.matrix[0][1]=0; pell_matrix.matrix[0][2]=1; 
    pell_matrix.matrix[1][0]=1; pell_matrix.matrix[1][1]=0; pell_matrix.matrix[1][2]=0; 
    pell_matrix.matrix[2][0]=0; pell_matrix.matrix[2][1]=1; pell_matrix.matrix[2][2]=0; 
  
    //Computando a matriz Q^n mod(n)
    Matrix<__int128_t> Qn_mod_matrix=matrix_powmod<__int128_t, int64_t>(pell_matrix, n, n);

    //Checando a condição de primalidade
    __int128_t result=(Qn_mod_matrix.matrix[0][0]+Qn_mod_matrix.matrix[1][1]+Qn_mod_matrix.matrix[2][2])%n;
    if(result<0) result=(result+n);


  //Resultado
  if(result==2) return true;
  else return false;    

};


//Função que testa a primalidade de um inteiro usando relações recursivas de ordem 3
bool cubic_recursive_sequence_primality_test(int64_t n){

  //Casos bases:
  if(n<2) return false;
  if(n==2 || n==3 || n==5) return true;
  if(!(n&1) || n%3==0 || n%5==0) return false;
  if(mod_bin_pow(2,(n-1), n)!=1) return false; //Teste de Fermat na base 2 para rápida detecção de compostos


  //Resultado
  if(third_order_pell_primality_test(n) && narayana_primality_test(n)) return true;
  else return false;

};


//**********************************************************************************************************************************
//FIM DO HEADER
#endif
