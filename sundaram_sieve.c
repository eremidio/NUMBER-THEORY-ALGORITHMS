//VAMOS IMPLEMENTAR O ALGORITMO DA PENEIRA DE SUNDARAM  PARA CALCULAR NÚMEROS PRIMOS ARTÉ UM CERTO LIMITE
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o sundaram_sieve sundaram_sieve.c -lm

/*CABEÇALHO*/
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//FUNÇÃO QUE APLICA A PENEIRA DE SUNDARAM PARA UMA SEQUÊNCIA DE INTEIROS ATÉ UM DADO VALOR
void sundaram_sieve(int n){
//VARIÁVEIS LOCAIS
bool number_list[n+1];
int i, j, k;
int ground;
double sqrt_n;

//PROCEDIMENTOS
//INICIALIZANDO A LISTA DE BOOLEANOS
for(k=0; k<n+2; ++k)
number_list[k]=true;

//AJUSTE DE VARIÁVEIS

sqrt_n=sqrt(n);
ground=floor(sqrt_n);



//APLICANDO A PENEIRA DE SUNDARAM A LISTA DE BOOLEANOS
for(j=1; j<n; ++j){
for(i=1; i<j; ++i){
if((i+j+2*i*j)<n)
number_list[i+j+2*i*j]=false;
                  };
                  };





//PRINTANDO A LISTA DE NÚMEROS PRIMOS
printf("2, 3, ");
for(k=2; (2*k+1)<n; ++k){

for(i=0; i<ground; ++i){
if(i*i==2*k+1)
continue;
                       };

if(number_list[k]==true)
printf("%d, ", (2*k+1));
                  };
                          };


//FUNÇÃO PRINCIPAL
int main(){
//DEFINIÇÃO DE VARIÁVEIS
int n;
//RECEBENDO INPUT DO USUÁRIO E EXIBINDO OS NÚMEROS PRIMOS
printf("Vamos calcular os números primos até um certo valor usando a peneira de Sundaram.\n");
printf("Usuário digite um número inteiro:\n");
scanf("%d", &n);
sundaram_sieve(n);
printf("\n");

//FINALIZANDO A APLICAÇÃO
return 0;
          }

