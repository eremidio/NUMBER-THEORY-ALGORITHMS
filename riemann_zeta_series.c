//VAMOS CRIAR  UM PROGRAMA QUE TESTA AS RORINAS CRIADAS NO ARQUIVO riemann_zeta_series.h
//COMPILAR ESTE PROGRAMA COMO COMANDO: gcc -o riemann_zeta_series riemann_zeta_series.c -lm


//Cabeçalho
#include"riemann_zeta_series.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  long double apery_constant, pi, zeta2;

  //Procedimentos
    //Calculando o valor de π
    zeta2=riemann_zeta_asymptotic_series(2); //ζ(2)=π²/6
    pi=sqrt(zeta2*6);
    printf("[ζ(2)=π²/6] π=%.10Lf\n", pi);

    //Calculando o valor da constant de Apéry 
    apery_constant=riemann_zeta_asymptotic_series(3);
    printf("[Constante de Apéry] ζ(3)=%.10Lf\n", apery_constant);


  //Finalizando a aplicação
  return 0;
  
}
