//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUVO multiplicatve_partition_function.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o multiplicative_partition_function multiplicative_partition_function.c -O2 -lm


//Cabeçalho
#include"multiplicative_partition_function.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int32_t n;
  int64_t mn;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    //Calculando a função de partição multiplicativa
    mn=multiplicative_partition_function(n);
    printf("[Função de partição multiplicativa] m(%i)=%li\n", n, mn);

  //Finalizando a aplicação
  return 0;

}
