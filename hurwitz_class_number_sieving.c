//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO hurwitz_class_number2.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o hurwitz_class_number_sieving hurwitz_class_number_sieving.c -lm


//Cabeçalho
#include"hurwitz_class_number_sieving.h"
#include<stdio.h>



//Função principal
int main(){

  //Variáveis locais
  int64_t N;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] N: ");
    scanf("%li", &N);

    //Computando a função lambda de Hurwitz
    struct hurwitz_fraction*  hurwitz_lambda_array = hurwitz_lambda_function(N+1);

    printf("[Função lambda de Hurwitz] λ(n): ");
    for(int64_t i=0; i<=N; ++i){
      if(hurwitz_lambda_array[i].den==2)
        printf("λ(%li)=%li/%li, ", i, hurwitz_lambda_array[i].num, hurwitz_lambda_array[i].den);
      if(hurwitz_lambda_array[i].den==1)
        printf("λ(%li)=%li, ", i, hurwitz_lambda_array[i].num);
    };
    printf("...\n");
  

    //Computando o número de classe de Hurwitz
    struct hurwitz_fraction*  H_array = hurwitz_class_number_recursive(N, hurwitz_lambda_array);

    printf("\n[Número de classe de Hurwitz] H(n): ");
    for(int64_t j=0; j<=N; ++j){
      if(H_array[j].num%H_array[j].den==0) printf("H(%li)=%li, ", j, (H_array[j].num/H_array[j].den));
      else printf("H(%li)=%li/%li, ", j, H_array[j].num, H_array[j].den);

    };
    printf("...\n");

    //Limpando o cachê de memória
    if(hurwitz_lambda_array) free(hurwitz_lambda_array); hurwitz_lambda_array=NULL;
    if(H_array) free(H_array); H_array=NULL;


  //Finalizando a aplicação
  return 0;

}
