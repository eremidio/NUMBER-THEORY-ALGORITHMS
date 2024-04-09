//VAMOS CRIAR UM PROGRAMA QUE TESTA A PRIMALIDADE DE UM INTEIRO DE 64 BITS USANDO TENTATIVA POR DIVISÃO


//****************************************************************************************************************************
//CABEÇALHO
#ifndef TRIAL_DIVISION128_H
#define TRIAL_DIVISION128_H
#include"int128.h"
#include"sqrt128.h"
#include<stdbool.h>
#include<math.h>

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
 __int128_t remainder=1;

 uint64_t remainder_seed[48]={1,11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 121, 127, 131, 137, 139, 143, 149, 151, 157, 163, 167, 169, 173, 179, 181, 187, 191, 193, 197, 199, 209};
 uint64_t prime_seed[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
 uint64_t*prime_factors=NULL;

 uint64_t root=(uint64_t)sqrt128(n);
 uint64_t divisor=0, x=0, y=0, i, j;
 int factors_size=0;
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
 for(x=0; (divisor<=root || n==1); x++){

  for(y=0; y<48; y++){

   divisor=(210*x)+remainder_seed[y];

   if((n%prime_seed[i])==0){
    result=false;
    factors_size++;

    prime_factors=(uint64_t*)realloc(prime_factors, factors_size*sizeof(uint64_t));
    prime_factors[factors_size-1]=divisor;

    while((n%divisor)==0)
     n/=divisor;
                           };

                     };

                                       };


 //Fatores primos superiores a n^(1/2)
 if(n>1)
  remainder=n;

 //Exibindo o resultado da execução do algoritmo
 if(print_result==Yes){

  printf("Lista de fatores primos de encontrados: ");

  for(int j=0; j<factors_size; j++)
   printf("%lu, ", prime_factors[j]);
  
  if(remainder<2)
   printf("...\n");

  else{
   printf128(remainder);
   printf("...\n");
      };

                     };

 //Limpando o cachê de memória
 free(prime_factors);
 return result;

                                                                             };

//****************************************************************************************************************************
//FIM DO HEADER
#endif


 
