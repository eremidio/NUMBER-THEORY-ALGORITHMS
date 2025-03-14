//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO mobius_function_lambert_series.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o mobius_function_lambert_series mobius_function_lambert_series.c -O2


//Cabeçalho 
#include"mobius_function_lambert_series.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int32_t n;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    //Calculando a função de Möbius no intervalo {1,2,...,n}
    int8_t* mobius_array=compute_mobius_function(n);

    for(int32_t i=1; i<=n; ++i) printf("μ(%i)=%i, ", i, mobius_array[i]);
    printf("...\n");


    //Limpando o cachê de memória
    if(mobius_array) free(mobius_array);
    mobius_array=NULL;


  //Finalizando a aplicação
  return 0;

} 
