//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADASNO ARQUIVO new_factorization_algorithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o new_factorization_algorithm new_factorization_algorithm.c -lm -O2


//Cabeçalho
#include"new_factorization_algorithm.h"


//Função principal
int main(){

  //Variáveis locais
  uint64_t n;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro: ");
    if(scanf("%lu", &n)!=1) return 0;

    //Fatorando números inteiros
    new_factorization_algorithm(n);

  //Finalizando a aplicação
  return 0;

}
