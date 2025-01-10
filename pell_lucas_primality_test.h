//VAMOS CRIAR UM PROGRAMA TESTA A PRIMALIDADE DE NÚMEROS INTEIROS USANDO A SEQUÊNCIA DOS NÚMEROS DE PELL-LUCAS

/*
OS CHAMADOS NÚMEROS DE PELL-LUCAS SÃO UMA SEQUÊNCIA DE NÚMEROS INTEIROS DEFINIDO PELA RELAÇÃO:
Q(0)=2, Q(1)=2, Q(n)=2Q(n-1)+Q(n-2).

OS NÚMEROS DE  PELL-LUCAS PODEM COMPUTADOS USANDO-SE NÚMEROS ALGÉBRICOS Z(√2) E Z(√-2), POR MEIO
DA RELAÇÃO Q(n)=(1+√2)^n+(1-√-2)^n, O QUE PERMITE COMPUTAR RAPIDAMENTE Q(n). 

A SEGUINTE PROPOSIÇÃO PODE SER USADA PARA TESTAR A PRIMALIDADE DE UM INTEIRO n: SE FOR PRIMO,
ENTÃON Q(n)=2 (mod n). (A ARITMÉTICA PODE SER FEITA VIA GF(p²))

SE COMBINANDO COM UMTESTE DE FERMAT BASE 5 E SE n NÃO FOR MÚLTIPLO DE 2 E 3,TEM-SE UM EFICIENTE
TESTE DE PRIMALIDADE.

ESTE PROCEDIMENTO PODE SER GENERALIZADO AMPLIADO PARA UMCONJUNTO DE VÁRIAS SEQUÊNCIA DE INTEIROS,
CONSTRUÍDAS USANDO-SE UM CONJUNTO DE FUNÇÕES GERADORAS DO TIPO P(x)/Q(x) = Σa(n)x^n, ONDE P(x),
Q(x) SÃO POLINÔMIOS COM COEFICIENTES INTEIROS,NO CASO DA SEQUÊNCIA DE PELL-LUCAS P(x)=2x-2,
Q(x)=x²+2x-1.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Pell_number#Pell–Lucas_numbers
                          https://math.colgate.edu/~integers/x95/x95.pdf
                          https://oeis.org/A002203


*/



//***********************************************************************************
//CABEÇALHO
#ifndef PELL_LUCAS_PRIMALITY_TEST_H
#define PELL_LUCAS_PRIMALITY_TEST_H
#include<stdbool.h>
#include"cipolla_algorithm.h"


//CONSTANTES GLOBAIS
#define PELL_LUCAS1 10000
#define PELL_LUCAS2 10000000

//***********************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool pell_lucas_primality_test(int64_t);

//***********************************************************************************
//FUNÇÕES
//Função que implementa o teste de primalidade usando a sequência de Pell-Lucas
/*
NOTA: usaremos a estrutura 'algebraic_quadratic_number' e a função para rápida
      exponenciação modular em GF(p²) disponível no arquivo 'cipolla_algorithm.h'.

*/

bool pell_lucas_primality_test(int64_t n){

  //Casos bases: 
  if(n<2) return false;
  if(n==2 || n==3 || n==5) return true;
  if(!(n&1) || (n%3)==0) return false;


  //Teste 1: teste de Fermat base 5, 89, 97, 101, 1009, 2071723(rápida deteccção de compostos)
  if(mod_bin_pow(5, (n-1), n)!=1) return false;

  if(n>PELL_LUCAS1){
    if(mod_bin_pow(89, (n-1), n)!=1) return false;
    if(mod_bin_pow(97, (n-1), n)!=1) return false;
    if(mod_bin_pow(101, (n-1), n)!=1) return false;
  }

  if(n>PELL_LUCAS2){
    if(mod_bin_pow(1009, (n-1), n)!=1) return false;
    if(mod_bin_pow(2071723, (n-1), n)!=1) return false;
  }




  //Teste 2: teste da sequência de Pell-Lucas

  //Variáveis locais
  struct algebraic_quadratic_number z1={1, 1, 2}, z2={1, (-1), (-2)};
  struct algebraic_quadratic_number zp1, zp2;
  int64_t result;

  //Procedimentos
    //Computando Q(n)=(1+√2)^n+(1-√-2)^n (mod n)
    zp1=algebraic_quadratic_pow_mod(z1, n, n);
    zp2=algebraic_quadratic_pow_mod(z2, n, n);

    result=(zp1.a+zp2.a+2*n)%n;
  
  //Resultado
  if(result%n==2) return true;
  else return false;

};



//***********************************************************************************
//FIM DO HEADER
#endif
