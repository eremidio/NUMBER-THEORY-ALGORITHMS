//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO quadratic_frobenius_primality_test_polynomial_version.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o quadratic_frobenius_primality_test_polynomial_version quadratic_frobenius_primality_test_polynomial_version.cpp -O2 -lm


//Cabeçalho
#include"quadratic_frobenius_primality_test_polynomial_version.h"
#include<stdio.h>
using namespace std;


//Função principal
int main(){
  //Variáveis locais
  int64_t number;

  //Procedimentos
    //Recebendo o input
    printf("Número a ser testado: ");
    if(scanf("%li", &number)!=1)  return 0;


    //Usando o teste de Miller-Rabin para inteiros de 128 bits
    if(quadratic_frobenius_primality_test(number)==true)
      printf("O número em questão é primo.\n");
    else
      printf("O número em questão é composto.\n");


  //Finalizando a aplicação
  return 0;

}
