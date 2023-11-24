//VAMOS IMPLEMENTAR O ALGORITMO DE POLLARD PARA FATORAR NÚMEROS INTEIROSEM DOIS FATORES DISTINTOS
// COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o pollard_rho_factorization pollard_rho_factorization.c -O2

/*
O ALGORITMO DE POLLARD É UMA ALGORITMO BEM EFICIENTE PARA DECOMPOR UM NÚMERO INTEIRO EM DOIS FATORES PRIMOS.
O ALGORITMO BASEIA-SE NA GERAÇÃO GERAÇÃO DE UMA SEQUÊNCIA PSEUDO-ALEATÓRIA USANDO UM POLONÔMIO COMO p(x)=x²+1 OU 
p(x)=x²+1 mod(n), ONDE n É UM NÚMERO A SER FATORADO.

O ALGORITMO DE POLLARD É EXECUTADO NAS SEGUINTES ETAPAS:
1. PROVIDO UMA SEMENTE INICIAL x E y O VALOR DE p(x) E p(p(y)) É COMPUTADO.
2. OS VALORES DE x E y SÃO ATUALIZADOS x=p(x) E y = p(p(y)).
3. O VALOR DE d = mmc(|x-y|, n) É COMPUTADO.
4. CASO 1<d<n, d É UM FATOR NÃO TRIVIAL DE n. EM CASO DE d=n O TESTE FALHOU.

PARA OTIMIZAR O TESTE DIVERSAS BASES INICIAIS PODEM SER TESTADAS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm

*/

//*********************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdint.h>

//*********************************************************************************************************************
//FUNÇÕES
//Algoritmo de Euclides para calcular o mdc de dois inteiros
uint64_t euclides_check(uint64_t a, uint64_t b){
//Procedimentos
if(b==0)
return a;
else
return euclides_check(b, a%b);
                                               };

//Função que implementa o algoritmo de Pollard
void pollard_rho(uint64_t x, uint64_t y, uint64_t n){
//Variáveis locais
uint64_t factor1, factor2;
uint64_t remainder=1;
uint64_t a=1, counter=0;

//Procedimentos
//Testando inicialmente com x=2, y=2
restart:
while(remainder==1){
x=((x*x+1)%n);
y=((y*y+1)%n);
y=((y*y+1)%n);

if(x>y)
remainder=euclides_check((x-y), n);
if(x<y)
remainder=euclides_check((y-x), n);

if(remainder>1 && remainder<n){
factor1=remainder;
factor2=n/factor1;
printf("Fatores não triviais encontrados: %lu e %lu\n", factor1, factor2);
return;
                              };

//Atualizando variáveis
counter++;
if(counter>1e10){
counter=0;
a++;
                };

if(remainder==n){
printf("Teste falhou!");
return;
                };
                  };

                                                  };

//*********************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
//Variáveis locais
uint64_t number;
//Recebendo o input
printf("Digite o número a ser fatorado.\n->");
if(scanf("%li", &number)!=1)
return 0;

//Aplicando o algoritmo de Pollard rho (p-1)
pollard_rho(2, 2, number);

//Finalizando a aplicação
return 0;
          }
