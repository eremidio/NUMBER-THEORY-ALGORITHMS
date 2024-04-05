//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DA PENEIRA LINEAR PARA FATORAR NÚMEROS INTEIROS

/*
O ALGORITMO DA PENEIRA LINEAR CONSISTE NO USO DIRETO DO ALGORITMO DA PENEIRA DE ERATÓSTENES PARA FATORAR NÚMEROS. 
A IDEIA DO ALGORITMO É USAR O ALGORITMO DA PENEIRA DE ERATÓSTENES PARA SE CALCULAR O MENOR FATOR PRIMO DENTRO DE UM CERTO LIMITE.
UMA FATORAÇÃO DIRETA DO NÚMERO EM QUESTÃO É FACILMENTE OBTIDA DIVIDINDO-SE O NÚMERO EM QUESTÃO PELO SEU MENOR FATOR PRIMO, ATÉ 
UM NÚMERO PRIMO SEJA ENCONTRADO.

O ALGORITMO É EXTREMAMENTE EFICIENTE QUANDO MÚLTIPLAS FATORAÇÕES SÃO REQUERIDAS

PARA MAIORES INFORMAÇÕES: https://cp-algorithms.web.app/algebra/prime-sieve-linear.html

*/ 


//********************************************************************************************************************************
//CABEÇALHO
#ifndef LINEAR_SIEVE_FACTORIZATION_H
#define LINEAR_SIEVE_FACTORIZATION_H
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<assert.h>


//********************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void setup_sieve(int32_t[], int32_t);
void find_factorization(int32_t[], int32_t);
void linear_sieve_factorization(int32_t);

//********************************************************************************************************************************
//FUNÇÕES

//Função que usa o algoritmo da peneira de Eratóstenes para construir uma peneira de menores fatores primos de números inteiros
void setup_sieve(int32_t prime_factor_array[], int32_t bound){
//Variáveis 
int32_t prime, i;

//Procedimentos
//Inicializando o array de números inteiros
for(i=0; i<bound; ++i)
prime_factor_array[i]=i;

//Aplicando o algoritmo de Eratóstenes para construir a lista de menores fatores primos
for(prime=2; (prime*prime)<bound; prime++){

for(i=(prime*prime); i<bound; i+=prime){
if(prime_factor_array[i]==i)
prime_factor_array[i]=prime;
                                       };


                                          };

                                                             };




//Função que determina uma fatoração de um número inteiro usando uma lista de menores fatores primos de números inteiros
void find_factorization(int32_t prime_factor_array[], int32_t number){
//Variáveis locais
int32_t divisor;

//Procedimento
//Busca recursiva por fatores primos
printf("Eis a lista de fatores primos de %i: ", number);

//Loop principal
while(1){


//Condição de primalidade: fim do loop
if(number==prime_factor_array[number]){
printf("%i, ...\n", number);
break;
                                      };


//Fatoração
divisor=prime_factor_array[number];
printf("%i, ", divisor);
number/=divisor;

        };

                                                                     };



//Algoritmo de fatoração via peneira de Eratóstenes linear
void linear_sieve_factorization(int32_t bound){

//Varipáveis locais 
int32_t number;
int32_t* number_array=(int32_t*)malloc(bound*sizeof(int32_t));


//Procedimentos
//Preparando a lista de menores fatores primos
setup_sieve(number_array, bound);

//Loop principal
while(1){

//Recebendo input do usuário
printf("Número a ser fatorado (digite 0 para encerrar): ");

if(scanf("%i", &number)!=1 || number>bound){
printf("Valor inválido!\n");
continue;
                                            };


//Fim do algoritmo
if(number==0)
break;


//Fatorando o número em questão
find_factorization(number_array, number);

        };




//Limpando o cachê de memória
free(number_array);
                                              };


//********************************************************************************************************************************
//FIM DO HEADER
#endif
