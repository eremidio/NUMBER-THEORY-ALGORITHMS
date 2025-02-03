//UM PROGRAMA QUE TESTA AS ROTINAS DEFINIDAS NOS ARQUIVO mod_bin_exponentiation,h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o exponentiation exponentiation.c -lm

//Cabeçalho
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"mod_bin_exponentiation.h"

//Função principal

int main(){

  //Variáveis locais
  int a, b, n;
  int bin_array_size = 0;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite uma base:\n->");
    scanf("%d", &a);
    printf("Digite um expoente:\n->");
    scanf("%d", &b);
    printf("Digite um inteiro congruente:\n->");
    scanf("%d", &n);

    //Testes
    printf("Resultado biblioteca <math.h>: %d\n", ((int)pow(a, b)%n));
    printf("Exponencial modular: %lu\n", pow_mod(a, b, n));

  //Finalizando a aplicação
  return 0;

}

