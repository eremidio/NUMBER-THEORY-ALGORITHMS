//VAMOS CRIAR UM PROGRAMA TESTA AS ROTINAS CRIADAS NO ARQUIVO solovay_strassen.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o solovay_strassen solovay_strassen.c -lm -O2


//Cabeçalho
#include"solovay_strassen.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t number;

  //Procedimentos
    //Recebendo o input
    printf("Número a ser testado: ");
    if(scanf("%li", &number)!=1)  return 0;

    //Usando o teste de Solovay-Strassen para inteiros de 64 bits
    if(solovay_strassen(number)==true)
      printf("O número em questão é primo.\n");
    else
      printf("O número em questão é composto.\n");


  //Finalizando a aplicação
  return 0;

}

