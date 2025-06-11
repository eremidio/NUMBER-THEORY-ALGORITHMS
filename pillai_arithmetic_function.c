//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO pillai_arithmetic_function.h
//COMPILAR ESTE PROGRAMA: gcc -o pillai_arithmetic_function pillai_arithmetic_function.c -O2


//Cabeçalho
#include"pillai_arithmetic_function.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int32_t n;

  //Procedimentos
    input:
    //Recebendo input do usuário
    printf("[Inteiro-superior ou igual a 100] n: ");
    if(scanf("%i", &n)!=1) return 0;
    if(n<100) goto input;

    //Calculando a função P(n) intervalo {1,2,...,n}
    int32_t* pillai_array=compute_pillai_arithmetic_function(n);

    for(int32_t i=1; i<=n; ++i) printf("P(%i)=%i, ", i, pillai_array[i]);
    printf("...\n");


    //Teste de primalidade usando a função P(n)
    printf("\nPrimos  até %i: ", n);
    for(int32_t i=1; i<=n; ++i){
      if(pillai_primality_test(pillai_array, i)) printf("%i, ", i);
    }
    printf("...\n");

    //Limpando o cachê de memória
    if(pillai_array) free(pillai_array);
    pillai_array=NULL;


  //Finalizando a aplicação
  return 0;

}
