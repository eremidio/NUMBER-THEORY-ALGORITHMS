//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA SUBROTINAS UTÉIS NA CONTRUÇÃO DE SOMAS DE GAUSS, DE JACOBI E KLOOSTERMAN


/*

UM CARACTÉRE DE DIRICHLET MÓDULO q PODE SER DEFINIDO EM TERMOS DE RAÍZES DA UNIDADE ζ(p)=e^2πi/p POR MEIO DA SEGUINTE IDENTIDADE:
SEJA g A MENOR RAÍZ PRIMITIVA EM Z/qZ, PARA CADA ELEMENTO m SEJA k INTEIRO TAL QUE g^k=m, DEFINE-SE O CARACTÉRE MÓDULO q DE m=g^k
COMO χ(q; m)=ζ(q)^k. É FACIL VERIFICAR QUE A CONSTRUÇÃO ACIMA SATISFAZ TODAS AS CONDIÇÕES QUE DEFINEM UM CARACTÉRE NÚMERICO.

PODEMOS DEFINIR UM CARACTÉRE MÓDULO q DE ORDEM p, ISTO É TAL QUE [χ(p, q; m)]^p=1 PARA TODO m EM Z/qZ COM p DIVIDINDO (q-1), PELA
IDENTIDADE χ(p, q; m)=ζ(p)^k.

SOMAS DE GAUSS DENOTADAS POR G(p, q) (OU POR τ(χ)) PODEM SER CONSTRUÍDAS USANDO-SE OS CARACTÉRES NÚMERICOS DEFINIDOS ACIMA COMO
G(p, q) = Σχ(p, q; m) ζ(q)^m = Σ ζ(p)^k ζ(q)^{g^k} = Σζ(p)^{k (mod p} ζ(q)^{g^k (mod q)}. TAIS SOMAS POSSUEM PROPRIEDADES
ARITMÉTICAS QUE PODEM SER EXPLORADAS EM CERTOS ALGORITMOS EM TEORIA DOS NÚMEROS COMO O TESTE DE PRIMALIDADE APR-CL E O ALGORITMO
DE FATORAÇÃO USANDO POLINÔMIOS CICLOTÔMICOS.


PARA MAIORES INFORMAÇÕES: Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance
                          https://vladgl.blogspot.com/2015/06/gsoc-week-2-and-gauss-sums.html
                          https://e.math.cornell.edu/people/belk/numbertheory/GaussSums.pdf
                          https://surim.stanford.edu/sites/g/files/sbiybj26191/files/media/file/zhuor_gu_-_number_of_solutions_to_diophantine_equations_and_relations_to_the_riemann_hypothesis_0.pdf



*/


//***************************************************************************************************
//CABEÇALHO
#ifndef GENERALIZED_DIRICHLET_CHARACTER_H
#define GENERALIZED_DIRICHLET_CHARACTER_H
#include"least_primitive_root.h"
#include"mod_bin_exponentiation.h"
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

//CONSTANTES GLOBAIS
enum unity_root_notation{Zeta, Complex};


//***************************************************************************************************
//ESTRUTURAS USADAS NO ALGORITMO

//---------------------------------
//1: Caractére módulo q
struct unity_root_q{
  int64_t g;
  int64_t k;
  int64_t q;
  unsigned is_zero:1;//0: caractére não nulo, 1: caractére nulo
};

//---------------------------------
//2: Caractére módulo q de ordem p
struct unity_root_pq{
  int64_t g;
  int64_t k;
  int64_t p;
  int64_t q;
  unsigned is_zero:1;//0: caractére não nulo, 1: caractére nulo
};


//***************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t find_index(int64_t, int64_t, int64_t);
int64_t gcd_s64(int64_t, int64_t);

struct unity_root_q set_unity_root_q(int64_t, int64_t);
struct unity_root_pq set_unity_root_pq(int64_t, int64_t, int64_t);

void print_unit_root_q(struct unity_root_q*, enum unity_root_notation);
void print_unit_root_pq(struct unity_root_pq*, enum unity_root_notation);

struct unity_root_q unity_root_q_mul(struct unity_root_q*, struct unity_root_q*);
struct unity_root_pq unity_root_pq_mul(struct unity_root_pq*, struct unity_root_pq*);


//***************************************************************************************************
//FUNÇÕES
//Função que computa o logaritmo discreto (valuação p-ádica) de um inteiro n em Z/pZ
int64_t find_index(int64_t base, int64_t m, int64_t q){

  //Procedimentos 
    //Loop principal
    for(int64_t result=0; result<q; ++result){
      if(mod_bin_pow(base, result, q)==m)
        return result;
    }

  //Resultado (caso de falha)
  return (-1);

};

//Função que calcula o mdc de dois inteiros de 64 bits
int64_t gcd_s64(int64_t a, int64_t b){

  //Procedimentos
    //Loop principal:
    while(b>0){
      int64_t t=a%b;
      a=b;
      b=t;
    }

  //Resultado
  return a;

};


//Função que constroi um caractére de Dirichlet módulo um primo q
struct unity_root_q set_unity_root_q(int64_t m, int64_t q){

  //Variáveis locais
  int64_t gq=primitive_root_prime_module(q);
  int64_t index = find_index(gq, m, q);
  struct unity_root_q result={gq, index%(q-1), q, 0};

  //Condição de nulidade de um caractére númerico
  if(gcd_s64(m, q)>1 || index<0) result.is_zero=1;

  
  //Resultado
  return result;

};


//Função que constroi um caractére de Dirichlet módulo um primo q de ordem p
struct unity_root_pq set_unity_root_pq(int64_t m, int64_t p, int64_t q){

  //Restrição
  assert((q-1)%p==0 && "p deveser um divisor de (q-1)\n");


  //Variáveis locais
  int64_t gq=primitive_root_prime_module(q);
  int64_t index = find_index(gq, m, q);
  struct unity_root_pq result={gq, index%p, p, q, 0};

  //Condição de nulidade de um caractére númerico
  if(gcd_s64(m, q)>1 || index<0) result.is_zero=1;

  
  //Resultado
  return result;

};


//Função que printa uma raiz de unidade módulo primo q
void print_unit_root_q(struct unity_root_q* u1, enum unity_root_notation x){

  if(u1->is_zero==1){
    printf("0");
    return;
  }
  else if(x==Zeta) printf("ζ(%li)^%li", u1->q-1, u1->k);
  else printf("e^2πi%li/%li", u1->k, u1->q-1);

};


//Função que printa uma raiz de unidade módulo primo q de ordem p
void print_unit_root_pq(struct unity_root_pq* u1, enum unity_root_notation x){

  if(u1->is_zero==1){
    printf("0");
    return;
  }
  if(x==Zeta) printf("ζ(%li)^%li", u1->p, u1->k);
  else printf("e^2πi%li/%li", u1->k, u1->p);

};


//Função que define multiplicação de raízes de unidade módulo primo q
struct unity_root_q unity_root_q_mul(struct unity_root_q* u1, struct unity_root_q* u2){

  //Variáveis locais
  struct unity_root_q ur={u1->g, (u1->k+u2->k)%(u1->q-1), u1->q, (u1->is_zero|u2->is_zero)};


  //Resultado
  return ur;

};


//Função que define multiplicação de raízes de unidade módulo primo q de ordem q
struct unity_root_pq unity_root_pq_mul(struct unity_root_pq* u1, struct unity_root_pq* u2){

  //Variáveis locais
  struct unity_root_pq ur={u1->g, (u1->k+u2->k)%u1->p, u1->p, u1->q, (u1->is_zero|u2->is_zero)};


  //Resultado
  return ur;

};

//***************************************************************************************************
//FIM DO HEADER
#endif
