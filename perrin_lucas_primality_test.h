//VAMOS CRIAR UM PROGRAMA QUE TESTA A PRIMALIDADE DE INTEIROS DE 64 BITS USANDO NÚMEROS DE PERRIN

/*

PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/perrin_number.h

*/


//*******************************************************************************************************
//CABEÇALHO
#ifndef PERRIN_LUCAS_PRIMALITY_TEST_H
#define PERRIN_LUCAS_PRIMALITY_TEST_H
#include"jacobi_symbol.h"
#include"mod_bin_exponentiation128.h"
#include"lucas_sequence_matrix.h"
#include"perrin_number.h"


//*******************************************************************************************************
//DECLARÇÃO DE FUNÇÕES
bool perrin_lucas_primality_test(int64_t);

//*******************************************************************************************************
//FUNÇÕES
//Função que testa a primalidade de um inteiro usando sequências de Lucas e de Perrin
bool perrin_lucas_primality_test(int64_t n){

  //Casos bases:
  if(n<2) return false;
  if(n==2 || n==3) return true;
  if(!(n&1)) return false;

  //Variṕaveis locais
  int64_t P=5, Q=1, D;

  //Procedimentos
    //Teste 1:  teste de Fermat na base 2 para detecção rápida de compostos
    if(mod_bin_pow(2, (n-1), n)!=1) return false;

    //Determinando os parâmetros da sequencia de Lucas
    while(1){
      D=(P*P)-(4*Q);
      if(jacobi(D, n)==(-1)) break;
      else P+=2;
  
    }

    //Teste 2: teste da sequência de Perrin
    Matrix<__int128_t> perrin_matrix=modular_perrin_matrix<__int128_t>(n, n);
    if(perrin_matrix.matrix[0][0]!=0) return false;

    //Teste 3: teste da sequência de Lucas
    Matrix<__int128_t> lucas_matrix=lucas_sequence_modular_matrix<__int128_t, __int128_t>(P, Q, n, n);
    if(lucas_matrix.matrix[0][0]!=0) return false;

  
  //Caso passe nos testes acima um primo foi encontrado
  return true;

};

//*******************************************************************************************************
//FIM DO HEADER
#endif
