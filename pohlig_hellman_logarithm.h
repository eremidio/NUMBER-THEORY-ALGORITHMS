//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE POHLIG HELLMAN PARA O CÁLCULO DE LOGARITMO DISCRETO

/*
DADO UM NÚMERO INTEIRO, UM TEOREMA GARANTE QUE O MESMO POSSUI UMA EXPANSÃO ÚNICA EM POTÊNCIA DE FATORES PRIMOS. O ALGORITMO DE POHLIG-HELLMAN É USADO PARA CALCULAR 
LOGARITMOS DISCRETOS NOS CASOS EM QUE A ORDEM DO GRUPO CÍCLICO EM QUESTÃO É COMPLETAMENTE FATORADA EM RELAÇÃO A UMA PEQUENA BASE DE NÚMEROS PRIMOS. O ALGORITMO DE
POHLIG-HELLMAN PERMITE COMPUTAR A ORDEM DE VÁRIOS SUBGRUPOS CÍCLICOS DE ORDEM p(i)^k(i), ONDE p(i) É UM FATOR PRIMO DA ORDEM n DO GRUPO EM QUESTÃO. MEDIANTE UMA
EXPANSÃO DO VALOR DO LOGARITMO DISCRETO EM POTÊNCIAS DE p(i). O RESULTADO PARA O GRUPO ORIGINAL É RECUPERADO VIA TEOREMA DO RESÍDUO CHINÊS.

PARA MAIORES INFORMAÇÕES: https://risencrypto.github.io/PohligHellman/
                          https://en.wikipedia.org/wiki/Pohlig–Hellman_algorithm
                          https://www-ee.stanford.edu/~hellman/publications/28.pdf
*/

/*
Nota: Por questão de simplicidade não vamos implementar a formulação mais geral deste algoritmo que envolve a decomposição da ordem N do grupo cíclico em questão e a
recombinação dos resultados individuais via teorema de resíduo chinês. Se g e h são geradores e logaritmandos do grupo cíclico G de ordem N, para o subgrupo G(i) de
ordem N/(p(i)^e(i)) o logaritmo discreto é computado como g(i)^x(i)=h(i), com g(i)=g^(N/(p(i)^e(i))) e h(i)=h^(N/(p(i)^e(i))).
Gera-se um conjunto de relações x(i)=x [mod p(i)^e(i)] que resolvidas vias teorema de resíduo chinês retorna o resultado original de g^x=h.
Este procedimento rapidamente se torna dispendioso para uma workstation simples.
*/

//*******************************************************************************************************************************************************************
//CABEÇALHO
#ifndef POHLIG_HELLMAN_LOGARITHM_H
#define POHLIG_HELLMAN_LOGARITHM_H
#include"mod_bin_exponentiation.h"

//*******************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t modular_inverse(int64_t, int64_t);
int64_t trial_multiplication(int64_t, int64_t, int64_t);
int64_t pohlig_hellman_logarithm_prime_order(int64_t, int64_t, int64_t, int64_t);

//*******************************************************************************************************************************************************************
//FUNÇÕES AUXIARES
//Função que calcula o inverso modular de um número inteiro a (mod n) usando o algoritmo extendido de euclides
int64_t modular_inverse(int64_t a, int64_t n){
//Variáveis locais
int64_t  r0,r1, x0, x1, r2, x2;
//Procedimentos 
//Ajuste de variáveis
r0=a;
r1=n;
r2=1;
x0=1;
x1=0;

//Calculando os valores finais coeficientes recursivamente
while(r2>0){
int64_t quotient= r0/r1;
r2=r0-quotient*r1;
x2=x0-quotient*x1;

//Atualizando variáveis para a próxima iteração
if(r2>0){
r0=r1;
r1=r2;
x0=x1;
x1=x2;
        };
            };

//Resultado
if(x1<0)
return(x1+n);
else
return x1;
                                             };


//*******************************************************************************************************************************************************************
//FUNÇÕES 
//Função que calcula um logaritmo discreto por tentativa e erro usando aritmética modular
int64_t trial_multiplication(int64_t g, int64_t h, int64_t N){
//Variáveis locais
int64_t i;

//Procedimentos
//Loop principal
for(i=1; i<(h*10000000); i++){
if(mod_bin_pow(g, i, N)==h)
return i;
                             };
//Caso de falha
return i;


                                                             };

//Função que implementa o algoritmo de Pohlig-Hellman para um grupo cuja ordem é uma potência de um primo (p^e)
int64_t pohlig_hellman_logarithm_prime_order(int64_t g, int64_t h, int64_t p, int64_t e){
//Variáveis locais
int64_t N=bin_pow(p, e);
int64_t gamma=(g, (N/e), N);
int64_t hk, dk, k=0, temp;
int64_t x1=0, x2;

//Procedimentos
//1ª iteração
hk=mod_bin_pow(h, (N/e), N);
dk=trial_multiplication(gamma, hk, N);
x2=dk;
x1=x2;//Atualizando variável para a proxima iteração

//Demais iterações
for(k=1; k<e; k++){
temp=modular_inverse(bin_pow(g, x1), N)*h;
temp%=N;
hk=mod_bin_pow(temp, ((N/e)-k), N);
dk=trial_multiplication(gamma, hk, N);
x2=x1+(bin_pow(p,k)*dk);

//Atualizando varáveis para a próxima iteração
x1=x2;
                  };

//Resultado
return x2;
                                                                                        };

//*******************************************************************************************************************************************************************
//FIM DO HEADER
#endif

