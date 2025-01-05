//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO connarcchia_algorithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o cornarcchia_algorithm_composite_modulus cornarcchia_algorithm_composite_modulus.c -lm


//Cabeçalho
#include"cornarcchia_algorithm_composite_modulus.h"
#include<stdio.h>

//Função principal
int main(){

  //Variáveis locais
  int64_t x, y, m, d;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um inteiro m:");
    scanf("%li", &m);
    printf("Digite um inteiro d:");
    scanf("%li", &d);

  //Executando o algoritmo
  cornarcchia_algorithm_composite_modulus(d, m, &x, &y);
  printf("Solução de x²+%liy²=%li\n x=%li, y=%li\n", d, m, x, y);

  //Finalizando a aplicação
  return 0;

}
