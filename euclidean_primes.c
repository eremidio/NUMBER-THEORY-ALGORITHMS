//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO euclidean_primes.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o euclidean_primes euclidean_primes.c -lm



//Cabeçalho
#include"euclidean_primes.h"


//Função principal
int main(){

  //Variáveis locais
  int64_t bound1, bound2, bound3;


  //Procedimentos
    //Recebendo input do usuário
    printf("Limite superior para o conjunto de primos iniciais: ");
    scanf("%li", &bound1);

    printf("Limite inferior para o conjunto de primos euclidianos: ");
    scanf("%li", &bound2);

    printf("Limite superior para o conjunto de primos euclidianos: ");
    scanf("%li", &bound3);


    //Calculando um conjunto de primos euclidianos
    setup_euclidean_prime_set(bound1, bound2, bound3);

  //Finalizando a aplicação
  return 0;

}
