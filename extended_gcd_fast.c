//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO extended_gcd_fast.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o extended_gcd_fast extended_gcd_fast.c



//Cabeçalho
#include"extended_gcd_fast.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t a, b, gcd, u, v;

  //Procedimento
    //Recebendo input do usuário
    printf("Digite um inteiro positivo a: ");
    scanf("%li", &a);
    printf("Digite um inteiro positivo b: ");
    scanf("%li", &b);

    //Aplicando o algoritmo extendido de Euclides
    extended_gcd_fast(&u, &v, &gcd, a, b);
    printf("Coeficientes da indetidade de Bézout: au+bv=mdc(a,b): u=%li, v=%li\n", u, v);
    printf("mdc(a,b): %li\n", gcd);


  //Finalizando a aplicação
  return 0;


}
