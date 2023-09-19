//VAMOS CRIAR UM PROGRAMA PARATESTAR AS ROTINAS DEFINIDAS NO ARQUIVO totient_functions.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o totient_functions totient_functions.c -lm


//Cabeçalho
#include"totient_functions.h"
#include<stdio.h>
#include<stdint.h>


//Função principal
int main(){
//Variáveis locais
uint64_t number1, number2;
//Procedimentos
//Recebendo input do usuário
printf("Digite um número inteiro: ");
scanf("%lu", &number1);
printf("Digite um número inteiro: ");
scanf("%lu", &number2);

//Testando funções totientes
printf("λ(%lu)=%lu\n", number1, carmichael_function(number1));
printf("J(%lu, %lu)=%lu\n", number1, number2, jordan_totient_function(number2, number1));
printf("Ψ(%lu, %lu)=%Lf\n", number2, number1, dedekind_psi_function(number2, number1));

//Finalizando a aplicação
return 0;
          } 
