//VAMOS IMPLEMENTAR O ALGORITMO DE POLLARD PARA FATORAR NÚMEROS INTEIROSEM DOIS FATORES DISTINTOS
// COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o pollard_rho_factorization_128bits pollard_rho_factorization_128bits.c -lm

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
#include"int128.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>
#include<time.h>


//*********************************************************************************************************************
//FUNÇÕES
//Algoritmo de Euclides para calcular o mdc de dois inteiros
__int128_t euclides_check(__int128_t a, __int128_t b){
//Procedimentos
if(b==0)
return a;
else
return euclides_check(b, a%b);
                                                    };

//Função que usa um gerador de números para gerar um número usado no teste do algoritmo de Pollard rho
__int128_t generate_key(__int128_t  value){
//Caso geral escolhendo um palpite maior do que 7
//Semente para geração de números aleatórios
srand(time(NULL));
//Variáveis locais
__int128_t key;
//Selecionando uma chave aleatoriamente
selection:
key= 2+rand()%value-2;
//A chave escolhida deve ser coprima do número a ser fatorado 
if(euclides_check(value, key)!=1)
goto selection;

return key;
                                     };

//Função que implementa o algoritmo de Pollard
void pollard_rho(__int128_t x_, __int128_t y_, __int128_t n){
//Variáveis locais
__int128_t factor1, factor2;
__int128_t remainder=1;
__int128_t x=x_, y=y_;

//Procedimentos
//Testando inicialmente com x=2, y=2
restart:
while(remainder=1){
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
printf("Fatores não triviais encontrados:\n");
printf128(factor1);
printf128(factor2);
return;
                              };

if(remainder==n)
printf("Teste falhou!\n");
                  };

//Retestando com outras base
if(x_==2 && y_==2){
x=generate_key(n);
y=generate_key(n);
goto restart;
                  };
printf("Teste falhou!\n");

                                                    };
//*********************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
//Variáveis locais
__int128_t number;
char number_string[40];

//Recebendo o input
printf("Digite o número a ser fatorado.\n->");
scanf("%s", number_string);
number=scanf128(number_string);

//Aplicando o algoritmo de Pollard rho (p-1)
pollard_rho(2, 2, number);

//Finalizando a aplicação
return 0;
          }
