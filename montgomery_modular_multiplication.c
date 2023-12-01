//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO montgomery_modular_multiplication.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o montgomery_modular_multiplication montgomery_modular_multiplication.c

//Cabeçalho
#include"montgomery_modular_multiplication.h"
#include<stdio.h>

//Função principal 
int main(void){
int64_t a, b, N, N_, R, T, S;
int64_t am, bm, abm;

//Procedimentos.
//Recebendo input do usuário
printf("Digite um inteiro 'a': ");
scanf("%li", &a);
printf("Digite um inteiro 'b': ");
scanf("%li", &b);
printf("Digite um inteiro 'N': ");
scanf("%li", &N);
printf("Digite um inteiro 'R': ");
scanf("%li", &R);
printf("Digite um inteiro 'T': ");
scanf("%li", &T);

//Testando a função que reduz um número a sua forma de Montgomery
printf("a+b mod N: %li\n", ((a+b)%N));
am=montgomery_form(a, R, N);
bm=montgomery_form(b, R, N);
abm=montgomery_form((a+b), R, N);
printf("a*R mod N: %li\n", am);
printf("b*R mod N: %li\n", bm);
printf("(a+b)*R mod N: %li\n", abm);
printf("(a*R mod N)+(b*R mod N): %li\n", ((am+bm)%N));

//Testando a função que calcula um valor N' tal que N(N') mod R=(R-1)
N_=calculate_n_factor(N, R);
printf("N'=%li\n", N_);

//Testando a função que determina uma redução de Montgomery
S=montgomery_reduction(N, R, T);
printf("S: %li\n", S);

//Testando a função que define a multiplicação modular usando redução de Montgomery
printf("(a*b) mod N: %li\n", mod_mul_montgomery(a, b, N, R));

//Resultado final
return 0;
              }
