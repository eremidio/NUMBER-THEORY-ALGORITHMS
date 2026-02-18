//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO williams_factorization_algebraic.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o williams_factorization_algebraic williams_factorization_algebraic.c -lm -O2

//Cabeçalho
#include"williams_factorization_algebraic.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t n, B;


  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro a ser fatorado] n: ");
    if(scanf("%li", &n)!=1) return 0;

    printf("[Parâmetro] B: ");
    if(scanf("%li", &B)!=1) return 0;

    //Fatorando o número em questão
    williams_factorization_algebraic(n, B);


  //Finalizando a aplicação
  return 0;

}
