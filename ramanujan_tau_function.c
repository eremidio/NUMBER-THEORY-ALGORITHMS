//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO ramanujan_tau_function.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o ramanujan_tau_function ramanujan_tau_function.c -lm

//Cabeçalho
#include<stdio.h>
#include"ramanujan_tau_function.h"

//Função principal
int main(){

  //Variáveis locais
  int64_t number;

  //Procedimentos
    //Recebendo input do usuário
    printf("Usuário digite um número inteiro: ");
    scanf("%li", &number);

  //Calculando a função tau de Ramanujan
  printf("τ(%li) = %li\n", number, ramanujan_tau_function(number));

//Finalizando a aplicação
return 0;

};
