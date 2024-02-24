//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ROTINAS PARA O CÁLCULO DE FATORES DE NÚMEROS DA FORMA n=(b^k)+1 COM n, b, k INTEIROS

/*
O SEGUINTE TEOREMA PODE SER USADO COMO FERRAMENTA PARA AUXILIAR A ENCONTRAR FATORES PRIMOS DE NÚMEROS INTEIROS QUE PODEM SER ESCRITOS NA FORMA  n=(b^k)+1 COM n, b, k
INTEIROS:
SEJAM r E s, INTEIROS TAIS QUE r DIVIDE s, SE O QUOCIENTE DE s E r FOR ÍMPAR ENTÃO n'=(b^r)+1 DIVIDE n=(b^s)+1.

USANDO A SEQUÊNCIA DE DIVISIBILIDADE PARA NÚMEROS DA FORMA n=(b^k)-1 E O FATO DE SE n'=(b^k)+1, ENTÃO n"=n'n= b^(2k)-1, ENTÃO A SEGUINTE PROPOSIÇÃO É TRIVIAL:
FATORES PRIMOS DE  n"= b^(2k)-1 QUE NÃO SÃO FATORES PRIMOS DE n=(b^k)-1 SÃO FATORES DE n'=(b^k)+1.

EM ALGUNS CASOS TAIS PROPOSIÇÕES SÃO ÚTEIS EM DETECTAR FATORES PRIMOS DE GRANDES NÚMEROS QUE POSSUEM A FORMA ESPECIAL MENCIONADA.

GENERALIZAÇÕES DESTE PROCEDIMENTOS INCLUEM AS FATORAÇÕES DE AURIFEUILLAN QUE USANDO POLINÔMIOS CICLOTÔMICOS PERMITEM A RÁPIDA IDENTIFICAÇÃO DE FATORES PRIMOS DE CERTOS
NÚMEROS INTEIROS QUE PODEM SER ESCRITOS DE FORMA ESPECIAL.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Aurifeuillean_factorization
                          The Joy Of Factoring by Samuel Wagstaff Jr.

*/

//****************************************************************************************************************************************************
//CABEÇALHO
#ifndef PRIME_POWER_PLUSONE_FACTORIZATION_H
#define PRIME_POWER_PLUSONE_FACTORIZATION_H
#include"baillie_psw_prime_test.h"
#include"prime_power_minusone_factorization.h"

//****************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void proper_divisors_partial_factorization2(uint64_t, uint64_t*);
void prime_power_plusone_factorization(uint64_t, uint64_t);

//****************************************************************************************************************************************************
//FUNÇÕES

//Função que calcula fatores de n=(b^n)+1 comuns a n=(b^d)+1 com d|n e o quociente de 'n' e 'd' ímpar
void proper_divisors_partial_factorization2(uint64_t n, uint64_t* N){
//Variáveis locais
uint64_t root=sqrt(n);
uint64_t N_=(*N);
uint64_t i;

//Procedimentos
//Fatores 2,3
if(n%2==0){
while(n%2==0)
n/=2;

while(N_%2==0)
N_/=2;

printf("Fator de %lu encontrado: 2\n",(*N));
          };

if(n%3==0){
while(n%3==0)
n/=3;

while(N_%3==0)
N_/=3;

printf("Fator de %lu encontrado: 3\n",(*N));
          };


//Loop principal
for (i=5; i<=root; i+=6){

if(n%i==0){
while(n%i==0)
n/=i;

while(N_%i==0)
N_/=i;

printf("Fator de %lu encontrado: %lu\n", (*N), i);
          };

if(n==1) break;

if(n%(i+2)==0){
while(n%(i+2)==0)
n/=i;

while(N_%(i+2)==0)
N_/=(i+2);

printf("Fator de %lu encontrado: %lu\n", (*N), (i+2));
            };

if(n==1) break;
                        };


//Fatores > n^(1/2)
if(n>1){
printf("Fator de %lu encontrado: %lu\n", (*N), n);
N_/=n;

       };


//Ajuste de variáveis
(*N)=N_;
if((*N)>1)
printf("Cofator: %lu\n", (*N));
                                                                    };


//Função que calcula uma fatoração parcial ou completa de um número da forma n=(b^k)+1
void prime_power_plusone_factorization(uint64_t base, uint64_t power){
//Variáveis locais
uint64_t number=bin_pow(base, power)+1;
uint64_t divisor;
uint64_t n1=number;
uint64_t i, exponent;

//Procedimento
//-----
printf("Número a ser fatorado: %lu\n", number);

//Loop sobre divisores do expoente
for(i=1; i<=power; ++i){
if(n1==1)
break;

if((power%i)==0){
exponent=power/i;

if((exponent%2)==1){
divisor=bin_pow(base, exponent)+1;
proper_divisors_partial_factorization2(divisor, &n1);
                   };

                };
                       };

//Checagem se a fatoração foi completa
if(n1==1)
return;

else{
if(baillie_psw_test(n1)==true)
printf("%lu é primo.\n", n1);
else
printf("Demais fatores primos de %lu são os fatores primos de %lu^(%lu)-1 que não são fatores primos de %lu^(%lu)-1.\n", number, base, (2*power), base, power);
    };


                                                                     };

//****************************************************************************************************************************************************
//FIM  DO  HEADER
#endif
