//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO legendre_special_purpose_factorizationa_algorithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o legendre_special_purpose_factorization_algorithm legendre_special_purpose_factorization_algorithm.c -O2 -lm


//Cabeçalho
#include"legendre_special_purpose_factorization_algorithm.h"

//Função principal
int main(){

 //Variáveis locais
 uint64_t base1, base2, power;
 signed signal;

 //Procedimentos

 //Recebendo input do usuário
 printf("Base 1: ");
 if(scanf("%lu", &base1)!=1)
  return 0;

 printf("Base 2: ");
 if(scanf("%lu", &base2)!=1)
  return 0;

 printf("Expoente: ");
 if(scanf("%lu", &power)!=1)
  return 0;

 printf("+ (1) ou - (-1): ");
 if(scanf("%i", &signal)!=1)
  return 0;

 //Fatorando o número em questão n=(a^k)+(b^k),  n=(a^k)-(b^k)
 legendre_special_purpose_factorization_algorithm(base1, base2, power, signal);

 //Finalizando a aplicação
 return 0;

          }
 
