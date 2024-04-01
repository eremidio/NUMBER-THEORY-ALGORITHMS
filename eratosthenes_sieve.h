//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA A PENEIRA DE ERATÓSTENES PARA CALCULAR NÚMEROS PRIMOS

/*
A PENEIRA DE ERATÓSTENES ESTÁ ENTRE OS MAIS ANTIGOS E MAIS EFICIENTES ALGORITMOS PARA GERAÇÃO DE NÚMEROS PRIMOS.

NESTE ALGORITMO INICIALMENTE UMA LISTA DE NÚMEROS CONTENDO OS NÚMEROS DE 2 ATÉ UM DADO LIMITE n SÃO MARCADOS COMO PRIMOS. COMEÇANDO A PARTIR DO 2 QUE É TOMADO PRIMO,
TODOS OS MÚLTIPLOS DO NÚMERO NÚMERO DA LISTA SÃO DESCARTADOS. TAL PROCEDIMENTO É REPETIDO ATÉ QUE O VALOR MARCADO COMO PRIMO SEJA SUPERIOR A n^(1/2). TODOS OS ELEMENTOS
RESTANTES NA LISTA CONTEMPLAM OS NÚMEROS PRIMOS ATÉ O VALOR LIMITE.

ALGORITMOS MAIS RECENTES PARA GERAÇÃO DE PRIMOS COMO A PENEIRA DE PRITCHARD, A PENEIRA DE EULER, O ALGORITMO DE DIJKSTRA, ENTRE OUTROS SÃO VARIANTES DESTE ALGORITMOS.
USAREMOS UMA OTIMIZAÇÃO DO TIPO 30k+r.

PARA MAIORES INFORMAÇÕES: https://palak001.medium.com/sieve-of-eratosthenes-b91d3900d72c
                          https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes

*/

//***************************************************************************************************************************************
//CABEÇALHO
#ifndef ERATOSTHENES_SIEVE_H
#define ERATOSTHENES_SIEVE_H
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>


//***************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void eratosthenes_sieve(uint64_t);

//***************************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo da peneira Eratóstenes para computar números primos usando uma otimização do tipo 30k+r
void eratosthenes_sieve(uint64_t limit){
//Variáveis locais
uint64_t x=0, y=0, n=0, marker=0;
const int prime_seed[10]={2,3,5,7,11,13,17,19,23,29};//Primos inferiores a 30
const int remainder_seed[8]={1,7,11,13,17,19,23,29};//Possíveis resíduos módulo 30 de um número primo superior a 30
bool* number_array=(bool*)malloc((limit+1)*sizeof(bool));


//Procedimentos
//Marcando os primos na lista inferiores a 30
for(x=0; x<10; x++){

marker=prime_seed[x];
number_array[marker]=true;

                  };

if(limit<=30)
goto output_primes;


//Inicializando os membros da lista usando uma roda 30k+r:
for(x=1;; x++){


for(y=0;y<8; y++){

marker=30*x+remainder_seed[y];
number_array[marker]=true;

if(marker>limit)
break;
                 };

if(marker>limit)
break;
              };

//Descartando múltiplos de primos até a raíz quadrada do limite superior
for(x=7; (x*x)<=limit; x+=2){

if(number_array[x]==true){

for(y=(x*x); y<=limit; y+=x)
number_array[y]=false;


                        };

                           };


//Registrando os números primos computados
output_primes:
printf("Eis a lista de números primos até %lu:\n", limit);

for(n=0; n<=limit; n++){

if(number_array[n]==true)
printf("%lu, ", n);
                       };

printf("...\n");


//Limpando o cachê de memória
free(number_array);
                                       };

//***************************************************************************************************************************************
//FIMDO HEADER
#endif
