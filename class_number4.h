//VAMOS CRIAR UM PROGRAMA QUE COMPUTA NÚMEROS DE CLASSES DE CORPOS QUADRÁTICOS IMAGINÁRIOS USANDO A FUNÇÃO DE SOMAS DE QUADRADOS r(3,n)


/*

A SEGUINTE IDENTIDADE PODE SER USADA PARA COMPUTAR NÚMEROS DE CLASSE PARA CORPOS QUADRÁTICOS IMAGINÁRIOS Q(√-d)
CUJO DISCRIMINANTE É FUNDAMENTAL: SEJA r(3,n) A FUNÇÃO QUE DETERMINA DE QUANTAS FORMAS DISTINTAS UM INTEIRO n
PODE SER ESCRITO COMO A SOMA DE 3 QUADRADOS PERFEITOS, h(-d) O NÚMERO DE CLASSE ASSOCIADO A Q(√-d) E (|) O 
SÍMBOLO DE KRONECKER e D=|d|(VALOR ABSOLUTO DO DISCRIMINANTE), ENTÃO: r(3, D) = 12(1-(D|2))h(-d).

É IMPORTANTE RELEMBRAR O TEOREMA DE LEGENDRE QUE RESTRINGE A APLICAÇÃO DO PRESENTE MÉTODO: UM NÚMERO PODE SER
EXPRESSO COMO A SOMA DE TRÊS QUADRADOS n=a²+b²+c², SE E SOMENTE ELE NÃO FOR DA FORMA  n=(4^m)(8n+7) COM m, n
INTEIROS.

TAL RELAÇÃO É ÚTIL PARA COMPUTAR NÚMEROS DE CLASSE PARA DISCRIMINANTES FUNDAMENTAIS DA ORDEM DE 10^7 QUE
OBEDECEM A RESTRIÇÃO DO TEOREMA DE LEGENDRE, SENDO ÚTIL PARA COMPUTAR PEQUENAS LISTAS.


PARA MAIORES INFORMAÇÕES: A Course In Computational Algebraic Number Theory by Henri Cohen
                          https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/sum_of_squares_function.h

*/ 

//************************************************************************************************
//CABEÇALHO
#ifndef CLASS_NUMBER_SUM_OF_SQUARES_FUNCTION_H
#define CLASS_NUMBER_SUM_OF_SQUARES_FUNCTION_H
#include"sparse_polynomials.h"
#include"kronecker_symbol.h"
#include<math.h>


//************************************************************************************************
//ESTRUTURAS USADAS NO ALGORITMO
struct class_number_pair{
  int64_t d;//Discriminante fundamental
  int64_t h;//Número de classe
};

//************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool is_square_factor_free(int64_t);
bool is_fundamental_discriminant(int64_t);
polynomial<int64_t> generate_sum_of_squares_polynomial(int64_t);
std::vector<struct class_number_pair> compute_class_number_fundamental_discriminante(int64_t);

//************************************************************************************************
//FUNÇÕES
// Função que determina se um inteiro contém fatores quadráticos
bool is_square_free(int64_t n) {

  // Variáveis locais
  int64_t i, limit = sqrt(n);

  // Procedimentos
    // Casos triviais
    if (n < 4) return true;

    // Fatores 2 e 3
    if ((n % 4) == 0) return false;
    if ((n % 9) == 0) return false;

    // Loop principal com otimização 6k+1
    for (i = 5; i < (limit + 2); i += 6) {
      if ((n % (i * i)) == 0) return false;
      if ((n % ((i + 2) * (i + 2))) == 0) return false;
    };

  // Caso passe nos testes acima
  return true;
};


// Função que determina se um inteiro corresponde a um discrimante fundamental
bool is_fundamental_discriminant(int64_t n) {
  //Caso bases: n=1 e contém fatores primos repetidos
  if (n == 1) return false;
  if(is_square_free(n*(-1))==false) return false;


  //Variáveis locais
  int64_t mod4=(n%4), mod16=(n%16); // mod 4 e mod 16

  //Procedimentos
    //Testando se n (mod 4)=1 ou n (mod 16)=8, 12
    if(mod4<0) mod4+=4;
    if(mod4==1) return true;
 
    if(mod16<0) mod16+=16;
    if(mod16==8 || mod16==12) return true;



  // Caso o número não passe nos testes acima
  return false;
};

//Função que gera um polinômio correspondendo a uma soma parcial da série da função θ3(z=0, q)
polynomial<int64_t> generate_sum_of_squares_polynomial(int64_t n){

  //Variáveis locais
  polynomial<int64_t> result;
  univariate_monomial<int64_t> poly_term;



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


//Função que computa o número de classe para discriminantes fundamentais em um intervalo
std::vector<struct class_number_pair> compute_class_number_fundamental_discriminante(int64_t n){

  //Variáveis locais
  polynomial<int64_t> sum_of_squares_polynomial = generate_sum_of_squares_polynomial(n);
  polynomial<int64_t> multiplier = sum_of_squares_polynomial;  
  std::vector<struct class_number_pair> class_number_vector;
  int64_t D, r3;


  //Procedimentos
    //Computando {θ3(z=0, q)^3}
    sum_of_squares_polynomial = multiplier*sum_of_squares_polynomial;
    sum_of_squares_polynomial = multiplier*sum_of_squares_polynomial;

    //Removendo termos de expoentes elevados
    for(auto it=sum_of_squares_polynomial.monomials.begin(); it!=sum_of_squares_polynomial.monomials.end();){
      if((it->second.power)>(n*n)) it = sum_of_squares_polynomial.monomials.erase(it);
      else break;
    }


    //Computando os números de classes para discriminantes fundamentais D<(-4)
    for(int64_t j=5; j<=n; ++j){

      auto found=sum_of_squares_polynomial.monomials.find(j); //Checando se o j-ésimo coeficiente é não nulo
      if(found != sum_of_squares_polynomial.monomials.end()){
        r3=(found->second.coefficient);
        D=((-1)*j);
      }
      else continue;

      if(is_fundamental_discriminant(D) == false ) continue;
      
      struct class_number_pair q;
      q.d=D;
      q.h=r3/(12*(1-kronecker(found->second.power, 2)));
      class_number_vector.push_back(q);

    };

  
  //Resultado
  return class_number_vector;
 
};


//************************************************************************************************
//FIM DO HEADER
#endif
