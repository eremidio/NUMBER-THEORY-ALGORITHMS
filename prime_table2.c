//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO prime_table_reading.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o prime_table2 prime_table2.c -lm 


//Cabeçalho
#include"prime_table_reading.h"


//Função principal
int main(){

  //Variáveis locais
  char filename[50];
  uint64_t prime_list_size;
  uint64_t* prime_list =NULL;

  //Procedimentos
    //Recebendo input do usuário
    printf("Nome do arquivo que irá alocar a sequência de primos: ");
    scanf("%s", filename);

    //Lendo a lista de primos alocadas no arquivo
    prime_list=read_prime_table(filename, prime_list, &prime_list_size);

    //Printando a lista de primos na tela
    for(uint64_t i=0; i<prime_list_size; ++i)
      printf("%lu, ", prime_list[i]);
    printf("...\n");

  //Limpando o cachê de memória e finalizando a aplicação
  if(prime_list)
    free(prime_list);
  return 0;
  

          }
