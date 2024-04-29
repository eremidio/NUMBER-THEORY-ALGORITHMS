//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO lucas_primality_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o lucas_primality_test lucas_primality_test.c -lm -O2


//Cabeçalho
#include"lucas_primality_test.h"


//Função principal
int main(){
 //Váriaveis locais
 uint64_t number;
 bool result;

 //Procedimentos

 //Recebendo input do usuário
 printf("Digite um número que será testado:\n");
 if(scanf("%lu", &number)!=1);

 //Executando o teste de primalidade de Lucas
 result = lucas_primality_test(number, Verbose);
 if(result)
  printf("%lu é primo.\n", number);
 else
  printf("%lu não é primo.\n", number);

 //Finalizando a aplicação
  return 0;

          }
