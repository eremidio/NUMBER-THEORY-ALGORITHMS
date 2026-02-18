//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO williams_factorization.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o williams_factorization williams_factorization.c -lm -lgmp -O3



//Cabeçalho
#include"williams_factorization.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  char number_string[100];
  int32_t B=0, A=0;
  mpz_t n, factor;
  
  //Inicializando variáveis
  mpz_init(n); mpz_init(factor);

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro a ser fatorado] n: ");
    if(scanf("%99s", number_string)!=1) return 0;

    printf("[Parâmetro] B: ");
    if(scanf("%i", &B)!=1) return 0;

    printf("[Parâmetro da sequência de Lucas] A: ");
    if(scanf("%i", &A)!=1) return 0;

    mpz_set_str(n, number_string, 10/*base decimal*/);

    //Fatorando o número em questão 
    williams_factorization(n, factor, A, B);
    if(mpz_cmp(factor, n)==0)
      printf("Algoritmo falhou\n");
    else
      gmp_printf("Fator de %Zd encontrado: %Zd\n", n, factor);

    //Limpeza do cachê de memória
    mpz_clear(n); mpz_clear(factor);


  //Finalizando a aplicação
  return 0;

}

