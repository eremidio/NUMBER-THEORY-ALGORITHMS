//ESTE ARQUIVO CONTERÁ UMA IMPLEMENTAÇÃO DA PENEIRA DE ATKINS, UM DOS ALGORITMOS MAIS EFICIENTES PARA SE CALCULAR NÚMEROS PRIMOS

/*
O ALGORITMO DE ATKIN USA FORMAS QUADRÁTICAS PARA CALCULAR NÚMEROS PRIMOS.
OS SEGUINTES TEOREMAS PROVADOS NO ARTIGO ORIGINAL DE 2003 SÃO USADOS:
TEOREMA 1: SEJA n UM NATURAL , TAL QUE n≡ 1, 13, 17, 29, 37, 41, 49, 53 mod(60); ISTO É, n≡1 mod(4).
ENTÃO n É PRIMO SE E SOMENTE SE O NÚMERO SOLUÇÕES DE 4x²+y²=n FOR ÍMPAR E NÃO FOR UM QUADRADO PERFEITO.

TEOREMA 2: SEJA n UM NATURAL , TAL QUE n≡ 7, 19, 31, 43 mod(60); ISTO É, n≡1 mod(6).
ENTÃO n É PRIMO SE E SOMENTE SE O NÚMERO SOLUÇÕES DE 3x²+y²=n FOR ÍMPAR E NÃO FOR UM QUADRADO PERFEITO.

TEOREMA 3: SEJA n UM NATURAL , TAL QUE n≡ 11, 23, 47, 59 mod(60); ISTO É, n≡11 mod(12).
ENTÃO n É PRIMO SE E SOMENTE SE O NÚMERO SOLUÇÕES DE 3x²-y²=n FOR ÍMPAR E NÃO FOR UM QUADRADO PERFEITO.

O ALGORITMO É EXECUTADO NAS SEGUINTES ETAPAS:
1. UM ARRAY DE BOOLEANOS É INDEXADO POR UM LIMITE ESPECIFICADO PELO USUÁRIO.
2. INICIALMENTE TODOS OS ELEMENTOS DESTE ARRAY SÃO INSTANCIADOS COMO FALSO.
3. PARA TODOS OS INDEXES SUPERIORES A 60 A CONGRUÊNCIA POR 60 É COMPUTADA.
4. CASO O RESULTADO DA ETAPA SEJA 2, 3, 5 (FATORES PRIMOS DE 60), O NÚMERO É MARCADO COMO NÃO PRIMO. 
5. CASO O RESULTADO DA ETAPA 3 SEJA: 1, 7, 11, 13, 17, 23, 29, 31, 37, 43, 47, 49, 53, 59. É CHECADO SE O INDEX EM QUESTÃO SATIFAZ AS CONSDIÇÕES DOS TEOREMAS CITADOS ACIMA.
6. INDEXES SATISFAZENDO A CONDIÇÃO DOS TEOREMAS ACIMA SÃO MARCADOS COMO PRIMOS.

*/

//**********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef ATKIN_SIEVE_H
#define ATKIN_SIEVE_H
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

//CONSTANTES GLOBAIS
#define MAX_VALUES 8000000 //valor limite determinado pela memória RAM da máquina em estocar um array de booleanos

//**********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void atkin_sieve(uint64_t);

//**********************************************************************************************************************************************************************
//FUNÇÕES
//Função que implementa a peneirade Atkin para computar números primos até um determinado valor
void atkin_sieve(uint64_t limit){

//Variáveis locais
bool number_array[limit+1];
uint64_t n, x, y;


//Procedimentos
//2,3,5 são marcados comos primos
if(limit>=2)
number_array[2]=true;
if(limit>=3)
number_array[3]=true;
if(limit>=5)
number_array[5]=true;


//Loop principal: computando soluções das formas quadráticas 4x²+y², 3x²+y² e 3x²-y² e flipando as  repetivas entradas se n=1 (mod 4), 1 (mod 6), 11 (mod 12)
for(x=1; (x*x)<=limit; x++){
for(y=1; (y*y)<=limit; y++){

//Caso 1: n=1 (mod 4)
n=(4*x*x)+(y*y);

if(n<=limit && ((n%12)==1 || (n%12)==5))
number_array[n]^=true;
                       
//Caso 2: n=1 (mod 6)
n=(3*x*x)+(y*y);

if(n<=limit && (n%12)==7)
number_array[n]^=true;



//Caso 3: n=11 (mod 12)
n=(3*x*x)-(y*y);

if(n<=limit && x>y && (n%12)==11)
number_array[n]^=true;

                           };
                           };


//Marcando números com fatores primos repetidos como não primos
for(n=5; (n*n)<=limit; n++){

if(number_array[n]==true){
for(x=(n*n); x<=limit; x+=(n*n))
number_array[x]=false;
                         };


                          };


//Exibindo números primos na tela
printf("Eis a lista de primos até %lu:\n", limit);

for(n=0; n<=limit; n++){
//Marcando multiplos de 2,3,5 como não primos
if(n>=6 && ((n%2)==0 || (n%3)==0 || (n%5)==0))
number_array[n]=false;


if(number_array[n])
printf("%lu, ", n);
                       };

printf("...\n");

                                };



//**********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
