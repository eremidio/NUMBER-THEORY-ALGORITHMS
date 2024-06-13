//VAMOS CRIIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO mckee_algorithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o mckee_algorithm mckee_algorithm.c -lm


//Cabeçalho
#include"mckee_algorithm.h"

//Função principal
int main(){

  //Variáveis locais
  int64_t number;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro a ser fatorado: ");
    scanf("%li", & number);

  //Fatorando o número em questão
  mckee_algorithm(number);

  //Finalizando a aplicação
  return 0;

          }
