//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO mertens_function_recursive.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o mertens_function_recursive mertens_function_recursive.c -lm -O2


//Cabeçalho
#include"mertens_function_recursive.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t n;


  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%li", &n)!=1) return 0;

    //Computando um array de valores da função M(n)
    int64_t* mertens_array=compute_mertens_array(n);

    for(int64_t i=0; i<=n; ++i) printf("M(%li)=%li, ", i, mertens_array[i]);
    printf("...\n");


    //Liberando cachê de memória
    if(mertens_array) free(mertens_array); mertens_array=NULL;
  
  //Finalizando a aplicação
  return 0;  

}
