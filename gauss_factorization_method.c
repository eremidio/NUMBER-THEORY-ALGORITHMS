//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO gauss_factorization_method.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o gauss_factorization_method gauss_factorization_method.c -O2 -lm


//Cabeçalho
#include"gauss_factorization_method.h"

//Função principal
int main(){
//Variáveis locais
uint64_t number;

//Procedimentos
//Recebendo input do usuário
printf("Digite um número inteiro a ser fatorado: ");
if(scanf("%lu", &number)!=1)
return 0;

//Fatorando o número em questão
gauss_factorization_method(number);

//Finalizando a aplicação
return 0;
          }
