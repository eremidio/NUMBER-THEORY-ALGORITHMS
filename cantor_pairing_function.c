//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO cantor_pairing_function.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o cantor_pairing_function cantor_pairing_function.c -lm -O2


//Cabeçalho
#include"cantor_pairing_function.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  __int128_t z;
  int64_t x, y;
  char number_string[40];


  //Procedimentos 
    //Recebendo input do usuário
    printf("[Inteiro] x: ");
    if(scanf("%li", &x)!=1) return 0;
    printf("[Inteiro] y: ");
    if(scanf("%li", &y)!=1) return 0;
  

    //Calculando o valor π(a,b) associado via a função de pareamento de Cantor
    z=cantor_paring_function(x, y);
    printf("π(x,y)= "); printf128(z);


    //Recendo input do usuário
    printf("[Inteiro-resultado da função de pareamento de Cantor] π(x,y): ");
    if(scanf("%s", number_string)!=1) return 0;
    z=scanf128(number_string);

    //Calculando os valores a serem pareados pela função de Cantor
    inverse_cantor_paring_function(z, &x, &y);
    printf("x=%li\n", x);
    printf("y=%li\n", y);


  //Finalizando a aplicação
  return 0;

}

