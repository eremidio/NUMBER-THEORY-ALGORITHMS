//VAMOS CRIAR UM PROGRAMA QUE COMPUTAO NÚMERO DE PARTIÇÕES DE UM INTEIRO USANDO FUNÇÕES GERADORAS

/*
O NÚMERO DE PARTIÇÕES DE UM INTEIRO DENOTADO POR p(n) CORRESPONDE AO NÚMERO DE DIFERENTES
MANEIRAS DE ESCREVER UM INTEIRO COMO UMA SOMA DE INTEIROS NÃO NEGATIVOS.

A SEGUINTE RELAÇÃO PERMITE COMPUTAR VALORES DE p(n): Σp(n){x^n}=Π {1/(1-x^i)}, i=1,2,...
PARA |x|<1, 1/(1-x^i)=1+x^i+x^(2i)+x^(3i)+...

O NÚMEROS DE PARTIÇÕES DE INTEIROS CONTENDO PROPRIEDADES ESPECÍFICAS COMO PARTIÇÕES
CONTENDO APENAS PARCELAS ÍMPARES, OU TENDO UM NÚMERO RESTRITO DE PARCELAS PODEM SER
COMPUTADAS USANDO-SE DIFERENTES FUNÇÕES GERADORAS.

PARA MAIORES INFORMAÇÕES: https://math.berkeley.edu/~mhaiman/math172-spring10/partitions.pdf
                          Experimental Number Theory by F. R. Villegas


*/


//*********************************************************************************************************
//CABEÇALHO
#ifndef INTEGER_PARTITION_GENERATING_FUNCTION_H
#define INTEGER_PARTITION_GENERATING_FUNCTION_H
#include"sparse_polynomials.h"

//*********************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
polynomial<T> generate_integer_polynomial_factor(int64_t, int64_t);

template<typename T>
void compute_integer_partitions(int64_t);

//*********************************************************************************************************
//FUNÇÕES
//Função que gera um polinômio usado para computar partições de um inteiro
template<typename T>
polynomial<T> generate_integer_polynomial_factor(int64_t bound, int64_t step){

  //Variáveis locais
  polynomial<T> result;
  univariate_monomial<T> poly_term;

  //Procedimentos
    //Adicionando os termos do polinômio de intersee
    //1º termo
    poly_term.coefficient=1;  poly_term.power=0;
    result.monomials.insert({poly_term.power, poly_term});

    //Demais termos
    for(int64_t i=step; i<bound; i+=step){
      poly_term.power=i;
      result.monomials.insert({poly_term.power, poly_term});
    }


  //Resultado
  return result;

};


//Função que computa partições de um inteiro usando uma função geradora
template<typename T>
void compute_integer_partitions(int64_t limit){

  //Variáveis locais
  polynomial<T> integer_partition_polynomial=generate_integer_polynomial_factor<T>(limit, 1);


  //Procedimentos
    //Loop principal
    for(int64_t i=2; i<=(limit+2); i++){

      polynomial<T> partial_polynomial=generate_integer_polynomial_factor<T>(limit, i);
      integer_partition_polynomial =integer_partition_polynomial*partial_polynomial;


      //Removendo os termos de expoentes elevados
      for(auto it=integer_partition_polynomial.monomials.begin(); it!=integer_partition_polynomial.monomials.end();){
        if((it->first)>limit)
          it = integer_partition_polynomial.monomials.erase(it);
        else break;
      }

    }

    //Exibindo o resultado da execução do algoritmo
    auto it2=integer_partition_polynomial.monomials.begin();
    ++it2;

    for(; it2!=integer_partition_polynomial.monomials.end(); ++it2)
      std::cout<<"p("<<it2->second.power<<") = "<<it2->second.coefficient<<", ";
    std::cout<<"...\n";

};

//*********************************************************************************************************
//FIM DO HEADER
#endif
