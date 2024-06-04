//VAMOS CRIAR UM PROGRAMA QUE IMPLMENTA ROTINAS PARA RESOLVER EQUAÇÕES DIONFANTINAS LINEARES A MENOS DE UMA CONGRUÊNCIA

/*
SEJA a, b, n INTEIROS POSITIVOS. PARA DETERMINAR SOLUÇÕES DA EQUAÇÃO ax=b (mod n), AS SEGUINTES PROPOSIÇÕES SÃO ÚTEIS:

PROPOSIÇÃO 1: SOLUÇÕES INTEIRAS DA EQUAÇÃO ax=b (mod n) EXISTEM SE E SOMENTE mdc(a,n) DIVIDE b.
PROPOSIÇÃO 2: SOLUÇÕES INTEIRAS E DISTINTAS DA EQUAÇÃO ax=b (mod n) DIFEREM ENTRE SI POR UM VALOR n/mdc(a,n).
              O NÚMERO TOTAL DE SOLUÇÕES É IGUAL A mdc(a,n).


PARA MAIORES REFERÊNCIAS: Elements of Number Theory by I. M. Vinogradov

*/


//**************************************************************************************************************************************
//CABEÇALHO
#ifndef MODULAR_LINEAR_DIOFANTINE_EQUATION_H
#define MODULAR_LINEAR_DIOFANTINE_EQUATION_H
#include"modular_inverse.h"
#include<stdio.h>

//**************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t gcd_diofante(int64_t, int64_t);
void modular_linear_diofantine_equation(int64_t, int64_t,int64_t);


//**************************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides
int64_t gcd_diofante(int64_t a, int64_t b){

  if(b==0)
    return a;
  else
    return gcd_diofante(b, (a%b));
                                          };

//Função que resolve equações diofantinas do tipo ax=b (mod n)
void modular_linear_diofantine_equation(int64_t a, int64_t b, int64_t n){

  //Variáveis
  int64_t reduction_factor=gcd_diofante(a,n);
  int64_t solution_gap=n/reduction_factor;
  int64_t mod_inv;


  //Procedimentos

    //Restrição: mdc(a,n) deve ser um divisor de b
    if((b%reduction_factor)!=0){
      printf("A equação diofantina %lix=%li (mod %li) não possui solução\n", a, b, n);
      return;
                               };

    //Caso base: mdc(a,n)=1
    if(reduction_factor==1){

      //Cálculo da solução
      mod_inv=modular_inverse(a,n);
      printf("Solução da equação diofantina %lix=%li (mod %li)  --> x=%li\n", a, b, n, (mod_inv*b)%n);
      return;


                         };


    //Caso geral: mdc(a,n)>1

      //Redução da equação ao caso anterior
      int64_t reduction_factor2=gcd_diofante(a,b);
      

       //Restrição: mdc(a,n) deve ser um divisor de b
       if((n%reduction_factor2)!=0){
         printf("A equação diofantina %lix=%li (mod %li) não possui solução\n", a, b, n);
         return;
                                   };

       int64_t a_=a/reduction_factor2;
       int64_t b_=b/reduction_factor2;
       int64_t n_=n/reduction_factor2;
       reduction_factor=gcd_diofante(a,n);



      //Restrição: mdc(a,n) deve ser um divisor de b
      if((b%reduction_factor)!=0){
        printf("A equação diofantina %lix=%li (mod %li) não possui solução\n", a, b, n);
        return;
                                 };

      //Cálculo da solução
      mod_inv=modular_inverse(a_,n_);
      int64_t result=(mod_inv*b_)%n_;

      //Restrição: mdc(a,n)=0
      if(mod_inv==0){
        printf("A equação diofantina %lix=%li (mod %li) não possui solução\n", a, b, n);
        return;
                    };

      //Exibição do resultado do algoritmo
      while(result<n){

        printf("Solução da equação diofantina %lix=%li (mod %li)  --> x=%li\n", a, b, n, result);
        result+=solution_gap;    

                     };

                                                                        };



//**************************************************************************************************************************************
//FIM DO HEADER
#endif
