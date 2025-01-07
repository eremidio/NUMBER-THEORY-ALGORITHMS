//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO lehmer_gcd_algorithm.h
//COMPILAR ESTE PROEGRAMA COM O COMANDO: gcc -o lehmer_gcd_algorithm lehmer_gcd_algorithm.c -lm


//Cabeçalho
#include"lehmer_gcd_algorithm.h"


//Função principal
int main(){

  //Variáveis locais
  char number_string1[40];
  char number_string2[40];
  __int128_t a, b, gcd;


  //Procedimentos
    //Recebendo input
    printf("Valor 1: ");
    scanf("%s", number_string1);
    a=scanf128(number_string1);
    printf("Valor 2: ");
    scanf("%s", number_string2);
    b=scanf128(number_string2);



    //Calculando o produto das duas parcelas
    gcd =lehmer_gcd_s128(a, b);

    printf("mdc: ");
    printf128(gcd);

  //Finalizando a aplicação 
  return 0;

}
