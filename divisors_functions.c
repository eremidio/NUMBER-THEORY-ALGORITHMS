//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO divisors_functions.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o divisors_functions divisors_functions.c -lm -O2


//Cabeçalho
#include"divisors_functions.h"

//Função principal
int main(){

  //Variaveis locais
  int64_t n;

  //Procedimentos
    //Recebendo input do usuário
    printf("Inteiro positivo: ");
    if(scanf("%li", &n)!=1)
      return 0;

    //Calculando as funções de soma e contagem de divisores
    printf("τ(%li)=%li\n", n, divisors_counting(n));
    printf("σ(%li)=%li\n", n, sum_of_divisors(n));  

    if(is_perfect_number(n))
      printf("%li é um número perfeito\n", n);
    else
      printf("%li não é um número perfeito\n", n);


  //Resultado
  return 0;


          }
