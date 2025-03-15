//VAMOS CRIAR UM PROGRAMA PARA TESTAR MAS ROTINAS CRIADAS NO ARQUIVO sum_of_divisors_lambert_series.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o sum_of_divisors_lambert_series sum_of_divisors_lambert_series.c -O2


//Cabeçalho
#include"sum_of_divisors_lambert_series.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int32_t n;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    //Calculando a função σ(n) no intervalo {1,2,...,n}
    int32_t* sum_of_divisors_array=compute_sum_of_divisors_function(n);

    for(int32_t i=1; i<=n; ++i) printf("σ(%i)=%i, ", i, sum_of_divisors_array[i]);
    printf("...\n");


    //Limpando o cachê de memória
    if(sum_of_divisors_array) free(sum_of_divisors_array);
    sum_of_divisors_array=NULL;

  //Finalizando a aplicação
  return 0;

}
