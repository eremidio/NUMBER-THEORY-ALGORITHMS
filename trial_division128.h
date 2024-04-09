//VAMOS CRIAR UM PROGRAMA QUE TESTA A PRIMALIDADE DE UM INTEIRO DE 128 BITS USANDO TENTATIVA POR DIVISÃO


//****************************************************************************************************************************
//CABEÇALHO
#ifndef TRIAL_DIVISION128_H
#define TRIAL_DIVISION127_H
#include"int128.h"
#include"sqrt128.h"
#include<stdbool.h>


//CONSTANTES GLOBAIS
enum show_factorization128{Yes, No};

//****************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool trial_division128(__int128_t, enum show_factorization128);

//****************************************************************************************************************************
//FUNÇÕES
//Função que testa a primalidade de um número usaremos uma otimização 210k+l
bool trial_division128(__int128_t n, enum show_factorization128 print_result){

 //Variáveis locais
 int prime210[4]={2,3,5,7};
 int remainder_seed[48]={1,11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 121, 127, 131, 137, 139, 143, 149, 151, 157, 163, 167, 169, 173, 179, 181, 187, 191, 193, 197, 199, 209};
 __int128_t root=sqrt128(n);
 __int128_t* prime_factors=NULL;
 __int128_t divisor=0;
 __int128_t x, y, i, j;
 int factors_size=0;
 bool result=true;


 //Procedimentos
 //Teste por fatores 2,3,5,7
 for(i=0; i<4;++i){

  if(n==prime210[i]){

   if(prime_factors)
    free(prime_factors);  
   return true;

                   };

  if((n%prime210[i])==0){

   result=false;
   factors_size++;

   prime_factors=(__int128_t*)realloc(prime_factors, factors_size*sizeof(__int128_t));
   prime_factors[factors_size-1]=prime210[i];

   while((n%prime210[i])==0)
    n/=prime210[i];
                        };


                  };


 //Loop principal
 for(x=0;; x++){

  for(y=0; y<48; y++){

   divisor=(210*x)+remainder_seed[y];
   
   if(divisor>root || n<2)
    break;

   if((n%divisor)==0 && divisor>1){
    result=false;
    factors_size++;

    prime_factors=(__int128_t*)realloc(prime_factors, factors_size*sizeof(__int128_t));
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
  prime_factors=(__int128_t*)realloc(prime_factors, factors_size*sizeof(__int128_t));
  prime_factors[factors_size-1]=n;

        };

 //Exibindo o resultado da execução do algoritmo
 if(print_result==Yes){

  printf("Lista de fatores primos encontrados:\n");

  for(j=0; j<factors_size; j++)
   printf128(prime_factors[j]);
  printf("...\n");

                     };

 //Limpando o cachê de memória
 free(prime_factors);
 return result;
                                                                             };

//****************************************************************************************************************************
//FIM DO HEADER
#endif



