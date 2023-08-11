//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS RÓTINAS CRIADAS NO ARQQUIVO euler_totient_function.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o euler_totient_function euler_totient_function.c -lm

//Cabeçalho
#include<stdio.h>
#include"euler_totient_function.h"

//Função principal
int main(){
//Variáveis
uint64_t number;
//Recebendo input do usuário
printf("Usuário digite um número: ");
scanf("%li", &number);

//Calculando o valor da função totiente de Euler
printf("φ(%li) = %li.\n", number, euler_totient_function(number));

//Finalizando a aplicação
return 0;
          }
