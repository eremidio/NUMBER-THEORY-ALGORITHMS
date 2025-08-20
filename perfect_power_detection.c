//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO perfect_power_detection.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o perfect_power_detection perfect_power_detection.c -lm -O2


//Cabeçalho
#include"perfect_power_detection.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  uint64_t n;


  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n:");
    if(scanf("%lu", &n)!=1) return 0;


    //Detectando cubos perfeitos e quadrados perfeitos
    printf("Quadrados perfeitos até %lu: ", n);
    for(uint64_t m=1; m<=n; ++m){
      if(is_perfect_k_power(m, 2)) printf("%lu, ", m);
    }
    printf("...\n");

    printf("Cubos perfeitos até %lu: ", n);
    for(uint64_t m=1; m<=n; ++m){
      if(is_perfect_k_power(m, 3)) printf("%lu, ", m);
    }
    printf("...\n");


  //Finalizando a aplicação
  return 0;

}
