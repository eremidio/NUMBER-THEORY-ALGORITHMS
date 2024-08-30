//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA TESTES DE IRREDUTIBILIDADE DE POLINÔMIOS EM CORPOS FINITOS DO PRIMEIRO TIPO

/*

PARA OUTRA VARIUANTE DESTE ALGORITMO VER REFERÊNCIAS.
PARA MAIORES REFERÊNCIAS: Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance

*/


//******************************************************************************************
//CABEÇALHO
#ifndef POLYNOMIAL_IRREDUCIBILITY_H
#define POLYNOMIAL_IRREDUCIBILITY_H
#include"polynomial_exponentiation_finite_field.h"
#include"polynomial_gcd.h"
#include<cmath>


//******************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
bool irredutibility_criterion(polynomial<T>&, int64_t);


//******************************************************************************************
//FUNÇÕES
//Função que determina se um polinômio é irredutível sobre um corpo finito do primeiro tipo
template<typename T>
bool irredutibility_criterion(polynomial<T>& f, int64_t prime){

  //Variáveis locais
  polynomial<T> g, identity, poly_tester;


  //Procedimentos
    //Ajuste do polinômio g(x)=x, usado no cálculo
    g.degree=1;
    g.polynomial_coefficients.push_back(1); g.polynomial_coefficients.push_back(0);
    g.polynomial_powers.push_back(1); g.polynomial_powers.push_back(0);

    identity=g;

    //Loop principal
    for(int64_t i=1; i<=std::floor(f.degree>>1); ++i){

      //Cálculo de g(x)^p(mod f(x), p)
      polynomial<T> temp=polynomial_powmod_finite_field<T, int64_t>(g, f, prime, prime);
      g=temp;
      poly_tester=g-identity;
    
      //Teste de irredutibilidade
      polynomial<T> poly_gcd= polynomial_gcd<T>(g, poly_tester);
      if(is_unity_polynomial<T>(poly_gcd)==false)
        return false; //Um fator não trivial de f(x) foi encontrado

    }


  //Caso passe no teste acima um polinômio irredutível foi encontrado
  return true;

};


//******************************************************************************************
//FIM DO HEADER
#endif
