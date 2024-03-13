//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UM EFICIENTE ALGORITMO  PARA MULTIPLICAÇÃO DE INTEIROS DE 128 BITS USANDO OPERADORES BITWISE 



//****************************************************************************************************************************************
//CABEÇALHO
#ifndef BINARY_MULTIPLICATION_H
#define BINARY_MULTIPLICATION_H
#include"int128.h"



//****************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
__int128_t odd_multiplication(__int128_t,__int128_t);
__int128_t binary_multiplication(__int128_t,__int128_t);


//****************************************************************************************************************************************
//FUNÇÕES
//Função que multiplica dois inteiros ímpares de 128 bits
__int128_t odd_multiplication(__int128_t a, __int128_t b){

//Variáveis locais
__int128_t result = 0;
__int128_t mask = 1;


//Procedimentos 
//Loop principal
while(b>0){

if(b&1)
result += (a << mask);

mask++;
b>>= 1;
          };

//Resultado
return result;
                                                         };


//Função para multiplicação de inteiros de 128 bits usando apenas operações de manipulação de bits

__int128_t binary_multiplication(__int128_t p, __int128_t q){

//Variáveis locais
__int128_t even_counter=0;
__int128_t result;



//Procedimentos
//Redução do problema a multiplicação de dois inteiros ímpares
while(!(p&1)){
p>>=1;
even_counter++;
             };


while(!(q&1)){
q>>=1;
even_counter++;
             };


//TESTE USE UM /**/ APÓS O MESMO
/*
printf("even_counter:");
printf128(even_counter);
printf("p:");
printf128(p);
printf("q:");
printf128(q);
*/



//Resultado
if(even_counter == 0)
result = odd_multiplication(p, q) >> 1;

else
result = odd_multiplication(p, q) << (even_counter-1);

return result;
                                                            };


//****************************************************************************************************************************************
//FIM DO CABEÇALHO
#endif
