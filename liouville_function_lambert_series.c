//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO liouville_function_lambert_series.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o liouville_function_lambert_series liouville_function_lambert_series.c -O2


//Cabeçalho 
#include"liouville_function_lambert_series.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int32_t n;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    //Calculando a função de Liouville no intervalo {1,2,...,n}
    int8_t* liouville_array=compute_liouville_function(n);

    for(int32_t i=1; i<=n; ++i) printf("λ(%i)=%i, ", i, liouville_array[i]);
    printf("...\n");


    //Limpando o cachê de memória
    if(liouville_array) free(liouville_array);
    liouville_array=NULL;


  //Finalizando a aplicação
  return 0;

}  
