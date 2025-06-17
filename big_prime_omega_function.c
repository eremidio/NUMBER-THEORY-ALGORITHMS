//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO big_prime_omega_function.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o big_prime_omega_function big_prime_omega_function.c -O2


//Cabeçalho
#include"big_prime_omega_function.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int32_t n;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    //Calculando a função de Ω(n) no intervalo {1,2,...,n}
    int32_t* big_prime_omega_array = compute_capital_omega_function(n);

    for(int32_t i=1; i<=n; ++i) printf("Ω(%i)=%i, ", i, big_prime_omega_array[i]);
    printf("...\n");


    //Limpando o cachê de memória
    if(big_prime_omega_array) free(big_prime_omega_array);
    big_prime_omega_array=NULL;


  //Finalizando a aplicação
  return 0;

}
