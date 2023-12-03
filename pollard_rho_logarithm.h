//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE POLLARD ρ PARA O CÁLCULO DE LOGARITMOS DISCRETOS

/*
O ALGORITMO DE POLLARD RHO É UM EFICIENTE E PROBABILÍSTICO ALGORITMO PARA O CÁLCULO DE LOGARITMOS DISCRETOS SIMILAR AO ALGORITMO DE MESMO NOME USADO PARA FATORAR NÚMEROS
INTEIROS.
 
O ALGORITMO RESOLVE O SEGUINTE PROBLEMA SEJA G UM GRUPO DE ORDEM p-1), POR EXEMPLO, INTEIROS A MENOS DE UMA CONGRUÊNCIA MÓDULO p. SEJAM g UM GERADOR DESTE GRUPO E h UM 
ELEMENTO DESTE GRUPO ENTÃO EXISTE UM x TAL QUE g^x=h. PARA COMPUTAR x O ALGORITMO USA UMA FUNÇÃO QUE GERA DUAS TRIPLAS DE SNÚMEROS PSEUDOALEÁTÓRIOS (x1, a1, b1) E (x2, a2, b2) EM UM CONJUNTO FINITO S={0, ..., (p-1)}. SE f FOR UMA FUNÇÃO GERADORA AS SEQUÊNCIAS SÃO ATUALIZADAS USANDO-SE AS REGRAS: (x1, a1, b1) -> f(x1, a1, b1) E
(x2, a2, b2) -> f(x2, a2, b2) -> f²(x2, a2, b2). SE APÓS  UM CERTO NÚMERO DE ITERAÇÕES FOR POSSÍVEL ENCONTRAR VALORES x1=x2 (AS DUAS SEQUÊNCIAS COLIDEM), ENTÃO UMA 
IDENTIDADE DO TIPO (b1-b2) x =(a1-a2) (mod p) É SATISFEITA. TAL EQUAÇÃO É FACILMENTE RESOLVIDA PELO ALGORITMO DE EUCLIDES EXTENDIDO.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm_for_logarithms#Complexity
                          https://www.math.auckland.ac.nz/~sgal018/crypto-book/ch14.pdf

*/

//******************************************************************************************************************************************************************
//CABEÇALHO
#ifndef POLLARD_RHO_LOGARITHM_H
#define POLLARD_RHO_LOGARITHM_H
#include"mod_bin_exponentiation.h"
#include<stdbool.h>
#include<stdio.h>


//******************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t modular_inverse(int64_t, int64_t);
void pseudo_randomwalk(int64_t*, int64_t*, int64_t*, int64_t, int64_t, int64_t);
int64_t pollard_rho_logarithm(int64_t, int64_t , int64_t);

//******************************************************************************************************************************************************************
//FUNÇÕES
//Função que calcula o inverso modular de um número inteiro a (mod n) usando o algoritmo extendido de Euclides
int64_t  modular_inverse(int64_t a, int64_t n){
//Variáveis locais
int64_t  r0,r1, x0, x1, r2, x2;
//Procedimentos 
//Ajuste de variáveis
r0=a;
r1=n;
r2=1;
x0=1;
x1=0;

//Calculando os valores finais dos coeficientes recursivamente
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

//Função que produz triplas ordenadas de números pseudoaleatórios
void pseudo_randomwalk(int64_t* x, int64_t* a, int64_t* b, int64_t n, int64_t g, int64_t h){
//Variáveis locais
int64_t x_=(*x), a_=(*a), b_=(*b); 
int64_t remainder=(x_%3);

//Procedimentos
//Atualização de variáveis
//Caso 1: resto 0
if(remainder==0){
x_=(x_*x_)%(n+1);
a_=(a_*2)%n;
b_=(b_*2)%n;
                };

//Caso 2: resto 1
if(remainder==1){
x_=(x_*g)%(n+1);
a_=(a_+1)%n;
                };

//Caso 3: resto 2
if(remainder==2){
x_=(x_*h)%(n+1);
b_=(b_+1)%n;
                };


(*x)=x_;
(*a)=a_;
(*b)=b_;
                                                                                           };

//Função que implementa o algoritmo de Pollard ρ para o cálculo de logaritmos discretos
int64_t pollard_rho_logarithm(int64_t g, int64_t h, int64_t N){
//Variáveis locais
int64_t a1, b1, x1, a2, b2, x2, n;
int64_t a12, b12, result;

//Procedimentos
//Ajuste de variáveis para a primeira iteração
n=(N-1);
x1=1;
a1=0;
b1=0;
x2=x1;
a2=a1;
b2=b1;

//Loop principal
printf("    x1      a1      b1      x2      a2      b2\n----------------------------------------------------------------\n");
for (int i = 1; i < n; ++i){
pseudo_randomwalk(&x1, &a1, &b1, n, g, h);
pseudo_randomwalk(&x2, &a2, &b2, n, g, h);
pseudo_randomwalk(&x2, &a2, &b2, n, g, h);
printf("%6li %6li %6li %6li %6li %6li\n", x1, a1, b1, x2, a2, b2);

//Condição que determina o fim do Loop principal
if(x1==x2)
break;
                           };

//Condição que detemina se o algoritmo falhou
if((b2%n)==b1){
printf("O algoritmo não encontrou logaritmo de %li (mod %li), na base %li\n", h, N, g);
return 0;
              };

//Ajuste de variáveis
a12=(a2-a1);
while(a12<0)
a12+=n;
b12=(b1-b2);
while(b12<0)
b12+=n;

//Cálculo do resultado
result=(a12*modular_inverse(b12, n))%n;

//Ajuste de resultado
while(mod_bin_pow(g, result, N)!=h){
result/=2;

//Condição que detemina se o algoritmo falhou
if(result==0){
printf("O algoritmo não encontrou logaritmo de %li (mod %li), na base %li\n", h, N, g);
return 0;
             };

                                   };

//Resultado
return result;
                                                              };

//******************************************************************************************************************************************************************
//FIM DO HEADER
#endif
