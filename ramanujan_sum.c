//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO ramanujan_tau_function.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o ramanujan_sum ramanujan_sum.c -lm

//Cabeçalho
#include<stdio.h>
#include"ramanujan_sum.h"


//Função principal
int main(){

  //Variáveis locais
  int64_t n, q;

  //Procedimentos
    //Recebendo input do usuário
    printf("Usuário digite um número inteiro: ");
    scanf("%li", &q);
    printf("Usuário digite um número inteiro: ");
    scanf("%li", &n);

    //Calculando as funções de Möbius e as funções de Mertens
    printf("c(%li, %li) = %li\n", q, n, ramanujan_sum(q, n));

  //Finalizando a aplicação
  return 0;

}; 
