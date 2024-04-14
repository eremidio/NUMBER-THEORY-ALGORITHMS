//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO generalized_proth_prime_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o generalized_proth_prime_test generalized_proth_prime_test.c -lm -O2



//Cabeçalho
#include"generalized_proth_prime_test.h"

//Função principal
int main(){

 //Variáveis locais
 uint64_t k, prime, power, witness;


 //Procedimentos

 //Recebendo input do usuário
 printf("K: ");
 if(scanf("%lu", &k)!=1)
  return 0;

 printf("Primo ímpar: ");
 if(scanf("%lu", &prime)!=1)
  return 0;

 printf("Potência: ");
 if(scanf("%lu", &power)!=1)
  return 0;

 printf("Valor base para teste de primalidade: ");
 if(scanf("%lu", &witness)!=1)
  return 0;


 //Testando a primalidade do número de Proth generalizado
 generalized_proth_prime_test(k, prime, power, witness);

 //Finalizando a aplicação
 return 0;

          }
 
