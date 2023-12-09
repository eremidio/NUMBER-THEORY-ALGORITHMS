//VAMOS CRIARUM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO hart_factorization.h
//VAMOS COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o hart_factorization hart_factorization.c -lm


//Cabeçalho
#include"hart_factorization.h"
#include<stdio.h>

//Função principal
int main(){
//Variáveis locais
int64_t number;

//Procedimentos
//Recebendo input do usuário
printf("Digite um número inteiro a ser fatorado: ");
scanf("%li", &number);

//Fatorando o número em questão
hart_factorization(number);

//Finalizand
          }
