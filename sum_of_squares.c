//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO sum_of_squares.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o sum_of_squares sum_of_squares.c -lm

//Cabeçalho
#include"sum_of_squares.h"
#include<stdint.h>
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t n;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro: ");
    scanf("%li", &n);

  //Escrevendo o número em questão como a soma de dois quadrados se posśivel
  write_square_sum(n);


  //Finalizando a aplicação
  return 0;

}
