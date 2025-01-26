//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO montgomery_modular_reduction.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o montgomery_modular_reduction montgomery_modular_reduction.c

//Cabeçalho
#include"montgomery_modular_reduction.h"
#include<stdio.h>

//Função principal 
int main(void){

  //Variáveis locais
  int64_t x, y, N, R, N_;
  int s;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] x: ");
    scanf("%li", &x);
    printf("[Inteiro] y: ");
    scanf("%li", &y);  
    printf("[Inteiro - congruente ímpar] N(>x): ");
    scanf("%li", &N);  

    //Cálculo dos parâmetros usados na redução de Montgomery
    select_montgomery_parameters(&R, &s, &N_, N);


    //Calculando o produto e a exponenciação modular
    printf("[Produto de Montgomery] M(x, y) mod N=%li\n", montgomery_mul_mod(x, y, N, N_, R, s));
    printf("x^y mod N=%li\n", montgomery_pow_mod(x, y, N, N_, R, s));
    

  //Resultado final
  return 0;

}
