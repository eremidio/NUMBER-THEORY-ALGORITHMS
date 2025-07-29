//VAMOS CRIAR UM PROGRAMA QUE TESTA A PRIMALIDADE DE NÚMEROS INTEIROS USANDO POLINĨMIOS DE CHEBYSHEV

/*

A SEGUINTE OBSERVAÇÃO EM RTELAÇÃO AOS POLINÔMIOS DE CHEBYSHEV DO PRIMEIRO TIPO É ÚTIL PARA SE TESTAR SE UM INTEIRO É PRIMO
OU NÃO: PARA n PRIMO OS COEFICIENTES DE T(n, x) SÃO CONGRUENTES A 0 MÓDULO n EEXCETO O PRIMEIRO QUE É CONGRUENTE A 1
MÓDULO n. TAL OBSERVAÇÃO PODE SER USADA EM UM TESTE DE PRIMALIDADE SIMILAR AO TESTE AKS SE TRABALHADOS NO CORPO FINITO
mod(n, x^r-1), ONDE r É O MENOR PRIMO ÍMPAR TAL QUE n ≠ 1 (mod r). OS POLINÔMIOS DE CHEBYSHEV PODEM SER COMPUTADOS 
EM TEMPO LOGARÍTMICO USANDO TÉCNICAS PARA SE COMPUTAR RAPIDAMENTE SEQUÊNCIAS DE LUCAS A MENOS DE UMA CONGRÊNCIA.

PARA MAIORES INFORMAÇÕES: https://mathoverflow.net/questions/286304/chebyshev-polynomials-of-the-first-kind-and-primality-testing
                          https://mathoverflow.net/questions/286626/is-there-an-explicit-expression-for-chebyshev-polynomials-modulo-xr-1/286639#286639
                          https://math.stackexchange.com/questions/109214/chebyshev-polynomials-and-primality-testing
                          https://math.stackexchange.com/questions/2374393/primality-test-using-chebyshev-and-legendre-polynomials

*/


//***************************************************************************************************************************
//CABEÇALHO
#ifndef CHEBYSHEV_POLYNOMIAL_PRIMALITY_TEST_H
#define CHEBYSHEV_POLYNOMIAL_PRIMALITY_TEST_H
#include"baillie_psw_prime_test.h"
#include"sparse_polynomials.h"
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/cstdint.hpp>
using namespace boost::multiprecision;


//VARIÁVEIS GLOBAIS
polynomial<cpp_int> poly_array1[2][2];
polynomial<cpp_int> poly_array2[2][2];
polynomial<cpp_int> poly_array3[2][1];


//***************************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
polynomial<cpp_int> generate_division_polynomial(cpp_int);
void start_polynomial_matrices();
void polynomial_matrix_multiplication(polynomial<cpp_int>[2][2], polynomial<cpp_int>[2][2]);
void polynomial_matrix_reduction(polynomial<cpp_int>&, cpp_int);
void matrix_exponentiation(cpp_int);
bool quick_composite_detection(cpp_int);
bool chebyshev_primality_test(cpp_int);


//***************************************************************************************************************************
//FUNÇÕES 
//Função que gera um polinômio p(x)=x^r-1 com r primo tal que n≠ 1 (mod r)
polynomial<cpp_int> generate_division_polynomial(cpp_int n){

  //Variáveis locais
  uint64_t mod1prime=3;
  polynomial<cpp_int> result;
  univariate_monomial<cpp_int> poly_term;

  
  //Procedimentos
    //Selecionando um número primo que satizfas as condilções desejadas
    for(; ; mod1prime+=2){
      if(baillie_psw_test(mod1prime) && (n%mod1prime)>1) 
        break;
    }

    //Ajustando os termos do polinômio 
    poly_term.coefficient=1; poly_term.power=mod1prime;
    result.monomials.insert({poly_term.power, poly_term});
    poly_term.coefficient=(-1); poly_term.power=0;
    result.monomials.insert({poly_term.power, poly_term}); 

  //Resultado
  return result;

};


//Função que inicializa as matrizes de polinômios  usados no teste de primalidade
void start_polynomial_matrices(){

  //Variáveis locais
  univariate_monomial<cpp_int> poly_term;


  //Procedimentos: inicializando as matrizes de polinômios
    //Matriz 1:
    poly_term.coefficient=2; poly_term.power=1;
    (poly_array1[0][0]).monomials.insert({poly_term.power, poly_term});//p(x)=2x
    poly_term.coefficient=(-1); poly_term.power=0;
    (poly_array1[0][1]).monomials.insert({poly_term.power, poly_term});//p(x)=(-1)
    poly_term.coefficient=1; poly_term.power=0;
    (poly_array1[1][0]).monomials.insert({poly_term.power, poly_term});//p(x)=1
    poly_term.coefficient=0; poly_term.power=0;
    (poly_array1[1][1]).monomials.insert({poly_term.power, poly_term});//p(x)=0

    //Matriz 3:
    poly_term.coefficient=1; poly_term.power=1;
    (poly_array3[0][0]).monomials.insert({poly_term.power, poly_term});//p(x)=x
    poly_term.coefficient=1; poly_term.power=0;
    (poly_array3[1][0]).monomials.insert({poly_term.power, poly_term});//p(x)=1


};

//Função de multiplicação de matrizes de polinômios
void polynomial_matrix_multiplication(polynomial<cpp_int> mul1[2][2], polynomial<cpp_int> mul2[2][2]){

  //Variáveis locais
  polynomial<cpp_int> temp1, temp2;


  //Procedimentos: calculando os produtos de matrizes de polinômios
    //1º termo
    temp1=mul1[0][0]*mul2[0][0];  temp2=mul1[0][1]*mul2[1][0];
    poly_array2[0][0]=temp1+temp2;

    //2º termo   
    temp1=mul1[0][0]*mul2[0][1];  temp2=mul1[0][1]*mul2[1][1];
    poly_array2[0][1]=temp1+temp2;

    //3º termo   
    temp1=mul1[1][0]*mul2[0][0];  temp2=mul1[1][1]*mul2[1][0];
    poly_array2[1][0]=temp1+temp2;

    //4º termo   
    temp1=mul1[1][0]*mul2[0][1];  temp2=mul1[1][1]*mul2[1][1];
    poly_array2[1][1]=temp1+temp2;

};


//Função que reduz os coeficientes de uma matriz de polinômios
void polynomial_matrix_reduction(polynomial<cpp_int>& poly_modulus, cpp_int modulus){

  //Procedimentos
    //Reduzindo os polinômios em um corpo finito mod(n, x^r-1)
    if(poly_array2[0][0].degree()>(10*poly_modulus.degree()))
      poly_array2[0][0]=remainder<cpp_int>(poly_array2[0][0], poly_modulus);
    poly_array2[0][0]=polynomial_mod<cpp_int, cpp_int>(poly_array2[0][0], modulus);

    if(poly_array2[0][1].degree()>(10*poly_modulus.degree()))
      poly_array2[0][1]=remainder<cpp_int>(poly_array2[0][1], poly_modulus);
    poly_array2[0][1]=polynomial_mod<cpp_int, cpp_int>(poly_array2[0][1], modulus);

    if(poly_array2[1][0].degree()>(10*poly_modulus.degree()))
      poly_array2[1][0]=remainder<cpp_int>(poly_array2[1][0], poly_modulus);
    poly_array2[1][0]=polynomial_mod<cpp_int, cpp_int>(poly_array2[1][0], modulus);

    if(poly_array2[1][1].degree()>(10*poly_modulus.degree()))
      poly_array2[1][1]=remainder<cpp_int>(poly_array2[1][1], poly_modulus);
    poly_array2[1][1]=polynomial_mod<cpp_int, cpp_int>(poly_array2[1][1], modulus);

};


//Função que calcula uma exponencial de matrizes de polinômios
void matrix_exponentiation(cpp_int n){

  //Variáveis locais
  polynomial<cpp_int> poly_modulus=generate_division_polynomial(n);//p(x)=x^r-1
  polynomial<cpp_int> a[2][2], q[2][2];
  univariate_monomial<cpp_int> poly_term;
  cpp_int exponent=(n-1);


  //Procedimentos
    //Ajuste de matrizes usadas no cálculo
    poly_term.coefficient=1; poly_term.power=0;
    (a[0][0]).monomials.insert({poly_term.power, poly_term});
    (a[1][1]).monomials.insert({poly_term.power, poly_term});
    poly_term.coefficient=0; poly_term.power=0;
    (a[0][1]).monomials.insert({poly_term.power, poly_term});
    (a[1][0]).monomials.insert({poly_term.power, poly_term});
   

    q[0][0]=poly_array1[0][0];  q[0][1]=poly_array1[0][1];  q[1][0]=poly_array1[1][0];  q[1][1]=poly_array1[1][1];


    //Loop principal: exponenciação binária modular de matrizes
    while(exponent>0){

      if(exponent&1){
        polynomial_matrix_multiplication(a, q);
        polynomial_matrix_reduction(poly_modulus, n);
        a[0][0]=poly_array2[0][0];  a[0][1]=poly_array2[0][1];  a[1][0]=poly_array2[1][0];  a[1][1]=poly_array2[1][1];
      };

      //Ajustede variáveis para a próxima iteração
      exponent>>=1;
      polynomial_matrix_multiplication(q, q);
      polynomial_matrix_reduction(poly_modulus, n);
      q[0][0]=poly_array2[0][0];  q[0][1]=poly_array2[0][1];  q[1][0]=poly_array2[1][0];  q[1][1]=poly_array2[1][1];

    }
      
  //Resultado
  poly_array1[0][0]=a[0][0];  poly_array1[0][1]=a[0][1];  poly_array1[1][0]=a[1][0];  poly_array1[1][1]=a[1][1]; 

};


//Função para rápida detetcção de números compostos
bool quick_composite_detection(cpp_int  n){

  // Variáveis locais
  int small_primes[168] = {
      2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,  37,  41,  43,
      47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97,  101, 103, 107,
      109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181,
      191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263,
      269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
      353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433,
      439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521,
      523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613,
      617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701,
      709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
      811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887,
      907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};


    //Procedimentos
      //Teste 1: divisão por pequenos primos
      for(auto p:small_primes){
        if((n-p)==0) return true;
        if((n%p)==0) return false;
      }

      //Teste 2: checando se n^2 mod 6=1
      cpp_int n2=n*n;
      if(n2%6==1) return true;
      else return false;

};


//Função que executa o testede primalidade de um inteiro usando polinômios de Chebyshev
bool chebyshev_primality_test(cpp_int n){

  //Caso base: n<1000000
  if(n<2) return false;
  if(quick_composite_detection(n)==false) return false;
  if(n<1000000) return true;


  //Caso geral
  //Variáveis locais
  polynomial<cpp_int> poly_modulus=generate_division_polynomial(n);//p(x)=x^r-1
  cpp_int r=poly_modulus.degree();

  //Procedimentros
    //Preenchendo matrizes de polinômios usadosno cálculo
    start_polynomial_matrices();

    //Cálculando exponenciação de matrizes
    matrix_exponentiation(n);

    //Cálculo de T(n, x) mod(n, x^r-1)
    polynomial<cpp_int> temp1=poly_array1[0][0]*poly_array3[0][0], temp2=poly_array1[0][1]*poly_array3[1][0];
    polynomial<cpp_int> result=temp2+temp1;
    if(result.degree()>poly_modulus.degree()) result=remainder<cpp_int>(result, poly_modulus);
    result=polynomial_mod<cpp_int, cpp_int>(result, n);

    //Análise do resultado
    auto it=result.monomials.begin();
    if(it->second.coefficient==1) return true;
    else return false;

};


//***************************************************************************************************************************
//FIM DO HEADER
#endif
