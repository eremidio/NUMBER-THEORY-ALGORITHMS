//VAMOS IMPLEMENTAR UMA VERSÃO OTIMIZADA DO ALGORITMO DE FERMAT PARA FATORAR NÚMEROS INTEIROS DE 64 BITS

/*
UM TEOREMA DEVIDO A EULER AFIRMA QUE DADO UM n E a INTEIROS TAL QUE mmc(a,n)=1, ENTÃO a^φ(n)= 1 (mod n), ONDE φ(n) É A FUNÇÃO TOTIENTE DE EULER.
UMA VARIANTE DO ALGORITMO DE FERMAT USA ESTE TEOREMA PARA COMPUTAR FATORES PRIMOS DE UM NÚMERO INTEIRO.

PARA MAIORES INFORMAÇÕES: https://www.researchgate.net/publication/340357758_The_new_integer_factorization_algorithm_based_on_Fermat's_Factorization_Algorithm_and_Euler's_theorem

*/

//******************************************************************************************************************************************************************
//CABEÇALHO
#ifndef FAST_FERMAT_FACTORIZATION_H
#define FAST_FERMAT_FACTORIZATION_H
#include"mod_bin_exponentiation.h"
#include<stdio.h>
#include<math.h>
#include<time.h>

//******************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t modular_inverse(int64_t, int64_t);
int64_t generate_random_number(int64_t);
int64_t euclides_algorithm(int64_t, int64_t);
void fast_fermat_factorization(int64_t);

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

//Funçãoque gera um número aleatório de 64-bits
int64_t generate_random_number(int64_t n){
//Semente para geração de números aleatórios
srand(time(NULL));

//Variáveis locais
int64_t result=2+rand()%(n-3);

//Resultado
return result;

                                         };

//Função que implementa o algoritmo de Euclides 
int64_t euclides_algorithm(int64_t a, int64_t b){
if(b==0)
return a;
else
return euclides_algorithm(b, (a%b));
                                                };

//Função que implementa a variante do algoritmo de Fermat para fatorar números inteiros
void fast_fermat_factorization(int64_t n){
//Variáveis locais
int64_t c, a, s, t, u;
double x, y;
int64_t p, q;

//Procedimentos
//Inicializando variáveis
u=2*ceil(sqrt(n));

c=generate_random_number(n);
while(euclides_algorithm(c, n)!=1)
c=generate_random_number(n);

a=modular_inverse(c, n);
s=pow_mod(c, 2, n);
t=pow_mod(a, (n-u+1), n);

x=u/2.0;
if(t==1)
y=sqrt((x*x)-n);
else
y=0.1;

//Loop principal
while(ceil(y)!=floor(y)){
t*=s;
if(t>n)
t%=n;

u+=2;

if(t==1){
x=u/2.0;
y=sqrt((x*x)-n);
        };
                        };

//Cálculo dos fatores primos
p=(int64_t)(x+y);
q=(int64_t)(x-y);

//Exibindo  o resultado da execução do algoritmo
printf("Fatores de %li encontrados: %li e %li\n", n, p, q);
                                         };


//******************************************************************************************************************************************************************
//FIM DO HEADER
#endif 
