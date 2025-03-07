//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO vantieghems_criterion.h
//COMPILAR ESTE PROGRAMA COMO COMANDO: gcc -o vantieghems_criterion vantieghems_criterion.c -O2 -lgmp


//Cabeçalho
#include"vantieghems_criterion.h"
#include<stdio.h>

//Função principal
int main(){

  //Váriaveis locais
  unsigned long number;
  bool result;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número que será testado:\n");
    if(scanf("%lu", &number)!=1);

    //Executando o teste de primalidade de Lucas
    result = vantieghems_criterion(number);
    if(result) printf("%lu é primo.\n", number);
    else  printf("%lu não é primo.\n", number);

  //Finalizando a aplicação
  return 0;

}

