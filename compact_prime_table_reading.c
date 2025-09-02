//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO compact_prime_table_reading.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o compact_prime_table_reading compact_prime_table_reading.c -O2


//Cabeçalho
#include"compact_prime_table_reading.h"  


//Função principal
int main(){

  //Variáveis locais
  char* file_name="prime_difference_table.txt";
  size_t prime_diff_size=0;
  uint64_t prime=2, limit;

  
  //Procedimentos
    //Recebendo input do usuário
    printf("Limitante superior para sequência de números primos a serem lidos: ");
    if(scanf("%lu", &limit)!=1) return 0;    

    //Alocando lista de diferença de números primos
    uint8_t* prime_difference_array=read_prime_table_difference(file_name, &prime_diff_size);

    //Exibindo lista de primos até um dado limite
    printf("Primos até %lu: ", limit);

    for(size_t i=0; prime<(limit+1); ++i){
      printf("%lu, ", prime);
      prime+=prime_difference_array[i];
    }
    printf("...\n");


    //Limapando o cachê de memória
    if(prime_difference_array) free(prime_difference_array);
    prime_difference_array=NULL;


  //Finalizando o programa
  return 0;

}
