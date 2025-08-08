//VAMOS CRIAR UM PROGRAMA PARATESTAR AS ROTINAS CRIADAS NO ARQUIVO ramanujan_sum2.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o ramanujan_sum2 ramanujan_sum2.c -O2


//Cabeçalho
#include<stdio.h>
#include"ramanujan_sum2.h"


//Função principal
int main(){

  //Variáveis locais
  int32_t n, q;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;
    printf("[Inteiro] q: ");
    if(scanf("%i", &q)!=1) return 0;


    //Calculando a função c(q,n) no intervalo {1,2,...,n}
    int32_t* ramanujan_array = compute_ramanujan_sum(q, n);

    for(int32_t i=1; i<=n; ++i) printf("c(%i, %i)=%i, ", q, i, ramanujan_array[i]);
    printf("...\n");


    //Limpando o cachê de memória
    if(ramanujan_array) free(ramanujan_array);
    ramanujan_array=NULL;

  //Finalizando a aplicação
  return 0;

}
