//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO brent_pollard_rho_factorization.h
//COMPILAR ESTE PROGRAMA COMO COMANDO: gcc -o brent_pollard_rho_factorization brent_pollard_rho_factorization.c -O2


//Cabeçalho
#include"brent_pollard_rho_factorization.h"

//Função principal
int main(){
//Variáveis locais
char number_string[45];
__int128_t number;

//Procedimentos
//Recebendo input do usuário
printf("Digite um número a ser fatorado: ");
if(scanf("%s", number_string)!=1)
return 0;

number=scanf128(number_string);

//Executando o algoritmo de Brent
brent_pollard_rho_factorization(number);

//Finalizando a aplicação
return 0;

          }
