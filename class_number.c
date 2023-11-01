//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS IMPLEMENTADAS NO ARQUIVO class_number.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o class_number class_number.c -lm

//Cabeçalho
#include"class_number.h"
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

//Testando se n e -n são discriminantes fundamentais
if(is_fundamental_discriminant(n)==true)
printf("%li é um discrimante fundamental.\n", n);
else
printf("%li não é um discrimante fundamental.\n", n);

if(is_fundamental_discriminant(minus_n)==true)
printf("%li é um discrimante fundamental.\n", minus_n);
else
printf("%li não é um discrimante fundamental.\n", minus_n);


//Calculando o número de classe
if(is_fundamental_discriminant(minus_n)==true)
printf("h(%li)=%li (fórmula de Dirichlet)\n", minus_n, class_number_negative_discriminant(minus_n));

//Finalizando a aplicação
return 0;
          }
