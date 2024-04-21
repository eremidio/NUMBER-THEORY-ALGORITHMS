//VAMOS IMPLEMENTAR O ALGORITMO DE POLLARD PARA FATORAR NÚMEROS INTEIROSEM DOIS FATORES DISTINTOS
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o pollard_rho_factorization_128bits pollard_rho_factorization_128bits.c -O3

/*
O ALGORITMO DE POLLARD É UMA ALGORITMO BEM EFICIENTE PARA DECOMPOR UM NÚMERO INTEIRO EM DOIS FATORES PRIMOS.
O ALGORITMO BASEIA-SE NA GERAÇÃO GERAÇÃO DE UMA SEQUÊNCIA PSEUDO-ALEATÓRIA USANDO UM POLONÔMIO COMO p(x)=x²+1 OU p(x)=x²+1 mod(n), ONDE n É UM NÚMERO A SER FATORADO.

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
#include<stdint.h>
#include<math.h>

//*********************************************************************************************************************
//FUNÇÕES
//Algoritmo de Euclides para calcular o mdc de dois inteiros
__int128_t gcd128(__int128_t a, __int128_t b){

 if(b==0)
  return a;
 else
  return gcd128(b, a%b);
                                             };


//Função que implementa o algoritmo de Pollard
void pollard_rho(__int128_t x, __int128_t y, __int128_t n){

 //Variáveis locais
 __int128_t factor1, factor2;
 __int128_t remainder=1;
 uint64_t counter=0;
 uint64_t a=1;


 //Procedimentos
  //Testando inicialmente com x=2, y=2
  restart:
  while(remainder==1){
   x=((x*x+a)%n);
   y=((y*y+a)%n);
   y=((y*y+a)%n);


   if(x>y)
    remainder=gcd128((x-y), n);
   if(x<y)
    remainder=gcd128((y-x), n);


   if(remainder>1 && remainder<n){
    factor1=remainder;
    factor2=n/factor1;
    printf("Fatores não triviais encontrados:\n");
    printf128(factor1);
    printf128(factor2);
    return;
                                 };


   //Atualizando variáveis
   counter++;
   if(counter>1e10){
    counter=0;
    a++;
                   };

   if(remainder==n){
    printf("Teste falhou!\n");
    return;
                   };

                     };

   printf("Teste falhou!\n");

                                                  };

//*********************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){

 //Variáveis locais
 __int128_t number, seed1, seed2;
 char number_string[41], number_string1[41], number_string2[41];

 //Recebendo o input do 
 printf("Digite o número a ser fatorado: ");
 if(scanf("%s", number_string)!=1)
  return 0;
 number=scanf128(number_string);


 printf("Semente para geração de números pseudoaleatórios: ");
 if(scanf("%s", number_string1)!=1)
  return 0;
 seed1=scanf128(number_string1);

 printf("Semente para geração de números pseudoaleatórios: ");
 if(scanf("%s", number_string2)!=1)
  return 0;
 seed2=scanf128(number_string2);

 //Aplicando o algoritmo de Pollard rho (p-1)
 pollard_rho(seed1, seed2, number);

 //Finalizando a aplicação
 return 0;

          }
