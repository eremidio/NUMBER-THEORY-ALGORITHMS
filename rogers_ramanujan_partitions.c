//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADASNO ARQUIVO rogers_ramanujan_partitions.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o rogers_ramanujan_partitions rogers_ramanujan_partitions.c -O2


//Cabeçalho
#include"rogers_ramanujan_partitions.h"


//Função principal
int main(){

  //Variáveis locais
  int32_t n=0;


  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n:  ");
    if(scanf("%i", &n)!=1) return 0;

    //Restrição
    if(n>MAX_ROGERS_RAMANUJAN){
      fprintf(stderr, "Erro: valor do input elevado");
      return 0;
     }

    //Gerando a partições de Rogers-Ramanujan
    printf("Partições congruentes a 1,4 mod 5: ");
    compute_rogers_ramanujan_partition1(n, 1/*fixo*/, 0/*fixo*/);
    printf("...\n");

    printf("Partições congruentes a 2,3 mod 5: ");
    compute_rogers_ramanujan_partition2(n, 1/*fixo*/, 0/*fixo*/);
    printf("...\n");

    printf("Partições diferindo em pelo menos 2 unidades: ");
    compute_rogers_ramanujan_partition3(n, 1/*fixo*/, 0/*fixo*/);
    printf("...\n");

    printf("Partições diferindo em pelo menos 2 unidades (não contendo 1's): ");
    compute_rogers_ramanujan_partition3(n, 2/*fixo*/, 0/*fixo*/);
    printf("...\n");


  //Finalizando a aplicação
  return 0;

}

