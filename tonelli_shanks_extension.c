//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO tonelli_shanks_extension.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o tonelli_shanks_extension tonelli_shanks_extension.c


//Cabeçalho
#include"tonelli_shanks_extension.h"
#include<stdio.h>

//Função principal
int main(){

  //Variáveis locais
  int64_t a, prime, power;
  int64_t prime_power_modular_sqrt;


  //Procedimentos
    //Recebendo input do usuário
    printf("Classe residual: ");
    scanf("%li", &a);
    printf("Primo ímpar: ");
    scanf("%li", &prime);
    printf("Expoente: ");
    scanf("%li", &power);


    //Aplicando o algoritmo de Tonelli-Shanks para potências de números primos
    prime_power_modular_sqrt=tonelli_shanks_extension(a, prime, power);
    printf("Raíz quadrada de %li mod %li: %li\n", a, (int64_t)(bin_pow(prime,power)), prime_power_modular_sqrt);


  //Finalizando a aplicação
  return 0;
    
          }
