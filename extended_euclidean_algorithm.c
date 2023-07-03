//VAMOS CRIAR UM PROGRAMA QUE IMPLMENTA O ALGORITMO DE EUCLIDES EXTENDIDO EM C
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o extended_euclidean_algorithm extended_euclidean_algorithm.c -lm


/*
O ALGORITMO DE EUCLIDES EXTENDIDO É USADO PARA COMPUTAR O MÁXIMO DIVISOR COMUM DE DOIS NÚMEROS.  
PORÉM AO CONTRÁRIO DO ALGORITMO USUAL QUE APENAS RETORNA O mmc DE DOIS NÚMEROS, O ALGORITMO EXTENDIDO DETERMINA OS CHAMADOS 
COEFICIENTES DA IDENTIDADE DE BEZOUT.

PARA DOIS NÚMEROS a, b A IDENTIDADE DE BÉZOUT É ax+by=mmc(a, b).

QUANDO a E b SÃO RELATIVAMENTE PRIMOS ENTRE SI O ALGORITMO RETORNA O INVERSO MULTIPLICATIVO MODULAR DE UN NÚMERO.
PARA UM NÚMERO a, SEU INVERSO MULTIPLICATIVO x MÓDULO m SATIFAZ A RELAÇÃO: a.x ≡ 1 mod(m)

EM PARTICULAR PARA a E b RELATIVAMENTE PRIMOS mmc(a b)=1, NA IDENTIDADE DE BÉZOUT x É O INVERSO MULTIPLICATIVO DE a MÓDULO b
E y É O INVERSO MULTIPLICATIVO DE b MÓDULO a.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
https://medium.com/@curiosity-papers/extended-euclidean-algorithm-number-theory-7a013b73717d
https://medium.com/@curiosity-papers/a-complete-explanation-of-rsa-asymmetric-encryption-86089a9bef3a#687d

ADAPTAÇÕES DESTE ALGORITMO PODEM SER USADOS PARA DIVERSAS APLICAÇÕES EM CRIPTOGRAFIA E TEORIA DO NÚMEROS EM GERAL, ETC.

*/


//**************************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>

//**************************************************************************************************************************
//FUNÇÕES
void extended_euclidean_algorithm(int64_t a, int64_t b){
//Variáveis locais
int64_t r0,r1, x0, x1, y0, y1, r2, x2, y2;
//Procedimentos 
//Ajuste de variáveis
r0=a;
r1=b;
r2=1;
x0=1;
x1=0;
y0=0;
y1=1;
//Calculando os valores finais coeficientes recursivamente

while(r2>0){
int64_t quotient= r0/r1;

r2=r0-quotient*r1;
x2=x0-quotient*x1;
y2=y0-quotient*y1;
//Atualizando variáveis para a próxima iteração
if(r2>0){
r0=r1;
r1=r2;
x0=x1;
x1=x2;
y0=y1;
y1=y2;
        };

            };

//Ajuste de sinal
if(x2<0)
x2*=(-1);
if(y2<0)
y2*=(-1);

printf("mdc(%li, %li)= %li\n",a, b, r1);
printf("Coeficiente da identidade de Bézout: %li, %li\n", x1, y1);
printf("Razão de %li e %li pelo mmc(%li, %li): %li, %li\n",a, b, a, b, y2, x2);
                                                      };

//**************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
//Variáveis locais
int64_t a, b;
//Procedimentos 
//Recebendo input do usuário
printf("Usuário digite um número inteiro: ");
scanf("%li",&a);
printf("Usuário digite um número inteiro: ");
scanf("%li",&b);

//Realizando o teste
extended_euclidean_algorithm(a,b);

//Finalizando a aplicação
return 0;
          }
