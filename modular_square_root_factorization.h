//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UM ALGORITMO PARA FATORAR NÚMEROS INTEIROS USANDO RAÍZES QUADRADAS A MENOS DE UMA CONGRUÊNCIA

/*
COMPUTANDO RÁIZES QUADRADAS A MENOS DE UMA CONGRUÊNCIA, ISTO É, POR MEIO DE SOLUÇÕES DE EQUAÇÕES DIOFANTINAS DO TIPO x²= a (mod n) É 
POSSÍVEL FATORAR NÚMEROS INTEIROS COM PROBABILIDADE IGUAL A 50%, CALCULANDO-SE O mdc(|x-a|, n) (OU mdc(|x|, n)). TAL ALGORITMO NÃO
FUNCIONA SE n FOR UMA POTÊNCIA DE NÚMERO PRIMO.


PARA MAIORES INFORMAÇÕES: https://sites.math.rutgers.edu/~sk1233/courses/topics-S18/lec10.pdf


*/


//*******************************************************************************************************************************************************
//CABEÇALHO
#ifndef MODULAR_SQUARE_ROOT_FACTORIZATION_H
#define MODULAR_SQUARE_ROOT_FACTORIZATION_H
#include"tonelli_shanks.h"
#include<stdlib.h>


//*******************************************************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
int64_t gcd(int64_t, int64_t);
void fill_prime_buffer(int64_t, int64_t, int64_t[]);
void modular_square_root_factorization(int64_t, int64_t);


//*******************************************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides
int64_t gcd(int64_t a, int64_t b){

 if(b==0)
  return a;
 else
  return gcd(b, (a%b));
                                 };

//Função que preenche um buffer de primos usando um teste de Fermat na base 2
void fill_prime_buffer(int64_t n, int64_t  buffer_size, int64_t prime_buffer[]){

 //Variáveis locais
 int64_t i, index=0;

 //Procedimentos
  //Loop principal
  for(i=(n+1); ;++i){

   if(mod_bin_pow(2, (i-1), i)==1){
    prime_buffer[index]=i;
    index++;
                                  };

    if(index==buffer_size)
     break;
                    };
                                                                               };


//Função que fatora um inteiro usando raízes quadradas modulares, soluções de equações diofantinas do tipo x²= a (mod n) 
void modular_square_root_factorization(int64_t n, int64_t buffer_size){

 //Variáveis locais
 int64_t* prime_buffer=NULL;
 int64_t factor=0, cofactor=0;
 int64_t mod_sqrt_n, abs_diff;



 //Procedimentos
  //Preechendo o buffer de primos
  prime_buffer=(int64_t*)realloc(prime_buffer, buffer_size*sizeof(int64_t));
  fill_prime_buffer(n, buffer_size, prime_buffer);


  //Fatorando n usando raízes quadradas módulo um primo superior ao número a ser fatorado
  for(int64_t i=0; i<buffer_size; ++i){

   mod_sqrt_n = tonelli_shanks(n, prime_buffer[i]);

   factor=gcd(mod_sqrt_n, n);
   if(factor>1 && factor<n)
    break;

   if(mod_sqrt_n>prime_buffer[i])
    abs_diff=mod_sqrt_n-prime_buffer[i];
   else
    abs_diff=prime_buffer[i]-mod_sqrt_n;
    
   factor=gcd(abs_diff, n);      
   if(factor>1 && factor<n)
    break;
                                      };


  if(factor==1 || factor==n)
   printf("O algoritmo não encontrou fatores primos de %li\n", n);

  else{

   cofactor=n/factor;
   printf("Fatores de %li encontrados: %li e %li\n", n, factor, cofactor);

      };

  //Limpando o cachê de memória
  free(prime_buffer);
 
                                                                      };




//*******************************************************************************************************************************************************
//FIM DO HEADER
#endif 
