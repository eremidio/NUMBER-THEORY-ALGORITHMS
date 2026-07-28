//VAMOS CRIAR UM PROGRAMA QUE COMPUTA AS ROTINAS CRIADAS NO ARQUIVO prime_constellations_counting.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o prime_constellations_counting prime_constellations_counting.c -lm -O2


//Cabeçalho
#include"prime_constellations_counting.h"


//Função principal
int main(){

  //Variáveis locais
  long double x;
  int N; 

  //Procedimentos
    //Recebendo input do usuário
    printf("[Limite superior do intervalo] x: ");
    if(scanf("%Lf", &x)!=1) return 0;
    printf("[Número de elementos na constelação de primos] N: ");
    if(scanf("%d", &N)!=1) return 0;
    int* ktuple = (int*)malloc(N*sizeof(int));


    for(int i=0; i<N; ++i){
      printf("[Elementos na constelação de primos] a(%d): ", i);
      if(scanf("%d", &ktuple[i])!=1) goto cleaning;
    }


    printf("\nConstelação de primos da forma: (");
    for(size_t k=0; k<N; k++){
      printf("p+%d", ktuple[k]);
      if(k==(N-1)) break; else printf(", ");
    }
    printf(")\n");


    //Computando o número de ocorrência de constelações de primos
    long double occurences=prime_constellation_counting(ktuple, N, x);
    printf("Número de ocorrência aproximado da constelação até %.0Lf: %.0Lf\n", x, occurences);


    //Limpando o cachê de memória
    cleaning:
    if(ktuple) free(ktuple);
    ktuple=NULL;
        

  //Finalizando a aplicação
  return 0;

}
