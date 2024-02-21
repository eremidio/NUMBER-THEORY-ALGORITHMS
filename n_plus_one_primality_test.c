//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO n_plus_one_primality_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o n_plus_one_primality_test n_plus_one_primality_test.c -O2 -lm


//Cabeçalho
#include"n_plus_one_primality_test.h"

//Função principal
int main(){
//Váriaveis
int64_t number;

//Procedimentos
//Recebendo input do usuário
printf("Digite um número que será testado:\n");
if(scanf("%li", &number)!=1)
return 0;

//Executando o teste
if(n_plus_one_primality_test(number)==true)
printf("Primo encontrado!\n");
else
printf("Número composto.\n");


//Finalizando a aplicação
return 0;
          }
