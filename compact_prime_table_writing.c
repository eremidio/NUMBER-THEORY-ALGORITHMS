//VAMOS CRIAR UM PROGRAMA PARA CRIAR UMA TABELA COMPACTA DE NÚMEROS PRIMOS ESTOCANDO DIFERENÇA ENTRE SUCESSIVOS PRIMOS EM SEQUẼNCIA
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o compact_prime_table_writing compact_prime_table_writing.c -O2 -lm


//Cabeçalho
#include"pseudo_square_number.h"/*Qualquer teste de primalidade pode ser usado*/
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  char file_name[50];
  FILE* prime_table_file;
  uint64_t current_prime=3, n=0;
  uint8_t prime_difference=0;


  //Procedimentos
    //Recebendo input do usuário
    printf("Limitante superior para sequência de números primos: ");
    if(scanf("%lu", &n)!=1) return 0;
    printf("Nome do arquivo para alocar (diferenças entre) números primos: ");
    if(scanf("%49s", file_name)!=1) return 0;

    //Abrindo arquivo para escrita
    prime_table_file=fopen(file_name, "w");

    //Alocando primeiro termo da lista
    fprintf(prime_table_file, "1\n");//3=2+1

    //Loop principal
    for(uint64_t i=5; i<=n; i+=6){
      if(gauss_euler_primality_test(i)){
        prime_difference=i-current_prime;
        current_prime=i;
        fprintf(prime_table_file, "%u\n", prime_difference);
      }

      if(pseudosquare_primality_testing((i+2))){
        prime_difference=(i+2)-current_prime;
        current_prime=(i+2);
        fprintf(prime_table_file, "%u\n", prime_difference);
      }

    }

    //Fechando o arquivo
    fclose(prime_table_file);


  //Finalizando a aplicação
  return 0;

}
