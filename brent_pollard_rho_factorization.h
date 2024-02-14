//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA A VARIANTE BRENT DO ALGORITMO DE POLLARD RHO PARA FATORAR NÚMEROS INTEIROS

/*
O ALGORITMO DE BRENT É UMA VARIANTE DO ALGORITMO DE POLLARD RHO PARA FATORAR NÚMEROS INTEIROS. AO PASSO QUE NO ALGORITMO DE POLLARD RHO USA-SE DUAS SEQUÊNCIAS DE
INTEIROS PSEUDOALETÓRIAS x(i) E y(i), DE MODO QUE CICLOS SÃO DETECTADOS VIA mdc(|x(i)-y(i)|, n), ONDE n É O NÚMERO A SER FATORADO, NO ALGORITMO DE BRENT USA-SE
DOIS PONTEIROS QUE SÃO LIMITADOS POR SEQUÊNCIAS DE POTÊNCIAS DE 2. TAL MODIFICAÇÃO NA DETECÇÃO DE CICLOS, OTIMIZA O ALGORITMO ORIGINAL DE POLLARD EM APROXIDAMENTE 25% E
TAMBÉM É ÚTIL EM CERTAS CLASSES DE ALGORITMOS DE GERAÇÃO DE NÚMEROS PSEUALEATÓRIOS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Cycle_detection#Brent.27s_algorithm
                          https://www.connellybarnes.com/documents/factoring.pdf

*/

//********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef BRENT_POLLARD_RHO_FACTORIZATION_H
#define BRENT_POLLARD_RHO_FACTORIZATION_H
#include"int128.h"
#include<stdbool.h>

//********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool power2_checker(__int128_t);
__int128_t euclides_algorithm128(__int128_t, __int128_t);
void brent_pollard_rho_factorization(__int128_t);

//********************************************************************************************************************************************************************
//FUNÇÕES
//Função usada para detectar potências de 2
bool power2_checker(__int128_t x){
//Variáveis locais
__int128_t tester=1;

//Procedimentos
//Loop principal
while(tester<x){
tester<<=1;

if(tester>x)
return false;
               };

return true;
                                 };

//Função que implementa o algoritmo de Euclides
__int128_t euclides_algorithm128(__int128_t a, __int128_t b){
if(b==0)
return a;
else
return euclides_algorithm128(b, (a%b));
                                                            };

//Função que implmenta a variante de Brent do algoritmo de Pollard
void brent_pollard_rho_factorization(__int128_t number){
//Variáveis locais
__int128_t factor, cofactor;
__int128_t xi=2, xm=2;
uint64_t i;

//Procedimentos
//Loop principal
for(i=1;i<UINT64_MAX ; ++i){
//Calculando o valor de xi(n) a partir de  xi(n-1)
xi=((xi*xi)+1)%number;

//Cálculo de possíveis fatores primos do número a ser fatorado
factor=euclides_algorithm128((xi-xm), number);
if(factor>1){
cofactor=number/factor;
break;
            };

//Atualizando variuáveis para o próximo ciclo
if(power2_checker(i)==true)
xm=xi;

                           };

//Printando o resultadoda execução do algoritmo na tela
printf("\nNúmero a ser fatorado:\n");
printf128(number);
printf("Fatores encontrados:\n");
printf128(factor);
printf128(cofactor);
                                                       };




//********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
