//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO twin_prime_conjecture.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o twin_prime_conjecture twin_prime_conjecture.c -lm -O2


//Cabeçalho
#include"twin_prime_conjecture.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  long double interval_size, twin_prime_constant=compute_prime_twin_constant();


  //Procedimentos
    //Recebendo input do usuário
    printf("[Número real-tamanho do intevalo] L: ");
    if(scanf("%Lf", &interval_size)!=1) return 0;

    //Calculando a constante de primos gêmeos
    printf("[Constante dos primos gêmeos] C=%.9Lf\n", twin_prime_constant);

    //Computando o número aproximado de constelações de primos gêmeos em um intervalo de tamanho fixo
    printf("[Número aproximado de constelações de primos gêmeos em um intervalo de tamanho %.0Lf] #T=%.1Lf\n",
           interval_size, compute_twin_prime_pair_limit(interval_size));

    printf("[Erro na estiva anterior] R=%.1Lf\n", compute_error_term(interval_size));


  //Finalizando a aplicação
  return 0;

}
