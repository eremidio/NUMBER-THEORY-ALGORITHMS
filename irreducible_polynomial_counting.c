//VAOS CRIAR UMA ROTINA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO irreducible_polynomial_counting.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o irreducible_polynomial_counting irreducible_polynomial_counting.c -lm


//Cabeçalho
#include"irreducible_polynomial_counting.h"
#include<stdio.h>


//Função principal
int main(){

  //Variaveis locais
  int64_t prime_base, degree;


  //Procedimento
    //Recebendo input do usuário
    printf("[Característica do corpo de Galois] GF(p)->p (primo): ");
    scanf("%li", &prime_base);
    printf("[Grau do polinômio irredutível] d: ");
    scanf("%li", &degree);


    //Calculando o número de polinômios irredutíveis com o grau especificado
    printf("Número de polinômios irredutíveis de grau %li definidos sobre GF(%li): %li\n",
      degree, prime_base, irreducible_polynomial_counting(degree, prime_base));


  //Finalizando a aplicação
  return 0;

}
