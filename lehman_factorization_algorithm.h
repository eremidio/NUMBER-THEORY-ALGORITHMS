//VAMOS CRIAR UM PROGRAMA QUE IMPLMENTA O TESTE DE PRIMALIDADEDE DE LEHMAN

/*
O TESTE DE LEHMAN É UM ALGORITMO EXTREMAMENTE SIMPLES QUE PROVÊ UMA FATORAÇÃO DE UM INTEIRO OU DETERMINA SE O MESMO É PRIMO. O ALGORITMO  EM QUESTÃO É UM 
APRIMORAMENTO DO TESTE DE DIVISÃO POR TENTATIVA E ERRO.

*/ 

//****************************************************************************************************************************************************************.
//CABEÇALHO
#ifndef LEHMAN_FACTORIZATION_ALGORITHM_H
#define LEHMAN_FACTORIZATION_ALGORITHM_H
#include<math.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdbool.h>
#include<stdio.h>


//****************************************************************************************************************************************************************.
//DECLARAÇÃO DE FUNÇÕES
uint64_t gcd_lehman(uint64_t,uint64_t);
bool is_perfect_square(uint64_t*, uint64_t);
bool trial_division(uint64_t, uint64_t);
uint64_t minimum(uint64_t, uint64_t);
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


//Função que calcula a raíz quadrada de um inteiro e retorna se o número em questão é um quadrado perfeito
bool is_perfect_square(uint64_t* sqrt_n, uint64_t n){

  //Variáveis locais
  uint64_t helper, root=1;


  //Procedimentos
    //Ajuste da ordem de grandeza da raíz
    while((root*root)<n) root*=10;
    while((root*root)>n) root/=10;

    helper=root;

    //Ajuste fino do resultado
    while(helper>0){

      while((root*root)<n) root+=helper;

      if((root*root)==n)
        break;

      if((root*root)>n){
        root-=helper;
        helper/=10;
                       };
      
                   };


    while((root*root)<n) root++;
    
  //Resultado
  (*sqrt_n)=root;
  if(root*root==n)
    return true;
  else
    return false;
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

//Função que retorna a menor parcela de dois valores
uint64_t minimum(uint64_t a, uint64_t b){
  
  //Resultado
  return (a>b)?a:b;
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

      limit=minimum((4*k*n), (B*B));


      //Teste envolvendo forma quadráticas canônicas
      for(uint64_t a=2; a<=limit; ++a){
        
        c=(a*a)-(4*k*n);
        if(c>=0 && is_perfect_square(&b, c)==true){
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
