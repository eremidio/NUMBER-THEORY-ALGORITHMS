//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO prime_gaps_64bits.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o prime_gaps_64bits prime_gaps_64bits.c -lm -O3


//Cabeçalho
#include"prime_gaps_64bits.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t upper, lower, interval_size, register_size;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] Limite inferior para a busca de primos em um intervalo: ");
    if(scanf("%li", &lower)!=1) return 0;
    printf("[Inteiro] Limite superior para a busca de primos em um intervalo: ");
    if(scanf("%li", &upper)!=1) return 0;

    //Computando números primos no intervalo
    int64_t* sieving_interval = prime_sieving(lower, upper, &interval_size);

      //Teste: exibindo primos em um intervalo
      //for(int64_t i=0; i<interval_size; ++i){
      //  if(sieving_interval[i]>0) printf("%li, ", sieving_interval[i]);
      //};
      //printf("...\n");
     
    
    //Computando gaps entre primos em um dado intervalo
    struct prime_gap_register* prime_gap_array=compute_prime_gaps(sieving_interval, interval_size, &register_size);

    printf("Gaps entre primos no intervalo selecionado:\n");

    for(int64_t i=0; i<register_size; ++i){
      printf("n:%li  p(%li):%li,  p(%li):%li  g(%li):%i\n",i, i, prime_gap_array[i].lower_prime, i,
      prime_gap_array[i].upper_prime, i, prime_gap_array[i].prime_gap);
    }
    printf("...\n");

    //Limpando o cachê de memória
    if(sieving_interval) free(sieving_interval); sieving_interval=NULL;
    if(prime_gap_array) free(prime_gap_array); prime_gap_array=NULL;


  //Finalizando a aplicação
  return 0;

}

