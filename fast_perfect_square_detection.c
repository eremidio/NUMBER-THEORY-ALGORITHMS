//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO fast_perfect_square_detection.h 
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o fast_perfect_square_detection fast_perfect_square_detection.c -lm -O2


//Cabeçalho
#include"fast_perfect_square_detection.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  uint64_t n, r=0, counter=0;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%lu", &n)!=1) return 0;


    //Calculando número de quadrados perfeitos no limite espeficicado pelo usuário:
    for(uint64_t i=1; i<=n; ++i){
      if(perfect_square_detection_64bits(i, &r)){
        counter++;
        printf("%lu, ", i);
      }
    };

    printf("...\n\n");
    printf("Número de quadrados perfeitos até %lu: %lu\n", n, counter);


  //Finalizandoa aplicação
  return 0;

}

