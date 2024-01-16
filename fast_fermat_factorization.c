//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO fast_fermat_factorization.h
//COMPILAR ESTE PROGRAMA COM: gcc -o fast_fermat_factorization fast_fermat_factorization.c -lm -O2

//Cabeçalho
#include"fast_fermat_factorization.h"

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
fast_fermat_factorization(number);

//Finalizando a aplicação
return 0;
          }

