//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO fermat_prime_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o fermat_prime_test fermat_prime_test.c -lm -O2



//Cabeçalho
#include"fermat_prime_test.h"
#include<stdio.h>

//Função principal
int main(){

  //Váriaveis
  uint64_t number, counter=0;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um limitante a sua sequência de prováveis primos:\n");
    if(scanf("%lu", &number)!=1) return 0;

    //Executando o teste
    printf("Eis a sequência de (prováveis) primos até %lu:\n", number);
    for(uint64_t i=2; i<=number; ++i){
      if(fermat_primality_test(i)==true){
        printf("%lu, ", i);
        counter++;
                                        }

    }

    printf("...\n");
    printf("Números de primos encontrados: %lu\n", counter);

  //Finalizando a aplicação
  return 0;

}
