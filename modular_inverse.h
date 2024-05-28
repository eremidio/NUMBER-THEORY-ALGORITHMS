//VAMOS CRIAR UM PROGRAMA QUE CALCULA INVERSOS MODULARES USANDO OS TEOREMAS DE EULER E FERMAT PARA INTEIROS DE 64 BITS

/*

O INVERSO MODULAR DE UM NÚMERO a  A MENOS DE UMA CONGRUÊNCIA MÓDULO n É DEFINIDO COMO A SOLUÇÃO DA EQUAÇÃO
ax=1 (mod n). TAL SOLUÇÃO EXISTE SE a,n SÃO COPRIMOS. INVERSOS MODULARES DESEMPENHAM O PAPEL DE ELEMENTO 
INVERSO EM RELAÇÃO A OPERAÇÃO DE MULTIPLICAÇÃO NO GRUPO DE INTEIROS A MENOS DE UMA CONGRUÊNCIA.

O PRINCIPAL ALGORITMO USADO PARA COMPUTAR INVERSOS MODULARES É O ALGORITMO DE EUCLIDES EXTENDIDO. PORÉM
SE HOUVER UMA RÁPIDA ROTINA DE EXPONENCIAÇÃO E UMA ROTINA EFICIENTE PARA COMPUTAR A FUNÇÃO TOTIENTE DE EULER
φ(n), PODE-SE USAR OS TEOREMAS DE EULER E FERMAT PARA O CÁLCULO RÁPIDO DE INVERSOS MODULARES.

TEOREMA DE EULER: SE a,n SÃO DOIS INTEIROS COPRIMOS ENTÃO a^φ(n)=1 (mod n), ONDE φ(n) É A FUNÇÃO TOTIENTE DE
EULER.

TEOREMA DE FERMAT: SE a,n SÃO DOIS INTEIROS COPRIMOS E n FOR PRIMO ENTÃO a^(n-1)=1 (mod n).

DAS FÓRMULAS ACIMA SE n FOR COMPOSTO: a^[φ(n)-1] = a⁻¹ (mod n) E PARA n PRIMO a^(n-2)=a⁻¹ (mod n).


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Modular_multiplicative_inverse#Using_Euler's_theorem

*/ 



//********************************************************************************************************************
//CABEÇALHO
#ifndef MODULAR_INVERSE_H
#define MODULAR_INVERSE_H
#include"mod_bin_exponentiation128.h"
#include"euler_totient_function.h"
#include"gauss_euler_primality_test.h"


//********************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t modular_inverse(uint64_t, uint64_t);



//********************************************************************************************************************
//FUNÇÕES

//Função que calcula omodular inverso deum inteiro a menso de uma congruência
uint64_t modular_inverse(uint64_t a, uint64_t n){

  //Caso trivial: mdc(a,n)>1
  if(gcd_euclides(a, n)>1)
    return 0;


  //Caso 1: n é primo, teorema de Fermat
  else if(n==2 || gauss_euler_primality_test(n)==true)
    return mod_bin_pow(a, (n-2), n);


  //Caso 2: n é composto, teorema de Euler
  else
    return mod_bin_pow(a, (euler_totient_function(n)-1), n);

                                                };

//********************************************************************************************************************
//FIM DO HEADER
#endif
