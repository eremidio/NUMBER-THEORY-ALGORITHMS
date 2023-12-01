//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO barret_modular_multiplication.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o barret_reduction barret_reduction.c -lm

//Cabeçalho
#include"barret_reduction.h"
#include<stdint.h>
#include<stdio.h>


//Função principal
int main(void){
//Variáveis locais
int64_t a, N, mod;

//Procedimentos
//Recebendo input do usuário
printf("Digite um inteiro 'a': ");
scanf("%li", &a);
printf("Digite um inteiro 'N': ");
scanf("%li", &N);
//Testando a função de redução de Barret
mod=barret_reduction(a, N);
printf("a (mod N): %li\n", mod);

//Finalizando a aplicação
return 0;
              }


