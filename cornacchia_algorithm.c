//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO connarcchia_algorithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o cornacchia_algorithm cornacchia_algorithm.c -lm


//Cabeçalho
#include"cornacchia_algorithm.h"
#include<stdio.h>

//Função principal
int main(){

  //Variáveis locais
  int64_t x, y, m, d;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um inteiro m (primo):");
    scanf("%li", &m);
    printf("Digite um inteiro d:");
    scanf("%li", &d);

  //Executando o algoritmo
  cornacchia_algorithm(d, m, &x, &y);
  printf("Solução de x²+%liy²=%li\n x=%li, y=%li\n", d, m, x, y);

  //Finalizando a aplicação
  return 0;

}
