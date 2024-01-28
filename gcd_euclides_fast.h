//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UM ALGORITMO DE EUCLIDES USANDO OPERADORES BITWISE  

/*
O ALGORITMO DE EUCLIDES PODE SER OTIMIZADO BASEANDO-SE NAS SEGUINTES PROPOSIÇÕES FACILMENTE DEMONSTRÁVEIS:
1. SE a E b SÃO AMBOS PARES mdc(a, b) = 2.mdc(a/2, b/2)
2. SE a FOR ÍMPAR E b FOR PAR mdc(a, b) = mdc(a, b/2)
3. SE a E b SÃO AMBOS ÍMPARES mdc(a, b) = 2.mdc((a-b)/2, b)

PARA MAIORES INFORMAÇÕES: https://bjpcjp.github.io/pdfs/math/number-theory-ITA.pdf

*/


//*************************************************************************************************************************
//CABEÇALHO
#ifndef BINARY_GCD_H
#define BINARY_GCD_H
#include<stdint.h>

//*************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t fast_euclides_algorithm(uint64_t , uint64_t);

//*************************************************************************************************************************
//FUNÇÕES
//Algoritmo de euclides usando operações binárias
//Algoritmo de Euclides otimizado
uint64_t fast_euclides_algorithm(uint64_t a, uint64_t b){
//Procedimentos
//Caso trivial
if(b==a)
return a;

//Invertendo os argumentos da função se a<b
if(a<b)
return fast_euclides_algorithm(b, a);

//Recursão
//Caso 1: ambos pares
if(!(a&1) && !(b&1))
return 2*fast_euclides_algorithm((a>>1), (b>>1));
//Caso 2: ambos ímpares
if((a&1) && (b&1))
return fast_euclides_algorithm(((a-b)>>1), b);
//Caso 3: a ímpar e b par
if((a&1) && !(b&1))
return fast_euclides_algorithm(a, (b>>1));
//Caso 4: a par e b ímpar
if(!(a&1) && (b&1))
return fast_euclides_algorithm((a>>1), b);

                                                        };


//*************************************************************************************************************************
//FIM DO HEADER
#endif 
