//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE WILLIAN (p+1) PARA FATORAR NÚMEROS INTEIROS
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o williams_factorization williams_factorization.c -lm

/*
O ALGORITMO DE WILLIAN (p+1) USA SEQUÊNCIAS DE LUCAS PARA FATORAR NÚMEROS INTEIROS. 
A SEQUÊNCIAS DE LUCAS SÃO DEFINIDAS POR: 
V(0)=2, V(1)=A, E V(i)=AV(i-1)-V(i-2).

FATORES NÃO TRIVIAIS SÃO DA FORMA mdc([V(i)-2], n) ONDE n É O NÚMERO A SER FATORADO. 
FATORES PRIMOS p SERÃO ENCONTRADOS SE i FOR MÚLTIPLO DE UM p-(D/p) COM (D/p)=(-1) ONDE (D/p) É O SÍMBOLO DE JACOBI E D=A²-4.
NO CASO (D/p)=(-1) ESTE ALGORITMO SE REDUZ A UM VERSÃO MAIS LENTA DO ALGORITMO POLLARD RHO (p-1).

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Williams%27s_p_%2B_1_algorithm

*/


//**************************************************************************************************************************
//CABEÇALHO
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>

//CONSTANTES GLOBAIS
#define MAX_TRIALS 50

//**************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides para calcular o mdc de dois inteiros
int64_t gcd(int64_t a, int64_t b){
//Procedimentos
if(b==0)
return a;
else
return gcd(b, a%b);
                                 };

//Função que calcula o fatorial de um inteiro
int64_t factorial(int64_t n){
if(n==0 || n==1)
return 1;
else
return n*factorial(n-1);
                            };

//Função que implementa o algoritmo de Wilians (p+1)
void williams_algorithm(int64_t n){
//Variáveis locais
int64_t x, y, M, A=1, V;
int64_t factor1=1, factor2; 

//Procedimentos
//Ajuste de variáveis
pick:
A++;
M=factorial(A);
x=A;
y=((A*A)-2)%n;

//Loop principal: interando sobre os bits de A! exceto o primeiro
while(M>1){
//Checando a paridade do último bit e ajustando valores das variáveis
if(M&1){
x=((x*y)-A)%n;
y=((y*y)-2)%n;
       };

if(!(M&1)){
y=((x*y)-A)%n;
x=((x*x)-2)%n;
       };

//Bit shift
M>>=1;
          };

//Checando se fatores do número em questão foram encontrados
V=x;
factor1=gcd((V-2), n);

if(factor1!=1 && factor1!=n){
factor2=n/factor1;
printf("Fatores de %li: %li e %li.\n", n, factor1, factor2);
return;
                            }
else
goto pick;
                                  };


//**************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
//Variáveis
int64_t number;


//Recebendo input do usuário
printf("Digite un número inteiro para que fatores deste número seja calculado: ");
scanf("%li", &number);

//Calculando os fatores do número a ser decomposto
williams_algorithm(number);

//Finalizando a aplicação
return 0;
          }
