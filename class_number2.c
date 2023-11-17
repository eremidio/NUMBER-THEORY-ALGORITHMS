//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO class_number2.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o class_number2 class_number2.c -lm

//Cabeçalho
#include"class_number2.h"
#include<stdio.h>

//Função principal
int main(){
//Variáveis locais
int64_t n, minus_n;

//Procedimentos
//Recebendo input do usuário
printf("Digite um número inteiro correspondente a um discriminante fundamental: ");
scanf("%li", &n);

minus_n = (-1)*n;

//Calculando o número de classe
if(is_fundamental_discriminant(minus_n)==true)
printf("h(%li)=%li (formas quadráticas reduzidas)\n", minus_n, class_number_negative_discriminant2(minus_n));
else
printf("h(%li)=%li (formas quadráticas primitivas)\n", minus_n, class_number_negative_discriminant3(minus_n));

//Finalizando a aplicação
return 0;
          }

