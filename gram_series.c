//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO gram_series.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o  gram_series gram_series.c -lm -O3


//Cabeçalho
#include"gram_series.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t n;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%li", &n)!=1) return 0;


    //Calculando a proximação de contagem de primos usando a série de Gram
    long double Gx=gram_series_approximation(n);
    printf("[Aproximação de π(%li) via série de Gram] G(%li)=%0.9Lf\n", n, n, Gx);


  //Finalizando a aplicação
  return 0;

}
