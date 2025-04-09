//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO bruckman_lucas_primes_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o bruckman_lucas_prime_test bruckman_lucas_prime_test.c -lm -O2


//Cabeçalho
#include"bruckman_lucas_prime_test.h"
#include<stdio.h>


//Função principal

int main(){


 //Váriaveis
 int64_t number, i;
 int64_t counter=3;


 //Procedimentos
  //Recebendo input do usuário
  printf("Digite um limitante superior para a sequência de possíveis números: ");
  if(scanf("%li", &number)!=1) return 0;


  //Executando o teste
  printf("Eis sua sequência de prováveis números primos:\n2, 3, 5, ");

  for(i=7; i<=number; i+=2){
   if(bruckman_lucas_prime_test(i)==true){
    printf("%li, ", i);
    counter+=1;
                                    };
                        };
  printf("...\n");
  printf("Número de prováveis primos encontrados até %li: %li\n", number, counter);

 //Finalizando a aplicação
 return 0;

}
