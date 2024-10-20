//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO binary_jacobi_symbol.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o binary_jacobi_symbol binary_jacobi_symbol.c -lm


//Cabeçalho
#include"binary_jacobi_symbol.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t a, b;

  //Procedimento
    //Recebendo input
    printf("Digite um número inteiro: ");
    scanf("%li", &a);
    printf("Digite um número inteiro: ");
    scanf("%li", &b);

    //Calculando o símbolo de Jacobi
    printf("(%li|%li)= %d\n", a, b, binary_jacobi(a, b));

  //Finalizando a aplicação
  return 0;
          
}



