//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE PRIMALIDADE DE FRÖBENIUS USANDO POLINÔMIOS

/*
O TESTE DE PRIMALIDADE DE FRÖBENIUS É O MAIS EFICAZ TESTE DE PRIMALIDADE PARA
DETECÇÃO DE PSEUDOPRIMOS, COM PROBALIDADE QUE NÚMEROS COMPOSTOS PASSEM NO 
TESTE INFERIOR A 1/7710. EXISTEM DUAS VERSÕES DO TESTE UMA USANDO SEQUÊNCIAS 
DE LUCAS E OUTRA QUE EMPREGA POLINÔMIOS DE SEGUNDO GRAU f(x)=x²-bx-c, COM
((b²+ac)|n)=(-1) E (-c|n)=1, ONDE (|) DENOTA O SÍMBOLO DE JACOBI.

A VERSÃO USANDO POLINÔMIOS CHECA CONDIÇÕES SIMILARES A DO TESTE DE MILLER-
RABIN NO CORPO FINITO Z/nZ mod(f(x)), COMBINADO COM TESTES ENVOLVENDO PEQUENOS 
NÚMEROS PRIMOS.

PARA MAIORES INFORMAÇÕES: https://www.sciencedirect.com/science/article/pii/S0022314X98922478?via%3Dihub
                          https://arxiv.org/pdf/1908.02394


*/


//****************************************************************************************************
//CABEÇALHO
#ifndef QUADRATIC_FROBENIUS_PRIMALITY_TEST_POLYNOMIAL_H
#define QUADRATIC_FROBENIUS_PRIMALITY_TEST_POLYNOMIAL_H
#include"polynomial_exponentiation_finite_field.h"
#include"prime_power_detection.h"
#include"jacobi_symbol.h"


//****************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
polynomial<__int128_t> generate_identity_polynomial();
polynomial<__int128_t> generate_quadratic_polynomial(int64_t, int64_t);
bool trial_division_test(int64_t, int64_t);
bool quadratic_frobenius_primality_test(int64_t);
void parameters_selection(int64_t, int64_t&, int64_t&);
bool polynomial_test1(int64_t, int64_t, int64_t);
bool polynomial_test2(int64_t, int64_t, int64_t);
bool polynomial_test3(int64_t, int64_t, int64_t);


//****************************************************************************************************
//FUNÇÕES
//Função que retorna o polinômio f(x)=x
polynomial<__int128_t> generate_identity_polynomial(){

  //Variáveis locais
  polynomial<__int128_t> identity_polynomial;


  //Procedimentos: ajuste do resultado
  identity_polynomial.degree=1;
  identity_polynomial.polynomial_coefficients.push_back(1); identity_polynomial.polynomial_coefficients.push_back(0);
  identity_polynomial.polynomial_powers.push_back(1); identity_polynomial.polynomial_powers.push_back(0);

  //Resultado
  return identity_polynomial;

};


//Função que retorna o polinômio f(x)=x²-bx-c
polynomial<__int128_t> generate_quadratic_polynomial(int64_t b, int64_t c){

  //Variáveis locais
  polynomial<__int128_t> quadratic_polynomial;


  //Procedimentos: ajuste do resultado
  quadratic_polynomial.degree=2;
  quadratic_polynomial.polynomial_coefficients.push_back(1); quadratic_polynomial.polynomial_coefficients.push_back((-1)*b);
  quadratic_polynomial.polynomial_coefficients.push_back((-1)*c);
  quadratic_polynomial.polynomial_powers.push_back(2); quadratic_polynomial.polynomial_powers.push_back(1);
  quadratic_polynomial.polynomial_powers.push_back(0);

  //Resultado
  return quadratic_polynomial;

};


//Teste por divisção e erro
bool trial_division_test(int64_t n, int64_t bound){

  //Procedimentos
    //Fatores 3
    if(n%3==0) return false;

    //Loop principal: busca por fatores até um certo limite
    for(int64_t i=5; i<=bound; i+=6){
      if((n%i)==0 || (n%(i+2))==0) return false;
    }

  //Resultado
  return true;//n não contém fatores até B=50000 e/ou n<B²

};


//Função que determina os parâmetros b e c usados para construir o polinômio quadrático
void parameters_selection(int64_t n, int64_t& b, int64_t& c){
  
  //Variáveis locais
  int64_t b_, c_, D;

  //Procedimentos
    //Cálculo do parâmetro c
    for(c_=5; ; ++c_){
      if(jacobi_symbol_extension(((-1)*c_), n)==1) break;
    }

    //Cálculo do parâmetro b
    for(b_=1; ; ++b_){
      D=(b_*b_)+(c_*4);
      if(jacobi(D, n)==(-1)) break;
    }


  //Resultado
  b=b_; c=c_;

};

//Função que testa a relação de congruência x^[(n+1)/2] = l mod(n, x²-bx-c), com l ∈ Z/nZ 
bool polynomial_test1(int64_t n, int64_t b, int64_t c){

  //Variáveis locais
  polynomial<__int128_t> q_poly=generate_quadratic_polynomial(b, c);
  polynomial<__int128_t> i_poly=generate_identity_polynomial();
  polynomial<__int128_t> result;
  int64_t exponent=((n+1)/2);


  //Procedimentos
    //Cálculo de x^[(n+1)/2] mod(n, x²-bx-c)
    result=polynomial_powmod_finite_field<__int128_t, int64_t>(i_poly, q_poly, exponent, n);
    result.adjust_degree();

  //Resultado
  if(result.degree==0) return true;
  else return false;

};


//Função que testa a relação de congruência x^(n+1) = -c mod(n, x²-bx-c)
bool polynomial_test2(int64_t n, int64_t b, int64_t c){

  //Variáveis locais
  polynomial<__int128_t> q_poly=generate_quadratic_polynomial(b, c);
  polynomial<__int128_t> i_poly=generate_identity_polynomial();
  polynomial<__int128_t> result;
  int64_t exponent=(n+1);


  //Procedimentos
    //Cálculo de x^(n+1) mod(n, x²-bx-c)
    result=polynomial_powmod_finite_field<__int128_t, int64_t>(i_poly, q_poly, exponent, n);
    result.adjust_degree();

  //Resultado
  if(result.degree==0 && (result.polynomial_coefficients[0]*result.polynomial_coefficients[0])==(c*c)) return true;
  else return false;

};


//Função que implementa um teste similar ao teste de Miller-Rabin em Z/nZ mod(x²-bx-c)
bool polynomial_test3(int64_t n, int64_t b, int64_t c){

  //Variáveis locais
  polynomial<__int128_t> q_poly=generate_quadratic_polynomial(b, c);
  polynomial<__int128_t> i_poly=generate_identity_polynomial();
  polynomial<__int128_t> result;
  __int128_t N=((n*n)-1), s=0, r=0, n_=n;


  //Procedimentos
    //Cálculo dos parâmetros s e r
    while(!(N&1)){
      N>>=1;
      r++;
    }
    s=N;//s é ímpar


    //Teste 3.1: checando a relação de congruência x^s = 1 mod(n, x²-bx-c)
    result=polynomial_powmod_finite_field<__int128_t, __int128_t>(i_poly, q_poly, s, n_);
    if(result.degree!=0 || result.polynomial_coefficients[0]!=1) return false;

    //Teste 3.2: checando a relação de congruência x^[(2^j)s] = (-1) mod(n, x²-bx-c) para j=0,..., r-2
    for(; r>=2; --r){
      s>>=1;
      result=polynomial_powmod_finite_field<__int128_t, __int128_t>(i_poly, q_poly, s, n_);
      if(result.degree!=0 || result.polynomial_coefficients[0]!=(-1)) return false;
    }
  
  //Resultado
  return true;


};


//Função que implementa o teste de Fröbenius para testar a primalidade de inteiros de 64 bits
bool quadratic_frobenius_primality_test(int64_t n){

  //Casos base: primos inferiores a 30
  if(n<2) return false;
  if(n==2 || n==3 || n==5 || n==7 || n==11 || n==13 || n==17 || n==19 || n==23 || n==29) return true;
  if(!(n&1)) return false;
  
  //Variáveis locais
  int64_t root, minimum;
  int64_t b, c;
  int B=50000;

  //Procedimentos  
    //Teste 1: testando se n é um quadrado perfeito
    if(fast_square_detection(n, &root) == true) return false;
    root=std::floor(std::sqrt(n));
  
    //Teste 2: divisão por tentativa e erro para detectar rapidamente compostos
    if(root>B){
      minimum=B;
      if(trial_division_test(n, minimum)==false) return false;
    };


    if(root<B){
      minimum=root;
      if(trial_division_test(n, minimum)==true) return true; //Se n<B² então o teste de divisão por tentativa e erro é suficiente
      else return false;
    }

    //Etapa 3: seleção de parâmetros b e c usados no algoritmo
    parameters_selection(n, b, c);
   
    //Etapa 4: testando a relação de congruência x^[(n+1)/2] = l mod(n, x²-bx-c), com l ∈ Z/nZ 
    if(polynomial_test1(n, b, c)==false) return false;

    //Etapa 5: testando a relação de congruência x^(n+1) = -c mod(n, x²-bx-c)
   if(polynomial_test2(n, b, c)==false) return false;

    //Etapa 6: teste similar ao de Miller-Rabin em Z/nZ mod (x²-bx-c)
    if(polynomial_test3(n, b, c)==false) return false;

  //Caso passe nos testes acima um primo foi encontrado
  return  true;

};




//****************************************************************************************************
//FIM DO HEADER
#endif
