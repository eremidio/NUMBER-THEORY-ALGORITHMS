//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO pseudosquare_prime_sieve.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o pseudosquare_prime_sieve pseudosquare_prime_sieve.c -O2


//Cabeçalho
#include"pseudosquare_prime_sieve.h"


//Função principal
int main(){

  //Variáveis locais
  uint64_t limit, sieve_size;


  //Procedimento
    //Recebendo input do usuário
    printf("Limite superior para a busca de primos: ");
    if(scanf("%lu", &limit)!=1) return 0;
    printf("Intervalo de segmetação: ");
    if(scanf("%lu", &sieve_size)!=1) return 0;

    //Computando números primos até um determinado limite
    pseudosquare_prime_sieve(limit, sieve_size);


  //Finalizando a aplicação
  return 0;

}
