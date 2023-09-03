//VAMOS CRIAR UM PROGAMA QURE IMPLMENTA DUAS ROTINAS PARA GERAÇÃO DE NÚMEROS USANDO RECURSÃO


/*

NÚMEROS PRIMOS PODEM SER GERADOS RECURSIVAMENTE USANDO-SE A SEGUINTES RELAÇÃO RECURSIVA: R(n) = R(n-1)+mdc(n, R(N-1)).
OS CÁLCULOS mdc(n, R(n-1)) EVENTUALEMENTE RESULTARÃO1 OU EN UM FATOR PRIMO. TAL RELAÇÃO É ÚTIL TAMBÉM PARA SE CHECAR A
EXISTÊNCIA DE PRIMOS p, q SATISFAZENDO A RELAÇÃO q=2p-1.

É POSSIVEL TAMBÉM GERAR PRIMOS USANDO A RELAÇÃO DE BENOI-CLOITRE: C(n) = C(n-1)+mmc(n, C(N-1)) E COMPUTANDO
C(n)/C(n-1) -1 QUE SERÁ IGUAL A 1 OU SERÁ PRIMO.

PARA MAIORES INFORMAÇÕES: https://www.youtube.com/watch?v=OpaKpzMFOpg


*/

//**************************************************************************************************************************
//CABEÇALHO
#ifndef RECURSIVE_PRIME_GENERATION_H
#define RECURSIVE_PRIME_GENERATION_H
#include<stdint.h>
#include<stdio.h>

//**************************************************************************************************************************
//FUNÇÕES

//Função que implementa o algoritmo de Euclides para calcular o mdc de dois inteiros
uint64_t gcd(uint64_t a, uint64_t b){
//Procedimentos
if(b==0)
return a;
else
return gcd(b, a%b);
                                    };

//Função que calcula primos recursivamente usando recursão
void recursive_prime_generation(uint64_t seed, uint64_t iterations){
//Variáveis locais
uint64_t counter;//Variável de iteração
uint64_t r0=seed, tester=0;

//Procedimento
//Loop principal usando relação recursiva
for(counter=1; counter<=iterations; ++counter){
if(tester>1)
printf("%lu, ", tester);

tester=gcd(counter, r0);
r0+=tester;
                                              };

printf("...\n");
                                                                   };

//**************************************************************************************************************************
//FIM DO HEADER
#endif
