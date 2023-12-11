/*VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA VARIANTE DO ALGORITMO (p+1) DE WILLWIAMS PARA FATORAR NÚMEROS INTEIROS USANDO CORPOS ALGÉBRICOS NÚMERICOS
NO LUGAR DE SEQUÊNCIAS DE LUCAS*/

/*
O ALGORITMO DE FATORAÇÃO (p+1) PODE SER REEXPRESSO EM TERMOS DE ARITMÉTICA USANDO CORPOS NÚMERICOS QUADRÁTICOS Q(√n)=a+b√n NO LUGAR DE SEQUÊNCIAS DE LUCAS.
ESTE ALGORITMO É PARTICULARMENTE ÚTIL PARA SEMIPRIMOS (PRODUTOS DE DOIS FATORES PRIMOS).
GENERALIZAÇÕES INCLUEM A FATORAÇÃO VIA POLINÔMIOS CICLOTÔMICOS.
PARA MAIORES INFORMAÇÕES: https://www.semanticscholar.org/paper/Factoring-with-cyclotomic-polynomials-Bach-Shallit/b47948d1d665cb8276bc638d5fca6eabd23806c7

*/

//******************************************************************************************************************************************************************
//CABEÇALHO
#ifndef WILLIAM_FACTORIZATION_ALGEBRAIC_H
#define WILLIAM_FACTORIZATION_ALGEBRAIC_H
#include"int128.h"
#include<time.h>
#include<stdio.h>


//******************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void algebraic_multiplication(__int128_t[], __int128_t[], __int128_t[], __int128_t, __int128_t);
void algebraic_exponentiation(__int128_t[], __int128_t[], __int128_t, __int128_t, __int128_t);
void algebraic_rationalization(__int128_t[], __int128_t[], __int128_t, __int128_t);
__int128_t gcd128(__int128_t, __int128_t);
void williams_algebraic_factorization(__int128_t, __int128_t);


//******************************************************************************************************************************************************************
//FUNÇÕES
//Função que executa a multiplicação de números em um corpo algébrico a menos de uma relação de congruência
// z1.z2=(a1.a2+b1.b2.ω²)+(a1.b2+a2.b1)ω=(a1.a2+b1.b2.n)+(a1.b2+a2.b1)ω.
void algebraic_multiplication(__int128_t result[], __int128_t parcel1[], __int128_t parcel2[], __int128_t root_squared, __int128_t number){
//Calculando a 1ª parcela do resultado  
result[0]=(parcel1[0]*parcel2[0])+(parcel1[1]*parcel2[1]*root_squared);

//Ajuste do valor da 1ª parcela  módulo primo congruente 
while(result[0]<0 && abs(result[0])>number)
result[0]=result[0]+number;
if(result[0]>number)
result[0]=(result[0]%number);

//Calculando a 2ª parcela do resultado  
result[1]=(parcel1[0]*parcel2[1])+(parcel1[1]*parcel2[0]);

//Ajuste do valor da 2ª parcela  módulo primo congruente 
while(result[1]<0 && abs(result[1])>number)
result[1]=result[1]+number;
if(result[1]>number)
result[1]=(result[1]%number);
                                                                                                                                          };

//Função que executa a exponenciação de números em um corpo algebrico a menos de uma relação de congruência
void algebraic_exponentiation(__int128_t result[], __int128_t parcel[], __int128_t root_squared, __int128_t exponent, __int128_t number){
//Variáveis locais
__int128_t algebraic_number[2], algebraic_product[2], algebraic_squared[2], temp[2];
__int128_t power=0;

//Procedimentos
//Ajuste de variáveis
algebraic_number[0]=parcel[0];
algebraic_number[1]=parcel[1];

//1ª iteração
algebraic_multiplication(algebraic_squared, algebraic_number, algebraic_number, root_squared, number);
power+=2;

//Ajuste de variáveis
algebraic_product[0]=algebraic_squared[0];
algebraic_product[1]=algebraic_squared[1];

//Loop principal com otimização binária
while(power<exponent){
//Caso 1
if((power*power)<exponent){
algebraic_multiplication(temp, algebraic_product, algebraic_product, root_squared, number);

//Ajuste de variáveis
algebraic_product[0]=temp[0];
algebraic_product[1]=temp[1];

power=power*2;

//TESTE USE UM // APÓS O MESMO
//printf("marco 3\n");

continue;
                          };

//Caso 2
if((power+2)<exponent){
algebraic_multiplication(temp, algebraic_product, algebraic_squared, root_squared, number);

//Ajuste de variáveis
algebraic_product[0]=temp[0];
algebraic_product[1]=temp[1];

power=power+2;

//TESTE USE UM // APÓS O MESMO
//printf("marco 4\n");

continue;
                     };

//Caso 3
algebraic_multiplication(temp, algebraic_product, algebraic_number, root_squared, number);

//Ajuste de variáveis
algebraic_product[0]=temp[0];
algebraic_product[1]=temp[1];

power++;
//TESTE USE UM // APÓS O MESMO
//printf("marco 5\n");

                      };

//Resultado
result[0]=algebraic_product[0]%number;
result[1]=algebraic_product[1]%number;

                                                                                                                                        };

//Função que racionaliza um inteiro algébrico x=t⁺/t, com t=a+b√n  e t⁺=a-b√n 
void algebraic_rationalization(__int128_t result[], __int128_t parcel[], __int128_t root_squared, __int128_t number){
//Variáveis locais
__int128_t numerator[2];
__int128_t denominator;

//Procedimentos
//Cálculo do denominador
denominator=((parcel[0]*parcel[0])-(parcel[1]*parcel[1]*root_squared));
//Cálculo do numerador
numerator[0]=((parcel[0]*parcel[0])+(parcel[1]*parcel[1]*root_squared));
numerator[1]=(-2)*parcel[0]*parcel[1];

//Resultado
result[0]=numerator[0]/denominator;
result[1]=numerator[1]/denominator;
                                                                                                                    };

//Função que implementa o algoritmo de Euclides para inteiros de 128bits
__int128_t gcd128(__int128_t a, __int128_t b){
if(b==0)
return a;
else
return gcd128(b, a%b);
                                             };

//Função que implementa a versão algébrica do algoritmo (p+1)de Williams para fatorar números inteiros
void williams_algebraic_factorization(__int128_t number, __int128_t E){
//Semente para geração de números aléatorios
srand(time(NULL));

//Variáveis locais
__int128_t a, b, d;
__int128_t t[2];
__int128_t x[2];
__int128_t x_powered[2];
__int128_t v, u;
__int128_t factor1, factor2;
int64_t random_number;

//Procedimentos
//Ajuste de variáveis
random_number=rand()%100000000000000000;
a=(random_number*random_number)%number;
random_number=rand()%100000000000000000;
b=(random_number*random_number)%number;
random_number=rand()%100000000000000000;
d=(random_number*random_number)%number;

t[0]=a;
t[1]=b;
algebraic_rationalization(x, t, d, number);

//TESTE USE UM // APÓS O MESMO
//printf("marco 1\n");

//Calculo de x^E (mod N)
algebraic_exponentiation(x_powered, x, E, d, number);

//TESTE USE UM // APÓS O MESMO
//printf("marco 2\n");

//Ajuste de variáveis
u=x_powered[0];
v=x_powered[1];


//Cálculo de fatores primos
factor1=gcd128(gcd128((u-1), v), number);

if(factor1<2 || factor1>(number)){
printf("O algoritmo não encotrou um fator primo do número em questão\n");
return;
                                 };

factor2=(number/factor1);

//Printando o resultado na tela
printf("Resultado da execução do algoritmo:\n");
printf128(number);
printf128(factor1);
printf128(factor2);

                                                                      };



//******************************************************************************************************************************************************************
//FIM DO HEADER
#endif
