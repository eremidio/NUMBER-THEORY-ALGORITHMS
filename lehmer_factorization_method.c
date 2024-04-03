//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO lehmer_factorization_method.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o lehmer_factorization_method lehmer_factorization_method.c -lm -O2


//Cabeçalho
#include"lehmer_factorization_method.h"

//Função principal
int main(){
//Variáveis locais
__int128_t number;
char number_string[41];

//Recebendo input do usuário
printf("Digite o número a ser fatorado: ");

if(scanf("%s", number_string)!=1)
return 0;
number=scanf128(number_string);

//Aplicando o algoritmo de Lehmer
lehmer_factorization_method(number);

//Finalizando a aplicação
return 0;

          }

