//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO extended_gcd_fast.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o binary_extended_gcd binary_extended_gcd.c



//Cabeçalho
#include"binary_extended_gcd.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t x, y, gcd, a, b;

  //Procedimento
    //Recebendo input do usuário
    printf("Digite um inteiro positivo x: ");
    scanf("%li", &x);
    printf("Digite um inteiro positivo y: ");
    scanf("%li", &y);

    //Aplicando o algoritmo extendido de Euclides
    binary_extended_gcd(&a, &b, &gcd, x, y);
    printf("Coeficientes da indetidade de Bézout: ax+by=mdc(a,b): a=%li, b=%li\n", a, b);
    printf("mdc(a,b): %li\n", gcd);


  //Finalizando a aplicação
  return 0;


}
