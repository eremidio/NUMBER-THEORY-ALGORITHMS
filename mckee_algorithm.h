//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE MCKEE PARA FATORAR NÚMEROS INTEIROS E COMO UM TESTE DE PRIMALIDADE

/*
O ALGORITMO DE MCKEE É UMA VARIANTE DO ALGORITMO DE FATORAÇÃO DE EULER QUE UTILIZA REPRESENTAÇÕES DE FORMAS
QUADRÁTICAS PARA FATORAR INTEIROS. UMA FORMA QUADRÁTICA f(x,y)=ax²+bxy+cy² É DITA REPRESENTAR UM INTEIRO n,
SE EXISTIREM x,y INTEIROS TAIS QUE f(x, y)=n. O ALGORITMO DE MCKEE GENERALIZA O MÉTODO DE FATORAÇÃO DE EULER
E UMA ANTIGA VARIANTE DESTE MÉTODO DEVIDO A FERMAT, PERMITINDO ENCONTRAR PARES (u, v) DE INTEIROS TAIS QUE
u²-Δv² = 0 (mod 4n) COM Δ=b²-4ac E Δ<0. OS PARES (u, v) SATISFAZEM DETERMINADAS RELAÇÕES DE CONGRUÊNCIA QUE
PERMITEM DECOMPOR n EM FATORES PRIMOS OU QUE ATESTAM QUE n É PRIMO, NO CASO EM QUE n NÃO POSSUA FATORES
PRIMOS MENORES QUE 3n^(1/3).

PARA MAIORES INFORMAÇÕES: https://londmathsoc.onlinelibrary.wiley.com/doi/abs/10.1112/blms/28.4.351
                          Prime Numbers. A Computational Perspective by R.Crandall & Carl B. Pomerance
*/

/*
OBSERVAÇÃO: O algoritmo requer computar soluções de equações do tipo x²=a (mod n), com n composto o que é um problema equivalente
a fatoração em si. Por esta razão tal cálculo foi feito por força bruta usando o algoritmo de Newton-Raphson para checar se um
dado inteiro é quadrado perfeito. Uma alternativa seria usar o algoritmo de Tonelli-Shanks ou Cipolla para computar x para cada
fator primo de n e combinar os resultados via teorema do resíduo chinês.

*/


//****************************************************************************************************************************************************
//CABEÇALHO
#ifndef MCKEE_ALGORITHM_H
#define MCKEE_ALGORITHM_H
#include"prime_power_detection.h"
#include<stdio.h>
#include<stdlib.h>



//****************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void small_factors_removing(int64_t*);
int64_t euclides_algorithm(int64_t, int64_t);
void mckee_algorithm(int64_t);

//****************************************************************************************************************************************************
//FUNÇÕES
//Função que determina se um inteiro possui pequenos fatores primos 3n^(1/3) por tentativa e erro
void small_factors_removing(int64_t* n){

  //Variáveis locais
  int64_t divisors;
  int64_t N_=(*n);
  int64_t upper_bound=(3*cbrt(N_));


  //Procedimentos
    //Fatores 2, 3
    if((N_%2)==0){
      printf("Fator encontrado: 2.\n");
      while((N_%2)==0)
      N_/=2;
    };


    if((N_%3)==0){
      printf("Fator encontrado: 3.\n");
      while((N_%3)==0)
        N_/=3;
    };


    //Loop principal com otimização 6k+1
    for(divisors=5; divisors<(upper_bound+1); divisors+=6){
      if((N_%divisors)==0){
        printf("Fator encontrado: %li.\n", divisors);
        while((N_%divisors)==0)
        N_/=divisors;
                          };

      if((N_%(divisors+2))==0){
        printf("Fator encontrado: %li.\n", (divisors+2));
        while((N_%(divisors+2))==0)
          N_/=(divisors+2);
                              };

    };


  //Resultado da execução desta subrotina
  if(N_<(*n)){
    (*n)=N_;
    printf("\nCofator: %li\n", (*n));
  };

};


 //Função que implementa o algoritmo de Euclides
int64_t euclides_algorithm(int64_t a, int64_t b){

  if(b==0)
    return a;
  else
    return euclides_algorithm(b, (a%b));
};


//Função que implementa o algoritmo de Mckee para fatorar números inteiros usando representações via formas quadráticas de discriminante negativo
void mckee_algorithm(int64_t n){


  //Checando se o número em questão possuí pequenos fatores primos inferiores a 3n^(1/3)
  small_factors_removing(&n);
  if(n==1)
    return;


  //Caso geral o número em questão não contém fatores pequenos
    //Variáveis locais
    int64_t* roots=NULL; 
    int64_t root_size=0;
    int64_t ui, u, v, x0, d, root_4d, root_an, bound;
    int64_t a, i;
    int64_t factor=1, cofactor=1;



  //Procedimento
    //Ajuste de variáveis
    x0=floor(sqrt(n-(cbrt(n)*cbrt(n))));
    d=floor(n-(floor(x0)*floor(x0)));


    //Teste 1: divisibilidade de por algum fator primo de d
    factor=euclides_algorithm(n, d);
    if(factor>1 && factor<n){
      cofactor=n/factor;
      goto end;
    };

  
    //Teste 2: checando se n é um quadrado perfeito
    int64_t temp=floor(sqrt(n));
    if((temp*temp)==n){
      cofactor=temp;
      factor=temp;
      goto end;
    };


    //Teste 3: congruências definidas por meio de representações de formas quadráticas
    bound=floor(2*sqrt(d/3.0));
    root_4d=sqrt(4*d);

    for(a=1; a<=bound; a++){
      //Calculando soluções da equação u²=4an (mod 4d)
      roots=(int64_t*)realloc(roots, 0);
      root_size=0;
      int64_t temp1=(4*a*n)%(4*d);

      for(int64_t i=root_4d; i<(d<<2); ++i){
        if(((i*i)%(d<<2))==temp1){
          root_size++;
          roots=(int64_t*)realloc(roots, root_size*sizeof(int64_t));
          roots[root_size-1]=i;
                                 }
      }

      if(root_size==0) continue;
      else root_an=sqrt(a*n);

      //Cálculo de possíveis divisores
      for(int64_t j=0; j<root_size; ++j){
        ui=roots[j];
        u=(ui%(d<<2));
        int64_t tester=((4*a*n)-(u*u))/(d<<2);
        
        
        if(fast_square_detection(tester, &v)==true){
    
          int64_t tester2=(2*x0*v)-u;
          factor=euclides_algorithm(tester2, n);

          if(factor>1 && factor<n){
            cofactor=n/factor;
            goto end;
                                  }

        }
        
      

      } 
            



    };


  //Resultado da execução do algoritmo
  end:
  if(factor>1 && factor<n){
    printf("Fator encontrado: %li.\n", factor);
    printf("Fator encontrado: %li.\n", cofactor);
  }
  else
    printf("%li é primo.\n", n);


  //Limpando o cachê de memória
  if(roots) free(roots);
  
 
                               };


//****************************************************************************************************************************************************
//FIM DO  HEADER
#endif
