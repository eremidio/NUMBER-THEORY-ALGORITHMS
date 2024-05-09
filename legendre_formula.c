//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS DO ARQUIVO legendre_formula.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o legendre_formula legendre_formula.c -lm -O2


//Cabeçalho
#include"legendre_formula.h"


//Função principal
int main(){

 //Variáveis locais
 int64_t limit;

 //Procedimentos
  //Recebendo input do usuário
  printf("Limite superior para a contagem de primos: ");
  if(scanf("%li", &limit)!=1)
    return 0;

  //Contagem de primos
  printf("Número de primos até %li: %li.\n", limit, prime_counting_function(limit));


 //Finalizando a aplicação
 return 0;

          }
