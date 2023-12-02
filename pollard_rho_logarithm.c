//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO pollard_rho_logarithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o pollard_rho_logarithm pollard_rho_logarithm.c

//Cabeçalho
#include"pollard_rho_logarithm.h"
#include<stdint.h>
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

//Teste da função que calcula inversos modulares
//printf("73-¹ mod 87:%li\n", modular_inverse(73, 87));

//Executando o algoritmo de Pollard ρ para o cálculo de logaritmos discretos
log=pollard_rho_logarithm(g, h, N);
printf("Logaritmo de %li (mod %li), na base %li = %li\n", h, N, g, log);

//Finalizando a aplicação
return 0;
          }
