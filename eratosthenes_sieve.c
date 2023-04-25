//VAMOS IMPLEMENTAR EM C UM PROGRAMA QUE USA A PENEIRA DE ERASTÓTENES PARA CALCULAR TODOS OS NÚMEROS PRIMOS ATÉ UM DADO VALOR FORNECIDO PELO USUÁRIO
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o eratosthenes_sieve eratosthenes_sieve.c -lm


/*CABEÇALHO*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

//FUNÇÃO QUE APLICA A PENEIRA DE ERASTÓTENES PARA UM DADO INTEIRO n 
void eratosthenes_sieve(int n){
//VARIÁVEIS LOCAIS
bool number_list[n+1];
double sqrt_n;
int ground;
int i, j, prime;

//AJUSTANDO O ARRAY DE VALORES BOOLEANOS
for (i=0; i<n+2; ++i)
number_list[i]=true;

//AJUSTE DE VARIÁVEIS
sqrt_n=sqrt(n);
ground=floor(n);


//APLICANDO A PENEIRA DE ERATÓSTENES ALISTA DE VALORES BOOLEANOS
for (prime=2; prime<ground; prime++){
for(i=prime*prime; i<n; i+=prime)
number_list[i]=false;
                     
                                       };

//EXIBINDO A LISTA DE NÚMEROS PRIMOS
printf("2, ");
for(i=2; i<n
; ++i){
if(number_list[i]==true)
printf("%d, ", i);
                    };

                              };
//FUNÇÃO PRINCIPAL
int main(){
//DEFINIÇÃO DE VARIÁVEIS
int n;
//RECEBENDO INPUT DO USUÁRIO E EXIBINDO OS NÚMEROS PRIMOS
printf("Usuário digite um número inteiro:\n");
scanf("%d", &n);
eratosthenes_sieve(n);
printf("\n");

//FINALIZANDO A APLICAÇÃO
return 0;
          }
