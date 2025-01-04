//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE RABIN PARA TESTAR A IRREDUTIBILIDADE DE POLINÔMIOS COM COEFICIENTES EM CORPOS FINITOS DO PRIMEIRO

/*
O ALGORITMO DE RABIN É UMA EFICIENTE ALGORITMO PARA TESTAR A IRREDUTIBILIDADE DE POLINÔMIOS COM
COEFICIENTES DEFINIDOS SOBRE CORPOS FINITOS E BASEIA-SE NA SEUINTE PROPOSIÇÃO: SEJA p PRIMO E
f(x) UM POLINÔMIO MÔNICO COM COEFICIENTES EM GF(p), SEJA n O GRAU DE f(x) E p(1),..., p(k) OS
FATORES PRIMOS DE n ENTÃO f(x) É IRREDUTÍVEL SE E SOMENTE SE f(x) E p(x)=x^[p^(n/p(i))]-x PARA
i=1,..,k NÃO TIVEREM FATORES COMUNS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Factorization_of_polynomials_over_finite_fields#cite_note-5
                          https://epubs.siam.org/doi/10.1137/0209024
                          https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/polynomial_irreducibility.h

*/ 


//***********************************************************************************************
//CABEÇALHO
#ifndef RABIN_POLYNOMIAL_IRREDUCIBILITY_TEST_H
#define RABIN_POLYNOMIAL_IRREDUCIBILITY_TEST_H
#include"polynomial_gcd_finite_field.h"
#include"polynomial_irreducibility.h"

//***********************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
polynomial<__int128_t> generate_rabin_factor_polynomial(int64_t, int64_t);

template<typename T>
bool rabin_irredutibility_criterion(polynomial<T>&, int64_t);

//***********************************************************************************************
//FUNÇÕES
//Função que cria um polinômio do tipo f(x)=x^(p^k)-x para testar irredutibilidade de polinômios em GF(P)
polynomial<__int128_t> generate_rabin_factor_polynomial(int64_t prime, int64_t k){

  //Variáveis locais
  polynomial<__int128_t> linear_poly;
  polynomial<__int128_t> result;
  __int128_t deg=bin_pow(prime, k);

  //Procedimentos
    //Ajuste do polinômio f(x)=x
    linear_poly.degree=1;
    linear_poly.polynomial_powers={1,0};
    linear_poly.polynomial_coefficients={1,0};


    //Ajuste dos polinômio r(x)=f(x)^[p^k]
    result=polynomial_bin_pow<__int128_t, __int128_t>(linear_poly, deg);
    result=result-linear_poly;
  

  //Resultado
  return result;

};


//Função que implementa o teste de irredutibidade de Rabin em GF(p)
template<typename T>
bool rabin_irredutibility_criterion(polynomial<T>& p1, int64_t prime){

  //Variáveis locais
  polynomial<__int128_t> f=polynomial_cast<T, __int128_t>(p1), q, r;
  polynomial<__int128_t> gcd_poly, tester_poly;
  std::vector<int64_t> f_degree_factors;
  int64_t exponent;


  //Procedimentos
    //Calculando fatores primos do expoente do polinômio a ser testado
    factoring_gf2(f_degree_factors, f.degree);

    
    //Loop principal
    for(auto p:f_degree_factors){

      exponent=f.degree/p;
      tester_poly=generate_rabin_factor_polynomial(prime, exponent);
      gcd_poly=polynomial_gcd_finite_field<__int128_t>(f, tester_poly, prime);
      if(is_unity_polynomial<__int128_t>(gcd_poly)==false) return false;//Fator primo de  f(x) encontrado

    }


    //Testando se g(x)=x^[deg(f(x))]-x mod(f(x), p) é igual a 0
    exponent=f.degree;
    tester_poly=generate_rabin_factor_polynomial(prime, exponent);
    fast_polynomial_division_finite_field<__int128_t>(tester_poly, f, q, r, (__int128_t)prime);

    if(is_zero_polynomial<__int128_t>(r)==false) return false;


  //Caso passe nos testes acima um polinômio irredutível sobre GF(p) foi encontrado
  return true;


};

//***********************************************************************************************
//FIM DO HEADER
#endif 
