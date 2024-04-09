//VAMOS CRIAR UM PROGRAMA QUE TESTAS AS ROTINAS CRIADAS NO ARQUIVO trial_division.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o  trial_division trial_division.c -lm -O2


//Cabeçalho
#include"trial_division.h"


//Função principal
int main(){
//Váriaveis locais
uint64_t number;

//Procedimentos
//Recebendo input do usuário
printf("Digite um número que será testado: ");
if(scanf("%lu", &number)!=1)
return 0;

//Executando o teste
if(trial_division(number, Yes)==true)
printf("Primo encontrado!\n");


//Finalizando a aplicação
return 0;
          }
