//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTI8NAS CRIADAS NO ARQUIVO integer_partition_recursive.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o integer_partition_recursive integer_partition_recursive.c -O3


//Cabeçalho
#include"integer_partition_recursive.h"


//Função principal
int main(){

  //Variáveis locais
  int n;

  //Procedimentos
    //Recebendo input dos usuários
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    //Computando partições multiplicativas m(n)
    generate_additive_partitions(n, 1/*fixo*/, 0/*fixo*/);


  //Finalizando a aplicação
  return 0;

}
