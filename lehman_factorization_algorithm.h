//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE LEHMAN PARA FATORAR NÚMEROS INTEIROS E COMO TESTE DE PRIMALIDADE

/*
O TESTE DE LEHMAN É UM ALGORITMO EXTREMAMENTE SIMPLES QUE PROVÊ UMA FATORAÇÃO DE UM INTEIRO OU DETERMINA SE O MESMO É PRIMO.
O ALGORITMO  EM QUESTÃO É UM APRIMORAMENTO DO TESTE DE DIVISÃO POR TENTATIVA E ERRO, QUE USA REPRESENTAÇÕES DE INTEIROS VIA 
FORMAS QUADRÁTICAS.

PARA MAIORES INFORMAÇÕES: A Course In Computational Algebraic Number Theory by Henri Cohen

*/ 

//****************************************************************************************************************************************************************.
//CABEÇALHO
#ifndef LEHMAN_FACTORIZATION_ALGORITHM_H
#define LEHMAN_FACTORIZATION_ALGORITHM_H
#include"prime_power_detection.h"
#include<stdio.h>


//****************************************************************************************************************************************************************.
//DECLARAÇÃO DE FUNÇÕES
uint64_t gcd_lehman(uint64_t,uint64_t);
bool trial_division(uint64_t, uint64_t);
void lehman_factorization_algorithm(uint64_t);


//****************************************************************************************************************************************************************.
//FUNÇÕES
//Função que calcula o mdc de dois inteiros usando o algoritmo de Euclides
uint64_t gcd_lehman(uint64_t a,uint64_t b){

  if(b==0)
    return a;
  else
    return gcd_lehman(b, (a%b));

};



//Função que realiza a busca por fatores primos até n^(1/3)
bool trial_division(uint64_t n, uint64_t B){

  //Variáveis locais
  uint64_t factor=0;

  //Procedimentos
    //Busca por fatores 2 ou 3
    if((n%2)==0){
      printf("Fatores primos encontrados: 2 e %lu\n", (n/2));
      return true;
    };


    if((n%3)==0){
      printf("Fatores primos encontrados: 3 e %lu\n", (n/3));
      return true;
    };


    //Loop principal com otimização 6k+1
    for(uint64_t i=5; i<(B+100); i+=6){
  
      if((n%i)==0){
        printf("Fatores primos encontrados: %lu e %lu\n", i, (n/i));
        return true;
                  };

      if((n%(i+2))==0){
        printf("Fatores primos encontrados: %lu e %lu\n", (i+2), (n/(i+2)));
        return true;
                      };

    };


  //Caso o número não passe no teste acima ele é o produto de no máximo dois fatores primos ou é primo
  return false;
   
};

//Função que implementa o algoritmo de Lehman para fatorar números inteiros
void lehman_factorization_algorithm(uint64_t n){

  //Variáveis locais
  uint64_t B=cbrt(n);
  uint64_t b, c, r, m, k=0, limit;
  uint64_t factor, cofactor;


  //Procedimentos
    //Busca por fatores primos até n^(1/3)
    if(trial_division(n, B)==true)
      return;

    //Loop principal: expressando o inteiro a ser fatorado como uma forma quadrática
    while(true){

      //Condição de primalidade
      if(k>B){
        printf("%lu é primo\n", n);
        return;
             };

      //Ajuste de variáveis 
      if((k&1)){
        r=k+n;
        m=4;
      }
      else{
        r=1;
        m=2;
      };

      limit=((4*k*n)>(B*B))?(B*B):(4*k*n);


      //Teste envolvendo forma quadráticas canônicas
      for(uint64_t a=2; a<=limit; ++a){
        
        c=(a*a)-(4*k*n);
        if(c>=0 && fast_square_detection(c, &b)==true){
          factor=gcd_lehman((a+b), n);

          if(factor>1 && factor <n){
            cofactor=n/factor;
            printf("Fatores primos encontrados: %lu e %lu\n",factor, cofactor);
            return;
                                   };
         };
          
     
       };

      //Atualizando variáveis para a próxima iteração
      k++;

    };//Fim do loop principal


};



//****************************************************************************************************************************************************************.
//FIM DO HEADER
#endif
