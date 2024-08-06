//VAMOS CRIAR UM PROGRAMA QUE CALCULA RAÍZES QUADRADAS A MENOS DE UMA CONGRUÊNCIA USANDO O ALGORITMO DE BERKELAMP-RABIN

/*
O ALGORITMO DE BERKELAMP-RABIN É UM ALGORITMO PROBABILÍSTICO QUE PERMITE DETERMINAR AS RAÍZES DE UM 
POLINÔNIO SOBRE UM CORPO FINITO DO PRIMEIRO TIPO (INTEIRO A MENOS DE UMA CONGRUÊNCIA) F(p).

O ALGORITMO BASEIA-SE NA SEGUINTE OBERVAÇÃO: CALCULAR RAÍZES DE UM POLINÔMIO É EQUIVALENTE A SUA
DECOMPOSIÇÃO EM FATORES LINEARES f(x)=x-a, a SENDO UMA RAÍZES.

DE MODO SIMILAR AO GRUPO DE INTEIROS COM OPERAÇÃO DE MULTIPLICAÇÃO, PODE-SE DEFINIR UM ANÁLOGO A
LEI DE RECIPROCIDADE QUADRATICA SE UMA EXPRESSÃO DO TIPO f(x)=x-a, FOR UM DIVISOR DE
g(x)=x^((p-1)/2)+1 OU g(x)=x^((p-1)/2)-1.


SEJA p(x) UM POLINÔMIO DEFINIDO SOBRE F(p) (INTEIROS A MENOS DE UMA CONGRUÊNCIA mod p). SEJA
λ UM ELEMENTO DE F(p) E q(x) O POLINÔMIO RESULTANTE DA TRANSFORMAÇÃO DE x-> x-λ. CALCULANDO-SE
x^((p-1)/2) (mod q(x)), TEMOS QUE O RESULTADO É IGUAL A +1,-1 SE AS RAÍZES DE p(x) SÃO 
SIMULTANEAMENTE RESÍDUOS OU NÃO RESÍDUOS QUADRÁTICOS mod p. CASO CONTRÁRIO TOMANDO-SE
mdc(g(x), q(x)) UMA FATORAÇÃO NÃO TRIVIAL DE p(x) EM F(p) É OBTIDA. O PROCEDIMENTO PODE SER
APLICADO RECURSIVAMENTE. A ALEATORIEDADE DO ALGORITMO CONSISTE NA ESCOLHA DO PARÂMETRO λ.


NO CASO PARTICULAR DE DETERMINAR AS SOLUÇÕES DA EQUAÇÃO DIOFANTINA x²= a (mod p), ISTO EQUIVALE A
DETERMINAR AS RAÍZES DO POLINÔMIO f(x)=x²-a (mod p). O PROCEDIMENTO ACIMA SE TORNA EXTREMAMENTE 
SIMPLES.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Berlekamp–Rabin_algorithm#Modular_square_root

*/


//-------------------------------------------------------------------------------------------------------------
//CABEÇALHO
#ifndef BERKELAMP_RABIN_MODULAR_SQUARE_ROOT_H
#define BERKELAMP_RABIN_MODULAR_SQUARE_ROOT_H
#include"legendre_symbol.h"
#include"polynomial_exponentiation.h"
#include"polynomial_modulus_reduction.h"

//-------------------------------------------------------------------------------------------------------------
//DECLARAÇÃO DE FUNÇÕES
polynomial<int64_t> set_quadratic_polynomial(int64_t,int64_t);
polynomial<int64_t> set_powering_polynomial(int64_t);
bool find_quadratic_residue(int64_t&, int64_t, int64_t, int64_t);
int64_t berkelamp_rabin_modular_square_root(int64_t, int64_t);


//-------------------------------------------------------------------------------------------------------------
//FUNÇÕES
//Função que gera um polinômio do segundo grau q(x)=(x-λ)²-a=x²-2λx+(λ²-a)
polynomial<int64_t> set_quadratic_polynomial(int64_t lambda, int64_t a){

  //Variáveis locais
  polynomial<int64_t> result;


  //Procedimento
    //Cálculo do resultado
    result.degree=2;
    result.polynomial_coefficients.push_back(1);
    result.polynomial_coefficients.push_back((lambda*(-2)));
    result.polynomial_coefficients.push_back(((lambda*lambda)-a));
    result.polynomial_powers.push_back(2);  result.polynomial_powers.push_back(1); result.polynomial_powers.push_back(0);


  //Resultado
  return result;


};

//Função que calcula um polinômio p(x)=x^a-1
polynomial<int64_t> set_powering_polynomial(int64_t a){

  //Variáveis locais
  polynomial<int64_t> first_deg_poly;
  polynomial<int64_t> result;


  //Procedimento
    //Ajuste do termo linear x
    first_deg_poly.degree=1;
    first_deg_poly.polynomial_coefficients.push_back(1); first_deg_poly.polynomial_coefficients.push_back(0);
    first_deg_poly.polynomial_powers.push_back(1); first_deg_poly.polynomial_powers.push_back(0);

    //Cálculo do resultado
    result=polynomial_bin_pow<int64_t, int64_t>(first_deg_poly, a);
    result.polynomial_coefficients[a]=(-1);

  //Resultado
  return result;


};

//Função que encontra classes residuais quadráticas β²=a (mod n)
bool find_quadratic_residue(int64_t& beta, int64_t lambda, int64_t a, int64_t p){

  //Variáveis locais
  polynomial<int64_t> power_poly= set_powering_polynomial(a);
  
  //Procedimentos
    //Testando o valor de λ
    polynomial<int64_t> quadratic_poly=set_quadratic_polynomial(lambda, a);
    polynomial<int64_t>remainder_poly=remainder(power_poly, quadratic_poly);
    polynomial<int64_t>reduced_poly=polynomial_modulus_reduction<int64_t,int64_t>(remainder_poly, p);

    if(reduced_poly.degree==1){
        beta=reduced_poly.polynomial_coefficients[1];
        return true;
    }      


  //Caso de falha
  beta=0;
  return false;


};

//Função que resolve a equação diofantina x²=a (mod p) usando o algoritmo de Berkelamp-Rabin
int64_t berkelamp_rabin_modular_square_root(int64_t a, int64_t p){

  //Restrição a classes resíduais quadráticas mod p
  if(legendre(a,p)!=1) return 0;

  //Variáveis locais
  int64_t beta, lambda=2, tester1, tester2;

  //Procedimentos
    //Determinando os parâmetros λ e β
    while(lambda <p){

      if(find_quadratic_residue(beta, lambda, a, p)==true){
        tester1=(beta+lambda);
        tester2=(beta-lambda);

        if((tester1*tester1)%p==a) return tester1;
        else if((tester2*tester2)%p==a) return tester2;
      }

      else lambda++;


    }
    

  //Resultado em caso de falha
  return 0;

};



//-------------------------------------------------------------------------------------------------------------
//FIM DO HEADER
#endif
