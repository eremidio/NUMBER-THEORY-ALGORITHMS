//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO williams_factorization_algebraic.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o williams_factorization_algebraic williams_factorization_algebraic.c

//Cabeçalho
#include"williams_factorization_algebraic.h"
#include<stdio.h>


//Função principal
int main(){
//Variáveis locais
char number_string1[40];
char number_string2[40];
__int128_t n, E;
//Procedimento
//REcebendo input do usuário
printf("Digite um número que será fatorado: ");
if(scanf("%s", number_string1)!=1)
return 0;
n=scanf128(number_string1);
printf("Digite um número inteiro auxiliar(expoente): ");
if(scanf("%s", number_string2)!=1)
return 0;
E=scanf128(number_string2);

//Executando o algoritmo
williams_algebraic_factorization(n, E);

//Finalizando a aplicação
return 0;
          }
