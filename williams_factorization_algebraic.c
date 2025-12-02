//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO williams_factorization_algebraic.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o williams_factorization_algebraic williams_factorization_algebraic.c -lm -O2

//Cabeçalho
#include"williams_factorization_algebraic.h"
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
    williams_factorization_algebraic(number);


  //Finalizando a aplicação
  return 0;

}
