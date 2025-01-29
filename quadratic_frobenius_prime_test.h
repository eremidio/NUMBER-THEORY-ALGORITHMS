//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE FRÖBENIUS PARA TESTAR A PRIMALIDADE DE UM NÚMERO INTEIRO

/*
O TESTE DE PRIMALIDADE DE FRÖBENIUS É UM TESTE PROBABILÍSTICO QUE USA POLINÔMIOS DO SEGUNDO GRAU E OS CHAMADOS
ENDOMORFISMOS DE FRÖBENIUS (x->x^p EM ANEIS COMUTATIVOS COM CARACTERÍSICA p, COM p PRIMO) PARA TESTAR A
PRIMALIDADE DE UM INTEIRO. NÚMEROS COMPOSTOS QUE PASSAM ESSE TESTES SÃO DENOMINADOS PSEUDOPRIMOS DE FRÖBENIUS.

O TESTE É BASEADO NA SEGUINTE PROPOSIÇÃO: SEJAM a,b INTEIROS TAIS QUE Δ=a²-4b NÃO SEJA UM QUADRADO PERFEITO.
UM INTEIRO COMPOSTO n É DENOMINADO UM PSEU DO PRIMO DE FRÖBENIUS EM RELAÇÃO A f(x)=x²-ax+b SE AS SEGUINTES 
CONDIÇÕES FOREM VÁLIDAS:
1. x²=(x-a) (mod f(x), n) se (Δ|n)=-1
2. x²=x (mod f(x), n) se (Δ|n)=1
(p|q) DENOTA O SÍMBOLO DE JACOBI.


O TESTE DE FRÖBENIUS É UM DOS TESTES PROBABILÍSTICOS MAIS EFICIENTES QUE EXISTEM, COMPOSTOS TEM PROBABILIDADE 
DE 1/7710 DE PASSAREM NO TESTE.

O TESTE EM QUESTÃO PODE TAMBÉM SER EXPRESSO EM TERMOS DE SEQUÊNCIAS DE LUCAS DO PRIMEIRO E SEGUNDO TIPO.
UM INTEIRO n É CONSIDERADO UM PSEUDOPRIMO DE FRÖBENIUS SE:
SEJAM D=P²-4Q, δ=(D|n)

1.gcd(n, 2QD)=1
2. U(n-δ)=0 (mod n+1)
3. V(n-δ)=2Q^((1-δ)/2)


GENERALIZAÇÕES DESTE TESTE EXISTEM QUE INCORPORAM UMA CLASSE MAIOR DE POLINÔMIOS (VER ARTIGO NAS 
REFERÊNECIAS).

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Quadratic_Frobenius_test#Concept
                          https://trizenx.blogspot.com/2020/01/primality-testing-algorithms.html
                          https://en.wikipedia.org/wiki/Frobenius_endomorphism
                          https://en.wikipedia.org/wiki/Frobenius_pseudoprime
                          Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance

ARTIGO ORIGINAL DISPONÍVEL EM:
https://www.sciencedirect.com/science/article/pii/S0022314X98922478?via%3Dihub


*/ 

//********************************************************************************************************************************************************************
// CABEÇALHO
#ifndef QUADRATIC_FROBENIUS_PRIMALITY_TEST_H
#define QUADRATIC_FROBENIUS_PRIMALITY_TEST_H
#include"mod_bin_exponentiation128.h"
#include"kronecker_symbol.h"
#include <unistd.h> /*Para windows use o arquivo 'windows.h' e 'conio.h' que contém a mesma função sleep()*/
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


enum show_frobenius_witness{Verbose, Succint};

//********************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
int64_t gcd_frobenius(int64_t, int64_t);
int64_t modular_inverse(int64_t, int64_t);
bool quadratic_frobenius_primality_test_one_run(int64_t, enum show_frobenius_witness);
bool quadratic_frobenius_primality_test(int64_t, enum show_frobenius_witness);

//********************************************************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides
int64_t gcd_frobenius(int64_t a, int64_t b){

  if(b==0)return a;
  else return gcd_frobenius(b, (a%b));
};


//Função que calcula inversos multiplicativo modular usando o algoritmo de Euclides extendido
int64_t modular_inverse(int64_t a, int64_t n){

  // Variáveis locais
  int64_t r0, r1, x0, x1, r2, x2;

  // Procedimentos
    // Ajuste de variáveis
    r0 = a;
    r1 = n;
    r2 = 1;
    x0 = 1;
    x1 = 0;

    // Calculando os valores finais dos coeficientes recursivamente
    while (r2 > 0) {
      int64_t quotient = r0 / r1;
      r2 = r0 - quotient * r1;
      x2 = x0 - quotient * x1;

      // Atualizando variáveis para a próxima iteração
      if (r2 > 0) {
        r0 = r1;
        r1 = r2;
        x0 = x1;
        x1 = x2;
        };
      };

  // Resultado
  if (x1 < 0)
    return (x1 + n);
  else
    return x1;

};


//Função que implementa uma rodada do teste de primalidade de Fröbenius
bool quadratic_frobenius_primality_test_one_run(int64_t n, enum show_frobenius_witness x){

  //Caso base: n é par e primos inferiores a 30
  if(!(n&1))
    return false;

  if(n==2 || n==3 || n==5 || n==7 || n==11 || n==13 || n==17 || n==19 || n==23 || n==29) return true;
  if(n%2==0 || n%3==0 || n%5==0 || n%7==0 || n%11==0 || n%13==0 || n%17==0 || n%19==0 || n%23==0 || n%29==0) return false;

  //Semente para geração de números aleatórios
  srand(time(NULL));

  //Variáveis locais
  int64_t tester;
  int64_t a, b=1, b_inv, d;
  int64_t m, w;
  __int128_t temp, u, v;
  int* bit_string=NULL;
  int bit_size=0;



  //Procedimentos
    start:
    //Definindo parâmetros a,b no intervalo [1,2,...,(n-2)]
    a=1+rand()%((n-1)>>3);
    b=1+rand()%((n-1)>>3);
    

    if((b&1)==0 || a<0) goto start;

    b_inv=modular_inverse(b, n);
    d=(a*a)-(4*b);

    //Teste que checa se um fator primo de n foi encontrado
    tester=gcd_frobenius(n, (2*a*b*d));

    if(tester>1 && tester<n){
      if(x==Verbose)
        printf("Testemunha da composição de %li: %li e %li\n", n, a, b);
      return false;
                            };

    if(tester==n)
      goto start;


    //Cálculo dos parâmetros w, m usados no algoritmo
    m=(n-kronecker(d, n))/2;
    temp=((((a*a)%n)*b_inv)-2)%n;
    w=temp;


    //Calculando a string binária associada ao parâmetro m
    while (m > 0) {
      bit_size++;
      bit_string = (int*)realloc(bit_string, bit_size * sizeof(int));
      bit_string[bit_size - 1] = m & 1;
      m >>= 1;
    }


    //Ajuste dos parâmetros da sequência de Lucas
    u=2;
    v=w;

    //Computando os termos da sequência de Lucas
    for(int i=(bit_size-1); i>=0; --i){

      if(bit_string[i]==1){
        u=((u*v)-w)%n;
        v=((v*v)-2)%n;
                          };

      if(bit_string[i]==0){
        v=((u*v)-w)%n;
        u=((u*u)-2)%n;
                          };


    };


    //Limpando o cachê de memória
    if(bit_string) free(bit_string);


    //Análise da execução do algoritmo
      //Teste de Lucas
      if((w*u)%n!=((v<<1)%n)){
        if(x==Verbose)
          printf("Testemunha da composição de %li: %li e %li\n", n, a, b);
        return false;
      };




      //Teste de Fröbenius
      int64_t t= mod_bin_pow(b, ((n-1)/2), n);

      if(((t*u)%n)==2){
        printf("Testemunha da primalidade de %li: %li e %li\n", n, a, b);
        return true;
                      }
      else{
      if(x==Verbose)
        printf("Testemunha da composição de %li: %li e %li\n", n, a, b);
      return false;
           };

   
      return true;

};


//Função que implementa o teste de primalidade de Fröbenius
bool quadratic_frobenius_primality_test(int64_t n, enum show_frobenius_witness x){

  //Resultado
  for(int i=0; i<3; ++i){
    if(quadratic_frobenius_primality_test_one_run(n, x)==true) return true;
    sleep(1);
  }

  return false;

};


//********************************************************************************************************************************************************************
// FIM DO HEADER
#endif
