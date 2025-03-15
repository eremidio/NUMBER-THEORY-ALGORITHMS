//VAMOS CRIAR UM PROGRAMA PARA TESTAR MAS ROTINAS CRIADAS NO ARQUIVO divisor_counting_lambert_series.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o divisor_counting_lambert_series divisor_counting_lambert_series.c -O2


//Cabeçalho
#include"divisor_counting_lambert_series.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int32_t n;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    //Calculando a função d(n) no intervalo {1,2,...,n}
    int32_t* divisors_counting_array=compute_divisor_counting_function(n);

    for(int32_t i=1; i<=n; ++i) printf("d(%i)=%i, ", i, divisors_counting_array[i]);
    printf("...\n");


    //Limpando o cachê de memória
    if(divisors_counting_array) free(divisors_counting_array);
    divisors_counting_array=NULL;

  //Finalizando a aplicação
  return 0;

}
