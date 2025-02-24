//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO complementary_error_function.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o complementary_error_function complementary_error_function.c -lm


//Cabeçalho
#include"complementary_error_function.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  long double x, erfcx;


  //Procedimento
    //Recebendo input do usuário
    printf("[Argumento real] x: ");
    scanf("%Lf", &x);

    //Calculando a função erfc(x)
    erfcx=complementary_error_function(x);
    printf("erfc(%Lf)=%.10Lf\n", x, erfcx);

  //Finalizando a aplicação
  return 0;

}
