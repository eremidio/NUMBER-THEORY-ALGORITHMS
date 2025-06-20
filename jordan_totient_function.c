//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO jordan_totient_function.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o jordan_totient_function jordan_totient_function.c -O2


//Cabeçalho
#include"jordan_totient_function.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int32_t n;
  int k;


  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;
    printf("[Inteiro] k: ");
    if(scanf("%i", &k)!=1) return 0;

    //Computando a função totiente de Jordan
    int64_t* jordan_totient_array=compute_jordan_totient_array(n, k);
    for(int32_t i=0; i<=n; ++i) printf("J(%i, %i)=%lu, ", i, k, jordan_totient_array[i]);
    printf("...\n");

    //Limpando o cachê de memória
    if(jordan_totient_array) free(jordan_totient_array); jordan_totient_array=NULL;


  //Finalizando a aplicação
  return 0;

}
