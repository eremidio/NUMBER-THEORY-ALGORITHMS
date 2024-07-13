//VAMOS IMPLEMENTAR O ALGORITMO DA PENEIRA DE SUNDARAM PARA CALCULAR NÚMEROS PRIMOS ATÉ UM CERTO LIMITE
//COMPILAR ESTE PROGRAMA COM O COMANDO: clang -o sundaram_sieve sundaram_sieve.c -lm -O2

/*
PARA MAIORES INFORMAÇÕES: https://canonica.ai/page/Sieve_of_Sundaram

*/

//***********************************************************************************************************************************
//CABEÇALHO 
#include"prime_power_detection.h"
#include<stdlib.h>
#include<stdio.h>


//***********************************************************************************************************************************
//FUNÇÕES
//Função que implementa a peneira de Sundaram
void sundaram_sieve(int64_t n){

  //Vatriáveis locais
  bool number_list[n+1];
  int64_t i, j, k;
  int64_t temp, number;

  //Procedimentos
    //Inicializando a a lista de booleanos
    for(k=0; k<n+2; ++k) number_list[k]=true;

    //Descartando números compostos
   for(j=1; j<n; ++j){
     for(i=1; i<j; ++i){
       if((i+j+2*i*j)<n) number_list[i+j+2*i*j]=false;
     };
   };

   //Exibindo a lista de primos computados
   printf("2, 3, ");
   for(k=2; (2*k+1)<n; ++k){
     number=(2*k+1);
     if(number_list[k]==true && fast_square_detection(number, &temp)==false)
       printf("%li, ", number);
   };

   printf("...\n");


};


//***********************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){

  //Variáveis  locais
  int64_t n;


  //Procedimentos
    //Recebendo input do9 usuário
    printf("Vamos calcular os números primos até um certo valor usando a peneira de Sundaram.\n");
    printf("Usuário digite um número inteiro:\n");
    if(scanf("%li", &n)!=1) return 0;

    //Calculando números primos usando a peneira de Sundaram    
    printf("Eis a lista de números primos até %li: \n", n);
    sundaram_sieve(n);


  //Finalizando a aplicação
  return 0;

}
