//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE BAILLIE-PSW PARA TESTAR A PRIMALIDADE DE UM NÚMERO INTEIRO

/*
O TESTE DE PRIMALIDADE BAILLIE-PSW É UM DOS TESTE DE PRIMALIDADE MAIS IMPORTANTES EM TEORIA DE NÚMEROS.
É UMA MISTURA DAS ABORDAGENS DO TESTE DE MILLER-RABIN E DO TESTE DE LUCAS PARA PROVÁVEIS PRIMOS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Baillie–PSW_primality_test
                          https://en.wikipedia.org/wiki/Lucas_pseudoprime#Strong_Lucas_pseudoprimes
                          https://medium.com/@shruti.singh20/primality-testing-algorithms-dbea1ff9f0c7
    
*/ 

//********************************************************************************************************************
//CABEÇALHO
#ifndef BAILLIE_PSW_PRIME_TEST_H
#define BAILLIE_PSW_PRIME_TEST_H
#include<stdbool.h>
#include<stdint.h>
#include<math.h>
#include<time.h>
#include"mod_bin_exponentiation.h"
#include"jacobi_symbol.h"


//********************************************************************************************************************
//FUNÇÕES
//Função que testa se um número é divisível por pequenos números primos, usaremos primos até 100
bool small_prime_factor_test(uint64_t n, uint64_t prime_seed[]){
//Loop principal
for(int counter=0; counter<25; counter++){
if(n%prime_seed[counter]==0)
return false;
                                         };

return true;
                                                               }

//Função que realiza o teste de Lucas Lehmer para a primalidade dos chamados números de Merssene da forma 2^p-1
bool lucas_lehmer_test(uint64_t n){
//Parte 1: obtendo o expoente
//Checando se o número em questão é um número de Merssene
uint64_t p=7; //Expoente
uint64_t mersenne;
while(true){
mersenne=bin_pow(2, p)-1;
if(mersenne==n)//Expoente encontrado 
break;
//Recursão
if(mersenne<n){
p++;
continue;
              };
if(mersenne>n)//O número em questão não é um número de Mersenne
return false;//Vai para o próxima etapa
           };

//Parte2: O teste de Lucas - Lehmer.
//A sequência de Lucas Lehmer é definida como: S(0)=4 e S(N)=S(N-1)^2-2.
//Se S(N-1)= 0 mod(N)então o número de Mersenne em questão é primo

//Variáveis locais
uint64_t i;//Variáveis de iteração
uint64_t lucas_lehmer=4;
//Procedimentos
for(i=0; i<p-2; ++i)
lucas_lehmer=((lucas_lehmer*lucas_lehmer)-2)%mersenne;

if(lucas_lehmer==0)
return true;
else
return false;
                                  };

//Função que realiza o teste de Baillie para testar a primalidade de um número primo
bool baillie_test(uint64_t n){
//Checando se o número em questão é um quadrado perfeito
//Variáveis locais
double sqrt_n = sqrt(n);
uint64_t limit = round(sqrt_n);
//Procedimentos
if(floor(sqrt_n)-sqrt_n>=0)
return false;

//Checando se o número de questão pode ser escrito como a diferença de quadrados,
//Variáveis locais
uint64_t i;

for(i=1; i<limit; ++i){
if(n%(limit-i)==0){
uint64_t factor1=limit-i;
uint64_t factor2=n/factor1;
if(factor1!=1 && factor2!=1)
return false;
                  };
                      };
return true;
                             };

// Teste de Lucas usando sequências de Lucas
bool lucas_sequence_test(int64_t n, int64_t P, int64_t Q){
int64_t U0 = 0, U1 = 1, V0 = 2, V1 = P;
int64_t k = 1;/*variável que registra o número de iterações (n-2) e (n-1)determinam o n-ésimo termo*/;
int64_t D =  P * P - 4 * Q;//Discrimante da equação característica x²-Px+Q=0
while (k <= n){
//Caso trivial
if (k == n)
return U1 == 0;


//Calculando os termos da sequência de Lucas de primeiro e segundo tipo usando as relações recursivas:
//x(n)=p.x(n-1)-q.x(n-2),com U(0)=1, U(1)=1 e V(0)=2, V(1)=P
int64_t U2 = P * U1 - Q * U0, V2 = P * V1 - Q * V0;

//Assegurando que os termos da sequência estão dentro do limite de validade
if (U1 % 2 == 0)
U2 %= n;
else
U2 = (U2 + n) % n;

if (V1 % 2 == 0)
V2 %= n;
else
V2 = (V2 + n) % n;

//Atualizando os termos na sequência x(n-1)--> x(n)
U0 = U1; U1 = U2; V0 = V1; V1 = V2;
k *= 2;
if (k == n)
return U1 == 0;

//Calculando o discrimante da equação característica x²-Px+Q=0
//Condição de primalidade
if (D == 1)
return true;

//Atualizando os parâmetros para a proxima iteração
D = (D + D) % n;
P = (P * P - 2 * Q) % n;
Q = (Q * Q) % n;
if (Q < 0)
Q += n;
               }
return false;
                                                       };

//Função geral
bool baillie_psw_test(uint64_t n){
//Caso trivial primos inferiores a 100
if(n<2)
return false;

uint64_t prime_seed[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};

for(int counter=0; counter<25; counter++){
if(n==prime_seed[counter])
return true;
                                         };

//Teste1: pequenos fatores primos
if(small_prime_factor_test(n, prime_seed)==false)
return false;


//Teste 2: Teste de Lucas-Lehmer para números de Mersenne
else if(lucas_lehmer_test(n)==true)
return true;


//Teste3: Realizando o teste de Baillie
if(n<1e16 && baillie_test(n)==false)
return false;

//Teste 4: Realizando teste de Fermat para primos inferiores a 100
for(int counter=0; counter<25; counter++){
if(mod_bin_pow(prime_seed[counter],(n-1), n)!=1)
return false;
                                         };

//Teste 5: Calculando o símbolo de Jacobi 
if((jacobi(2, n)*jacobi(2, n))!=1)
return true;
if((jacobi(3, n)*jacobi(3, n))!=1)
return true;
if((jacobi(5, n)*jacobi(5, n))!=1)
return true;
if((jacobi(7, n)*jacobi(7, n))!=1)
return true;
if((jacobi(11, n)*jacobi(11, n))!=1)
return true;
if((jacobi(13, n)*jacobi(13, n))!=1)
return true;
if((jacobi(17, n)*jacobi(17, n))!=1)
return true;
if((jacobi(19, n)*jacobi(19, n))!=1)
return true;
if((jacobi(23, n)*jacobi(23, n))!=1)
return true;
if((jacobi(29, n)*jacobi(29, n))!=1)
return true;
if((jacobi(31, n)*jacobi(31, n))!=1)
return true;
if((jacobi(37, n)*jacobi(37, n))!=1)
return true;


//Teste 6: Teste PSW da sequência de Lucas
else if(lucas_sequence_test(n, 2, 1)==false || lucas_sequence_test(n, 3, 1)==false || lucas_sequence_test(n, 5, 1)==false)
return false;
else if(lucas_sequence_test(n, 7, 1)==false || lucas_sequence_test(n, 11, 1)==false || lucas_sequence_test(n, 13, 1)==false)
return false;
else if(lucas_sequence_test(n, 17, 1)==false || lucas_sequence_test(n, 19, 1)==false || lucas_sequence_test(n, 23, 1)==false)
return false;
else if(lucas_sequence_test(n, 29, 1)==false || lucas_sequence_test(n, 31, 1)==false || lucas_sequence_test(n, 37, 1)==false)
return false;


//Caso o número passe no testes acima, um primo foi encontrado
else
return true;

                                 };

//********************************************************************************************************************
//FIM DO HEADER
#endif
