//VAMOS CRIARUM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO primorial_modular_partition.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o primorial_modular_partition primorial_modular_partition.c


//Cabeçalho
#include"primorial_modular_partition.h"


//Função principal
int main(){

  //Variáveis locais
  int n;

  //Procedimentos
    //Recebendo input dos usuários
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    //Computando partições primoriais modulares de inteiros em um intervalo
    primorial_sieve_setup();
    for(int i=3; i<=n; ++i) compute_primorial_partition(i);


  //Finalizando a aplicação
  return 0;

}

