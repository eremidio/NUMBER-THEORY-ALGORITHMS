//VAMOS CRIAR UM PROGRAMA IMPLEMENTA A CONTAGEM DE PRIMOS
//COMPILAR ESTE PROGRAMA COM A FUNÇÃO: gcc -o prime_counting_function prime_counting_function.c -lm

//***********************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include<math.h>
#include<assert.h>

#define SIEVE_MAX 8000000 //VALOR MÁXIMO CALCULADO VIA PENEIRA DE ERATÓSTENES
//***********************************************************************************************************************
//FUNÇÕES
//Função de contagem de primos para números pequenos usando a peneira de Eratóstenes
unsigned long long prime_counting_function(double x){
//Restrição do método a números até 10^6
assert(x<=SIEVE_MAX);

//Variáveis locais
unsigned long long n= (unsigned long long)x;
bool number_list[n];
unsigned long long ground, counter;
unsigned long long i, j, prime;

//AJUSTANDO O ARRAY DE VALORES BOOLEANOS
for (i=0; i<n; ++i)
number_list[i]=true;

//AJUSTE DE VARIÁVEIS
ground=floor(sqrt(n));


//APLICANDO A PENEIRA DE ERATÓSTENES A LISTA DE VALORES BOOLEANOS
for (prime=2; prime<=ground; prime++){
for(i=prime*prime; i<n; i+=prime)
number_list[i]=false;
                                     };
//Contagem de números primos
counter=0;
for(i=2; i<n; ++i){
if(number_list[i]==true){
//TESTE USE UM // APÓS O MESMO
//printf("%ld ", i);
counter++;
                        };
                  };

//Resultado
return counter;                     
                                };


//***********************************************************************************************************************
//FUNNÇÃO PRINCIPAL
int main(){
//Variáveis locais
double x;
//Procedimentos 
//Recebendo input do usuário
printf("Digite um limite:\n");
scanf("%lf", &x);
//Calculando o número de primos até o valor limite
printf("Número de primos até %llu: %llu.\n", (unsigned long long)x, prime_counting_function(x));

//Finalizando a aplicação
return 0;
          }
