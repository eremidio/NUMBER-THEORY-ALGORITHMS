//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO prime_number_estimation.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o prime_number_estimation prime_number_estimation.c -lm


//Cabeçalho
#include"prime_number_estimation.h"
#include<stdio.h>

//Função principal
int main(){

  //Variáveis locais
  uint64_t nth, upper_prime, lower_prime;
  uint64_t limit, lower_prime_counting, upper_prime_counting;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um inteiro: ");
    if(scanf("%lu",&nth)!=1) return 0;

    printf("Digite um limite para a contagem de primos: ");
    if(scanf("%lu",&limit)!=1) return 0;

    //Cálculando limitantes para o n-ésimo número primo;
    get_nth_prime_bounds(nth, &upper_prime, &lower_prime);
    printf("Limitantes para o %lu-ésimo primo: %lu<p(%lu)<%lu \n", nth, lower_prime, nth, upper_prime);

    //Cálculo do limitante da função de contagem de primos
    prime_counting_function_bounds(limit, &upper_prime_counting, &lower_prime_counting);
    printf("Limitantes para π(%lu): %lu<π(%lu)<%lu \n", limit, lower_prime_counting, limit, upper_prime_counting);


  //Finalizando a aplicação
  return 0;

}
