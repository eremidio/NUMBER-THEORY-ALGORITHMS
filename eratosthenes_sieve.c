//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO eratosthenes_sieve.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o eratosthenes_sieve eratosthenes_sieve.c -O2

//Cabeçalho
#include"eratosthenes_sieve.h"

//Função principal
int main(){
//Variáveis locais
uint64_t n;

//Procedimentos
//Recebendo input do usuário
printf("Limite superior para a sequência de números primos:\n");
if(scanf("%lu", &n)!=1)
return 0;

//Computandonúmeros primos usando a peneira de Eratóstenes
eratosthenes_sieve(n);

//Finalizando a aplicação
return 0;
          }
