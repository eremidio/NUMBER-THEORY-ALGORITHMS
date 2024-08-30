//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA TESTES DE IRREDUTIBILIDADE DE POLINÔMIOS EM CORPOS FINITOS DO PRIMEIRO TIPO

/*

PARA OUTRA VARIUANTE DESTE ALGORITMO VER REFERÊNCIAS.
PARA MAIORES REFERÊNCIAS: Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance
                          https://math.stackexchange.com/questions/14787/finding-irreducible-polynomials-over-gf2-with-the-fewest-terms

*/


//******************************************************************************************
//CABEÇALHO
#ifndef POLYNOMIAL_IRREDUCIBILITY_H
#define POLYNOMIAL_IRREDUCIBILITY_H
#include"mod_bin_exponentiation128.h"
#include"polynomial_exponentiation_finite_field.h"
#include"polynomial_gcd.h"
#include<cmath>


//******************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void factoring_gf2(std::vector<int64_t>&, int64_t);

template<typename T>
polynomial<T> generate_gf2_polynomial(int64_t);

template<typename T>
bool gf2_irredutibility_criterion(polynomial<T>&);


template<typename T>
bool irredutibility_criterion(polynomial<T>&, int64_t);


//******************************************************************************************
//FUNÇÕES
//Função que determinafatores primos de um inteiro de 64 bits
void factoring_gf2(std::vector<int64_t>& prime_vector, int64_t n){

  //Variáveis locais
  int64_t root=std::sqrt(n);

  //Procedimentos
    //Ajuste de variáveis
    prime_vector.resize(0);

    //Fatores 2 e 3
    if(!(n&1)){
      prime_vector.push_back(2);
      while(!(n&1)) n>>=1;
    }

    if(n==1) return;

    if(n%3==0){
      prime_vector.push_back(3);
      while(n%3==0) n/=3;
    }

    if(n==1) return;

    //Loop principal
    for(int64_t i=5; i<=root; i+=6){
      if(n%i==0){
        prime_vector.push_back(i);
        while(n%i==0) n/=i;
      }
      
      if(n==1) return;

      if((n%(i+2))==0){
        prime_vector.push_back((i+2));
        while((n%(i+2))==0) n/=(i+2);
      }

      if(n==1) return;
    }


    //Fatores superiores a n^(1/2)
    if(n>1)  prime_vector.push_back(n);
  
};
 
//Função que cria um polinômio do tipo f(x)=x^(2^k)-x para testar irredutibilidade de polinômios em GF(2)
template<typename T>
polynomial<T> generate_gf2_polynomial(int64_t k){

  //Variáveis locais
  polynomial<T> result;

  //Procedimentos
    //Ajuste do grau do polinômio
    result.degree=bin_pow(2, k);

    //Ajuste dos coeficientes do polinômio
    for(int64_t i=result.degree; i>=0; --i){
      result.polynomial_powers.push_back(i);
      if(i==result.degree || i==1)
        result.polynomial_coefficients.push_back(1);
      else result.polynomial_coefficients.push_back(0);
    }

  //Resultado
  return result;
};


//Função que implementa teste de irredutibilidade em polinômios binários definidos sobre  GF(2)
template<typename T>
bool gf2_irredutibility_criterion(polynomial<T>& f){

  //Variáveis locais
  polynomial<T> gf2_tester, gf2_remainder, gf2_gcd;
  std::vector<int64_t> prime_factors;
  int64_t gf2_key, m=f.degree;

  //Procedimentos
    //Teste 1: testando se p(x)= x^(2^m)-x satisfaz a p(x)= 0 (mod f(x))
    gf2_tester=generate_gf2_polynomial<T>(m);
    gf2_remainder=remainder<T>(gf2_tester, f);

    for(auto& c:gf2_remainder.polynomial_coefficients) c&=1;
    gf2_remainder.adjust_degree();
    if(is_zero_polynomial<T>(gf2_remainder)==false) return false;

    //Fatorando o expoente do polinômio
    factoring_gf2(prime_factors, m);

    //Teste 2: checando se mdc(q(x), f(x))=1, para q(x)= x^[2^(m/p)]-x para cada divisor primo de m=deg(f(x))
    for(auto p:prime_factors){
      gf2_key=m/p;
      gf2_tester=generate_gf2_polynomial<T>(gf2_key);
      gf2_gcd=polynomial_gcd<T>(gf2_tester, f);

      for(auto& c:gf2_gcd.polynomial_coefficients) c&=1;//Redução dos coeficientes mod 2
      gf2_gcd.adjust_degree();

      if(is_unity_polynomial<T>(gf2_gcd)==false)
        return false; //Um fator não trivial de f(x) foi encontrado
    }

  
  //Caso passe nos testes acima um polinômio irredutível sobre GF(2) foi encontrado
  return true;

};

//Função que determina se um polinômio é irredutível sobre um corpo finito do primeiro tipo
template<typename T>
bool irredutibility_criterion(polynomial<T>& f, int64_t prime){

  //Caso base: p=2
  if(prime==2) return gf2_irredutibility_criterion(f);

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
      for(auto& c:poly_gcd.polynomial_coefficients) c%=prime;//Reduzindo coeficientes mod p
      poly_gcd.adjust_degree();

      if(is_unity_polynomial<T>(poly_gcd)==false)
        return false; //Um fator não trivial de f(x) foi encontrado

    }


  //Caso passe no teste acima um polinômio irredutível foi encontrado
  return true;

};


//******************************************************************************************
//FIM DO HEADER
#endif
