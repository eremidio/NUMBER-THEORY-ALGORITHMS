//VAMOS CRIAR UM PROGRAMA QUE TESTAS AS ROTINAS CRIADAS NO ARQUIVO kronecker_symbol.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o kronecker kronecker.c -lm


//Cabeçalho
#include"kronecker_symbol.h"
#include<stdint.h>
#include<stdio.h>

//Função principal
int main(){
//Variáveis locais
int64_t a, n;

//Procedimentos
//Recebendo input do usuário
printf("Digite um inteiro: ");
scanf("%li", &a);
printf("Digite um inteiro: ");
scanf("%li", &n);

//Calculando o símbolo de Legendre
printf("(%li/%li) = %i\n", a, n, kronecker(a, n));

//Finalizando a aplicação
return 0;
          }
