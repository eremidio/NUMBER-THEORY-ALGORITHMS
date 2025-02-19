//VAMOS CRIAR UM PROGRAMA QUE CALCULA NÚMEROS DA SEQUÊNCIA DE FIBONACCI USANDO FUNÇÕES GERADORAS

/*
A SEQUÊNCIA DE FIBONACCI PODE SER OBTIDA POR MEIO DA FUNÇÃO GERADORA: Σ F(n)(x^n)=1/{1-(x+x²)}.

TAL FÓRMULA PODE SER FACILMENTE DEMONSTRADA REESCREVENDO-A COMO (1-x-x²) ΣF(n)(x^n) = 1 E
USANDO A RELAÇÃO F(n)-F(n-1)-F(n-2)=0.

PARA MAIORES INFORMAÇÕES: Number Theory in the Spirit of Ramanujan by Bruce C. Berndt
                          https://math.stackexchange.com/questions/338740/the-generating-function-for-the-fibonacci-numbers

*/ 


//**************************************************************************************************************
//CABEÇALHO
#ifndef FIBONACCI_GENERATING_FUNCTION_H
#define FIBONACCI_GENERATING_FUNCTION_H
#include"sparse_polynomials.h"

//**************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
polynomial<T> generate_fibonacci_polynomial(int64_t);

template<typename T>
std::vector<T> compute_fibonacci_numbers(polynomial<T>&);

//**************************************************************************************************************
//FUNÇÕES
//Função que computa somas parciais da série geradora da sequência de Fibonacci
template<typename T>
polynomial<T> generate_fibonacci_polynomial(int64_t n){

  //Variáveis locais
  polynomial<T> fibonacci_polynomial; 
  polynomial<T> partial_fib_poly1, partial_fib_poly2;
  univariate_monomial<T> poly_term;

  
  //Procedimentos
    //Adicionando o primeiro termo
    poly_term.coefficient=1; poly_term.power=0;
    fibonacci_polynomial.monomials.insert({poly_term.power, poly_term});
  
    //Definindo o polionômio fib1(x)=x+x²
    poly_term.coefficient=1; poly_term.power=1;
    partial_fib_poly1.monomials.insert({poly_term.power, poly_term});
    poly_term.coefficient=1; poly_term.power=2;
    partial_fib_poly1.monomials.insert({poly_term.power, poly_term});

    partial_fib_poly2=partial_fib_poly1;


    //Computando a soma parcial da série geradora da sequência de Fibonacci
    for(int64_t i=1; i<=n; ++i){

      fibonacci_polynomial=fibonacci_polynomial+partial_fib_poly2;
      partial_fib_poly2=partial_fib_poly2*partial_fib_poly1;

      //Removendo os termos de expoentes elevados
      if(fibonacci_polynomial.degree()>(n<<1)){
        for(auto it=fibonacci_polynomial.monomials.begin(); it!=fibonacci_polynomial.monomials.end();){
          if((it->first)>n)
            it = fibonacci_polynomial.monomials.erase(it);
          else break;
        }

      };

      
    };


    //Removendo os termos de expoentes elevados
    for(auto it=fibonacci_polynomial.monomials.begin(); it!=fibonacci_polynomial.monomials.end();){
      if((it->first)>n) it = fibonacci_polynomial.monomials.erase(it);
      else break;
    };


  //Resultado
  return fibonacci_polynomial;

};


//Função que computa asequência de Fibonacci a partir da sua função geradora
template<typename T>
std::vector<T> compute_fibonacci_numbers(polynomial<T>& fibonacci_polynomial){

  //Variáveis locais
  std::vector<T> fib_vector;

  //Procedimentos
    //Loop sobre os coeficientes da série geradora da sequência de Fibonacci
    for(auto it=fibonacci_polynomial.monomials.begin(); it!=fibonacci_polynomial.monomials.end(); ++it){
      T fib=it->second.coefficient;
      fib_vector.push_back(fib);
    }

  //Resultado
  return fib_vector;


};

//**************************************************************************************************************
//FIM DO HEADER
#endif
