//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO prime_power_minus_one_factorization.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o prime_power_minusone_factorization prime_power_minusone_factorization.c -lm

//Cabeçalho
#include"prime_power_minusone_factorization.h"


//Função principal
int main(){
//Variáveis locais
uint64_t b, p;

//Procedimentos
//Recebendo input do usuário
printf("Digite uma base: ");
scanf("%lu", &b);
printf("Digite um expoente: ");
scanf("%lu", &p);

//Aplicando o algoritmo de fatoração de números inteiros
prime_power_minusone_factorization(b, p);

//Finalizando a aplicação
return 0;
          };
