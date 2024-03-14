//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO strassen_pollard_factorization.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o strassen_pollard_factorization strassen_pollard_factorization.c -O2


//Cabeçalho
#include"strassen_pollard_factorization.h"


//Função principal
int main(){
//Variáveis locais
__int128_t number;
char number_string[41];

//Recebendo o input
printf("Digite o número a ser fatorado: ");
if(scanf("%s", number_string)!=1)
return 0;
number=scanf128(number_string);

//Aplicando o algoritmo de Strassen-Pollard
strassen_pollard_factorization(number);

//Finalizando a aplicação
return 0;
          }
