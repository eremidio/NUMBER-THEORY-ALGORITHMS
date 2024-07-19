//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO primitive_root.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o primitive_root primitive_root.c -lm

//Cabeçalho
#include<stdio.h>
#include"primitive_root.h"

//Função principal
int main(){

  //Variáveis locais
  uint64_t number;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro: ");
    scanf("%lu", &number);

    //Calculando as raízes primitivas de n
    primitive_root(number);

  //Finalizando a aplicação
  return 0;

}
