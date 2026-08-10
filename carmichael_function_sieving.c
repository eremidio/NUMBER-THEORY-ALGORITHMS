//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO carmichael_function_sieving.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o carmichael_function_sieving carmichael_function_sieving.c -lm -O2


//Cabeçalho
#include"carmichael_function_sieving.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int32_t n;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    //Calculando a função de totiente de Carmichael no intervalo {1,2,...,n}
    int32_t* carmichael_array = compute_carmichael_function(n);

    for(int32_t i=1; i<=n; ++i) printf("λ(%i)=%i, ", i, carmichael_array[i]);
    printf("...\n");


    //Limpando o cachê de memória
    if(carmichael_array) free(carmichael_array); carmichael_array=NULL;


  //Finalizando a aplicação
  return 0;

}
