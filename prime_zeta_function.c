//VAMOS CRIAR UM PROGRAMA QUETESTA AS ROTINAS CRIADAS NO ARQUIVO prime_zeta_function.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o  prime_zeta_function prime_zeta_function.c -lm -O2


//Cabeçalho
#include"prime_zeta_function.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  long double s;


  //Procedimentos 
    //Recebendo input do usuário
    printf("[Número real] s: ");
    if(scanf("%Lf", &s)!=1) return 0;

    //Calculando a função zeta primo P(s)
    long double Ps=prime_zeta_function(s);
    printf("P(%.1Lf)=%.9Lf\n", s, Ps);


  //Finalizanado a aplicação
  return 0;  

}
