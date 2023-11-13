//ESTE ARQUIVO CONTÉM FUNÇÕES AUXILIARES USADAS NO ALGORITMO

//*********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef GENERAL_NUMBER_FIELD_SIEVE_AUXILIARY_FUNCTIONS_H
#define GENERAL_NUMBER_FIELD_SIEVE_AUXILIARY_FUNCTIONS_H
#include"mod_bin_exponentiation128.h"
#include<cmath>
#include<stdbool.h>

//*********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void square_root_128(__int128_t&, __int128_t);
__int128_t euclides_algorithm(__int128_t, __int128_t);
bool is_int64_prime(int64_t); 
__int128_t legendre_symbol(__int128_t, __int128_t);
__int128_t pow128(__int128_t, __int128_t);

//*********************************************************************************************************************************************************************
//FUNÇÕES
//Função que calcula a raíz quadrada de um número inteiro ou um limitante inferior e checa se o número em questão é um quadrado perfeito
void square_root_128(__int128_t& square_root, __int128_t number){
if(number<1e10){
//Variáveis locais
__int128_t odd=1;

//Procedimento
square_root=0;

//Loop principal
while(number>0){
number-=odd;
odd+=2;
square_root++;

if(number==0)
return;

               };
//Resultado
return;
               }

//Números grandes
else{
//Variáveis locais
__int128_t attempt=100000;
__int128_t helper;

//Procedimentos
//Determinando um limitante inferior
while((attempt*attempt)>number)
attempt/=10;
while((attempt*attempt)<number)
attempt*=10;

//Ajuste de variáveis
helper=attempt;

//Ajuste do valor da raíz
while(helper>0){
while((attempt*attempt)<number)
attempt+=helper;

if((attempt*attempt)==number){
square_root=attempt;
break;
                             };

if((attempt*attempt)>number){
attempt-=helper;
helper/=10;
                            };
               };
    };
                                                                };

//Função que implementa o algoritmo de Euclides
__int128_t euclides_algorithm(__int128_t a, __int128_t b){
//Resultado
if(b==0)
return a;
else
return euclides_algorithm(b, a%b);
                                                         };



//Função que determina se um inteiro de 64 bits é primo ou não
bool is_int64_prime(int64_t p){
//Casos triviais
if(p<2)
return false;

if(p==2 || p==3)
return true;

if((p%2)==0 || (p%3)==0)
return false;

//Caso geral:
//Variáveis locais
int64_t i, limit=std::sqrt(p);

//Procedimentos
//Loop principal
for(i=5; i<=limit; i+=6){
if((p%i)==0 || (p%(i+2))==0)
return false;
                        };

return true;
                              }; 

//Função que calcula o símbolo de Legendre usando exponenciação binária e o critério de Euler
__int128_t legendre_symbol(__int128_t a, __int128_t p){
return mod_bin_pow(a, ((p-1)/2), p);
                                                      }; 

//Função que calcula uma potência de envolvendo inteiros de 128 bits
__int128_t pow128(__int128_t base, __int128_t power){
//Caso trivial
if(power==0)
return 1;

//Variáveis locais
__int128_t result=1;
__int128_t counter=0;

//Procedimentos
for(; counter<=power; counter++)
result*=base;

//Resultado
return result;
                                                    };

//*********************************************************************************************************************************************************************
//FIM DO HEADER
#endif    
