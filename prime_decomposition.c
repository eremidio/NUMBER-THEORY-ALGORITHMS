//VAMOS CRIAR UM PROGRAMA PARATESTAR AS ROTINAS DEFINIDAS NO ARQUIVO prime_decomposition.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o prime_decomposition prime_decomposition.c -lm


//Cabeçalho
#include"prime_decomposition.h"
#include<stdio.h>
#include<stdint.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t number1, number2;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro: ");
    scanf("%li", &number1);
    printf("Digite um número inteiro: ");
    scanf("%li", &number2);


  //Testando funções airtméticas
    //Algoritmo de Euclides otimizado
    printf("mdc(%li, %li)=%li\n", number1, number2, euclides_algorithm(number1, number2));

    //Decomposição em primos
    printf("ω(%li)=%li\n", number1, omega_function(number1));
    printf("Ω(%li)=%li\n", number1, capital_omega_function(number1));
    printf("ν(%li, %li)=%li\n", number1, number2, p_adic_valuation(number1, number2));
    printf("λ(%li)=%li\n", number1, liouville_function(number1));
    printf("D(%li)=%li\n", number1, arithmetic_derivative(number1));
    printf("ld(%li)=%lf\n", number1, logarithmic_derivative(number1));

  //Finalizando a aplicação
  return 0;

}
