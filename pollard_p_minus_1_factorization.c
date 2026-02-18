//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO pollard_p_minus_1_factorization.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o pollard_p_minus_1_factorization pollard_p_minus_1_factorization.c -O2 -lgmp -lm


//Cabeçalho
#include"pollard_p_minus_1_factorization.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  char number_string[100];
  int64_t B=0;
  int st2;
  mpz_t n, factor;
  
  //Inicializando variáveis
  mpz_init(n); mpz_init(factor);

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro a ser fatorado] n: ");
    if(scanf("%99s", number_string)!=1) return 0;

    printf("[Parâmetro] B: ");
    if(scanf("%li", &B)!=1) return 0;

    printf("[Parâmetro] Estágio 2 ('0'= não, '1'= sim): ");
    if(scanf("%d", &st2)!=1) return 0;

    mpz_set_str(n, number_string, 10/*base decimal*/);

    //Fatorando o número em questão 
    pollard_p_minus_1_factorization(n, factor, B, st2);
    if(mpz_cmp(factor, n)==0)
      printf("Algoritmo falhou\n");
    else
      gmp_printf("Fator de %Zd encontrado: %Zd\n", n, factor);

    //Limpeza do cachê de memória
    mpz_clear(n); mpz_clear(factor);


  //Finalizando a aplicação
  return 0;

}
