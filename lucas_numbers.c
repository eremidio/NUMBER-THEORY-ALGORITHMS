//VAMOS CRIARUM PROGRAMA PARA TESTAR ROTINAS CRIADAS NO ARQUIVO lucas_numbers.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o lucas_numbers lucas_numbers.c -O2 -lm


//Cabeçalho
#include"lucas_numbers.h"
#include<stdio.h>


//Função principal
int main(){
//Variáveis locais
int64_t n;

//Procedimento
//Recebendo input do usuário
printf("Digite um inteiro: ");
if(scanf("%li", &n)!=1)
return 0;

//Calculando os números de Lucas e Fibonacci
printf("%li-ésimo número de Lucas (recursão): %li\n", n, recursive_lucas_number(n));
printf("%li-ésimo número de Lucas (via razão de ouro): %li\n", n, lucas_number_golden_ratio(n));
printf("%li-ésimo termo da sequência de Fbonacci (em termos do número de Lucas correspondente): %li\n", n, fibonacci_number(n));


//Finalizando a aplicação
return 0;
          }
