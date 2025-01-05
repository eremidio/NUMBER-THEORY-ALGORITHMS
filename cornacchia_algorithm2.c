//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO cornarcchia_algorithm2.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o cornacchia_algorithm2 cornacchia_algorithm2.c


//Cabeçalho
#include"cornacchia_algorithm2.h"
#include<stdio.h>

//Função principal
int main(){

  //Variáveis locais
  int64_t x, y, p, D;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um inteiro p (primo):");
    scanf("%li", &p);
    printf("Digite um inteiro D:");
    scanf("%li", &D);

  //Executando o algoritmo
  modified_cornacchia_algorithm(D, p, &x, &y);
  printf("Solução de x²+%liy²=%li\n x=%li, y=%li\n", (-D), (p<<2), x, y);

  //Finalizando a aplicação
  return 0;

}
