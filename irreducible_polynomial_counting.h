/*

A SEGUINTE FÓRMULA É ÚTIL PARA DETERMINAR O NÚMERO DE POLINÔMIOS DE GRAU k QUE SÃO IRREDUTÍVEIS
TOMANDO COEFICIENTES EM UM CORPO FINITO DO PRIMEIRO TIPO F(p) INTEIROS A MENOS DE UMA
CONGRUÊNCIA MÓDULO UM PRIMO p:

n(k)=k⁻¹Σ μ(k/d)p^d, ONDE A SOMA É REALIZADA SOBRE OS DIVISORES d DE k.

ESTA FÓRMULA É UM EXEMPLO APLICAÇÃO DA FÓRMULA DE INVERSÃO DE MÖBIUS.

PARA MAIORES REFERÊNCIAS: Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance
                          https://mathworld.wolfram.com/IrreduciblePolynomial.html

*/ 


//********************************************************************************************
//CABEÇALHO
#ifndef IRREDUCIBLE_POLYNOMIAL_COUNTING_H
#define IRREDUCIBLE_POLYNOMIAL_COUNTING_H
#include"mobius_function.h"
#include"mod_bin_exponentiation.h"

//********************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t irreducible_polynomial_counting(int64_t, int64_t);


//********************************************************************************************
//FUNÇÕES
//Função que computa o número de polinômios irredutíveis de grau k em um corpo finito de característica p
int64_t irreducible_polynomial_counting(int64_t degree, int64_t prime){

  //Variávieis locais
  int64_t sum=0;


  //Procediumentos
    //Loop sobre divisores do grau do polinômio
    for(int64_t i=1; i<=degree; ++i){
      if((degree%i)==0)
        sum+= (mobius_function(degree/i)*bin_pow(prime, i));
    }

  //Resultado
  return (sum/degree);

};



//********************************************************************************************
//FIM DO HEADER
#endif 
