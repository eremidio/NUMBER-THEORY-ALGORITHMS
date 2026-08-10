//VAMOS CRIAR UKM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO sum_of_squares_function_sieving.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o sum_of_squares_function_sieving sum_of_squares_function_sieving.c -lm -O2


//Cabeçalho
#include"sum_of_squares_function_sieving.h"
#include<stdio.h>

//Função principal
int main(){

  //Variáveis locais
  int64_t n;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%li", &n)!=1) return 0;

    //Calculando a função r(2, n)
    int64_t* rk2_array = compute_sum_of_square_function_k2(n);

    for(int64_t i=1; i<=n; ++i) printf("r(2, %li)=%li, ", i, rk2_array[i]);
    printf("...\n\n");


    //Calculando a função r(3, n)
    int64_t* rk3_array = compute_sum_of_square_function_k3(n);

    for(int64_t i=1; i<=n; ++i){
      if(rk3_array[i]>0) printf("r(3, %li)=%li, ", i, rk3_array[i]);
    }
    printf("...\n\n");


    //Calculando a função r(4, n)
    int64_t* rk4_array = compute_sum_of_square_function_k4(n);

    for(int64_t i=1; i<=n; ++i){
      printf("r(4, %li)=%li, ", i, rk4_array[i]);
    }
    printf("...\n\n");


    //Calculando a função r(5, n)
    int64_t* rk5_array = compute_sum_of_square_function_k5(n);

    for(int64_t i=1; i<=n; ++i){
      if(rk5_array[i]>0) printf("r(5, %li)=%li, ", i, rk5_array[i]);
    }
    printf("...\n\n");


    //Calculando a função r(6, n)
    int64_t* rk6_array = compute_sum_of_square_function_k6(n);

    for(int64_t i=1; i<=n; ++i){
      printf("r(6, %li)=%li, ", i, rk6_array[i]);
    }
    printf("...\n\n");


    //Calculando a função r(8, n)
    int64_t* rk8_array = compute_sum_of_square_function_k8(n);

    for(int64_t i=1; i<=n; ++i){
      printf("r(8, %li)=%li, ", i, rk8_array[i]);
    }
    printf("...\n\n");

    //Limpando o cachê de memória
    if(rk2_array) free(rk2_array); rk2_array=NULL;
    if(rk3_array) free(rk3_array); rk3_array=NULL;
    if(rk4_array) free(rk4_array); rk4_array=NULL;
    if(rk5_array) free(rk5_array); rk5_array=NULL;
    if(rk6_array) free(rk6_array); rk6_array=NULL;
    if(rk8_array) free(rk8_array); rk8_array=NULL;
  

  //Finalizando a aplicação
  return 0;

}
