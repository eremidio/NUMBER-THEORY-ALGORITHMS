//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO safe_primes.h
//COMPILAR ESTE PROGRAMA COMO COMANDO: g++ -o safe_primes safe_primes.c -lm


//Cabeçalho
#include"safe_primes.h"
#include<stdio.h>


//Função principal
int main(){

  //Váriaveis locais
  uint64_t number, q;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número que será testado:\n");
    scanf("%lu", &number);
    q=(number<<1)+1;

    //Executando o teste
    if(terzic_safe_prime_test(number)==true)
      printf("%lu é primo\n", q);
    else
      printf("%lu não é primo\n", q);

  //Finalizando a aplicação
  return 0;

}
