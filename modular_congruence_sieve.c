//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO modular_congruence_sieve.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o modular_congruence_sieve modular_congruence_sieve.c -lm


//Cabeçalho
#include"modular_congruence_sieve.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t residue_classes6[2]={1,5};
  int64_t residue_classes30[8]={1,7,11,13,17,19,23,29};
  int64_t n;


  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n:");
    scanf("%li", &n);
  
    //Calculando lista de possíveis números primos num intervalo
    int64_t* sieve_interval= (int64_t*)malloc(n*sizeof(int64_t));

    for(int64_t i=2; i<n; ++i){

      if(i<30) continue;
      sieve_interval[i]=i;

    };
  
    printf("Intervalo original: ");
    for(int64_t i=2; i<n; ++i){
      if(sieve_interval[i]>0) printf("%li, ", sieve_interval[i]);      
    }
    printf("..\n\n");


    //Aplicando um filtro nos valores da forma 6k+1 e 6k+5
    congruence_sieve_interval(sieve_interval, residue_classes6, 6, n, 2);
    printf("Intervalo original excluindo inteiros das formas (6k+1) e (6k+5): ");
    for(int64_t i=2; i<n; ++i){
      if(sieve_interval[i]>0) printf("%li, ", sieve_interval[i]);      
    }
    printf("..\n\n");


    //Aplicando um filtro nos valores da forma 30k+r com r={1,7,11,13,17,19,23,29}
    congruence_sieve_interval(sieve_interval, residue_classes30, 30, n, 8);
    printf("Intervalo original excluindo inteiros das formas 30k+r com r={1,7,11,13,17,19,23,29}: ");
    for(int64_t i=2; i<n; ++i){
      if(sieve_interval[i]>0) printf("%li, ", sieve_interval[i]);      
    }
    printf("..\n\n");


    //Limpando o cachê de memória
    free(sieve_interval); sieve_interval=NULL;
  

  //Finalizando a aplicação
  return 0;

} 
