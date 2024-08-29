//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ALGORITMOS QUE TESTAM A IRREDUTIBILIDADE DE POLINÔMIOS DEFINIDOS SOBRES OS RACIONAIS/INTEIROS

/*
UM POLINÔMIO É DITO IRREDUTÍVEL SE O MESMO NÃO PUDER SER DECOMPOSTO NO PRODUTO DE 
OUTROS POLINÔMIOS DE MENOR GRAU QUE NÃO SEJAM CONSTANTES (GRAU ZERO). ESTA
DEFINIÇÃO É SIMILAR A NOÇÃO DE PRIMALIDADE PARA NÚMEROS INTEIROS. TODO POLINÔMIO
É DECOMPOSÁVEL EM UM PRODUTO DE POLINÔMIOS IRREDUTÍVEIS DEFINIDO COM COEFICIENTES
SOBRE UM CORPO NÚMERICO.


PARA MAIORES INFORMAÇÕES: https://mathworld.wolfram.com/IrreduciblePolynomial.html
                          https://en.wikipedia.org/wiki/Eisenstein%27s_criterion#Indirect_(after_transformation)
                          https://en.wikipedia.org/wiki/Cohn%27s_irreducibility_criterion
                          https://en.wikipedia.org/wiki/Perron%27s_irreducibility_criterion

*/

//*************************************************************************************************************************
//CABEÇALHO
#ifndef POLYNOMIAL_RATIONAL_IRREDUCIBILITY_H
#define POLYNOMIAL_RATIONAL_IRREDUCIBILITY_H
#include<algorithm>
#include"horners_polynomial_evaluation.h"
#include"polynomial_exponentiation.h"
#include"polynomial_cast.h"
#include"miller_rabin_128bits.h"
#include<fstream>
#include<sstream>


//*************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
polynomial<T> polynomial_lifting(polynomial<T>&,  T);
template<typename T>
polynomial<T> polynomial_reversal(polynomial<T>&);


template<typename T>
bool perron_irreducibility_criterion(polynomial<T>&);
template<typename T>
bool cohn_irreducibility_criterion(polynomial<T>&, T);
template<typename T>
bool eisenstein_irreducibility_criterion(polynomial<T>&);



//*************************************************************************************************************************
//FUNÇÕES
//Função que calcula um polinômio q(x) a partir de outro polinômio p(x) com base na transformação T:x->(x-a)
template<typename T>
polynomial<T> polynomial_lifting(polynomial<T>& p1, T shift){

  //Variáveis locais
  polynomial<T> result=generate_zero_polynomial<T>();
  polynomial<T> linear_polynomial;
  std::vector<T>  multipliers=p1.polynomial_coefficients;
  std::vector<int64_t> exponents=p1.polynomial_powers;
  

  //Procedimento
    //Ajuste do polinômio linear
    linear_polynomial.degree=1;
    linear_polynomial.polynomial_coefficients.push_back(1); linear_polynomial.polynomial_coefficients.push_back(((-1)*shift)); 
    linear_polynomial.polynomial_powers.push_back(1); linear_polynomial.polynomial_powers.push_back(1);

    //Loop principal: iterando sobre os coeficientes e expoentes do polinômio original
    for(int64_t i=0;  i<exponents.size(); ++i){
      polynomial<T> parcel=polynomial_bin_pow<T, int64_t>(linear_polynomial, exponents[i]);
      for(auto& c:parcel.polynomial_coefficients) c*=multipliers[i];
      result=result+parcel;

    }


  //Resultado
  return result;

};

//Função que inverte a ordem do coeficiente de um polinômio
template<typename T>
polynomial<T> polynomial_reversal(polynomial<T>&p1){

  //Variáveis locais
  polynomial<T> result=p1;

  //Procedimento
    //Invertendo os coeficientes de um polinômio
    std::reverse(result.polynomial_coefficients.begin(), result.polynomial_coefficients.end());


  //Resultado
  return result;

};


//Função que implementa o teste de primalidade de Perron para polinômios mônicos
template<typename T>
bool perron_irreducibility_criterion(polynomial<T>& p1){

  //Restrição a polinômios mônicos
  if(p1.polynomial_coefficients[0]!=1) return false; //Critério não aplicável
  if(p1.degree==0) return false;//Caso trivial
  if(p1.degree==1) return true;//Caso trivial

  //Variáveis locais
  polynomial<T>  temp=p1;
  T coeff_sum=0;
  T second_coeff;

  //Procedimentos
    //Calculando o valor absoluto dos coeficientes
    for(auto& c:temp.polynomial_coefficients){
      if(c<0) c*=(-1);
    }

    second_coeff=temp.polynomial_coefficients[1];

    //Calculando a soma dos coeficientes do polinômio exceto o segundo
    for(int64_t i=2; i<temp.polynomial_coefficients.size(); ++i)
      coeff_sum = coeff_sum+temp.polynomial_coefficients[i];


    //Resultado da execução do algoritmo
    if(second_coeff>coeff_sum) return true;
    if(second_coeff==coeff_sum){

      //Testando a condição adicional p(1)≠0 e p(-1)≠0
      T tester1=horners_polynomial_evaluation<T, T>(p1, 1);
      T tester2=horners_polynomial_evaluation<T, T>(p1, (-1));

      if(tester1!=0 && tester2!=0) return true;
      else return false;

    }

  //Caso não passe nos testes acima o teste é inconclusivo
  return false;


};


//Função que implementa o teste de irredutibilidade de Cohn para polinônios com pequenos coeficientes
/*
NOTA: Problemas podem ocorrer por conta de overflow de inteiros.
      Usaremos inteiros de 128 bits no cálculo.
*/
template<typename T>
bool cohn_irreducibility_criterion(polynomial<T>& p1, T bound){

  //Casos base
  if(p1.degree==0) return false;
  if(p1.degree==1) return true;


  //Variáveis locais
  polynomial<__int128_t> bigint_poly=polynomial_cast<T, __int128_t>(p1);
  __int128_t poly_value, largest_coeff=bigint_poly.polynomial_coefficients[0];
  

  //Procedimentos
    //Calculando o maior coeficiente do polinômio a ser testado
    for(auto c:bigint_poly.polynomial_coefficients){
      if(c>largest_coeff) largest_coeff=c;
    }

    //Restrição
    assert(bound>largest_coeff);    

    //Teste de irredutibilidade
    for(__int128_t i=(largest_coeff+1); i<=bound; ++i){
      poly_value=horners_polynomial_evaluation<__int128_t, __int128_t>(bigint_poly, i);
      if(miller_rabin128(poly_value)==true) return true;
    }

  //Caso não passe no teste acima o resultado é inconclusivo
  return false;

};



//Funcão que implementa o critério de irredutibilidade de Eisentein
template<typename T>
bool eisenstein_irreducibility_criterion(polynomial<T>& p1){


  //Casos base
  if(p1.degree==0) return false;
  if(p1.degree==1) return true;

  //Variáveis locais
  std::vector<int64_t> primes;
  std::string prime_string;
  int64_t prime;


  //Procedimentos
    //Preenchendo um buffer de números primos até 5x10^6
    std::ifstream prime_file("prime_list.txt");

    while (std::getline(prime_file, prime_string)) {
      std::istringstream iss(prime_string);
      if (iss >> prime) {
        if (prime <= 5000000) { 
          primes.push_back(prime);
        }
      }
    }

    prime_file.close(); 

    //Aplicando o critério irredutibilidade de Eisenstein
    for(auto p:primes){

      //Teste 1
      if(p1.polynomial_coefficients[0]%p==0) return false;
     
      //Teste 2
      if((p1.polynomial_coefficients[p1.polynomial_coefficients.size()-1]%(p*p))==0)
        return false;

      //Teste 3
      int counter=0;

      for(int64_t i=1; i<p1.polynomial_coefficients.size(); ++i){
        T coeff=p1.polynomial_coefficients[i];
        if(coeff%p!=0) counter++;
        
      }   
    
      if(counter==0) return true;
    }

  //Caso de falha
  return false;
  
};



//*************************************************************************************************************************
//FIM DO HEADER
#endif
