//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO carmichael_numbers.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: clang -o carmichael_numbers carmichael_numbers.c -lm


//Cabeçalho
#include"carmichael_numbers.h"
#include<stdio.h>

//Função principal
int main(){

  //Variáveis locais
  uint64_t number;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro: ");
    scanf("%lu", &number);

    //Testando se o número em questão é um número de Carmichael
    bool test=carmichael_checker(number);

    if(test==true)
     printf("O número %lu é um número de Carmichael.\n", number);
    else
     printf("O número %lu não é um número de Carmichael.\n", number);


  //Finalizando a aplicação
  return 0;

}
