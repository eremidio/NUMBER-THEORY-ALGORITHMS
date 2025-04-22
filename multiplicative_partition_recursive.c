//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO multiplicative_partition_recursive.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o multiplicative_partition_recursive multiplicative_partition_recursive.c -O2


//Cabeçalho
#include"multiplicative_partition_recursive.h"


//Função principal
int main(){

  //Variáveis locais
  int32_t n;

  //Procedimentos
    //Recebendo input dos usuários
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    //Computando partições multiplicativas m(n)
    generate_multiplicative_partitions(n, 2, 0);//2 é o menor divisor de qualquer inteiro e 0 indica o index do slot que aloca o primeiro divisor encontrado


  //Finalizando a aplicação
  return 0;

}

