//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO euler_totient_function_lambert_series.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o euler_totient_function_lambert_series euler_totient_function_lambert_series.c -O2

//Cabeçalho 
#include"euler_totient_function_lambert_series.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int32_t n;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    //Calculando a função totiente de Euler no intervalo {1,2,...,n}
    int32_t* totient_array=compute_totient_function(n);

    for(int32_t i=1; i<=n; ++i) printf("φ(%i)=%i, ", i, totient_array[i]);
    printf("...\n");


    //Limpando o cachê de memória
    if(totient_array) free(totient_array);
    totient_array=NULL;

  //Finalizando a aplicação
  return 0;

}
