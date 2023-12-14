//VAMOS CRTIAR UM PROGRAMA QUE CALCULA A SEQUÊNCIA DE FIBONACCI VIA A RAZÃO DE OURO
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o fibonacci_golden_ratio fibonacci_golden_ratio.c -lm

/*
A RAZÃO DE OURO É DEFINIDA PELA EQUAÇÃO φ=a/b, ONDE (a+b)/a=a/b, DONDE φ²+φ+1=0 E TEMOS QUE φ=(1+√5)/2. O N-ÉSIMO TERMO DA SEQUÊNCIA DE FIBONACCI É DADO POR:
F(n)=(φ^n)/(√5).

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Golden_ratio
*/

//**********************************************************************************************************************************************************************
//CABEÇALHO
#include<math.h>
#include<stdint.h>
#include<stdio.h>

//**********************************************************************************************************************************************************************
//FUNÇÃO
uint64_t fibonacci(uint64_t n){
//Caso base
if(n==0)
return 0;

//Variáveis locais
const double root5=sqrt(5);
const double golden_ratio=(1.0+root5)/2;

//Resultado
return round(pow(golden_ratio, n)/root5);
                             };


//**********************************************************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
//Variáveis locais
uint64_t n, i;

//Procedimento
//Recebendo input do usuário
printf("Quantos números você deseja incluir na sequência de Fibonacci: ");
scanf("%lu", &n);

//Gerando a sequência de Fibonacci
for(i=0; i<n; i++)
printf("%lu, ",fibonacci(i));
printf("...\n");

//Finalizando a aplicação
return 0;
          }
