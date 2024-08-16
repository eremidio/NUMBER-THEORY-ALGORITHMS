//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO lucas_lehmer_riesel_prime_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o lucas_lehmer_riesel_prime_test lucas_lehmer_riesel_prime_test.c




//Cabeçalho
#include"lucas_lehmer_riesel_prime_test.h"


//Função principal
int main(){

 //Variáveis locais
 int64_t k, power;

 //Procedimentos

 //Recebendo input do usuário
 printf("K: ");
 if(scanf("%li", &k)!=1)
  return 0;

 printf("Potência: ");
 if(scanf("%li", &power)!=1)
  return 0;


 //Algoritmo de Lucas-Lehmer-Riesel
 lucas_lehmer_riesel_prime_test(k, power);


 //Finalizando a aplicação
 return 0;

}
