//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE FRÖBENIUS PARA TESTAR A PRIMALIDADE DE UM NÚMERO INTEIRO

/*
O TESTE DE PRIMALIDADE DE FRÖBENIUS É UM TESTE PROBABILÍSTICO QUE USA POLINÔMIOS DO SEGUNDO GRAU E OS CHAMADOS ENDOMORFISMOS DE FRÖBENIUS PARA TESTAR A PRIMALIDADE DE
UM INTEIRO. NÚMEROS COMPOSTOS QUE PASSAM ESSE TESTES SÃO DENOMINADOS PSEUDOPRIMOS DE FRÖBENIUS.
VAMOS IMPLEMENTAR UMA VERSÃO DO TESTE USANDO SEQUÊNCIAS DE LUCAS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Quadratic_Frobenius_test#Concept
                          https://trizenx.blogspot.com/2020/01/primality-testing-algorithms.html

ARTIGO ORIGINAL DISPONÍVEL EM: https://www.sciencedirect.com/science/article/pii/S0022314X98922478?via%3Dihub

*/ 


//********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef QUADRATIC_FROBENIUS_PRIME_TEST_H
#define QUADRATIC_FROBENIUS_PRIME_TEST_H
#include"jacobi_symbol.h"
#include<stdbool.h>

//********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void parameter_selection(int64_t*, int64_t*, int64_t);
void modular_lucas_sequence(int64_t*, int64_t*, int64_t, int64_t, int64_t);
bool quadratic_frobenius_primality_test(int64_t);

//********************************************************************************************************************************************************************
//FUNÇÕES
//Função que determinaparâmetros P e Q usados no teste de primalidade de Fröbenius
void parameter_selection(int64_t* P, int64_t* Q, int64_t n){
//Variáveis locais
int64_t p, q=2, d;

//Procedimentos
//Loop principal: seleção do parâmetro P
for(p=5; ;p+=2){
d=((p*p)-(4*q));
if(euclides_check(n, (2*q*d))==1 && (jacobi(d, n)*(-1))==1)
break;
               };

//Ajuste de variáveis
(*P)=p;
(*Q)=q;
                                                           };

//Função que implementa o cálculo das sequências de Lucas a menos de uma relação de congruência para o teste de primalidade de Fröbenius
void modular_lucas_sequence(int64_t* U, int64_t* V, int64_t P, int64_t Q, int64_t n){
//Variáveis locais
__int128_t V0=2, V1=P, V2;
__int128_t U0=0, U1=1, U2;
int64_t i, upper=(n+1);

//Procedimentos 
//Loop principal
for(i=2; i<=upper; ++i){
U2=((P*U1)-(Q*U2));
V2=((P*V1)-(Q*V2));

if(U2>n)
U2%=n;
if(V2>n)
V2%=n;

//Atualizando variáveis para a próxima iteração
U0=U1; U1=U2;
V0=V1; V1=V2;
                       };

//Ajuste de variáveis
(*U)=(U2%n);
(*V)=(V2%n);
                                                                                    };

//Função que implementa o teste de primalidade de Fröbenius
bool quadratic_frobenius_primality_test(int64_t n){
//Variáveis locais
int64_t P, Q;
int64_t U, V;

//Procedimentos
//Seleção de parâmetros P e Q para ocálculo das sequências de Lucas
parameter_selection(&P, &Q, n);

//Cálculo das sequências de Lucas
modular_lucas_sequence(&U, &V, P, Q, n);

//Resultado da execução do algoritmo
if(U==0 && V==(2*Q))
return true;
else
return false;
                                                  };

//********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
