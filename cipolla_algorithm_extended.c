//VAMOS CRIAR UM PROGRAMA TESTA AS AS ROTINAS CRIADAS NO ARQUIVO cipolla_algorithm_extended.h
//COMPILAR ESTE COMPILADO COM O COMANDO: g++ -o cipolla_algorithm_extended cipolla_algorithm_extended.c


//Cabeçalho
#include"cipolla_algorithm_extended.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t n, sqrt_n, prime, power, prime_power;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um inteiro: ");
    scanf("%li", &n);
    printf("Digite um inteiro primo ímpar: ");
    scanf("%li", &prime);
    printf("Digite um inteiro (expoente do primo ímpar): ");
    scanf("%li", &power);

    //Algoritmo de Cipolla
    prime_power=bin_pow(prime, power);
    sqrt_n=cipolla_algorithm_extended(n, prime, power);
    printf("√%li (mod %li)= %li\n", n, prime_power, sqrt_n);

  //Finalizando a aplicação
  return 0;


}
