//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO pollard_rho_factorization.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o pollard_rho_factorization pollard_rho_factorization.c -02 -lgmp


//Cabeçalho
#include"pollard_rho_factorization.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  char number_string[80];
  int a=0;
  mpz_t n, factor;
  
  //Inicializando variáveis
  mpz_init(n); mpz_init(factor);

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro a ser fatorado] n: ");
    if(scanf("%79s", number_string)!=1) return 0;

    printf("[Semente inicial] a: ");
    if(scanf("%d", &a)!=1) return 0;

    mpz_set_str(n, number_string, 10/*base decimal*/);

    //Fatorando o número em questão 
    pollard_rho_factorization(n, factor, a);
    if(mpz_cmp(factor, n)==0)
      printf("Algoritmo falhou\n");
    else
      gmp_printf("Fator de %Zd encontrado: %Zd\n", n, factor);

    //Limpeza do cachê de memória
    mpz_clear(n); mpz_clear(factor);


  //Finalizando a aplicação
  return 0;

}
