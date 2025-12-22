//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA ROTINA QUE REDUZ FORMAS QUADRÁTICAS BINÁRIAS

/*

FORMAS QUADRÁTICAS BINÁRIAS f(x,y)=ax²+bxy+cy² SÃO EXTREMAMENTE IMPORTANTES EM TEORIA DE NÚMEROS. UMA FORMA QUADRÁTICA
PODE SER REPRESENTADO POR UMA TRIPLA ORDENADA (a, b, c), O DISCRIMINANTE DEUMA FORMA QUADRÁTICA É DADO POR Δ=b²-4ac.
UMA FORMA QUADRÁTICA É DITA SER REDUZIDA SE A SEGUINTE RELAÇÃO FOR SATISFEITA: |b|≲ a ≲ c. SE UMA DESTA RELAÇÕES FOR
UMA IGUALDADE ENTÃO b ≳ 0.

FORMAS QUADRÁTICAS PODEM SER TRANSFORMADAS EM OUTRAS QUADRÁTICAS VIA UMA TRANSFORMAÇÃO LINEAR. TAL FATO ESTABELECE UMA
RELAÇÃO DE EQUIVALÊNCIA ENTRE FORMAS QUADRÁTICAS. DUAS FORMAS QUADRÁTICAS PERTENCEMA MESMA CLASSE DE EQUIVALÊNCIA SE
ELAS ESTÃO RELACIONADAS A MENOS DE UMA TRANSFORMAÇÃO LINEAR.

UM TEOREMA DE GAUSS AFIRMA QUE TODA FORMA QUADRÁTICA DE DISCRIMINANTE NEGATIVO É EQUIVALENTE A UMA FORMA QUADRÁTICA
REDUZIDA. ESTE TEOREMA PERMITE DETERMINAR UM CONJUNTO DE CLASSES DE EQUIVALÊNCIAS DE FORMAS QUADRÁTICAS.

FORMAS QUADRÁTICAS BINÁRIAS ESTÃO DIRETAMENTE RELACIONADAS COM A TEORIA DE CORPOS ALGÉBRICOS QUADRÁTICOS (REAIS E
IMAGINÁRIOS) E SÃO DE GRANDE INTERESSE EM TEORIA DE NÚMEROS ALGÉBRICA.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Binary_quadratic_form
                          A Course In Computational Algebraic Number Theory by Henri Cohen

*/

//********************************************************************************************************************************************
// CABEÇALHO
#if !defined BINARY_QUADRATIC_FORM_REDUCTION_H
#define BINARY_QUADRATIC_FORM_REDUCTION_H
#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include<math.h>


//********************************************************************************************************************************************
//ESTRUTURAS USADAS NO ALGORITMO
//Estrutura que representa uma forma quadrática f(x, y)=ax²+bxy+cy²
struct binary_quadratic_form{
  int64_t a;
  int64_t b;
  int64_t c;
};


//Algumas funções utilidade para se operar com formas quadráticas
//-----------------------------------------------------------------
//Computar discriminante
int64_t binary_quadratic_form_discriminant(struct binary_quadratic_form f){

  //Resultado
  return (f.b*f.b-(4*f.a*f.c));
}

//Checando se uma forma quadrática possui discriminante negativo (é definida Δ<0 se  ou Δ>0 indefinida)
bool is_positive_definite(struct binary_quadratic_form f){

  //Resultado
  return (binary_quadratic_form_discriminant(f)<0 && f.a>0);

};

//Função que exibe uma forma quadrática 
void print_binary_quadratic_form(struct binary_quadratic_form f){
  printf("f(x, y) = %lix² + %lixy + %liy²", f.a, f.b, f.c);

};

//Função que implementa o algoritmo de Euclides para inteiros de 64 bits
int64_t gcd_s64(int64_t a, int64_t b){

  //Procedimentos
    //Ajuste de variáveis
    if(a<0) a = (-a);
    if(b<0) b = (-b);

    //Loop principal:
    while(b>0){
      int64_t t=b;
      b=a%b;
      a=t;
    }

  //Resultado
  return a;

};

//Função que checa se in inteiro é um quadrado perfeito
bool is_perfect_square(int64_t n){
    if (n < 0) return false;
    int64_t r = floor(sqrt(n));
    return r*r == n;
};

//Função que checa se uma forma quadrática é primitiva
bool is_primitive(struct binary_quadratic_form f){
  return gcd_s64(gcd_s64(f.a, f.b), f.c) == 1;
};

//Função que checa se uma forma quadrática é degenerada
bool is_degenerate(struct binary_quadratic_form f){

  //Variáveis locais
  int64_t delta=binary_quadratic_form_discriminant(f);

  //Resultado
  if(delta<0) return false;
  if(is_perfect_square(delta)) return true;
  return false;

};


//********************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
bool is_reduced(struct binary_quadratic_form);
struct binary_quadratic_form reduce_quadratic_form(struct binary_quadratic_form);


//********************************************************************************************************************************************
//FUNÇÕES
//Função que checa se uma forma quadrática primitiva de discriminante negativo é reduzida
bool is_reduced(struct binary_quadratic_form f){

  //Variáveis locais
  int64_t abs_b=(f.b>0)?f.b:(-f.b);


  //Resultado: checando condições que determinam se f(x, y) está reduzida ou não
  if(abs_b>f.a || f.a>f.c || abs_b>f.c) return false;
  if(abs_b==f.a || f.a==f.c){
    if(f.b<0) return false;
  }

  return true;

};

//Função que reduz uma forma quadrática
struct binary_quadratic_form reduce_quadratic_form(struct binary_quadratic_form f){

  //Caso base: f(x, y) já está reduzida
  if(is_reduced(f)) return f;

  
  //Variáveis locais
  int64_t a=f.a, b=f.b, c=f.c;


  //Procedimentos
    
    //Checando a condição de redução de formas quadráticas
    if(b>(-a) && b<=a)
      goto final_step_reduction;

    //Loop euclidiano
    while(1){

      //Redução euclidiana mod 2a
        int64_t a2=(a<<1);
        int64_t r=b%a2;
        int64_t q=(b-r)/a2;

        if(r>a){
          r=r-a2;
          q++;
        }

        c=c-(((b+r)*q)>>1);
        b=r;
      
      //Condição que determina o fim do loop
      final_step_reduction:
      if(a>c){
        b=(-b);
        int64_t t=a;
        a=c; c=t;
        continue;
      }
      
      if(a==c && b<0) b=(-b);
      break;
    }

  //Resultado
  struct binary_quadratic_form red_f; 
  red_f.a=a; red_f.b=b; red_f.c=c;   
  return red_f;

};


//********************************************************************************************************************************************
// FIM DO HEADER
#endif
