//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO binary_window_exponentiation.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o binary_window_exponentiation binary_window_exponentiation.c -O2


//Cabeçalho
#include"binary_window_exponentiation.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  uint64_t a, b, m;
  size_t bit_shift;


  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] Base: ");
    if(scanf("%lu", &a)!=1) return 0;

    printf("[Inteiro] Expoente: ");
    if(scanf("%lu", &b)!=1) return 0;

    printf("[Inteiro] Módulo: ");
    if(scanf("%lu", &m)!=1) return 0;

    printf("[Inteiro] Bit_length (b≲10): ");
    if(scanf("%zu", &bit_shift)!=1) return 0;

    //Testes
    uint64_t r=pow_mod_window(a,b, m, bit_shift);
    printf("Exponencial modular: %lu^%lu (mod %lu) = %lu\n", a, b, m, r);


  //Finalizando a aplicação
  return 0;

}
