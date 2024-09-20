//VAMOS CRIAR UM PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO aks_prime_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o aks_prime_test aks_prime_test.c -lm -lgmp


//Cabeçalho
#include"aks_prime_test.h"
#include<stdint.h>
#include<stdbool.h>
#include<stdio.h>


//Função principal 
int main(){

  //Variáveis locais
  uint64_t i;

  //Procedimentos
    //Testando a primalidade de um número
    printf("Listas de primos até 3000: ");
    for(i= 1; i<3001; i++){
      if(aks_primality_test(i)==true)
        printf("%lu, ", i);
      };
    printf("...\n");

  //Finalizando a aplicação
  return 0;

}
