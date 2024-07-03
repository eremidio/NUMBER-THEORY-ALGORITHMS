//VAMOS CRIAR UM PROGRAMA PARA TESTAR ROTINAS CRIADAS NO ARQUIVO euler_factorization_algorithm.h 
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o euler_factorization_algorithm euler_factorization_algorithm.c -lm -O2


//Cabeçalho
#include"euler_factorization_algorithm.h"


//Fuynção principal
int main(){

  //Variáveis locais
  int64_t number;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro a ser fatorado: ");
    if(scanf("%li", &number)!=1) return 0;

    //Fatorando o número em questão
    euler_factorization_method(number);

  //Finalizando a aplicação
  return 0;


}
