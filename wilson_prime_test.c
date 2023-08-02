//VAM0S IMPLEMENTAR UM PROGRAMA EM C QUE IMPLEMENTA O TEOREMA DE WILSON PARA DECIDIR SE UM NÚMERO É PRIMO
//COMPILAR ESTEPROGRAMA COM O COMANDO: gcc -o wilson_prime_test wilson_prime_test.c

/*
O CHAMADO TEOREMA DE WILSON AFIRMA QUE UM NÚMERO p É PRIMO SE E SOMENTE SE (p-1)!=(p-1) mod(p).
ESTE TEOREMA FORNECE UM TESTE EXTREMAMENTE BÁSICO PARA TESTAR A PRIMALIDADE DE UM NÚMERO.

*/

//**************************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>


//**************************************************************************************************************************
//FUNÇÕES
bool wilson_test(uint64_t n){
//Variáveis locais
uint64_t result=1;
//Procedimentos
for(uint64_t i=2; i<n; ++i)
result=(result*i)%n;

if(result==(n-1))
return true;
else
return false;
                            };


//**************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
//Variáveis locais
uint64_t number, i;

//Procedimentos
//Recebendo um input do usuário
printf("Digite um limitante para sua sequência de números primos: ");
scanf("%lu", &number);

//Printando uma sequência de números primos
for(i=2; i<=number; ++i){
if(wilson_test(i)==true)
printf("%lu, ",i);
                        };
printf("\n");

//Finalizando a aplicação
return 0;
          }
