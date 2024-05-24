//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE GAUSS-EULER PARA TESTAR A PRIMALIDADE DE INTEIRO DE 64-BITS

/*
USANDO A LEI DA RECIPROCIDADE QUADRÁTICA DE GAUSS E O CRITÉRIO DE EULER UM SIMPLES TESTE DE PRIMALIDADE É DEFINIDO PARA INTEIROS DE 64 BITS.
SEJA (a|q) O SÍMBOLO DE LEGENDRE, A LEI DE RECIPROCIDADE QUADRÁTICA AFIRMA QUE PARA DOIS PRIMOS ÍMPARES p E q (p|q)(q|p)={(-1)^((p-1)/2)}{(-1)^((q-1)/2)}.

O CRITÉRIO DE EULER ESTABELECE QUE PARA UM INTEIRO a COPRIMO COM UM PRIMO ÍMPAR p: (a|p)=a^((p-1)/2) (mod p).

O SEGUINTE TEOREMA É USADO NO TESTE DE  PRIMALIDADE EM QUESTÃO:
PARA UM PRIMO ÍMPAR p: (2|p)=+1 SE p=7 (mod 8) OU p=1 (mod 8); (2|p)=(-1) SE p=3 (mod 8) OU p=5 (mod 8).

OS RESULTADOS ACIMA NOS PERMITE TESTAR A PRIMALIDADE DE UM INTEIRO DE 64 BITS USANDO SIMPLES OPERAÇÕES DE EXPONENCIAÇÃO E ARITMÉTICA MODULAR.
SE EQUIPADO COM O TESTE DE MILLER-RABIN É POSSSÍVEL CRIAR UM EFICIENTE MÉTODO DETERMINÍSTICO PARA TESTAR A PRIMALIDADE DE INTEIROS DE ATÉ 64 BITS. 

PARA MAIORES INFORMAÇÕES: https://arxiv.org/pdf/2311.07048.pdf

*/


//*******************************************************************************************************************************************************************
//CABEÇALHO
#ifndef GAUSS_EULER_PRIMALITY_TEST_H
#define GAUSS_EULER_PRIMALITY_TEST_H
#include"mod_bin_exponentiation128.h"
#include"legendre_symbol.h"
#include<stdbool.h>
#include<math.h>

//*******************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool small_prime_checking(uint64_t);
bool gauss_euler_primality_test(uint64_t);

//*******************************************************************************************************************************************************************
//FUNÇÕES
//Função usada para detectar pequenos primos
bool small_prime_checking(uint64_t n){
//Casos triviais
if(n<2)
return false;
if(n==2 || n==3)
return true;
if((n%2)==0 || (n%3)==0)
return false;

//Variáveis locais
uint64_t i, limit=sqrt(n);

//Loop principal 
for(i=5; i<limit; i+=6){
if((n%i)==0 || (n%(i+2))==0)
return false;
                       };
return true;

                                     };

//Função que implementa o teste de primalidade de Gauss-Euler
bool gauss_euler_primality_test(uint64_t n){
//Variáveis locais
uint64_t tester, tester2, prime;

//Procedimentos
//Teste 1
if((n%8)==1 || (n%8)==7){
if(mod_bin_pow(2, ((n-1)/2), n)!=1)
return false;
                        };

//Teste 2
if((n%8)==3 || (n%8)==5){
if(mod_bin_pow(2, ((n-1)/2), n)!=(n-1))
return false;
                        };

//Ajuste de variável
tester=floor(sqrt(n));
tester2=mod_bin_pow(tester, ((n-1)/2), n);

//Teste 4
if(tester2!=1 && tester2!=(n-1))
return false;

//Ajuste de variável
tester+=1;
tester2=mod_bin_pow(tester, ((n-1)/2), n);

//Teste 5
if(tester2!=1 && tester2!=(n-1))
return false;

//Ajuste de variável
tester=floor(sqrt((n/2)));
tester2=mod_bin_pow(tester, ((n-1)/2), n);

//Teste 6
if(tester2!=1 && tester2!=(n-1))
return false;

//Ajuste de variável
tester+=1;
tester2=mod_bin_pow(tester, ((n-1)/2), n);

//Teste 7
if(tester2!=1 && tester2!=(n-1))
return false;

//Etapa 8: busca por um primo pequeno da forma p=8k+5 tal que (n|p)=(-1)
prime=5;
while(true){
if(small_prime_checking(prime)==true && legendre(n, prime)==(-1))
break;
else 
prime+=8;
           };

//Teste 9
if(mod_bin_pow(prime, ((n-1)/2), n)!=(n-1))
return false;

//Etapa 10: busca por um primo pequeno da forma p=8k+5 tal que (n|p)=(-1)
prime=1;
while(true){
if(small_prime_checking(prime)==true && legendre(n, prime)==(-1))
break;
else 
prime+=8;
           };

//Teste 11
if(mod_bin_pow(prime, ((n-1)/2), n)!=(n-1))
return false;

//Caso o número passe nos testes acima um primo foi encontrado
return true;



                                           };


//*******************************************************************************************************************************************************************
//FIM DO HEADER
#endif
