//VAMOS CRIAR UM PROGRAMA PARATESTAR AS ROTINAS DEFINIDAS NO ARQUIVO logarithmic_functions.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o  logarithmic_functions logarithmic_functions.c -lm


//Cabeçalho
#include"logarithmic_functions.h"
#include<stdio.h>
#include<stdint.h>


//Função principal
int main(){
//Variáveis locais
uint64_t number1;
//Procedimentos
//Recebendo input do usuário
printf("Digite um número inteiro: ");
scanf("%lu", &number1);

//Testando funções logarítmicas
printf("Λ(%lu)=%lf\n", number1, von_mangoldt_function(number1));
printf("Θ(%lu)=%lf\n", number1, first_chebyshev_function(number1));
printf("ψ(%lu)=%lf\n", number1, second_chebyshev_function(number1));
printf("Π(%lu)=%lf\n", number1, pi_weight_function(number1));

//Finalizando a aplicação
return 0;
          }
