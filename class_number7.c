//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO class_number7.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o class_number7 class_number7.c -lm -O2


//Cabeçalho
#include"class_number7.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  __int128_t U, T;
  int32_t D;
  
  //Procedimentos
    //Recebendo input do usuário
    printf("[Discriminante fundamental] D: ");
    if(scanf("%i", &D)!=1) return 0;

    //Computando a unidade fundamental e o regulador R(D) de Q(√D)
    compute_fundamental_unit(&T, &U, D);
    printf("Unidade fundamental: η=(1/2)(T+U√%i)\n", D);
    printf("T = "); printf128(T);
    printf("U = "); printf128(U);

    double epsilon =0.5*(T+sqrt(D)*U);
    double RD=log(epsilon);
    printf("[Regulador] R(%i)=%0.4lf\n", D, RD);


    //Computando o número de classe usando aproximações vias séries-L de Dirichlet
    int32_t hD= class_number_dirichlet_l_series_heuristic(D, RD);
    printf("[Número de classe - valor provável] h(%i)=%i\n", D, hD);
    if(hD==0) printf("Aproximação heurística não convergida!\n");


  //Finalizando a aplicação
  return 0;

}
