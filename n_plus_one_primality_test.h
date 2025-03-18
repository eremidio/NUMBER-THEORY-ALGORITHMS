// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE PRIMALIDADE (n+1)

/*
O TESTE DE PRIMALIDADE (n+1) É UM EFICIENTE TESTE DE PRIMALIDADE PARA TESTAR A
PRIMALIDADE UM INTEIRO n, QUE REQUER A FATORAÇÃO DE (n+1) E USA SEQUÊNCIAS DE
LUCAS. O ALGORITMO SE BASEIA NOS SEGUINTES LEMAS:

SEJAM x²+px+q UM POLINÔMIO COM ((p²-q)|n) =(-1) (SÍMBOLO DE JACOBI), ISTO É,
(p²-q) NÃO É UM QUADRADO PERFEITO MÓDULO. O POLINÔMIO EM QUESTÃO POSSUI DUAS
RAÍZES REAIS UMA DAS QUAIS r=(p+[(p²-q)^(1/2)])/2. E SEJAM V(m) E U(m) AS
SEQUÊNCIAS DE LUCAS DO PRIMEIRO E SEGUNDO TIPOS.

LEMA 1:r^m=(V(m)+U(m)[(p²-q)^(1/2)])/2.
LEMA 2: SEJAM a, b INTEIROS DE MESMA PARIDADE E 2r=a+b[(p²-q)^(1/2)] (mod n), SE
n FOR PRIMO ENTÃO 2(r^n)=a-b[(p²-q)^(1/2)](mod n)
LEMA 3: SE n FOR PRIMO ENTÃO U(n+1)=0 (mod n).

COMBINANDO OS RESULTADOS ACIMA É POSSIVEL DEMONSTRAR O SEGUINTE TEOREMA:
SEJA d=(p²-q) TAL QUE (d|n)=(-1) , UM NÚMERO n É PRIMO SE E SOMENTE SE
U(n+1)=0 (mod n) E U((n+1)/r)≠0 (mod n) PARA CADA FATOR PRIMO DE (n+1).

SE TOMARMOS s(k)=V(k)[2^(2^k)], OBTEMOS O TESTE DE LUCAS-LEHMER PARA NÚMEROS DE
MERSENNE n=(2^k)-1 QUE AFIRMA n É PRIMO SE E SOMENTE SE s(k-2)=0 (mod n), PARA A
SEQUÊNCIA s(0)=4, s(k+1)=[s(k)]²-2. NA LISTA DOS MAIORES PRIMOS JÁ COMPUTADOS OS
PRIMOS DE MERSENNE SÃO OS MAIS ABUNDANTES.

PARA MAIORES INFORMAÇÕES: https://t5k.org/prove/prove3_2.html
                          Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance

*/

//********************************************************************************************************************************************************
// CABEÇALHO
#if !defined N_PLUS_ONE_PRIMALITY_TEST_H
#define N_PLUS_ONE_PRIMALITY_TEST_H
#include <math.h>
#include "jacobi_symbol.h"
#include"factorization_map.h"
#include "mod_bin_exponentiation128.h"
#include"lucas_sequence_matrix.h"

//********************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
void set_lucas_sequence_parameters(int64_t*, int64_t*, int64_t);
bool n_plus_one_primality_test(int64_t);

//********************************************************************************************************************************************************
// FUNÇÕES
// Função que calcula os parâmetros p, q a serem usados para computar as sequências de Lucas no teste de primalidade (n+1): (D|n)=(-1)
void set_lucas_sequence_parameters(int64_t* P, int64_t* Q, int64_t n) {
  // Variáveis locais
  int64_t i = 3, j = 2;
  int64_t d, tester;

  // Procedimentos
  // Calculando um valor de d adequado
  for (d = 5;; d+=4) {
    if (jacobi(d, n) == (-1)) break;
  };

  // Calculando o valor dos parâmetros P e Q usados no teste
  while (true) {
    tester = ((i * i) - (4 * j));

    if (tester == d) break;
    if (tester > d) ++j;
    if (tester < d) ++i;
  };

  (*P) = i;
  (*Q) = j;
};

// Função que implementa o teste de primalidade (n+1)
bool n_plus_one_primality_test(int64_t n) {

  //Casos bases: primos inferiores a 10
  if(n<2) return false;
  if(n==2 || n==3 || n==5 || n==7) return true;
  if(!(n&1)) return false;
  if(n%3==0 || n%5==0 || n%7==0) return false;
  

  //Variáveis locais
  uint64_t prime_factor_array[30], divisors_array[30];
  int64_t P, Q;
  int multiplicities[30];
  int64_t max_P=4*std::log(n)*log(n);

  

  //Procedimentos
    //Inicializando os arrays de fatores primos
    for(int i=0; i<30; ++i){
      prime_factor_array[i]=1;
      divisors_array[i]=1;
      multiplicities[30]=0;
    }

    //Fatorando (n+1) e calculando a lista de divisores r=(n+1)/p onde p é  um fator primo de (n+1)
    factorization_map((n+1), prime_factor_array, multiplicities);
    for(int j=0; j<30; ++j){
      if(prime_factor_array[j]>1)
        divisors_array[j]=(n+1)/prime_factor_array[j];

    }

    //Selecionando parâmetros P e Q para o cálculo das sequências de Lucas
    set_lucas_sequence_parameters(&P, &Q, n);

    start_test:
    //Teste 1: checando se U(n+1)= 0 (mod n)
    Matrix<__int128_t> lucas_matrix1=lucas_sequence_modular_matrix<__int128_t, __int128_t>(P, Q, n, n);
    if(lucas_matrix1.matrix[0][0]!=0){ 
      if(P<max_P){
        Q=(Q+P+1);
        P=P+2;
        goto start_test;
      }
      else return false;
    }

    //Teste 2: checando se para cada divisor de p de (n+1) se U((n+1)/p) ≠ 0 (mod n)
    for(int k=0; k<30; ++k){
      if(divisors_array[k]>1){
        Matrix<__int128_t> lucas_matrix2=lucas_sequence_modular_matrix<__int128_t, __int128_t>(P, Q, divisors_array[k], n);
        if(lucas_matrix2.matrix[1][0]==0){
          if(P<max_P){
            Q=(Q+P+1);
            P=P+2;
            goto start_test;
          }
          else return false;
        }

      }
    }

  //Caso passe nos testes acima um primofoi encontrado
  return true;

};

//********************************************************************************************************************************************************
// FIM DO HEADER
#endif
