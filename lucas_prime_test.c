//VAMOS CRIAR UM PROGRAMA QUE IMPLMENTA O TESTE DE PRIMALIDADE DE LUCAS 
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o lucas_prime_test lucas_prime_test.c -lm


/*
 O TESTE DE PRIMALIDADE DE LUCAS É UM TESTE PROBABiLÍSTICO QUE FAZ USO DAS CHAMADAS SEQUÊNCIAS DE LUCAS DO PRIMEIRO TIPO.
 ESTAS SEQUÊNCIAS SÃO DEFINIDAS PELAS RELAÇÕES DE RECORRÊNCIA:
 U(0)=0, U(1)=1, U(N)=P.U(N-1)-Q.U(N-2).

 OS PARÂMETROS P=1, Q=-1, FUNCIONAM PERFEITAMENTE PARA INTEIROS ÍMPARES QUE NÃO SÃO DA FORMA 4k+1,COM k INTEIRO POSITIVO.
 

 O ALGORITMO É IMPLEMENTADO NAS SEGUINTES ETAPAS:
 1. UMA ETAPA PRELIMINAR TESTANDO SE UM DADO NÚMERO É DIVISIVEL PELOS PRIMEIROS NÚMEROS PRIMOS.
 2. CALCULAMOS s=log2(n)+1. 
 3. ESCOLHEMOS UM INTEIRO k TAL QUE 2^k>(P*P-4Q)^(s-1)
 4. COMPUTA-SE O k-ÉSIMO TERMO DA SEQUÊNCIA DE LUCAS
 5. SE k=0, 2^(s-1), -2^(s-1); O TESTE É INCONCLUSIVO
 6. COMPUTA-SE O mdc DO k-ÉSIMO TERMO E DE n, CASO O RESULTADO SEJA 1 O NÚMERO EMQUESTÃO É UM PROVÁVEL PRIMO.
    CASO CONTRÁRIO, O NÚMERO É COMPOSTO.

*/


//********************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include<stdint.h>
#include<math.h>
#include<time.h>
#include"mod_bin_exponentiation.h"


//********************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides
uint64_t gcd_euclides(uint64_t a, uint64_t b){
if(b==0)
return a;
else
return gcd_euclides(b, a%b);

                                             };

//Função que calculao k-ésimo termo na sequência de Lucas a menos de uma relação de congruência
uint64_t lucas_sequence(uint64_t n, uint64_t P, uint64_t Q, uint64_t k){
//Variáveis
uint64_t U0=0;
uint64_t U1=1;
uint64_t U2;
uint64_t i;//Variável de iteração
                                  
//Procedimentos
for(i=0; i<k; ++i){
U2=(((P*U1)%n)-((Q*U0)%n))%n;

//Atualizando variáveis para a próxima iteração
U0=U1;
U1=U2;
                  };                                     
return U1;
                                                                       };

//Teste de primalidade
bool lucas_test(uint64_t n){
//Variáveis locais
uint64_t s=log2l(n)+1;
uint64_t k=1, lucas_term;

//Procedimentos 
//Determinando quantos termos da sequência de Lucas devem ser calculados
while (bin_pow(2, k)<=bin_pow(5, s-1))
++k;

//Calculando o k-ésimo termo da sequência de Lucas  e checando se o teste é aplicável ou não 
lucas_term = lucas_sequence(n, 1, -1, k);

if(lucas_term==0 || lucas_term==bin_pow(2, s-1) || lucas_term==((-1)*bin_pow(2, s-1))){
printf("Teste inconclusivo.\n");
return false;
                                                                                       }
else{
if(gcd_euclides(lucas_term, n)==1)
return true;
else
return false;
    };


                           }


//********************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
//Váriaveis
uint64_t number;
//Procedimentos
//Recebendo input do usuário
printf("Digite um número que será testado:\n");
scanf("%lu", &number);

//Executando o teste
if(lucas_test(number)==true)
printf("Provável primo encontrado!\n");
else
printf("Número composto.\n");

//Finalizando a aplicação
return 0;
          }
