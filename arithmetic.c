//PROGRAMA PARA TESTAR OS PROCEDIMENTOS DEFINIDOS NO ARQUIVO arithmetic.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o arithmetic arithmetic.c


//Cabeçalho
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"arithmetic.h"


//Função principal
int main(){

  //Variáveis locais
  int64_t a, b;


  //Procedimento
    //Recebendo input do usuário
    printf("Digite um número inteiro: ");
    scanf("%li", &a);
    printf("Digite um número inteiro: ");
    scanf("%li", &b);

    //Performando operações aritméticas
    printf("%li+%li=%li\n", a, b, bit_add(a, b));
    printf("%li-%li=%li\n", a, b, bit_sub(a, b));
    printf("%li*%li=%li\n", a, b, bit_mul(a, b));
    printf("%li/%li=%li\n", a, b, bit_div(a, b));

  //Finalizando a aplicação
  return 0;

}
