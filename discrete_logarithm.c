//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO discrete_logarithm.h
//COMPILAR ESTE PROGRAMA COMO O COMANDO: gcc -o discrete_logarithm discrete_logarithm.c -lm


//Cabeçalho
#include"discrete_logarithm.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t x, result, y, z;


  //Procedimentos
    //Recebendo input do usuário
    printf("Digite uma base: ");
    scanf("%li", &x);

    printf("Digite um logaritmando: ");
    scanf("%li", &y);

    printf("Digite um inteiro congruente: ");
    scanf("%li", &z);

    //Calculando o logaritmo discreto
    result=discrete_logarithm_brute_force(x, y, z);
    printf("[Busca linear] Logaritmo discreto de log(%li) na base %li módulo %li: %li\n", y, x, z, result);

    result=discrete_logarithm_analytical_formula(x, y, z);
    printf("[Fórmula analítica] Logaritmo discreto de log(%li) na base %li módulo %li: %li\n", y, x, z, result);


  //Finalizando
  return 0;

}
