//VAMOS CRIAR UM PROGRAMA QUE TESTAS AS ROTINAS CRIADAS NO ARQUIVO trial_division128.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o  trial_division128 trial_division128.c -O2


//Cabeçalho
#include"trial_division128.h"


//Função principal
int main(){

 //Variáveis locais
 __int128_t number;
 char number_string[41];

 //Recebendo o input
 printf("Digite o número a ser testado: ");
 if(scanf("%s", number_string)!=1)
  return 0;
  number=scanf128(number_string);

 //Executando o teste
 if(trial_division128(number, Yes)==true)
  printf("Primo encontrado!\n");


 //Finalizando a aplicação
 return 0;
          }
