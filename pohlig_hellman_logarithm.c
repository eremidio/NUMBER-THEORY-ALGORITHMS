//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO pohlig_hellman_logarithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o pohlig_hellman pohlig_hellman_logarithm.c 

//Cabeçalho
#include"pohlig_hellman_logarithm.h"
#include<stdio.h>

//Função principal
int main(){
//Variáveis locais
int64_t log1, log2, g, h, N, p, e;
//Procedimentos
//Recebendo input do usuário
printf("Digite o valor da base do logaritmo (gerador do grupo g): ");
scanf("%li", &g);
printf("Digite o valor da base do logaritmando h: ");
scanf("%li", &h);
printf("Digite o valor do número primo correspondente a ordem do grupo cíclico G1: ");
scanf("%li", &p);
printf("Digite o valor do expoente correspondente a ordem do grupo cíclico G1: ");
scanf("%li", &e);


//Executando o algoritmo de Pollard ρ para o cálculo de logaritmos discretos
log1= pohlig_hellman_logarithm_prime_order(g, h, p, e);
printf("Logaritmo de %li (mod %li) na base %li = %li\n", h,bin_pow(p,e), g, log1);

//Finalizando a aplicação
return 0;
          }


