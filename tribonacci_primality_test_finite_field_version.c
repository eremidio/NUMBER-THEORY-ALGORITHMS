//VAMOS CRIAR UM PROGRAMAPARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO tribonacci_primality_test_finite_field_version.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o tribonacci_primality_test_finite_field_version tribonacci_primality_test_finite_field_version.c -lm -O2


//Cabeçalho
#include"tribonacci_primality_test_finite_field_version.h"
#include<stdio.h>

//Função principal
int main(){

  //Variáveis locais
  int64_t number;

  //Procedimentos
    //Recebendo o input
    printf("Número a ser testado: ");
    if(scanf("%li", &number)!=1)  return 0;


    //Usando o teste de Miller-Rabin para inteiros de 128 bits
    if(tribonacci_primality_test_finite_field(number)==true)
      printf("O número em questão é primo.\n");
    else
      printf("O número em questão é composto.\n");


  //Finalizando a aplicação
  return 0;

}
