//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO mersenne_prime.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o mersenne_prime mersenne_prime.c -lgmp -lm -O2


//Cabeçalho
#include"mersenne_prime.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  mpz_t M; mpz_init(M);
  uint64_t n;


  //Procedimentos
    //Recebendo input do usuário
    printf("[Index do número de Mersenne] n: ");
    if(scanf("%lu", &n)!=1) goto end;

    //Calculando o n-ésimo número de Mersenne
    get_mersenne_number(M, n);
    gmp_printf("M(%lu) = %Zd\n", n, M);

    //Aplicando o teste de Lucas-Lehmer
    bool test=is_mersenne_prime(n, M);
    if(test) printf("M(%lu) é primo\n", n);
    else printf("M(%lu) não é primo\n", n);  
    

    //Limpando o cachê de memória
    end:
    mpz_clear(M);

  //Finalizando a aplicação
  return 0;


}
