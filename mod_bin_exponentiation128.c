//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRTIADAS NO ARQUIVO mod_bin_exponentiation128.h
//COMPILAR COM O COMANDO: gcc -o mod_bin_exponentiation128 mod_bin_exponentiation128.c

//Cabeçalho
#include"int128.h"
#include"mod_bin_exponentiation128.h"
#include<stdio.h>


//Função principal
int main(){
//Variáveis locais
__int128_t a, b, m, power1, power2, power3;
char number_string1[45], number_string2[45], number_string3[45];

//Procedimento
//Recebendo input do usuário
printf("Digite um número: ");
scanf("%s", number_string1);
a=scanf128(number_string1);

printf("Digite um número: ");
scanf("%s", number_string2);
b=scanf128(number_string2);

printf("Digite um número: ");
scanf("%s", number_string3);
m=scanf128(number_string3);

//Teste das funções de exponenciação modular
power1=mod_pow(a, b, m);
power2=bin_pow(a, b);
power3=mod_bin_pow(a, b, m);

printf("Exponencial modular: ");
printf128(power1);
printf("Exponencial binária: ");
printf128(power2);
printf("Exponencial modular binária: ");
printf128(power3);

//Finalizando a aplicação
          }
