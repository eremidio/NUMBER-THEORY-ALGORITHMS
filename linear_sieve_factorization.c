//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO linear_sieve_factorization.h 
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o linear_sieve_factorization linear_sieve_factorization.c -O2


//Cabeçalho
#include"linear_sieve_factorization.h"


//Função principal
int main(){
//Variáveis locais
int32_t number;

//Procedimentos
//Recebendo input do usuário
printf("Digite um limitante superior: ");
if(scanf("%i", &number)!=1)
return 0;

//Fatorando o número em questão
linear_sieve_factorization(number);

//Finalizando a aplicação
return 0;
          }


