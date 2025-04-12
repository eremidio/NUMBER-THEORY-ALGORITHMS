//VAMOS CRIAR UM PROGRAMA QUE COMPUTA NÚMEROS CICLOTÔMICOS DE SYLVESTER

/*
SEJA UM POLINÔMIO DO SEGUNDO GRAU p(x)=x²+Px+Q E A RESPECTIVA SEQUÊNCIA DE LUCAS DO PRIMEIRO TIPO ASSOCIADA U(n).
SEJAM a, b AS DUAS RAÍZES DESTE POLINÔMIO E D=P²-4Q O SEU DISCRTIMINANTE.

OS NÚMEROS CICLOTÔMICOS DE SYLVESTER SÃO UMA SEQUÊNCIA ASSOCIADA A SEQUÊNCIA DE LUCAS U(n) DEFINIDOS PELA RELAÇÃO
Q(n)=Π {a-b(ζ^r)}, ONDE ζ=e^(i2π/n) É UMA RAÍZ PRIMITIVA DA UNIDADE (n, r COPRIMOS) E r=1,2,...,(n-1).

TAIS NÚMEROS  SATISFAZEM A RELAÇÃO: Π Q(d)=U(n), ONDE d SÃO OS DIVISORES DE n. DESTA FORMA ELES PODEM SER
COMPUTADOS USANDO UMA VARIANTE DA PENEIRA DE ERATÓSTENES.

NÚMEROS CICLOTÔMICOS DE SYLVESTER SÃO USADOS NO ALGORITMO DE WARD PARA SE TESTAR A PRIMALIDADE DE UM INTEIRO p.
SEJA n>√p, SE Q(p) FOR DIVISÍVEL POR n ENTÃO OU p É PRIMO OU p=(n-1)² COM (n-1) PRIMO N>4 OU p=n²-1, COM n-1 E
n+1 PRIMOS.


PARA MAIORES INFORMAÇÕES: https://msp.org/pjm/1959/9-4/pjm-v9-n4-p23-p.pdf
                          https://mathworld.wolfram.com/SylvesterCyclotomicNumber.html
                          https://mathworld.wolfram.com/WardsPrimalityTest.html

*/


//********************************************************************************************************************
//CABEÇALHO
#ifndef SYLVESTER_CYCLOTOMIC_NUMBERS_H
#define SYLVESTER_CYCLOTOMIC_NUMBERS_H
#include"lucas_sequence_matrix.h"
#include"prime_power_detection.h"
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/cstdint.hpp>
#include<vector>
#include<stdint.h>
#include<iostream>
#include<cmath>
using namespace boost::multiprecision;



//**********************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t gcd_S64(int64_t, int64_t);
std::vector<cpp_int> compute_sylvester_cyclotomic_numbers(int64_t, int64_t, int64_t);
bool ward_primality_test(int64_t, std::vector<cpp_int>&);


//**********************************************************************************************************************
//FUNÇÕES
//Função que calcula o gcd de dois inteiros
int64_t gcd_s64(int64_t a, int64_t b){
  
  if(b==0) return a;
  else return gcd_s64(b,(a%b));

};

//Função que computa os números ciclotômicos de Sylvester em um intervalo
std::vector<cpp_int> compute_sylvester_cyclotomic_numbers(int64_t P, int64_t Q, int64_t n){

  //Variáveis locais
  std::vector<cpp_int> sylvester_cyclotomic_vector;
  cpp_int P_=P, Q_=Q, Qn;

  
  //Procedimentos
    //Adicionando os primeiros elementos a lista
    sylvester_cyclotomic_vector.push_back(1);//Q(0)=1
    sylvester_cyclotomic_vector.push_back(1);//Q(1)=1
    Qn=P_;  sylvester_cyclotomic_vector.push_back(Qn);//Q(2)=P
    Qn=P_*Qn; Qn=Qn-Q_; sylvester_cyclotomic_vector.push_back(Qn);//Q(3)=P²-Q
    Qn=Qn-Q_; sylvester_cyclotomic_vector.push_back(Qn);//Q(4)=P²-2Q


    //Prenchendo um vetor com termos da sequência de Lucas
    for(int64_t i=5; i<=n;++i){
      Matrix<cpp_int> l_matrix=lucas_sequence_matrix<cpp_int, int64_t>(P_, Q_, i);
      cpp_int E=l_matrix.matrix[1][0];//U(i)
      sylvester_cyclotomic_vector.push_back(E);
    } 

    //Calculando os números ciclotômicos de Sylvester usando a identidade  Π Q(d)=U(n),
    for(int64_t j=2; j<=(n/2); ++j){
      for(int64_t k=(2*j); k<=n; k+=j){
        if(k<=4) continue;
        sylvester_cyclotomic_vector[k]=sylvester_cyclotomic_vector[k]/sylvester_cyclotomic_vector[j];  
      }
    }

  //Resultado
  return sylvester_cyclotomic_vector; 

};


//Função que implementa o teste de primalidade de Ward
bool ward_primality_test(int64_t n, std::vector<cpp_int>& sylvester_cyclotomic_vector){


  //Casos bases 
  if(n<2) return false;
  if(n==2 || n==3 || n==5 || n==7) return true;
  if(!(n&1)) return false;  

  //Variáveis locais
  cpp_int N=n;
  int64_t sqrt_n=std::sqrt(n), sc_size=sylvester_cyclotomic_vector.size();
  int64_t index=0;

  //Procedimentos
    //Achando um index i tal quen divide Q(i)
    for(int64_t i=(sqrt_n+1); i<sc_size; ++i){
      if(sylvester_cyclotomic_vector[i]%N==0){
        index=i; break;
      }
    };

    if(index==0){
      std::cout<<"Teste inconclusivo!\n";
      return false;
    }

    //Análise dos resultados   
    int64_t p=index+1;
    int64_t q=index-1; 
    if(gcd_s64(index, n)>1 || gcd_s64(q, n)>1 || gcd_s64(q, n)>1) return false;

    if(n==(q*q)){
      if(ward_primality_test(q, sylvester_cyclotomic_vector)==true && q>3)
        return false;
    };

    if(n==(p*q)){
      if(ward_primality_test(p, sylvester_cyclotomic_vector)==true && ward_primality_test(q, sylvester_cyclotomic_vector) ==true)
        return false;

    }

    
  //Caso passe nos testes acima um primo foi encontrado
  return true;

};


//**********************************************************************************************************************
//FIM DO HEADER
#endif
