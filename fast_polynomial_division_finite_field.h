//VAMOS CRIAR UM PROGRAMA QUER IMPLEMENTA ROTINAS EFICIENTES PARA DIVISÃO DE POLINÔMIOS DEFINIDOS EM CORPOS FINITOS DO PRIMEIRO TIPO

/*
A SEGUINTE VARIANTE DO ALGORITMO DE EUCLIDES PODE SER USADA PARA COMPUTAR O QUOCIENTE q E O RESTO r DA
DIVISÃO DE DOIS INTEIROS a, b, ISTO É, a=bq+r. SEJA |_a/b_| UM LIMITANTE INFERIOR DO QUOCIENTE DE a E
b, SE ESTE LIMITANTE PUDER SER COMPUTADO ENTÃO POR DEFINIÇÃO q=|_a/b_| E r = a-bq = a (mod b). q PODE
SER FACILMENTE COMPUTADO USANDO O ALGORITMO DE NEWTON-RAPHSON.

SEJA h(x)=(1/x)-b, TEMOS QUE h'(x)=-(1/x²), PODEMOS CALCULAR 1/b APLICANDO A SEQUÊNCIA
x(i+1)=x(i)-(f(x(i))/f'(x(i))), A FUNÇÃO h(x). SUBSTITUINDO EM  f(x) A EXPRESSÃO DE h(x) OBTÉM-SE QUE
x(i+1)=2x(i)-bx²(i). A IDEIA DO PRESENTE  ALGORITMO É EXPLORAR RELAÇÕES IDÊNTICAS A ESTAS PARA
POLINÔMIOS.

PARA MAIORES REFERÊNCIAS: https://math.mit.edu/classes/18.783/2017/LectureNotes4.pdf
                          Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance

*/ 


//************************************************************************************************************************************
//CABEÇALHO
#ifndef FAST_POLYNOMIAL_DIVISION_H
#define FAST_POLYNOMIAL_DIVISION_H
#include"polynomial_rational_irreducibility.h"
#include"polynomial_exponentiation_finite_field.h"
#include"polynomial_exponentiation.h"
#include"polynomial_modulus_reduction.h"
#include"polynomial_gcd.h"
#include"mod_bin_exponentiation128.h"
#include<cmath>


//************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
polynomial<T> generate_powering_monomial(int64_t);

template<typename T>
void fast_polynomial_division_finite_field(polynomial<T>&, polynomial<T>&, polynomial<T>&, polynomial<T>&, T);

//************************************************************************************************************************************
//FUNÇÕES
//Função que gera um polinômio do tipo f(x)=x^n
template<typename T>
polynomial<T> generate_powering_monomial(int64_t n){

  //Variáveis locais
  polynomial<T> linear_polynomial, result;


  //Procediemntos
    //Ajuste do polinômio m(x)=x
    linear_polynomial.degree=1;
    linear_polynomial.polynomial_coefficients.push_back(1); linear_polynomial.polynomial_coefficients.push_back(0);
    linear_polynomial.polynomial_powers.push_back(1); linear_polynomial.polynomial_powers.push_back(0);

    //Cálculo do resultado
    result=polynomial_bin_pow<T, int64_t>(linear_polynomial, n);

  //Resultado
  return result;

};

//Função que calcula o quociente e o resto da divisão de dois polinômios (o divisor deve ser um polinômio mônico)
template<typename T>
void fast_polynomial_division_finite_field(polynomial<T>& A, polynomial<T>& B, polynomial<T>& quotient, polynomial<T>& remainder, T prime){

  //Caso base:
  if(B.degree>A.degree){
    quotient=generate_zero_polynomial<T>();
    remainder=A;
    return;
  };
  
  //Variáveis locais
  polynomial<T> p1, p2, g0, g1, f, s;
  polynomial<T> mod_poly1, mod_poly2;
  int64_t m=A.degree-B.degree;
  int64_t k=std::ceil(log(m))+1;

  //Procedimentos
    //Calculando f(x)=rev(B) : invertendo os coeficientes do polinômio B(x)
    f=polynomial_reversal<T>(B);
    g0=generate_unity_polynomial<T>();
    

    //Loop principal
    for(int64_t i=1; i<=k; ++i){
    
      //Cálculo do loop: g(k+1, x)=2g(k, x)-f(x)g²(k, x) mod x^(2^i)
      p1=g0;
      for(auto& c:p1.polynomial_coefficients) c<<=1;

      p2=(f*g0); p2=polynomial_modulus_reduction<T, T>(p2, prime);
      p2=(p2*g0); p2=polynomial_modulus_reduction<T, T>(p2, prime);

      mod_poly1=generate_powering_monomial<T>(bin_pow(2, i));

      g1=p1-p2;
      g1=polynomial_modulus_reduction<T, T>(g1, prime);
      if(g1.degree>mod_poly1.degree){
        polynomial<T> temp1=g1/mod_poly1; polynomial<T> temp2=mod_poly1*temp1;
        g1=g1-temp2;
      }
      g1=polynomial_modulus_reduction<T, T>(g1, prime);

      //Atualizando variável para a próxima iteração
      g0=g1;

    }
  
    //Calculando s(x)=rev(A)g(k, x) mod x^(m+1)
    f=polynomial_reversal<T>(A);
    s= f*g1;
    s=polynomial_modulus_reduction<T, T>(s, prime);
    
    mod_poly2=generate_powering_monomial<T>((m+1));
    if(s.degree>mod_poly2.degree){
      polynomial<T> temp1=s/mod_poly2; polynomial<T> temp2=mod_poly2*temp1;
      s=s-temp2;
    };
    s=polynomial_modulus_reduction<T, T>(s, prime);


  //Resultado
  mod_poly1=generate_powering_monomial<T>((m-s.degree));
  f=polynomial_reversal<T>(s);
  quotient=(f*mod_poly1);
  quotient=polynomial_modulus_reduction<T, T>(quotient, prime);
  

  p1=B*quotient;
  p1=polynomial_modulus_reduction<T, T>(p1, prime);
  remainder=A-p1;
  remainder=polynomial_modulus_reduction<T, T>(remainder, prime);

};

//************************************************************************************************************************************
//FIM DO HEADER
#endif
