//VAMOS CRIAR UM PROGRAMA PARA TESTAR A ROTINA NO ARQUIVO gcd_euclides_fast.h
//COMPILAR ESTE PROGRAMA COM: gcc -o gcd_euclides_fast gcd_euclides_fast.c


//Cabeçalho
#include"gcd_euclides_fast.h"
#include<stdio.h>
#include<stdint.h>


//Função principal
int main(){
//Variáveis locais
uint64_t a, b;

//Procedimentos
//Recebendo input do usuário
printf("Digite um inteiro: ");
scanf("%lu", &a);
printf("Digite um inteiro: ");
scanf("%lu", &b);

//Calculando o mdc de a e b
printf("mdc(%lu, %lu)=%lu\n", a, b, fast_euclides_algorithm(a, b));

//Finalizando a aplicação
return 0;
          }
