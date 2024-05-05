//VAMOS CRIAR UM PROGRAMA QUE COMPUTA A ORDEM MULTIPLICATIVA DE UM INTEIRO MÓDULO OUTRO INTEIRO COPRIMO PARA INTEIROS DE 64 BITS

/*
A ORDEM MULTIPLICATIVA DE UM INTEIRO a MÓDULO UM INTEIRO n DENOTADA POR ord(a) É DEFINIDA COMO O MENOR INTEIRO x TAL QUE a^x=1 (mod n).

PARA O GRUPOS DE INTEIROS A MENOS DE UMA CONGRUÊNCIA O SEGUINTE TEOREMA DEVIDO A EULER É ÚTIL PARA COMPUTAR A ORDEM MULTIPLICATIVA DE UM INTEIRO:
SE a,n SÃO DOIS INTEIROS COPRIMOS ENTÃO a^φ(n)=1 (mod n), ONDE φ(n) É A FUNÇÃO TOTIENTE DE EULER.

TAL TEOREMA PROVIDO DA FATORAÇÃO DE φ(n) PROVÊ UM EFICIENTE MÉTODO DE SE CALCULAR A ORDEM MULTIPLICATIVA DE UM INTEIRO. A RECIPROCA É VERDADEIRA
ord(a) É EQUIVALENTE A FATORAR n, ESSA É A PARTE CLÁSSICA DO ALGORITMO DE SHOR (QUE USA TRANSFORMADA DE FOURIER E SUPERPOSIÇÃO DE ESTADOS 
QUÂNTICOS PARA DETERMINAR ord(a) DE FORMA EFICAZ), SE a^x=1 (mod n) E x FOR PAR ENTÃO SE (a^x)-1 = 0 (mod n), PORTANTO [a^(x/2)-1][a^(x/2)+1] = 0 (mod n).

ALGORITMOS MAIS EFICAZES PERMITEM REAGRUPRAR OS FATORES PRIMOS DE φ(n), REDUZINDO ASSIM O NÚMERO DE EXPONENCIAÇÔES NECESSÁRIAS PARA COMPUTAR ord(a).

PARA MAIORES INFORMAÇÕES: A Course In Computational Number Theory by H. Cohen


*/ 


//*************************************************************************************************************************************************************
//CABEÇALHO
#ifndef MULTIPLICATIVE_ORDER_H
#define MULTIPLICATIVE_ORDER_H
#include"euler_totient_function.h"
#include"mod_bin_exponentiation128.h"
#include<stdio.h>

//*************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void extract_prime_factors(uint64_t, uint64_t[], uint64_t[]);
uint64_t multiplicative_order(uint64_t, uint64_t);


//*************************************************************************************************************************************************************
//FUNÇÕES

//Função que fatora um número inteiro e aloca seus fatores primos em um array
void extract_prime_factors(uint64_t t, uint64_t prime_factor[], uint64_t multiplicities[]){

 //Variáveis locais
 uint64_t sqrt_t=sqrt(t);
 int k=0, multiplicity=0;

    //TESTE USE UM /**/ APÓS O MESMO
    /*printf("φ(n)=%lu\n", t);
    printf("φ(n)^(1/2)=%lu\n", sqrt_t);*/


 //Procedimentos
  //Fatores 2, 3
  if((t%2)==0){

   multiplicity=0;
   prime_factor[k]=2;
    
   while((t%2)==0){
    t/=2;
    multiplicity++;
                  };

   multiplicities[k]=multiplicity;
   k++;
              };


   if((t%3)==0){

   multiplicity=0;
   prime_factor[k]=3;
    
   while((t%3)==0){
    t/=3;
    multiplicity++;
                  };

   multiplicities[k]=multiplicity;
   k++;
              };

    
  //Fatores primos até n^(1/2): loop usando uma otimização 6k+1
  for(uint64_t i=5; i<(sqrt_t+1); i+=6){

    
   if(t==1)
    break;

   if((t%i)==0){

   multiplicity=0;
   prime_factor[k]=i;
    
   while((t%i)==0){
    t/=i;
    multiplicity++;
                  };

   multiplicities[k]=multiplicity;
   k++;
              };

    
   if(t==1)
    break;

   if((t%(i+2))==0){

   multiplicity=0;
   prime_factor[k]=i;
    
    
   while((t%(i+2))==0){
    t/=(i+2);
    multiplicity++;
                      };

   multiplicities[k]=multiplicity;
   k++;

                   };    



                                       };


  //Fator superior a n^(1/2)
  if(t>1){
   multiplicities[k]=1;
   prime_factor[k]=t;

         }
   

    //TESTE USE UM /**/ APÓS O MESMO
    /*printf("φ(n)=%lu\n", t); 
    for(; k>=0; --k){
     printf("Prime factor: %lu\n", prime_factor[k]);   printf("Multiplicity: %lu\n", multiplicities[k]);  
                    };*/
                                                                                          };


//Função que calcula aordem multiplicativa de um inteiro congruente a um número coprimo
uint64_t multiplicative_order(uint64_t a, uint64_t n){

 //Restrição: o algoritmose aplica apenas quando n é coprimo com a
 if(gcd_euclides(a, n)>1){
  printf("%lu e %lu não coprimos, o algoritmo não se aplica a estes parâmetros.\n", a, n);
  return 0; 
                         };

 //Variáveis locais
 uint64_t primes[70], multiplicities[70];
 uint64_t totient=euler_totient_function(n);
 uint64_t M=totient, multiplicity=0, lowest=totient;


 //Procedimentos
    //TESTE USE UM /**/ APÓS O MESMO
    /*printf("%lu\n", totient);*/

  //Fatorando φ(n)
  extract_prime_factors(totient, primes, multiplicities);
   


  //Teste sobre os fatores primos de φ(n): determinando o menor x tal que a^x=1 (mod n)
  for(int k=0; k<80; ++k){
    
    if(primes[k]==0)
     break;
    
   //Ajuste de variáveis
   multiplicity=multiplicities[k];
   M=totient/bin_pow(primes[k], multiplicity);

   //Testando se o expoente φ(n) pode ser reduzido
   for(int l=multiplicity; l>=0; --l){

    if(mod_bin_pow(a, M, n)==1 && M<lowest)
     lowest=M;
    else
     M*=primes[k];
                                     }
   

                         };  
  

 //Resultado
 return lowest; 
                                                     };


//*************************************************************************************************************************************************************
//FIM DO HEADER
#endif
