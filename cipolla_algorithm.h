//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE CIPOLLA PARA ENCONTRAR RAÍZES QUADRADAS CONGRUENTE MÓDULO UM NÚMERO PRIMO

/*
O ALGORITMO DE CIPOLLA É UM ALGORITMO EFICIENTE PARA RESOLVER EQUAÇÕES DO TIPO: x² = N (mod p), COM p PRIMO. ESTE ALGORITMO USA ARITMÉTICA BÁSICA EM CORPOS NÚMERICOS 
ALGÉBRICOS Q(√n), COM ELEMENTOS z=(a+b√n) (n>0 OU n<0). USANDO A NOTAÇÃO ω=√n, TEMOS PARA z1=a1+b1ω e z2=a2+b2ω  AS SEGUINTES OPERAÇÕES:
z1+z2=(a1+a2)+(b1+b2)ω e z1.z2=(a1.a2+b1.b2.ω²)+(a1.b2+a2.b1)ω=(a1.a2+b1.b2.n)+(a1.b2+a2.b1)ω.

NESTE ALGORITMO A ARIMÉTICA É FEITA SOBRE O CORPO FINITO F(p), INTEIROS A MENOS DE UMA CONGRUÊNCIA MÓDULO p.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Cipolla%27s_algorithm

*/


//*******************************************************************************************************************************************************************
//CABEÇALHO
#ifndef CIPOLLA_ALGORITHM_H
#define CIPOLLA_ALGORITHM_H
#include"mod_bin_exponentiation.h"
#include<stdio.h>
#include<math.h>

//*******************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t legendre_symbol(int64_t, int64_t);
void algebraic_multiplication(int64_t[], int64_t[], int64_t[], int64_t, int64_t);
int64_t cipolla_algorithm(int64_t, int64_t);

//*******************************************************************************************************************************************************************
//FUNÇÕES
//Função que calcula o símbolo de Legendre usandoo critério de Euler
int64_t legendre_symbol(int64_t a, int64_t p){
//Variáveis locais
uint64_t a_=a;
uint64_t p_=p;

//Resultado
return mod_bin_pow(a_, ((p_-1)/2), p_);
                                             };

//Função que executa a multiplicação de números em um corpo algebrico a menos de uma relação de congruência
// z1.z2=(a1.a2+b1.b2.ω²)+(a1.b2+a2.b1)ω=(a1.a2+b1.b2.n)+(a1.b2+a2.b1)ω.
void algebraic_multiplication(int64_t result[], int64_t parcel1[], int64_t parcel2[], int64_t root_squared, int64_t prime){
//Calculando a 1ª parcela do resultado  
result[0]=(parcel1[0]*parcel2[0])+(parcel1[1]*parcel2[1]*root_squared);

//Ajuste do valor da 1ª parcela  módulo primo congruente 
while(result[0]<0 && abs(result[0])>prime)
result[0]=result[0]+prime;
if(result[0]>prime)
result[0]=(result[0]%prime);

//Calculando a 2ª parcela do resultado  
result[1]=(parcel1[0]*parcel2[1])+(parcel1[1]*parcel2[0]);

//Ajuste do valor da 2ª parcela módulo primo congruente 
while(result[1]<0 && abs(result[1])>prime)
result[1]=result[1]+prime;
if(result[1]>prime)
result[1]=(result[1]%prime);
                                                                                                                          };

//Função que implementa o algoritmo de Cipolla
int64_t cipolla_algorithm(int64_t n, int64_t prime){

//Variáveis locais
int64_t a, tester, root;
int64_t max_power=((prime+1)/2);
int64_t power=0;
int64_t algebraic_number[2], algebraic_product[2], algebraic_squared[2], temp[2];

//Procedimento
//Seleção do parâmetro a tal que (a²-n|p)=1
for(a=2; ;a++){
tester=(a*a)-n;
root=tester;

while(tester<0)
tester+=prime;

if(legendre_symbol(tester, prime)==(prime-1))
break;
              };

//TESTE USE UM  // APÓS  O MESMO
//printf("a: %li, root: %li\n", a, root);

//Arítmetica no corpo algébrico Q(√n) mod p
//Ajuste de variáveis
algebraic_number[0]=a;
algebraic_number[1]=1;

//1ª iteração
algebraic_multiplication(algebraic_squared, algebraic_number, algebraic_number, root, prime);
power+=2;

//Ajuste de variáveis
algebraic_product[0]=algebraic_squared[0];
algebraic_product[1]=algebraic_squared[1];

//Loop principal com otimização binária
while(power<max_power){
//Caso 1
if((power*power)<max_power){
algebraic_multiplication(temp, algebraic_product, algebraic_product, root, prime);

//Ajuste de variáveis
algebraic_product[0]=temp[0];
algebraic_product[1]=temp[1];

power*=2;
                           };

//Caso 2
if((power+2)<max_power){
algebraic_multiplication(temp, algebraic_product, algebraic_squared, root, prime);

//Ajuste de variáveis
algebraic_product[0]=temp[0];
algebraic_product[1]=temp[1];

power+=2;
                       };

//Caso 3
if(power==(max_power-1)){
algebraic_multiplication(temp, algebraic_product, algebraic_number, root, prime);

//Ajuste de variáveis
algebraic_product[0]=temp[0];
algebraic_product[1]=temp[1];

power++;
                        };

                      };

//Resultado
return algebraic_product[0];
                                                   };


//*******************************************************************************************************************************************************************
//FIM DO HEADER
#endif
