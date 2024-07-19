//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO wilson_prime_test.h
//COMPILAR ESTEPROGRAMA COM O COMANDO: gcc -o wilson_prime_test wilson_prime_test.c


//Cabeçalho
#include"wilson_prime_test.h"
#include<stdio.h>

//Função principal
int main(){

  //Variáveis locais
  uint64_t number, i;

  //Procedimentos
    //Recebendo um input do usuário
    printf("Digite um limitante para sua sequência de números primos: ");
    scanf("%lu", &number);

    //Printando uma sequência de números primos
    for(i=2; i<=number; ++i){
      if(wilson_prime_test(i)==true) printf("%lu, ",i);
    };

    printf("...\n");

  //Finalizando a aplicação
  return 0;

}
