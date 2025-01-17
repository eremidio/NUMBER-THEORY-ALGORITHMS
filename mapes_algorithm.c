//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADA NO ARQUIVO mapes_algorithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o mapes_algorithm mapes_algorithm.c -lm


//Cabeçalho
#include"mapes_algorithm.h"
#include<stdio.h>


//Função principal
/*
VER: Prime Numbers And Computer Methods For Factorization, by Hans Riesel,
     na página 15 para ver a tabela a ser reproduzida aqui.
*/
int main(){

  //Variáveis locais
  int64_t primes_10[4]={2,3,5,7};
  int64_t primes_20[8]={2,3,5,7,11,13,17,19};
  int64_t current=1, mapes_value, x;

  //Procedimentos
    //-----
    printf("φ(1,4)=1\n");


    //Loop principal
    for(x=2; x<120; ++x){
      mapes_value=mapes_algorithm(x, 4, primes_10);
      if(mapes_value>current){
        printf("φ(%li, 4)=%li\n", x, mapes_value);
        current=mapes_value;
      }

    }

    //-------
    //Teste 2 (página 28)
    printf("φ(10000, 8)=%li\n", mapes_algorithm(10000, 8, primes_20));


  //Finalizando a aplicação
  return 0;

}

