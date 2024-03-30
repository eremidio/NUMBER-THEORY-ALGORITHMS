//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO trinomial_integer_factorization.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o trinomial_integer_factorization trinomial_integer_factorization.c -O2


//Cabeçalho
#include"trinomial_integer_factorization.h"


//Função principal
int main(){

//Variáveis locais
int64_t number;

//Procedimentos
//Recebendo input do usuário
printf("Digite um número inteiro a ser fatorado: ");
if(scanf("%li", &number)!=1)
return 0;

//Fatorando o número em questão
trinomial_integer_factorization(number);

//Finalizando a aplicação
return 0;
          }
