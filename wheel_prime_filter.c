//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO wheel_prime_filter.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o wheel_prime_filter wheel_prime_filter.c -lm


//Cabeçalho
#include"wheel_prime_filter.h"
#include<stdio.h>


//Função principal
int main(){
  
  //Variáveis locais
  uint64_t * number_list=NULL;
  uint64_t limit, list_size;
  int prime_seed;

  //Procedimento
    //Recebendo input do usuário
    printf("Digite um limitante para a sequência de possíveis primos:");
    scanf("%li", &limit);
    printf("Digite o números de  primos usados para construir a lista(<10):");
    scanf("%i", &prime_seed);

    //Aplicando o algoritmo de roda para gerar lista de possíveis primos
    number_list=wheel_prime_filter(limit, prime_seed, &list_size);
    for(uint64_t i=0; i<list_size; ++i){
      printf("%lu, ", number_list[i]);
    }
    printf("...\n");

    //Limpando o cachê de memória
    if(number_list) free(number_list);
    number_list=NULL;

  //Encerrando a aplicação
  return 0;

}

