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


  //Testando peneira num intervalo
  printf("Teste  Φ(1000, 11): %li\n", phi_mn_raw(1000, 11));
  printf("Teste  Φ(10000, 25): %li\n", phi_mn_raw(10000, 25));
  printf("Teste  Φ(1000000, 168): %li\n", phi_mn_raw(1000000, 168));

 //Finalizando a aplicação
 return 0;

          }
