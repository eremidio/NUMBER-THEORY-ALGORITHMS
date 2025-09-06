//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO dirichlet_l_series.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o dirichlet_l_series dirichlet_l_series.c -lm -O3


//Cabeçalho
#include"dirichlet_l_series.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  double s;
  int k;


  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] k:  "); if(scanf("%i", &k)!=1) return 0;
    printf("[Real] s:  "); if(scanf("%lf", &s)!=1) return 0;

    //Calculandon o resultado parcial da série-L
    long double d_series = compute_l_series(k, s);
    printf("L(%i, %lf)=%.7Lf\n", k, s, d_series);


    //Aproximando o valor de π
    const long double pi = (4.0*compute_l_series((-4), 1));
    printf("π ≃ %.7Lf\n", pi);
  

  //Fianlizando a aplicação
  return 0;
}

