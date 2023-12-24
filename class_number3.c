//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO HEADER class_number3.h
//COMPILAR ESTE PROGRAMA: gcc -o class_number3 class_number3.c -lm


//Cabeçalho
#include"class_number3.h"
#include<stdio.h>

//Função principal
int main(){
//Variáveis locais
int64_t n;

//Procedimentos
//Recebendo input do usuário
printf("Digite um número inteiro correspondente a um discriminante fundamental: ");
scanf("%li", &n);

//Calculando o número de classe
printf("h+(%li)=%li (número de classe reduzido)\n", n, narrow_class_number_positive_discriminant(n));
printf("h(%li)=%li\n", n, class_number_positive_discriminant(n));

//Finalizando a aplicação
return 0;
          }
