//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO atkin_sieve.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o atkin_sieve atkin_sieve.c -O2 -lm


//Cabeçalho
#include"atkin_sieve.h"

//Função principal
int main(){

  //Variáveis locais
  int64_t n;

  //Procedimentos
    //Recebendo o input do usuário
    printf("[Inteiro - limitante para a sequência de números primos] n: ");
    if(scanf("%li", &n)!=1) return 0;


    //Computando números primos usando o crivo de Atkin
    atkin_sieve(n);


  //Finalizando a aplicação
  return 0;
          
}
