//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO primes_in_airithmetic_progression.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o primes_in_arithmetic_progression primes_in_arithmetic_progression.c -lm -O2


//Cabeçalho
#include"primes_in_arithmetic_progression.h"


//Função principal
int main(){

  //Variáveis locais
  bool* prime_array=fill_prime_array_sieve(100000000);
  int64_t x0=1000, x=x0;

  //Procedimentos
    //Calculando valores da função π(a, b; x) mod 8 e mod 4
    for(int i=0; i<5; ++i){
      printf("Valor aproximando π(a, 4; %li) ≃ %.3f\n", x, modular_prime_function_approximation(x, 4));
      printf("Valor exato π(1, 4; %li) = %li\n", x, modular_prime_function_exact(x, 1, 4, prime_array));
      printf("Valor exato π(3, 4; %li) = %li\n", x, modular_prime_function_exact(x, 3, 4, prime_array));
      x*=10;
    }

    x=x0;      
    for(int i=0; i<5; ++i){
      printf("Valor aproximando π(a, 8; %li) ≃ %.3f\n", x, modular_prime_function_approximation(x, 8));
      printf("Valor exato π(1, 8; %li) = %li\n", x, modular_prime_function_exact(x, 1, 8, prime_array));
      printf("Valor exato π(3, 8; %li) = %li\n", x, modular_prime_function_exact(x, 3, 8, prime_array));
      printf("Valor exato π(5, 8; %li) = %li\n", x, modular_prime_function_exact(x, 5, 8, prime_array));
      printf("Valor exato π(7, 8; %li) = %li\n", x, modular_prime_function_exact(x, 7, 8, prime_array));
      x*=10;
    }

    x=x0;      
    for(int i=0; i<5; ++i){
      printf("Valor aproximando π(a, 7; %li) ≃ %.3f\n", x, modular_prime_function_approximation(x, 7));
      printf("Valor exato π(1, 7; %li) = %li\n", x, modular_prime_function_exact(x, 1, 7, prime_array));
      printf("Valor exato π(2, 7; %li) = %li\n", x, modular_prime_function_exact(x, 2, 7, prime_array));
      printf("Valor exato π(3, 7; %li) = %li\n", x, modular_prime_function_exact(x, 3, 7, prime_array));
      printf("Valor exato π(4, 7; %li) = %li\n", x, modular_prime_function_exact(x, 4, 7, prime_array));
      printf("Valor exato π(5, 7; %li) = %li\n", x, modular_prime_function_exact(x, 5, 7, prime_array));
      printf("Valor exato π(6, 7; %li) = %li\n", x, modular_prime_function_exact(x, 6, 7, prime_array));
      x*=10;
    }

  //Limpando o cachê de memória
  if(prime_array){
    free(prime_array); prime_array=NULL;
  }

  
  //Finalizando a aplicação
  return 0;

}
