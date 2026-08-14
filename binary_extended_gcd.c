//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO extended_gcd_fast.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o binary_extended_gcd binary_extended_gcd.c



//Cabeçalho
#include"binary_extended_gcd.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t u, v, gcd, a, b;

  //Procedimento
    //Recebendo input do usuário
    printf("Digite um inteiro positivo x: ");
    scanf("%li", &a);
    printf("Digite um inteiro positivo y: ");
    scanf("%li", &b);

    //Aplicando o algoritmo extendido de Euclides
    binary_extended_gcd(&u, &v, &gcd, a, b);
    printf("Coeficientes da indentidade de Bézout: ua+vb=mdc(a,b): a=%li, b=%li\n", u, v);
    printf("mdc(a,b): %li\n", gcd);


  //Finalizando a aplicação
  return 0;


}
