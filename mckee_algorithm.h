//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE MCKEE PARA FATORAR NÚMEROS INTEIROS E COMO UM TESTE DE PRIMALIDADE

/*
O ALGORITMO DE MCKEE É UMA VARIANTE DO ALGORITMO DE FATORAÇÃO DE EULER QUE UTILIZA REPRESENTAÇÕES DE FORMAS QUADRÁTICAS PARA FATORAR INTEIROS.
UMA FORMA QUADRÁTICA f(x,y)=ax²+bxy+cy² É DITA REPRESENTAR UM INTEIRO n, SE EXISTIREM x,y INTEIROS TAIS QUE f(x, y)=n.
O ALGORITMO DE MCKEE GENERALIZA O MÉTODO DE FATORAÇÃO DE EULER E UMA ANTIGA VARIANTE DESTE MÉTODO DEVIDO A FERMAT, PERMITINDO ENCONTRAR PARES (u, v) DE INTEIROS
TAIS QUE u²-Δv² = 0 (mod 4n) COM Δ=b²-4ac E Δ<0. OS PARES (u, v) SATISFAZEM DETERMINADAS RELAÇÕES DE CONGRUÊNCIA QUE PERMITEM DECOMPOR n EM FATORES PRIMOS OU QUE
ATESTAM QUE n É PRIMO, NO CASO EM QUE n NÃO POSSUA FATORES PRIMOS MENORES QUE 3n^(1/3).

PARA MAIORES INFORMAÇÕES: https://londmathsoc.onlinelibrary.wiley.com/doi/abs/10.1112/blms/28.4.351
                          Prime Numbers. A Computational Perspective by R.Crandall & Carl B. Pomerance
*/

/*
OBSERVAÇÃO: O algoritmo requer computar soluções de equações do tipo x²=a (mod n), com n composto o que é um problema equivalente a fatoração em si. Por esta
razão tal cálculo foi feito por força bruta usando o algoritmo de Newton-Raphson para checar se um dado inteiro é quadrado perfeito. Uma alternativa seria usar o 
algoritmo de Tonelli-Shanks para computar x para cada fator primo de n e combinar os resultados via teorema do resíduo chinês. Se n tiver fatores primos repetidos
o algoritmo de Cipolla extendido para potências de números primos (ver referências no respectivo algoritmo) deve ser usado.

*/


//****************************************************************************************************************************************************
//CABEÇALHO
#ifndef MCKEE_ALGORITHM_H
#define MCKEE_ALGORITHM_H
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<math.h>


//****************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void small_factors_removing(int64_t*);
int64_t euclides_algorithm(int64_t, int64_t);
int64_t floor_square_root(int64_t);
void mckee_algorithm(int64_t);

//****************************************************************************************************************************************************
//FUNÇÕES
//Função que determina se um inteiro possui pequenos fatores primos 3n^(1/3) por tentativa e erro
void small_factors_removing(int64_t* n){
//Variáveis locais
int64_t divisors;
int64_t N_=(*n);
int64_t upper_bound=(3*cbrt(N_));

//Procedimentos
//Fatores 2, 3
if((N_%2)==0){
printf("Fator encontrado: 2.\n");
while((N_%2)==0)
N_/=2;
             };

if((N_%2)==0){
printf("Fator encontrado: 3.\n");
while((N_%3)==0)
N_/=3;
             };

//Loop principal com otimização 6k+1
for(divisors=5; divisors<(upper_bound+1); divisors+=6){
if((N_%divisors)==0){
printf("Fator encontrado: %li.\n", divisors);
while((N_%divisors)==0)
N_/=divisors;
                   };

if((N_%(divisors+2))==0){
printf("Fator encontrado: %li.\n", (divisors+2));
while((N_%(divisors+2))==0)
N_/=(divisors+2);
                   };

                                                      };

//Resultado da execução desta subrotina
if(N_<(*n)){
(*n)=N_;
printf("\nCofator: %li\n", (*n));
           };

                                       };

//Função que implementa o algoritmo de Euclides
int64_t euclides_algorithm(int64_t a, int64_t b){
if(b==0)
return a;
else
return euclides_algorithm(b, (a%b));
                                                };

//Função que usa o algoritmo de Newton-Raphson para calcular limitante inferior de raízes quadradas
int64_t floor_square_root(int64_t n){
//Variáveis locais
int bit_size=log2(n);
int64_t x= pow(2, ceil(bit_size));
int64_t y;

//Procedimento
//Loop principal
while(x>0){
y=floor((x+floor(n/(1.0*x)))/2.0);
if(y>=x)
return x;
else
x=y;
          };

return 0;
                                    };

//Função que implementa o algoritmo de Mckee para fatorar números inteiros usando representações via formas quadráticas de discriminante negativo
void mckee_algorithm(int64_t n){
//Checando se o número em questão possuí pequenos fatores primos inferiores a 3n^(1/3)
small_factors_removing(&n);
if(n==1)
return;

//Caso geral o número em questão não contém fatores pequenos
//Variáveis locais
double tester2;
int64_t ui, u, v, x0, d, tester, bound, bound2;
int64_t a, i;
int64_t factor=1, cofactor=1;


//Procedimento
//Ajuste de variáveis
x0=floor(sqrt(n-(cbrt(n)*cbrt(n))));
d=floor(n-(floor(x0)*floor(x0)));

//Teste 1: divisibilidade de por algum fator primo de d
factor=euclides_algorithm(n, d);
if(factor>1 && factor<n){
cofactor=n/factor;
goto end;
                        };

//Teste 2: checando se n é um quadrado perfeito
tester=floor_square_root(n);
if((tester*tester)==n){
cofactor=tester;
factor=tester;
goto end;
                      };

//Teste 3: congruências definidas por meio de representações de formas quadráticas
bound=floor(2*sqrt(d/3.0));

for(a=1; a<=bound; a++){
while(ui<(4*d)){
//Resolvendo relações de congruência u²= (4an) (mod 4d)
tester=(4*n*a);
ui=floor_square_root(tester);
if((ui*ui)>tester || (ui*ui)<tester){
tester+=(4*d);
continue;
                                    }
//Caso um inteiro u tenha sido encontrado
else{
u=(ui%(4*d));
bound2=(2*sqrt(a*n));

while(u<bound2){
tester2=(((4.0*n*a)-(u*u))/(4*d));
v=floor_square_root(tester);

if((v*v)==tester2 && ((u%(2*n))!=(2*x0*v) || (u%(2*n))!=((2*n)-(2*x0*v)))){
factor=euclides_algorithm(((2*x0*v)-u), n);
if(factor>1 && factor<n){
cofactor=n/factor;
goto end;
                        };
                                                                          }
else
u+=(4*d);
               };
    };

               };
                       };

//Resultado da execução do algoritmo
end:
if(factor>1 && factor<n){
printf("Fator encontrado: %li.\n", factor);
printf("Fator encontrado: %li.\n", cofactor);
                        }
else
printf("%li é primo.\n", n);
 
                               };


//****************************************************************************************************************************************************
//FIM DO  HEADER
#endif
