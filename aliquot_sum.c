//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO aliquot_sum.h
//COMPILAR O PROGRAMA COM O COMANDO: gcc -o aliquot_sum aliquot_sum.c -lm -O3


//Cabeçalho
#include"aliquot_sum.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int32_t n;


  //Procedimentos
    //Recebendo input do usuário  
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    //Computando a função aritmética s(n)
    int32_t* aliquot_sum_array=compute_aliquot_sum_array(n);

    printf("Função aritmética de soma de aliquota no intevalo [0, %i]:\n ", n);
    for(int32_t i=0; i<=n; ++i) printf("s(%i)=%i, ", i, aliquot_sum_array[i]);
    printf("...\n\n");
    
    //Checando por números perfeitos, primos, defectivos e abundantes
    printf("Números primos no intevalo: ");
    for(int32_t i=0; i<=n; ++i){
      if(is_prime_number_aliq(i, aliquot_sum_array))  printf("%i, ", i);
    }
    printf("...\n\n");

    printf("Números perfeitos no intevalo: ");
    for(int32_t i=0; i<=n; ++i){
      if(is_perfect_number_aliq(i, aliquot_sum_array))  printf("%i, ", i);
    }
    printf("...\n\n");

    printf("Números abundantes no intevalo: ");
    for(int32_t i=0; i<=n; ++i){
      if(is_abundant_number_aliq(i, aliquot_sum_array))  printf("%i, ", i);
    }
    printf("...\n\n");

    printf("Números defectivos no intevalo: ");
    for(int32_t i=0; i<=n; ++i){
      if(is_defective_number_aliq(i, aliquot_sum_array))  printf("%i, ", i);
    }
    printf("...\n\n");



    //Limpando o cachê de memória
    if(aliquot_sum_array) free(aliquot_sum_array); aliquot_sum_array=NULL;

  //Finalizando a aplicação
  return 0;

}
