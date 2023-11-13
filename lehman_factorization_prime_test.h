//VAMOS CRIAR UM PROGRAMA QUE IMPLMENTA O TESTE DE PRIMALIDADEDE DE LEHMAN

/*
O TESTE DE LEHMAN É UM ALGORITMO EXTREMAMENTE SIMPLES QUE PROVÊ UMA FATORAÇÃO DE UM INTEIRO OU DETERMINA SE O MESMO É PRIMO. O ALGORITMO  EM QUESTÃO É UM 
APRIMORAMENTO DO TESTE DE DIVISÃO POR TENTATIVA E ERRO.

*/ 

//****************************************************************************************************************************************************************.
//CABEÇALHO
#ifndef LEHMAN_FACTORIZATION_PRIME_TEST_H
#define LEHMAN_FACTORIZATION_PRIME_TEST_H
#include"gcd_euclides_fast.h"
#include<math.h>
#include<stdint.h>
#include<stdbool.h>
#include<stdio.h>


//****************************************************************************************************************************************************************.
//DECLARAÇÃO DE FUNÇÕES
bool is_perfect_square(uint64_t*, uint64_t);
bool trial_division(uint64_t, uint64_t);
void lehman_factorization_prime_test(uint64_t);


//****************************************************************************************************************************************************************.
//FUNÇÕES
//Função que calcula araíz quadrada deum inteiro e retorna se o número em questão é um quadrado perfeito
bool is_perfect_square(uint64_t* sqrt_n, uint64_t n){
//Variáveis locais
uint64_t odd=1;

//Procedimentos
//Ajuste de variáveis
*sqrt_n=0;

//Loop principal
while(n>0){
n-=odd;
(*sqrt_n)++;
odd+=2;

if(n<0)
return false;
          };

return true;
   
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

//Caso o número não passe no teste acima ele é o produto de no máximo dois fatores primos
return false;
   
                                               };

//Função que determina fatores primos de um número ou determina se ele é primo
void lehman_factorization_prime_test(uint64_t n){
//Passo 1: busca por fatores primos até n^(1/3)
//Variáveis locais
uint64_t smoothness=cbrt(n);
//Procedimentos
//Teste de divisão
if(trial_division(n,smoothness)==true)
return;

//Passo 2: cálculo de fatores primos usando formas quadráticas
//Variáveis locais
uint64_t a, b, c, k, r, m;
uint64_t factor1=0, factor2=0;


//Procedimentos 
//Loop principal
for(k=0; k<(smoothness+2); ++k){
//Condição que n seja primo
if(k>smoothness){
printf("%lu é primo.\n", n);
return;
                };

//Definindo os parâmetros r, m
if((k%2)==0){
r=1;
m=2;
            }
else{
m=4;
r=(n+k);
    };

//Loop secundário
for(a=(4*k*n); a<=((4*k*n)+(smoothness*smoothness)); ++a){
if(a!=(r%m))
continue;

c=((a*a)-(4*k*n));
if(is_perfect_square(&b, c)==true){
factor1=binary_gcd((a+b), n);
factor2=n/factor1;
if(factor1>1){
printf("Fatores de %lu encontrados:m %lu e %lu\n", n, factor1, factor2);
return;
             };
                                  };

                                                         };

                               };

                                                };


//****************************************************************************************************************************************************************.
//FIM DO HEADER
#endif
