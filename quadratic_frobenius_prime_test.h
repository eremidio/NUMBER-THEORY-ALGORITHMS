// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE FRÖBENIUS PARA TESTAR A PRIMALIDADE DE UM NÚMERO INTEIRO

/*
O TESTE DE PRIMALIDADE DE FRÖBENIUS É UM TESTE PROBABILÍSTICO QUE USA POLINÔMIOS DO SEGUNDO GRAU E OS CHAMADOS ENDOMORFISMOS DE FRÖBENIUS
PARA TESTAR A PRIMALIDADE DE UM INTEIRO. NÚMEROS COMPOSTOS QUE PASSAM ESSE TESTES SÃO DENOMINADOS PSEUDOPRIMOS DE FRÖBENIUS. O TESTE EM
QUESTÃO PODE TAMBÉM SER EXPRESSO EM TERMOS DE SEQUÊNCIAS DE LUCAS 

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Quadratic_Frobenius_test#Concept
                          https://trizenx.blogspot.com/2020/01/primality-testing-algorithms.html

ARTIGO ORIGINAL DISPONÍVEL EM:
https://www.sciencedirect.com/science/article/pii/S0022314X98922478?via%3Dihub

*/

//********************************************************************************************************************************************************************
// CABEÇALHO
#ifndef QUADRATIC_FROBENIUS_PRIMALITY_TEST_H
#define QUADRATIC_FROBENIUS_PRIMALITY_TEST_H
#include"mod_bin_exponentiation.h"
#include"jacobi_symbol.h"
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
bool quadratic_frobenius_primality_test(int64_t, enum show_frobenius_witness);

//********************************************************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides
int64_t gcd_frobenius(int64_t a, int64_t b){

  if(b==0)
    return a;
  else
    return gcd_frobenius(b, (a%b));
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


//Função que implementa o teste de primalidade de Fröbenius
bool quadratic_frobenius_primality_test(int64_t n, enum show_frobenius_witness x){

  //Caso base: n é par
  if(!(n&1))
    return false;

  //Semente para geraçção de números aleatórios
  srand(time(NULL));

  //Variáveis locais
  int64_t root=sqrt(n);
  int64_t tester;
  int64_t a, b, b_inv, d;
  int64_t m, w;
  __int128_t temp, u, v;
  int* bit_string=NULL;
  int bit_size=0;



  //Procedimentos
    start:
    //Definindo parâmetros a,b no intervalo [1,2,...,(n-2)]
    a=1+rand()%root;
    b=1+rand()%root;
    

    if((b%2)==0 || a<0) goto start;

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
    m=(n-jacobi(d, n))/2;
    temp=((((a*a)%n)*b_inv)-2)%n;
    w=temp;


    //Calculando a string binária associada ao parâmetro m
    while(m>0){
      bit_size++;
      bit_string=(int*)realloc(bit_string, bit_size*sizeof(int));
 
      if((b&1)) bit_string[bit_size-1]=1;
      else bit_string[bit_size-1]=0;

      m>>=1;   
              };

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


    //Análise da execução do algoritmo
      //Teste de Lucas
      if((w*u)!=((v<<1)%n)){
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





//********************************************************************************************************************************************************************
// FIM DO HEADER
#endif
