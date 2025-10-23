//VAMOS CRIAR UM TESTA AS ROTINAS CRIADAS NO ARQUIVO primorial_prime_sieve_setup.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o primorial_prime_sieve_setup primorial_prime_sieve_setup.c 


//Cabeçalho
#include"primorial_prime_sieve_setup.h"
#include<stdio.h>


//Função principal
int main(){

  //Procedimentos
    //Precomputando os primoriais
    compute_primorial_sequence();
    
    printf("Sequência de primoriais:\n");
    for(int i=0; i<15; ++i) printf("%lu\n", small_primorials[i]);


    //Precomputando a sequência geradora de números primos
    compute_Tnk_prime_generating_sequence();

    printf("\nSequência geradora de números primos:\n");
    for(int i=0; i<15; ++i){
      for(int j=0; j<=i; ++j){
        if(Tnk_prime_generating_sequence[i][j]>0)
          printf("%lu ", Tnk_prime_generating_sequence[i][j]);
      }
      printf("\n");
    };

    printf("\n");

  //Finalizando a aplicação
  return  0;

}

