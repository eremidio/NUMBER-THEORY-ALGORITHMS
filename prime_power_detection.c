//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO prime_power_detection.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o prime_power_detection prime_power_detection.c -lm -O2 


//Cabeçalho
#include"prime_power_detection.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t number, sqrt_n, prime;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um inteiro: ");
    if(scanf("%li", &number)!=1) return 0;


    //Detectando se o número em questão é um quadrado perfeito
    if(fast_square_detection(number, &sqrt_n)==true)  printf("Raíz quadrada de %li = %li\n", number, sqrt_n);
    else printf("%li não é um quadrado perfeito\n", number);


    //Detectando se o número em questão é uma potência de um número primo
    if(fast_prime_power_detection(number, &prime)==true)  printf("%li é uma potência do número primo %li\n", number, prime);
    else printf("%li não é potẽncia de um número primo\n", number);


  //Finalizando a aplicação
  return 0;


}

