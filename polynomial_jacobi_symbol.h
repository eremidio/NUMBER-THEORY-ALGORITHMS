//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ROTINAS PARA CALCULAR O SÍMBOLO DE JACOBI DE POLINÔMIOS DEFINIDOS SOBRE
//CORPOS FINITOS DO PRIMEIRO TIPO PARA PRIMOS DE ATÉ 64 BITS

/*
O SÍMBOLO DE JACOBI PODE SER DEFINIDO PARA POLINÔMIOS CUJOS COEFICIENTES TOMAM VALORES
EM UM CORPO FINITO DO PRIMEIRO TIPO (INTEIROS CONGRUENTES MÓDULO UM PRIMO) DA SEGUINTE
FORMA: SEJAM DOIS POLINÔMIOS COM COEFICIENTES EM F(p) g(x) E f(x). O SÍMBOLO DE JACOBI
É DEFINIDO COM SENDO (g|f)=0 SE mdc(f(x), g(x)) ≠ 1, (g|f)=1 SE g FOR UMA CLASSE
RESIDUAL QUADRÁTICA mod (p, f(x)), ISTO É, SE EXISTIR h(x) TAL QUE h(x)²=g(x) mod f(x)
E (g|f)=(-1) CASO CONTRÁRIO, COM A RESTRIÇÃO DE f(x) SER UM POLINÔMIO MÔNICO.

ESTA EXTENSÃO DO SÍMBOLO DE JACOBI SATISFAZ A LEI DE RECIPROCIDADE QUADRÁTICA: 
(g|f)=(-1)^{[(p-1)/2].deg(g).deg(f)}(f|g).

PARA MAIORES INFORMAÇÕES: Algorithmic Number Theory vol. 1 by E. Bach, J. Shallit

*/ 


//*************************************************************************************
//CABEÇALHO
#ifndef POLYNOMIAL_JACOBI_SYMBOL_H
#define POLYNOMIAL_JACOBI_SYMBOL_H
#include"polynomial_irreducibility.h"
#include"polynomial_monic_finite_field.h"
#include"fast_polynomial_division_finite_field.h"
#include"jacobi_symbol.h"


//*************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int polynomial_jacobi_symbol(polynomial<int64_t>&, polynomial<int64_t>&, int64_t);


//*************************************************************************************
//FUNÇÕES
//Função que calcula o símbolo de Jacobi generalizado para dois polinômios definidos sobre F(p)
int polynomial_jacobi_symbol(polynomial<int64_t>& u, polynomial<int64_t>& v, int64_t prime){

  //Variáveis locais
  polynomial<int64_t> quotient, remainder;
  int64_t leading_coefficient;
  int s;

  //Procedimentos
    //Calculando o quociente e o resto de divisão de dois polinômios usando o algoritmo de Euclides
    fast_polynomial_division_finite_field<int64_t>(u, v, quotient, remainder, prime);
    u=remainder;
    if(u.degree==0 && u.polynomial_coefficients[0]==0) return 0;

    //Checando se o grau do resto de divisão é nulo
    leading_coefficient=u.polynomial_coefficients[0];
    if(leading_coefficient<0) leading_coefficient+=prime;

    s=jacobi(leading_coefficient, prime);
    if(remainder.degree<1) return s; //Fim do algoritmo
  

    //Caso o resto da divisão depolinômios tenha grau maior que 0 o algoritmo é executado recursivamente
      //Fazendo o polinômio u mônico
      polynomial<int64_t> monic_poly=make_monic_polynomial_finite_field<int64_t>(u, prime);
      if( (((prime-1)>>1)%2)==1 && (u.degree&1) && (v.degree&1)) s*=(-1);
      
    //Chamada recursiva do algoritmo
    return s*polynomial_jacobi_symbol(v, monic_poly, prime);

};



//*************************************************************************************
//FIM DO HEADER
#endif
