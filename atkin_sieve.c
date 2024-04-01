//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO atkin_sieve.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o atkin_sieve atkin_sieve.c -O2


//Cabeçalho
#include"atkin_sieve.h"

//Função principal
int main(){
//Variáveis locais
uint64_t number;

//Procedimentos
//Recebendo o input do usuário
printf("Usuário digite um limitante superior para sua sequência de números primos:\n->");
if(scanf("%lu", &number)!=1)
return 0;


//Aplicando o algoritmo de Atkin para computar e exibir
atkin_sieve(number);

//Finalizando a aplicação
return 0;
          }
