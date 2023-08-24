//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO baillie_psw_prime_test.H
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o baillie_psw_prime_test baillie_psw_prime_test.c -lm


//CABEÇALHO
#include<stdio.h>
#include"baillie_psw_prime_test.h"

//FUNÇÃO PRINCIPAL

int main(){
//Váriaveis
uint64_t number;
//Procedimentos
//Recebendo input do usuário
printf("Digite um número que será testado:\n");
scanf("%lu", &number);

//Executando o teste
if(baillie_psw_test(number)==true)
printf("Provável primo encontrado!\n");
else
printf("Número composto.\n");


//Finalizando a aplicação
return 0;
          }
