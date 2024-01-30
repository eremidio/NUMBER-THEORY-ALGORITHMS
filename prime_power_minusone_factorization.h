//VAMOS CRIAR UM PROGRAMA QUE FATORA NÚMEROS INTEIROS DA FORMA N=(b^n)-1, COM b, n INTEIROS

/*
PARA NÚMEROS DA FORMA N=(b^n)-1 O SEGUINTE TEOREMA É ÚTIL EM SUA DECOMPOSIÇÃO EM FATORES PRIMOS:
PARA b, n INTEIROS E N=(b^n)-1, OS FATORES PRIMOS DE p N SATISFAZEM A SEGUINTE CONDIÇÃO: [1] p É UM DIVISOR DE N'=(b^d)-1,ONDE d É UM DIVISOR NÃO TRIVIAL DE n, [2] p É DA FORMA p= 1 (mod n), OU SE p>2  E n FOR ÍMPAR p= 1 (mod 2n).

PARA MAIORES REFERÊNCIAS: A Course In Number Theory And Criptography by Neal Koblitz.

*/

//****************************************************************************************************************************************************
//CABEÇALHO
#ifndef PRIME_POWER_MINUSONE_FACTORIZATION_H
#define PRIME_POWER_MINUSONE_FACTORIZATION_H
#include"mod_bin_exponentiation.h"
#include<stdbool.h>
#include<stdio.h>
#include<math.h>


//****************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void proper_divisors_partial_factorization(uint64_t, uint64_t, uint64_t*);
void congruence_divisors_factorization(uint64_t, uint64_t*);
void prime_power_minusone_factorization(uint64_t, uint64_t);

//****************************************************************************************************************************************************
//FUNÇÕES
//Função que calcula fatores primos de um inteiro N=(b^n)-1, baseados na fatoração parcial de N'=(b^d)-1 com d|n
void proper_divisors_partial_factorization(uint64_t base, uint64_t power, uint64_t* N){
//Variáveis locais
uint64_t N_=(*N);
uint64_t n=bin_pow(base, power)-1;
uint64_t root=sqrt(n);
uint64_t i, k=0;
uint64_t* factor_array = NULL;

//TESTE USE UM // APÓS TESTE
//printf("n: %lu\n", n);

//Procedimentos 
//Fatoração de n usando divisão por tentativa e erro
if((n%2)==0){
k++;
factor_array=(uint64_t*)realloc(factor_array, sizeof(uint64_t)*k);
factor_array[k-1]=2;
while((n%2)==0)
n/=2;
            };

if((n%3)==0){
k++;
factor_array=(uint64_t*)realloc(factor_array, sizeof(uint64_t)*k);
factor_array[k-1]=3;
while((n%3)==0)
n/=3;
           };

for(i=5; i<(root+7); i+=6){

if((n%i)==0){
k++;
factor_array=(uint64_t*)realloc(factor_array, sizeof(uint64_t)*k);
factor_array[k-1]=i;
while((n%i)==0)
n/=i;
           };

if((n%(i+2))==0){
k++;
factor_array=(uint64_t*)realloc(factor_array, sizeof(uint64_t)*k);
factor_array[k-1]=(i+2);
while((n%(i+2))==0)
n/=(i+2);
           };

                         };

if(n>1){
k++;
factor_array=(uint64_t*)realloc(factor_array, sizeof(uint64_t)*k);
factor_array[k-1]=n;
       };

//Testando se fatores primos de N foram encontrados
for(i=0; i<k; i++){
if((N_%factor_array[i])==0){
printf("Fator de %lu encontrado: %lu\n", (*N), factor_array[i]);
while((N_%factor_array[i])==0)
N_/=factor_array[i];
                           };
                  };

//Ajuste de variáveis 
(*N)=N_;
if(N_>1)
printf("\nN: %lu\n", N_);

//Limpeza do cachê de memória
free(factor_array);
                                                                                      };

//Função que busca por fatores primos da forma p= 1 (mod n) ou p= 1 (mod 2n) se n for ímpar
void congruence_divisors_factorization(uint64_t power, uint64_t* N){
//Variáveis locais
uint64_t N_=(*N);
uint64_t root=sqrt(N_);
uint64_t divisor=1, step;

//Procedimentos
//Ajuste de  variáveis
if((power%2)==1)
step=power*2;
else
step=power;

//Loop principal
while(divisor<(root+2*step)){
divisor+=step;

if((N_%divisor)==0){
printf("Fator de %lu encontrado: %lu\n", (*N), divisor);
while((N_%divisor)==0)
N_/=divisor;
                   };
                           };


//Condição que determina a primalidade de N
if(N_<(*N) && N_>1)
printf("Fator de %lu encontrado: %lu\n", (*N), N_);

if(N_==(*N))
printf("%lu é primo.\n", N_);

                                                                   };

//Algoritmo para fatorar números da forma N=(b^n)-1
void prime_power_minusone_factorization(uint64_t base, uint64_t power){
//Variáveis locais
uint64_t N=bin_pow(base, power)-1;
uint64_t N1=N;
uint64_t* exponent_divisors=NULL;
uint64_t i, j, k=1;

//Procedimentos
//---
printf("N: %lu\n", N1);

//Determinando divisores do expoentes
exponent_divisors=(uint64_t*)realloc(exponent_divisors, sizeof(uint64_t)*k);
exponent_divisors[k-1]=1;
//TESTE USE UM // APÓS O MESMO
//printf("%lu\n",exponent_divisors[k-1]);

for(i=1; i<power; ++i){
if((power%i)==0){
k++;
exponent_divisors=(uint64_t*)realloc(exponent_divisors, sizeof(uint64_t)*k);
exponent_divisors[k-1]=i;

//TESTE USE UM // APÓS O MESMO
//printf("%lu\n",exponent_divisors[k-1]);
                }
                      };

//Etapa 1: buscando fatores primos entre números da forma N'=(b^d)-1
for(j=0; j<k; j++){
proper_divisors_partial_factorization(base, exponent_divisors[j], &N1);
                  };

//Etapa 2: busca por fatores primos da forma p=1 (mod n) ou p=1 (mod 2n)
if(N1>1)
congruence_divisors_factorization(power, &N1);

//Limpando cachê de memória
free(exponent_divisors);
                                                                      };



//****************************************************************************************************************************************************
//FIM DO HEADER
#endif
