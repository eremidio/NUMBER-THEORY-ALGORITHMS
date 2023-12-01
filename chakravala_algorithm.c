//VAMOS CRIAR QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO chakravala_algorithm.h
//COMPILAR ESTE PROGRAMA COM: gcc -o chakravala_algorithm chakravala_algorithm.c -lm


//Cabeçalho
#include"chakravala_algorithm.h"
#include<stdio.h>

//Função principal
int main(){
//Variáveis locais
int64_t x, y, a, N;

//Procedimentos
//Recebendo input do usuário
printf("Digite um número inteiro 'N': ");
scanf("%li", &N);
printf("Digite um número inteiro 'a' (palpite inicial): ");
scanf("%li", &a);

//Aplicando o algoritmo de Chakravala
chakravala_algorithm(N, a, &x, &y);
printf("Solução da equação x²-%liy²=1\nx=%li, y=%li\n", N, x, y);

//Finalizando a aplicação
return 0;
          }
