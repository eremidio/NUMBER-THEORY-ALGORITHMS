//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO ali_primality_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o ali_primality_test ali_primality_test.c -O2


//Cabeçalho
#include"ali_primality_test.h"

//Função principal
int main(){

  //Variáveis locais
  uint64_t number;

  //Procedimentos
    //Recebendo o input
    printf("Número a ser testado: ");
    if(scanf("%lu", &number)!=1)  return 0;


    //Usando o teste de Miller-Rabin para inteiros de 128 bits
    if(ali_primality_test(number)==true)
      printf("O número em questão é (forte candidato a) primo.\n");
    else
      printf("O número em questão é composto.\n");


  //Finalizando a aplicação
  return 0;

} 
