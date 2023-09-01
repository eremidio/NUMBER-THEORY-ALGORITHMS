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
#include"arithmetic.h"

//*************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t binary_gcd(int64_t , int64_t);

//*************************************************************************************************************************
//FUNÇÕES
//Algoritmo de euclides usando operações binárias
//Usaremos a subtração via operadores bitwise bit_sub() disponível no arquivo arithmetic.h nesta implementação
int64_t binary_gcd(int64_t a, int64_t b){
//Procedimento
//Caso trivial
if(b==a)
return a;

//Invertendo os argumentos da função se a<b
if(a<b)
return binary_gcd(b, a);

//Caso 1: a e b diferentes e ambos pares
if(!(a&1) && !(b&1))
return 2*binary_gcd((a>>1),(b>>1));

//Caso 2: a e b diferentes, a é ímpar e b é par
if((a&1) && !(b&1))
return binary_gcd(a,(b>>1));

//Caso 3: a e b diferentes e ambos ímpares
if((a&1) && (b&1))
return binary_gcd((bit_sub(a, b)>>1), b);

//Caso 4: a e b diferentes, a é par e b é ímpar
if(!(a&1) && (b&1))
return binary_gcd(bit_sub(a, b), b);
                                         };


//*************************************************************************************************************************
//FIM DO HEADER
#endif 
