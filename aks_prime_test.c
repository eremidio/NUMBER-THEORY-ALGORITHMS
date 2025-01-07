//VAMOS CRIAR UM PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO aks_prime_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o aks_prime_test aks_prime_test.c -lm -O3


//Cabeçalho
#include"aks_prime_test.h"
#include<stdio.h>


//Função principal 
int main(){

  //Variáveis locais
  uint64_t i;

  //Procedimentos
    //Testando a primalidade de um número
    printf("Listas de primos de até 25000: ");
    for(i= 2; i<25000; i++){
      if(aks_primality_test(i, No)==true)
        printf("%lu, ", i);
      };
    printf("...\n");


  //Finalizando a aplicação
  return 0;

}
