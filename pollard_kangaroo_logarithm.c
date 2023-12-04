//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO pollard_kangaroo_logarithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o pollard_kangaroo_logarithm pollard_kangaroo_logarithm.c -lm

//Cabeçalho
#include"pollard_kangaroo_logarithm.h"
#include<stdio.h>

//Função principal
int main(){
//Variáveis locais
int64_t log, g, h, N;
//Procedimentos
//Recebendo input do usuário
printf("Digite o valor da base do logaritmo (gerador do grupo g): ");
scanf("%li", &g);
printf("Digite o valor da base do logaritmando h: ");
scanf("%li", &h);
printf("Digite o valor da ordem do grupo mod N: ");
scanf("%li", &N);

//Executando o algoritmo de Pollard ρ para o cálculo de logaritmos discretos
log=pollard_kangaroo_logarithm(g, h, N);
printf("Logaritmo de %li (mod %li), na base %li = %li\n", h, N, g, log);
          }
