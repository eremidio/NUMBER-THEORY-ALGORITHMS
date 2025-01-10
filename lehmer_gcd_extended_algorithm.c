//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO lehmer_gcd_extended_algorithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o lehmer_gcd_extended_algorithm lehmer_gcd_extended_algorithm.c


//Cabeçalho
#include"lehmer_gcd_extended_algorithm.h"


//Função principal
int main(){

  //Variáveis locais
  __int128_t a, b;
  char number_string1[40];
  char number_string2[40];


  //Procedimentos
    //Recebendo input
    printf("Valor 1: ");
    scanf("%s", number_string1);
    a=scanf128(number_string1);
    printf("Valor 2: ");
    scanf("%s", number_string2);
    b=scanf128(number_string2);

    //Executando o algoritmo de Lehmer extendido 
    lehmer_extended_algorithm(a, b);

  //Finalizando a aplicação 
  return 0;

}
