//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO quadratic_frobenius_prime_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o quadratic_frobenius_prime_test quadratic_frobenius_prime_test.c -lm

//Cabeçalho
#include"quadratic_frobenius_prime_test.h"
#include<stdio.h>

//Função principal
int main(){

  //Váriaveis
  int64_t number;


  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número que será testado:\n");
    scanf("%li", &number);

    //Executando o teste
    if(quadratic_frobenius_primality_test(number, Verbose)==true)
      printf("Provável candidato a primo encontrado!\n");
    else
      printf("Número composto.\n");

  //Finalizando a aplicação
  return 0;

}
