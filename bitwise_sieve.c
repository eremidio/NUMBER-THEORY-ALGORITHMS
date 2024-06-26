//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO bitwise_sieve.h
//COMPILAR ESTE PROGRAMA: gcc -o bitwise_sieve bitwise_sieve.c -lm 



//Cabeçalho
#include"bitwise_sieve.h"


//Função principal
int main(){

  //Variáveis locais
  uint64_t n;

  //Procedimentos
    //Recebendo input do usuário
    printf("Limite superior para a sequência de números primos:\n");
    if(scanf("%lu", &n)!=1) return 0;

    //Computandonúmeros primos usando a peneira de Eratóstenes
    bitwise_sieve(n);

  //Finalizando a aplicação
  return 0;

}
