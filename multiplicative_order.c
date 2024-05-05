//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO multiplicative_order.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o multiplicative_order multiplicative_order.c -lm


//Cabeçalho
#include"multiplicative_order.h"


//Função principal
int main(){

 //Variáveis
 uint64_t a, n;


 //Procedimentos
  //Recebendo input do usuário
  printf("Usuário digite um número n: ");
  scanf("%lu", &n);

  printf("Usuário digite um número a coprimo com n: ");
  scanf("%lu", &a);

  //Calculando o valor da ordem multiplicativa
  printf("ord(%lu) mod %lu = %lu.\n", a, n, multiplicative_order(a, n));


  //Finalizando a aplicação
  return 0;
          }
