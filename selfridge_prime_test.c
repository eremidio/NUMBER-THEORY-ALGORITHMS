//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO selfridge_prime_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o selfridge_prime_test selfridge_prime_test.c


//Cabeçalho
#include"selfridge_prime_test.h"
#include<stdio.h>



//Função principal
int main(){


 //Váriaveis
 uint64_t number, i;


 //Procedimentos
  //Recebendo input do usuário
  printf("Digite um limitante superior para a sequência de possíveis números: ");
  scanf("%li", &number);


  //Executando o teste
  printf("Eis sua sequência de prováveis números primos:\n2, 3, 5, ");

  for(i=7; i<=number; ++i){
   if(selfridge_prime_test(i)==true)
    printf("%li, ", i);
                        };
  printf("...\n");

 //Finalizando a aplicação
 return 0;

          }
