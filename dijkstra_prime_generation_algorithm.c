//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO dijkstra_prime_generation_algorithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o dijkstra_prime_generation_algorithm dijkstra_prime_generation_algorithm.c -O2


//Cabeçalho
#include"dijkstra_prime_generation_algorithm.h"

//Função principal
int main(){

  //Variáveis locais
  int64_t n;

  //Procedimento
    //Recebendo input do usuário
    printf("Usuário digite um número inteiro:\n");
    if(scanf("%li", &n)!=1) return 0;

    //Cálculando números primos usando o algoritmo de Dijkstra
    dijkstra_prime_generating_algorithm(n);
    printf("\n");

  //Finalizando a aplicação
  return 0;

}
