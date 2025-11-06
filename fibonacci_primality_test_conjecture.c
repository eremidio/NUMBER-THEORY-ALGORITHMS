//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO fibonacci_primality_test_conjecture.h
//COMILAR ESTE PROGRAMA COM O COMANDO: gcc -o fibonacci_primality_test_conjecture fibonacci_primality_test_conjecture.c -O2


//Cabeçalho
#include"fibonacci_primality_test_conjecture.h"
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

    for(i=7; i<=number; ++i){
      if(fibonacci_primality_test_conjecture(i)==true){
        printf("%li, ", i);
        counter+=1;
      };
    };

    printf("...\n");
    printf("Número de prováveis primos encontrados até %lu: %lu\n", number, counter);


  //Finalizando a aplicação
  return 0;

} 
