//VAMOS CRIAR UM PROGRAMA PARA PRÉ-COMPUTAR A FUNÇÃO φ(m, n) USANDO O ALGORITMO DE MAPES
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o mapes_algorithm2 mapes_algorithm2.c -lm


//Cabeçalho
#include"mapes_algorithm.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  FILE * mapes_file;
  char filename[45];
  int64_t primes_30[10]={2,3,5,7,11,13,17,19,23,29};
  int64_t phi_mn;
  int64_t n;


  //Procedimentos
    //Abrindo o arquivo para a escrita e recebendo input do usuário
    printf("Nome do arquivo onde será registrado os valores de φ(m, n): ");
    scanf("%s", filename);
    mapes_file=fopen(filename, "w");
    printf("[Inteiro] n(≲10): ");
    scanf("%li", &n);

    //Computando os valores de  φ(m, n) e registrando no arquivo
    for(int64_t i=0; i<=100000; ++i){
      phi_mn=mapes_algorithm(i, n, primes_30);
      printf("φ(%li, %li)=%li\n", i, n, phi_mn);
      fprintf(mapes_file, "%li\n", phi_mn);
    }  



    //Fechando o arquivo
    fclose(mapes_file);
  
  //Finalizando a aplicação
  return 0;  


}
