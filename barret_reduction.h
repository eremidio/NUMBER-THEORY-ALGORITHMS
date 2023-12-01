//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE REDUÇÃO DE BARRET PARA ARITMÉTICA MODULAR

/*
O ALGORITMO DE BARRET É UM ALGORITMO DE REDUÇÃO EXTREMAMENTE EFICIENTE PARA A ARITMÉTICA MODULAR DE NÚMEROS GRANDES QUE USA OPERAÇÕES DE MANIPULAÇÕES DE BITS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Barrett_reduction
                          https://en.algorithmica.org/hpc/arithmetic/division/
                          https://www.nayuki.io/page/barrett-reduction-algorithm
*/

//**********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef BARRET_REDUCTION_H
#define BARRET_REDUCTION_H
#include<stdint.h>
#include<inttypes.h>
#include<math.h>


//**********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t generate_magic_number(uint64_t, int*);
uint64_t barret_reduction(uint64_t, uint64_t);

//**********************************************************************************************************************************************************************
//FUNÇÕES
//Função que determina um númewro mágico m usado no algoritmo de redução de Barret
uint64_t generate_magic_number(uint64_t N, int* bit_shift){
//Procedimenros
//Ajuste de variáveis
(*bit_shift)=log2(N);

//Resultado
return floor(pow(4, (*bit_shift))/N);
                                                         };

//Função que reduz um inteiro a (mod N) usando a redução de Barret
uint64_t barret_reduction(uint64_t a, uint64_t N){
//Variáveis locais
int bit_shift;
uint64_t quotient;
uint64_t m=generate_magic_number(N, &bit_shift);

//Procedimentos
//Ajuste de variáveis
quotient=(a*m)>>(2*bit_shift);
a-=(quotient*N);

//Resultado
if(a>=N)
return (a-N);
else
return a;
                                                 };

//**********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
