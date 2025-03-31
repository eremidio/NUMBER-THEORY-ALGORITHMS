//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO logarithmic_functions_lambert_series.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o logarithmic_functions_lambert_series logarithmic_functions_lambert_series.c -lm -O2


//Cabeçalho
#include"logarithmic_functions_lambert_series.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t n;


  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%li", &n)!=1) return 0;

    //Computando a função de von Mangoldt em um intervalo
    printf("Λ(n) até  n=%li: ", n);
    double* mangoldt_array = generate_von_mangoldt_array(n);
    for(int64_t i=1; i<=n; ++i) printf("Λ(%li)=%.3lf, ", i, mangoldt_array[i]);
    printf("...\n\n");


    //Computando a função de Chebyshev do segundo tipo em um intervalo
    printf("Ψ(n) até  n=%li: ", n);
    double* chebyshev2_array = generate_chebyshev_second_array(n, mangoldt_array);
    for(int64_t i=1; i<=n; ++i) printf("Ψ(%li)=%.3lf, ", i, chebyshev2_array[i]);
    printf("...\n\n");


    //Computando a função de Chebyshev do primeiro tipo em um intervalo
    printf("θ(n) até  n=%li: ", n);
    double* chebyshev1_array = generate_chebyshev_first_array(n, mangoldt_array);
    for(int64_t i=1; i<=n; ++i) printf("θ(%li)=%.3lf, ", i, chebyshev1_array[i]);
    printf("...\n\n");


    //Limpando o cachê de memória
    if(mangoldt_array) free(mangoldt_array); mangoldt_array=NULL;
    if(chebyshev2_array) free(chebyshev2_array); chebyshev2_array=NULL;
    if(chebyshev1_array) free(chebyshev1_array); chebyshev1_array=NULL;


  //Finalizando a aplicação
  return 0;

}
