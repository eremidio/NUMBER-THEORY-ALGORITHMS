//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO aks_prime_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o aks_prime_test aks_prime_test.c -lm


//Cabeçalho
#include"aks_prime_test.h"
#include<stdint.h>
#include<stdbool.h>
#include<stdio.h>


//Função principal 
int main(){
//Variáveis locais
uint64_t i;

//Procedimentos
//Testando a primalidade de um número
for(i= 1; i<114; i++){
if(aks_primality_test(i)==true)
printf("%lu é primo\n", i);
else
printf("%lu não é primo\n", i);
                     };



//TESTES USE UM // APÓS OS MESMOS
//printf("%lu\n",mul_mod(6, 6, 5));
//printf("%lu\n", pow_mod(2, 65465, 5));
//if(power_prime_test(9)==false)
//printf("OK!\n");
//printf("%lu\n",fast_euclides_algorithm(3993, 847));
//printf("%lu\n", multiplicative_order(4, 5));


//Finalizando a aplicação
return 0;
          }
