//VAMOS CRIAR UM PROGRAMA QUE COMPUTA O LOGARITMO DISCRETO USANDO TENTATIVA E ERRO ENVOLVENDO EXPONENCIAÇÃO MODULAR
//COMPILAR ESTE PROGRAMA COMO O COMANDO: gcc -o discrete_logarithm discrete_logarithm.c

//Cabeçalho
#include<stdio.h>
#include<stdint.h>
#include"mod_bin_exponentiation.h"

#define MAX_LOG 1e12

//Funções
/*
Nesta função logaritmando deve ser menor que a número que define a ordem do grupo em, questão e a base deve ser uma raíz
primitiva do número que define a ordem do grupo em questão.

*/
int64_t discrete_logarithm(int64_t base, int64_t number, int64_t congruence){
//Procedimentos
for(int64_t i=0; i<=congruence; ++i){
if(mod_pow(base, i, congruence)==number)
return i;
                                    };
return (-1);
                                                                            };

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
printf("Digite uma im inteiro congruente: ");
scanf("%li", &z);

//Calculando o logaritmo discreto
result=discrete_logarithm(x, y, z);

if(result==(-1))
printf("Não foi encontrado um logaritmo no intervalo explicitado.\n");
else
printf("Logaritmo de %li na base %li módulo %li: %li.\n", x, y, z, result);

//Finalizando
return 0;
          }
