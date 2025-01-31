//VAMOS CRIAR UMA FUNÇÃO QUE COMPUTA A FUNÇÃO DE SOMAS DE QUADRADOS r(k,n) USANDO FUNÇÕES THETA DE JACOBI θ3(z, q)

/*

A FUNÇÃO DE SOMAS DE QUADRADOS r(k,n) É UMA FUNÇÃO ARITMÉTICA QUE COMPUTA DE QUANTAS FORMAS DISTINTAS UM INTEIRO n
PODE SER EXPRESSO COMO A SOMA DE k QUADRADOS PERFEITOS, CONSIDERANDO DISTINTAS ORDENS E SINAIS DOS FATORES. POR
EXEMPLO: r(2,1)=4, POIS 2=1²+1²=(-1)²+1²= 1²+(-1)²=(-1)²+(-1)²; r(5,2)=8, POIS 5=1²+2²=(-1)²+2²= 1²+(-2)²=
(-1)²+(-2)²=2²+1²=(-2)²+1²= 2²+(-1)²=(-2)²+(-1)².

TEOREMAS DEVIDO A JACOBI E LEGENDRE DETERMINAM CASOS NOS QUAIS r(k,n) É NÃO NULO PARA k=2,3,4; DADO UM VALOR DE n.
PARA OS CASOS k=2,3,4,6,8, EXISTEM FÓRMULAS EXPLÍCITAS PARA COMPUTAR r(k, n) EM TERMOS DE FUNÇÕES ARITMÉTICAS COMO
AS FUNÇÕES DE CONTAGEM DE DIVISORES d(n), A FUNÇÃO DE SOMA DE DIVISORES σ(n) E O NÚMERO DE CLASSE h(n).

A FUNÇÃO r(k, n) PODE SER EXPRESSA EM TERMOS DA FUNÇÃO THETA DE JACOBI θ3(z, q)=Σ{q^(n^2)}e^(i2zn), ONDE i DENOTA 
A UNIDADE IMAGINÁRIA E q, z SÃO NÚMEROS COMPLEXOS E n=..., -2, -1, 0, 1, 2, ... MAIS ESPECIFICAMENTE PARA z=0
A SEGUINTE IDENTIDADE É VÁLIDA: {θ3(z=0, q)^k}=Σr(k,n){q^(n^2)}. TEMOS QUE θ3(z=0, q)=1+2q+2(q^4)+2(q^9)+...; DE
MODO QUE θ3(z=0, q) PODE SER APROXIMADA USANDO-SE POLINÔMIOS.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Sum_of_squares_function#Formulae
                          https://en.wikipedia.org/wiki/Sum_of_two_squares_theorem#Jacobi's_two-square_theorem
                          https://en.wikipedia.org/wiki/Legendre%27s_three-square_theorem
                          https://en.wikipedia.org/wiki/Jacobi%27s_four-square_theorem
                          https://en.wikipedia.org/wiki/Theta_function#Jacobi_theta_function
                          https://mathworld.wolfram.com/SumofSquaresFunction.html
                          https://mathworld.wolfram.com/JacobiThetaFunctions.html

*/


//************************************************************************************************
//CABEÇALHO
#ifndef SUM_OF_SQUARES_FUNCTION_H
#define SUM_OF_SQUARES_FUNCTION_H
#include"sparse_polynomials.h"



//************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
polynomial<T> generate_sum_of_squares_polynomial(int64_t);

template<typename T>
void compute_sum_of_squares_function(int64_t, int64_t);

//************************************************************************************************
//FUNÇÕES
//Função que gera um polinômio correspondendo a uma soma parcial da série da função θ3(z=0, q)
template<typename T>
polynomial<T> generate_sum_of_squares_polynomial(int64_t n){

  //Variáveis locais
  polynomial<T> result;
  univariate_monomial<T> poly_term;



  //Procedimentos
    //Inicializando o polinômio
    poly_term.coefficient=1;  poly_term.power=0;
    result.monomials.insert({poly_term.power, poly_term}); 

    //Adicionando demais elementos
    for(int64_t i=1; (i*i)<n; ++i){
      poly_term.coefficient=2; poly_term.power=(i*i);
      result.monomials.insert({poly_term.power, poly_term}); 
    }
    

  //Resultado
  return result;

};


//Função que computa a função r(k, n) para valores de n em um intervalo e k fixo
template<typename T>
void compute_sum_of_squares_function(int64_t k, int64_t n){

  //Variáveis locais
  polynomial<T> sum_of_squares_polynomial = generate_sum_of_squares_polynomial<int64_t>(n);
  polynomial<T> multiplier = sum_of_squares_polynomial;  

  //Procedimentos
    //Computando {θ3(z=0, q)^k}
    if(k>1){
      for(int64_t i = 1; i<k; ++i){

        sum_of_squares_polynomial = multiplier*sum_of_squares_polynomial;

        //Removendo termos de expoentes elevados
        for(auto it=sum_of_squares_polynomial.monomials.begin(); it!=sum_of_squares_polynomial.monomials.end();){
          if((it->second.power)>(n*n)) it = sum_of_squares_polynomial.monomials.erase(it);
          else break;
        }
          
      }/*Para valores grandes de k usar a exponenciação binária*/
    };

    //Resultado da execução do algoritmo
    for(int64_t j=0; j<=n; ++j){
      std::cout<<"r("<<k<<", "<<j<<") = ";

      auto found=sum_of_squares_polynomial.monomials.find(j); //Checando se o j-ésimo coeficiente é não nulo
      if(found != sum_of_squares_polynomial.monomials.end()) std::cout<<found->second.coefficient<<", ";
      else std::cout<< 0 <<", ";      

    }   
    std::cout<<"...\n";


};

//************************************************************************************************
//FIM DO HEADER
#endif
