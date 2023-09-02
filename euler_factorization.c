//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE EULER PARA FATORAR NÚMEROS INTEIROS
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o euler_factorization euler_factorization.c -lm

/*
O ALGORITMO É ÚTIL PARA FATORAR NÚMEROS INTEIROS QUE PODEM SER EXPRESSOS DE PELOS DUAS FORMAS DISTINTAS COMO A SOMA DE
QUADRADOS, ISTO É n=a²+b²=c²+d².

USANDO QUE (a²-c²)=(d²-b²)  OU (a+c)(a-c)=(d+b)(d-b). TOMA-SE (a-c)=kl, (d-b)=km COM  k=mdc((d-b),(a-c)) E mdc(l, m)=1.
SIMILARMENTE (a+c)=hl', (d+b)=hm' COM h=mdc((d+b),(a+c)) E mdc(l', m')=1.

MANIPULAÇÕES ALGÉBRICAS USANDO A FÓRMULA DE BRAHMAGUPUTA-FIBONACCI E USANDO AS DEFINIÇÕES NOS PERMITE ESCREVER
n=[(k/2)²+(h/2)²][l²+m²] OBTENDO ASSIM DOIS FATORES DO NÚMERO EM QUESTÃO.

O ALGORITMO DE EULER CONSISTE EM ENCONTRAR DOIS PARES DE VALORES a, b E c, d SATISFAZENDO ESTAS CONDIÇÕES.
DE ACORDO O TEOREMA DA SOMA DE QUADRADOS EM TEORIA DOS NÚMEROS SE n TIVER UM FATOR p^k COM p PRIMO TAL QUE p = 3 (mod 4) E k 
ÍMPAR NÃO EXISTE VALORES DE a, b, c, d SATISFAZENDO A RELAÇÃO ACIMA.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Euler%27s_factorization_method

*/

//***************************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<math.h>
#include"baillie_psw_prime_test.h"

//***************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides para se calcular o mdc de dois inteiros
int64_t euclides_algorithm(int64_t a, int64_t b){
if(b==0)
return a;
else
return euclides_algorithm(b, a%b);
                                            };

//Função que checa se um número é quadrado perfeito
bool perfect_square_checker(int64_t n){
//Variáveis locais
int64_t odd=1;
//Procedimento
while(n>0){
n-=odd;
odd+=2;

if(n<0)
return false;
          };

return true;
                                      };

//Função que implementa o algoritmo de Euler
void euler_algorithm(int64_t n){
//Testando se o número em questão é primo
if(baillie_psw_test(n)==true){
printf("O número em questão é primo.\n");
return;
                             };
//Variáveis locais
int64_t a, b, c, d, tester;
int64_t A, B, C, D;
int64_t k, h, l, m, factor1, factor2;

//Procedimento
//Encontrando o primeiro par de quadrados na decomposição do número a ser fatorado
for(a=1; a<ceil(sqrt(n)); ++a){
tester=n-(a*a);
b=sqrt(tester);
if(perfect_square_checker(tester)==true)
break;
                              };

if(((a*a)+(b*b))!=n){
printf("Falha ao expressar o número a ser fatorado como a soma de quadrados! (1)\n");
return;
                    };

//Encontrando o segundo o par de quadrados na decomposição do número a ser fatorado
for(c=(a+1); c<n; ++c){
tester=n-(c*c);
d=sqrt(tester);
if(perfect_square_checker(tester)==true)
break;
                              };

if(((c*c)+(d*d))!=n){
printf("Falha ao expressar o número a ser fatorado como a soma de quadrados! (2)\n");
return;
                    };

//Cálculos das variáveis empregadas no algoritmo de Euler
A = (c-a);
B = (c+a);
C = (b-d);
D = (b+d);
k = euclides_algorithm(A, C);
h = euclides_algorithm(B, D);
l = euclides_algorithm(A, D);
m = euclides_algorithm(B, C);

//Cálculo dos fatores do número em questão
factor1 = ((k*k)+(h*h))/4;
factor2 = ((l*l)+(m*m))/4;
printf("Fatores de %li, encontrados: %li, %li\n",n, factor1, factor2);

                               };



//***************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
//Variáveis
int64_t number;

//Procedimentos
//Recebendo input do usuário
printf("Digite un número inteiro para que fatores deste número seja calculado.\n->");
scanf("%li", &number);

//Calculando os fatores do número a ser decomposto
euler_algorithm(number);

//Finalizando a aplicação
return 0;
          }
