//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO hart_factorization.h
//VAMOS COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o hart_factorization hart_factorization.c -lm -O2


//Cabeçalho
#include"hart_factorization.h"
#include<stdio.h>

//Função principal
int main(){
  //Variáveis locais
  int64_t number;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro a ser fatorado: ");
    if(scanf("%li", &number)!=1) return 0;

    //Fatorando o número em questão
    hart_factorization(number);

  //Finalizando a aplicação
  return 0;

}
