//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO farey_sequence.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o farey_sequence farey_sequence.c -lm


//Cabeçalho
#include"farey_sequence.h"
#include<stdio.h>

//Função principal
int main(){
//Variáveis locais
int n;
//Procedimento
//Recebendo input do usuário
printf("Usuário digite um número inteiro: ");
scanf("%i", &n);

//Gerando as sequências de Farey
for(int i=1; i<=n; ++i)
generate_farey_sequence(i, Down);

//Finalizando a aplicação
return 0;
          }
 
