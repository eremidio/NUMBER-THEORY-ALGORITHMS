//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ROTINAS PARA SE CALCULAR RAÍZES PRIMITIVAS DE UM NÚMERO INTEIRO n

/*
DADO UM NÚMER INTEIRO n UM NÚMERO INTEIRO m É UMA RAÍZ PRIMITIVA DE n SE TODOS OS INTEIROS COPRIMOS a COM n NO INTERVALO
(1, n-1) SÃO CONGRUENTES A UM DADA POTÊNCIA DE m.
EXEMPLO: SEJA n=5, COPRIMOS COM ELE SÃO {2, 3, 4}.
TEMOS:
2^1 = 2 (mod 5)
2^2 = 4 (mod 5)
2^3 = 3 (mod 5)
2^4 = 1 (mod 5)
2^5 = 2 (mod 5)
2^6 = 4 (mod 5)
2^7 = 3 (mod 5)
2^8 = 1 (mod 5)
2^9 = 2 (mod 5)
2^10 = 4 (mod 5)

NÚMEROS INTEIROS MÓDULO n FORMAM UM GRUPO CHAMADO GRUPO DA UNIDADES DE n CONSIDERANDO A OPERAÇÃO DE MULTIPLICAÇÃO.  ESTE GRUPO É CÍCLICO SE E SOMENTE n FOR: 1, 2, 4, p^k, OU 2p^k, COM p PRIMO E k INTEIRO. TAL OBSERVAÇÃO É UM INDÍCIO DOS NÚMEROS QUE
POSSUEM RAÍZES PRIMITIVAS.

NÃO EXISTE  UM ALGORITMO COMPROVADAMENTE EFICIENTE PARA O CÁLCULO DE UMA RAÍZ PRIMITIVA. PORÉM AS SEGUINTES ABORDAGEM SÃO EFICAZES:
1. PARA TESTAR UM CANDIDATO m A RAÍZ PRIMITIVA DE n PODEMOS USAR O FATO DE QUE A ORDEM MULTIPLICATIVA DE m (MENOR
EXPOENTE k TAL QUE m^k=1 (mod n)) É IGUAL A φ(n)=λ(n) (λ(n) É FUNÇÃO TOTIENTE REDUZIDA OU FUNÇÃO LAMBDA DE CARMICHAEL).
2. PODEMOS TAMBÉM COMPUTAR m^(φ(n)/p) PARA TODOS OS FATORES PRIMOS p DE φ(n), SE PARA TODO p O RESULTADO FOR DIFERENTE DE 1 UMA
RAÍZ PRIMITIVA DE n FOI ENCONTRADA.

O NÚMERO DE RAÍZES PRIMITIVAS DE UM NÚMERO n É φ(φ(n)). PARA UM PRIMO p SUA SOMA É IGUAL A FUNÇÃO DE MÖBIUS μ(p-1) E SEU
PRODUTO É IGUAL A 1 (mod p). SE m FOR UMA RAÍZ DE PRIMITIVA DE p TAMBÉM O É DE p^k PARA k INTEIRO A MENOS QUE:
m^(p-1)= 1 (mod p²) NESTE CASO p+m É. SE m FOR UMA RAÍZ DE PRIMITIVA DE p^k TAMBÉM O É DE p, ALÉM DISSO m OU m+p É UMA RAÍZ
PRIMITIVA DE 2(p^k). PARA p^k A SEGUINTE FÓRMULA É ÚTIL φ(p^k)=(p-1)p^(k-1).

RAÍZES PRIMITIVAS SÃO DE GRANDE INTERESSE TEÓRICO E PARA ALGORITMOS DE CRIPTOGRAFIA.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Primitive_root_modulo_n
                          https://en.wikipedia.org/wiki/Carmichael_function

*/

//*************************************************************************************************************************
//CABEÇALHO
#ifndef PRIMITIVE_ROOT_H
#define PRIMITIVE_ROOT_H
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include<math.h>
#include"mod_bin_exponentiation.h"
#include"euler_totient_function.h"

//*************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool primitive_root_checker(uint64_t);
void primitive_root(uint64_t);

//*************************************************************************************************************************
//FUNÇÕES
//Função que checa se um inteiro posui raízes primitivas
bool primitive_root_checker(uint64_t n){
//Casos triviais
if(n==1 || n==2 || n==4)
return true;
if((n%8)==0)
return false;

//Caso geral: n é da forma 2(p^k) ou p^k
//Variáveis locais
uint64_t odd_prime_factors=0;

//Eliminando o fator 2
if(n%2==0)
n/=2;

//Testando por fatores primos ímpares (um número não pode ser divisível por dois ímpares diferentes)
if(n%3==0)
odd_prime_factors=1;

//Loop principal com otimização 6k+1
for(uint64_t i=5; i<(sqrt(n)+10); i+=6){
if((n%i)==0 || (n%(i+2))==0){
odd_prime_factors++;
if(odd_prime_factors>1)
return false;
                            };
                                       };
return true;
                                       };

//Função que calcula as raízes primitivas de um número inteiro
void primitive_root(uint64_t n){
//Checando se o número em questão possui raízes primitivas
bool check=primitive_root_checker(n);
if(check==false){
printf("O número em questão não possui raízes primitivas!\n");
return;
                };

//Variáveis locais 
uint64_t validator = euler_totient_function(n);
uint64_t i, j;//Variável de iteração
uint64_t root_number=0;
uint64_t* primitive_root_array=NULL;

//Procedimentos iterando sobre possíveis candidatos (usaremos o algoritmo de Euclides definido em euler_totient_function.h)
for(i=1; i<n; ++i){
//Apenas números coprimos podem ser raízes primitivas
if(gcd_euclides(i, n)>1)
continue;

//Testando possíveis candidatos
for(j=1; j<(validator+2); ++j){
if(mod_bin_pow(i, j, n)==1)
break;
                              };
if(j==validator){
root_number++;
primitive_root_array=(uint64_t*)realloc(primitive_root_array, root_number*sizeof(uint64_t));
primitive_root_array[root_number-1]=i;
                };

                  };

//Exibindo as raízes primitivas encontradas
printf("Raízes primitivas de %lu: ", n);
for(uint64_t k=0; k<root_number; ++k)
printf("%lu, ", primitive_root_array[k]);
printf("...\n");

//Limpando o cachê de memoria
free(primitive_root_array);                                     

                               };

//*************************************************************************************************************************
//FIM DO HEADER
#endif
