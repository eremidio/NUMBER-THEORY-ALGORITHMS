//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO quadratic_reciprocity_primality_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o gauss_euler_primality_test gauss_euler_primality_test.c -lm


//Cabeçalho
#include"gauss_euler_primality_test.h"
#include<stdio.h>

//Função principal
int main(){
//Váriaveis locais
uint64_t number;

//Procedimentos
//Recebendo input do usuário
printf("Digite um número que será testado:\n");
scanf("%lu", &number);

//Executando o teste
if(gauss_euler_primality_test(number)==true)
printf("Primo encontrado!\n");
else
printf("Número composto.\n");

//Finalizando a aplicação
return 0;
          }
