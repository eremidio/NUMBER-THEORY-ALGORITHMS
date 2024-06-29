//VAMOS CRIAR UM PROGRAMA QUE TESTAS AS ROTINAS CRIADAS NO ARQUIVO rka_factorization_algorithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o rka_factorization_algorithm rka_factorization_algorithm.c -O2 -lm


//Cabeçalho
#include"rka_factorization_algorithm.h"


//Função principal
int main(){

  //Variáveis
  uint64_t number;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro a ser fatorado: ");
    if(scanf("%lu", &number)!=1) return 0;

    //Fatorando o número em questão
    rka_factorization_algorithm(number);

  //Finalizando a aplicação
  return 0;
}

