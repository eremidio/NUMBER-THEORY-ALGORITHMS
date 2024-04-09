//VAMOS CRIAR UM PROGRAMA QUE TESTA A PRIMALIDADE DE UM INTEIRO DE 64 BITS USANDO TENTATIVA POR DIVISÃO


//****************************************************************************************************************************
//CABEÇALHO
#ifndef TRIAL_DIVISION_H
#define TRIAL_DIVISION_H
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

//CONSTANTES GLOBAIS
enum show_factorization{Yes, No};

//****************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool trial_division(uint64_t, enum show_factorization);

//****************************************************************************************************************************
//FUNÇÕES
//Função que testa a primalidade de um número usaremos uma otimização 30k+l
bool trial_division(uint64_t n, enum show_factorization print_result){

 //Variáveis locais
 uint64_t N=n;
 uint64_t*prime_factors=NULL;
 int factors_size=0;
 uint64_t root=sqrt(n);
 uint64_t divisor, x=0, y=0, i, j;
 uint64_t prime_seed[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
 uint64_t remainder_seed[8]={1,7,11,13,17,19,23,29};
 bool result=true;


 //Procedimentos
 //Casos triviais primos menos que 100
 for(i=0; i<25;++i){

  if(n==prime_seed[i]){

   if(prime_factors)
    free(prime_factors);  
   return true;

                      };


  if((n%prime_seed[i])==0){

   result=false;
   factors_size++;

   prime_factors=(uint64_t*)realloc(prime_factors, factors_size*sizeof(uint64_t));
   prime_factors[factors_size-1]=prime_seed[i];

   while((n%prime_seed[i])==0)
    n/=prime_seed[i];
                          };


                   };

 //Loop principal
 for(x=3;; x++){

  for(y=0; y<8; y++){

   divisor=(30*x)+remainder_seed[y];
   
   if(divisor>root || n<2)
    break;

   if((n%divisor)==0){
    result=false;
    factors_size++;

    prime_factors=(uint64_t*)realloc(prime_factors, factors_size*sizeof(uint64_t));
    prime_factors[factors_size-1]=divisor;

    while((n%divisor)==0)
     n/=divisor;
                     };


                    };

   if(divisor>root || n<2)
    break;
               };


 //Fatores primos superiores a n^(1/2)
 if(n>1){

  factors_size++;
  prime_factors=(uint64_t*)realloc(prime_factors, factors_size*sizeof(uint64_t));
  prime_factors[factors_size-1]=n;

        };

 //Exibindo o resultado da execução do algoritmo
 if(print_result==Yes){

  printf("Lista de fatores primos de %lu: ", N);

  for(int j=0; j<factors_size; j++)
   printf("%lu, ", prime_factors[j]);
  printf("...\n");

                     };

 //Limpando o cachê de memória
 free(prime_factors);
 return result;
               
                                                                     };

//****************************************************************************************************************************
//FIM DO HEADER
#endif


