//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO triangular_partition_representation.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o triangular_partition_representation triangular_partition_representation.c -O2


//Cabeçalho
#include"triangular_partition_representation.h"


//Função principal
int main(){

  //Variáveis locais
  int64_t n=0;


  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n:  ");
    if(scanf("%li", &n)!=1) return 0;

    //Restrição
    if(n>MAX_TRIANGULAR){
      fprintf(stderr, "Erro: valor doinput elevado");
      return 0;
     }

    //Gerando a partições triangulares
    generate_triangular_partitions(n, 1/*fixo*/, 0/*fixo*/);

  //Finalizando a aplicação
  return 0;

}
