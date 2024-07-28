//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO gaussian_sum.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o gaussian_sum gaussian_sum.c -lm

//Cabeçalho
#include"gaussian_sum.h"
#include<stdio.h>

//Função principal
int main(){

  //Variáveis locais
  double _Complex gaussian_sum;
  int64_t p, q;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um inteiro: ");
    scanf("%li", &p);
    printf("Digite um inteiro: ");
    scanf("%li", &q);

  //Calculando a soma de Gauss
  gaussian_sum=quadratic_gaussian_sum(p, q);

  //Finalizando a aplicação
  return 0;

}
