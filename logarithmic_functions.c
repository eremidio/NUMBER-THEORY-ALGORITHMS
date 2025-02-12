//VAMOS CRIAR UM PROGRAMA PARATESTAR AS ROTINAS DEFINIDAS NO ARQUIVO logarithmic_functions.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o  logarithmic_functions logarithmic_functions.c -lm


//Cabeçalho
#include"logarithmic_functions.h"
#include<stdio.h>
#include<stdint.h>


//Função principal
int main(){

  //Variáveis locais
  uint64_t number1;
  uint64_t prime_list_size;
  uint64_t* prime_list =NULL;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro(<10000000): ");
    scanf("%lu", &number1);


    //Lendo a lista de primos  até 10^7 alocadas no arquivo 'prime_table.txt'
    prime_list=read_prime_table("prime_table.txt", prime_list, &prime_list_size);

    //Testando funções artiméticas logarítmicas
    printf("Λ(%lu)=%lf\n", number1, von_mangoldt_function(number1));
    printf("Θ(%lu)=%lf\n", number1, first_chebyshev_function(number1, prime_list));
    printf("ψ(%lu)=%lf\n", number1, second_chebyshev_function(number1, prime_list));


    //Limpando o cachê de memória
    if(prime_list) free(prime_list); prime_list=NULL;

  //Finalizando a aplicação
  return 0;

}
