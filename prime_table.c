//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO prime_table_writing.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o prime_table prime_table.c -lm


//Cabeçalho
#include"prime_table_writing.h"

//Função principal
int main(){

  //Variáveis locais
  char filename[50];
  uint64_t limit;

  //Procedimentos
    //Recebendo input do usuário
    printf("Nome do arquivo que irá alocar a sequência de primos: ");
    scanf("%s", filename);
    printf("Limite para sua sequência de primos: ");
    scanf("%lu", &limit);

    //Gerando a tabela de primos compacta
    generate_prime_table(limit, filename);


  //Finalizando a aplicação
  return 0;  

          }
