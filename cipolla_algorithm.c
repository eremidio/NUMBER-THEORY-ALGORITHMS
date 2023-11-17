//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO cipolla_algorithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o cipolla_algorithm cipolla_algorithm.c -lm

//Cabeçalho
#include"cipolla_algorithm.h"
#include<stdio.h>

//Função principal
int main(){
//Variáveis locais
int64_t algebraic_number[2]={2,1};
int64_t algebraic_number2[2]={(-1), (-3)};
int64_t algebraic_product[2], algebraic_product2[2];
int64_t n, sqrt_n, prime;

//Testes
//Teste da função de multiplicação de números algébricos
algebraic_multiplication(algebraic_product, algebraic_number, algebraic_number, (-6), 13);
printf("(2+1√-6)² (mod 13)=%li+(%li√-6)\n", algebraic_product[0], algebraic_product[1]);
algebraic_multiplication(algebraic_product2, algebraic_number2, algebraic_product, (-6), 13);
printf("(-2+4√-6)((-1)+(-3)√-6) (mod 13)=%li+(%li√-6)\n", algebraic_product2[0], algebraic_product2[1]);

//Recebendo input do usuário
printf("Digite um inteiro: ");
scanf("%li", &n);
printf("Digite um inteiro primo ímpar: ");
scanf("%li", &prime);

//Algoritmo de Cipolla
sqrt_n=cipolla_algorithm(n, prime);
printf("√%li (mod %li)= %li\n", n, prime, sqrt_n);

//Finalizando a aplicação
return 0;
          }
