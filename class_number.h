// VAMOS CRIAR UM PROGRAMA QUE COMPUTA O NÚMERO DE CLASSE PARA CORPOS ALGÉBRICOS QUADRÁTICOS IMAGINÁRIOS

/*
CORPOS ALGÉBRICOS NÚMERICOS SÃO EXTENSÕES DOS CORPOS DOS RACIONAIS FECHADOS EM
RELAÇÃO AS OPERAÇÕES ARITMÉTICAS. CONCEITOS ORIGINALMENTE DEFINIDOS NOS CORPOS
DOS RACIONAIS E INTEIROS COMO NÚMEROS PRIMOS E FATORACÃO EM NÚMEROS PRIMOS PODEM
SER FACILMENTE EXTENDIDOS PARA CORPOS ALGÉBRICOS MAIS GERAIS.

O NÚMERO DE CLASSE DENOTADO POR h É UM IMPORTANTE INVARIANTE QUE ESTÁ ASSOCIADO
A UM CORPO ALGÉBRICO E DETERMINA O QUÃO LONGE UM CORPO ALGÉBRICO SE DIFERE DE UM
DOMÍNIO DE FATORAÇÃO ÚNICO, ISTO É, DE QUANTAS MANEIRAS DISTINTAS UM ELEMENTO
NESTE CORPO ALGÉBRICO PODE SER DECOMPOSTO EM FATORES PRIMOS. POR EXEMPLO: NO
CORPO ALGÉBRICO Q(√-5) COMPOSTO POR NÚMEROS DA FORMA a+(√-5)b, COM a E b
RACIONAIS O NÚMERO 6 (a=6, b=0) ADMITE DUAS FORMAS DISTINTAS DE DECOMPOSIÇÃO EM
FATORES PRIMOS 6=(2+(√-5)0)(3+(√-5)0) E 6=(1+(√-5)1)(1-(√-5)1).

PARA CORPOS QUADRÁTICOS IMAGINÁRIOS Q(√-n) UMA POSSISIBILIDADE É CONTABILIZAR O
NÚMERO DE FORMAS QUADRÁTICAS REDUTÍVEIS COM DISCRIMINANTE -n, PARA ax²+bxy+cy²,
Δ=b²-4ac.

EM GERAL É EXTREMAMENTE COMPLEXO COMPUTAR NÚMEROS DE CLASSE PARA CORPOS
ALGEBRICOS GERAIS. PORÉM EM ALGUNS CASOS COMO É O CASO DE CORPOS QUADRÁTICOS
IMAGINÁRIOS DA FORMA Q(√-n), COM n INTEIRO E NÃO CONTENDO FATORES QUADRÁTICOS
ESTE CÁLCULO PODE SER EXTREMAMENTE SIMPLIFICADO. EM PARTICULAR, EXPRESSO EM
TERMOS DOS SÍMBOLOS DE KRONECKER, DOS DISCRIMINANTES Δ (QUE MENSURAM O QUANTO
INTEIROS ALGÉBRICOS SÃO DISTINGUÍVEIS, ISTO É, UNICAMENTE DECOMPOSTOS EM FATORES
PRIMOS NESTE DOMÍNIO, PARA n CONTENDO FATORES QUADRÁTICOS O DISCRIMINANTE NÃO É
BEM DEFINIDO, UMA VEZ QUE O POLINÔMIO CARACTERIZANDO O DOMÍNIO PODE TER RAÍZES
REPETIDAS, O DISCRIMINANTE DETERMINA SE OS INTEIROS ALGÉBRICOS FORMAM UMA
EXTENSÃO SEPARÁVEL DO CONJUNTO DOS INTEIROS).

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Arithmetic_function
                          https://en.wikipedia.org/wiki/Ideal_class_group
                          https://en.wikipedia.org/wiki/Class_number_formula
                          https://numberworld.blogspot.com/2018/05/methods-to-compute-class-number.html
                          https://people.reed.edu/~jerry/361/lectures/iqclassno.pdf
                          https://mathworld.wolfram.com/ClassNumber.html
                          Elementary Number Theory by Edmund Landau
                          Introduction to Modern Number Theory, by Yuri I. Manin and Alexei A. Panchishkin
                          A Course In Computational Algebraic Number Theory by Henri Cohen

*/

//*********************************************************************************************************************************************************************
// CABEÇALHO
#ifndef CLASS_NUMBER_QUADRATIC_FIELD_H
#define CLASS_NUMBER_QUADRATIC_FIELD_H
#include <assert.h>
#include<math.h>
#include"prime_table_reading.h"
#include "kronecker_symbol.h"

//*********************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
bool is_square_factor_free(int64_t);
bool is_fundamental_discriminant(int64_t);
int64_t automorphism_number(int64_t);
int64_t class_number_negative_discriminant(int64_t);
int64_t class_number_dirichlet_series(int64_t);

//*********************************************************************************************************************************************************************
// FUNÇÕES
// Função que determina se um inteiro contém fatores quadráticos
bool is_square_free(int64_t n) {

  // Variáveis locais
  int64_t i, limit = sqrt(n);

  // Procedimentos
    // Casos triviais
    if (n < 4) return true;

    // Fatores 2 e 3
    if ((n % 4) == 0) return false;
    if ((n % 9) == 0) return false;

    // Loop principal com otimização 6k+1
    for (i = 5; i < (limit + 2); i += 6) {
      if ((n % (i * i)) == 0) return false;
      if ((n % ((i + 2) * (i + 2))) == 0) return false;
    };

  // Caso passe nos testes acima
  return true;
};


// Função que determina se um inteiro corresponde a um discrimante fundamental
bool is_fundamental_discriminant(int64_t n) {
  //Caso bases: n=1 e contém fatores primos repetidos
  if (n == 1) return false;
  if(is_square_free(n)==false) return false;


  //Variáveis locais
  int64_t mod4=(n%4), mod16=(n%16); // mod 4 e mod 16

  //Procedimentos
    //Testando se n (mod 4)=1 ou n (mod 16)=8, 12
    if(mod4<0) mod4+=4;
    if(mod4==1) return true;
 
    if(mod16<0) mod16+=16;
    if(mod16==8 || mod16==12) return true;



  // Caso o número não passe nos testes acima
  return false;
};

// Função que calcula o número de automorfismos de formas quadráticas de um dado discriminante
int64_t automorphism_number(int64_t n) {
  if ((n * (-1)) == 3)
    return 6;
  else if ((n * (-1)) == 4)
    return 4;
  else
    return 2;
};


//Função que calcula o número de classe para um discriminante fundamental negativo (d<(-4)) usando a fórmula de Dirichlet
int64_t class_number_negative_discriminant(int64_t d){

 //Variáveis locais
 int64_t plus_d=(-1)*d;
 int64_t sum=0;
 int64_t i;


 //Procedimentos
  //Loop principal
  for(i=1; i<(plus_d/2); ++i){
    sum+=kronecker(d, i);
  }

 //Resultado 
 return sum/(2-kronecker(d, 2));

};


//Função que calcula o valor calcula o valor aproximado do número de classe usando as séries de Dirchlet L(1, χ(s))
/*
  NOTA: Essa fórmula fornece apenas um resultado aproximado (a série de Dirichlet é uma soma infinita sobre o
        o conjunto dos números primos), usando-se primos≳13200 o erro porcentual é de menos de 0,1% do valor
        correto.

*/
int64_t class_number_dirichlet_series(int64_t d){

  //Variáveis locais
  const double pi=4*atan(1.0);
  double product=sqrt(-d)/pi;
  uint64_t prime_list_size=0;
  uint64_t* prime_list =NULL;


  //Procedimentos
    //Lendo a lista de primos alocadas no arquivo
    prime_list=read_prime_table("prime_table.txt", prime_list, &prime_list_size);

    //Loop principal
    for(uint64_t i=0; i<prime_list_size; ++i){
      product*=((prime_list[i]*1.0)/(prime_list[i]-kronecker(d, prime_list[i])));
    }

    //Limpando o cachê de memória
    if(prime_list) free(prime_list); prime_list=NULL;

  //Resultado
  return product;

};

//*********************************************************************************************************************************************************************
// FIM DO HEADER
#endif
