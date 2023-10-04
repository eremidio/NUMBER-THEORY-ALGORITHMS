//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTAR O ALGORITMO DE DE TONELLI SHANKS PARA ENCONTRAR RAÍZES QUADRADAS A MENOS DE UMA CONGRUÊNCIA

/*
UM NÚMERO r É DEFINIDO COMO A RAÍZ QUADRADA DE UM NÚMERO n A MENOS DE UMA CONGRUÊNCIA ENVOLVENDO UM PRIMO p SE r²= n (mod p).
VÁRIOS ALGORITMOS EXISTEM PARA SOLUCIONAR ESTAS EQUAÇÕES AQUI VAMOS IMPLEMENTAR O ALGORITMO DE TONELLI SHANKS.

O ALGORITMO DE TONELLI-SHANKS É UM DOS ALGORITMOS MAIS EFICIENTES PARA COMPUTAR RAÍZES QUADRADAS A MENOS DE UMA RELAÇÃO DE
CONGRUÊNCIAE É BESEADO NO CRITÉRIO DE EULER PARA A EXISTÊNCIA DE QUADRADOS NÃO RESIDUAIS.

O ALGORITMO É IMPLMENTADO NAS SEGUINTES ETAPAS:
1. p É ESCRITO COMO p-1=Q.2^S COM Q ÍMPAR.
2. UM NÚMERO z QUE É UM QUADRADO NÃO RESIDUAL O INTERVALO [0, p-1] É ENCONTRADO,PODE-SE USAR O CRITÉRIO DE EULER
a^((p-1)/2) = (p-1) mod p = (-1) mod p.
3. INICIALIZA-SE AS VARIÁVEIS: M = S, c = z^Q, t=n^Q, R=n^((Q+1)/2).
4.EXECUTA-SE O LOOP PRINCIPAL USANDO O MENOR i TAL QUE t^(2^i) = 1 (mod p):

SE t=0, r=0. SE t=1, r=R.
DEFINE-SE UM b=c^2^(M-i-1).
AS VARIÁVEIS SÃO ATUALIZADAS DE ACORDO COM AS REGRAS:
M=i, c=b², t=tb², R=Rb.
5. UMA VEZ RESOLVIDO O VALOR DE r A OUTRA SOLUÇÃO É -r (mod p).
6. SE i=M ENTÃO n É UM QUADRADO NÃO RESIDUAL MÓDULO p.

PARA MAIORES INFORMAÇÕES: https://zerobone.net/blog/math/tonelli-shanks/

*/


//**************************************************************************************************************************
//CABEÇALHO
#if !defined MODULAR_SQUARE_ROOT_H
#define MODULAR_SQUARE_ROOT_H
#include<stdint.h>
#include<stdio.h>
#include<stdbool.h>
#include"mod_bin_exponentiation.h"


//**************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t modular_sqrt(int64_t, int64_t);
int64_t modular_sqrt1(int64_t, int64_t);
int64_t modular_sqrt2(int64_t, int64_t);

//**************************************************************************************************************************
//FUNÇÕES
//Função que calcula uma raíz quadrada modular de um número usando o algoritmo de Tonelli-Shanks para o caso geral
int64_t modular_sqrt1(int64_t n, int64_t p){
//Variáveis locais,
int64_t Q, S, z, i, M, c, t, R, r, b;

//Procedimentos
//Calculando os valores de Q, S
S=0;
int64_t p_even = p-1;
while((p_even%2)==0){
S++;
p_even/=2;
                    };
Q=p_even;

//TESTE USE UM // APÓS O MESMO
//printf("TESTE 1\nQ=%li, S=%li\n", Q, S);

//Encontrando um inteiro no intervaçlo 1, .., p-1 que é não quadrado perfeito modulo p
for(int64_t j=1; j<p; ++j){
z=j;
if(mod_bin_pow(z,(p-1)/2, p)==(p-1))
break;
                           };

//TESTE USE UM // APÓS O MESMO
//printf("TESTE 2\nz=%li\n", z);

//Inicializando variáveis usadas no cálculo
M=S%p;
c=mod_bin_pow(z, Q, p);
t=mod_bin_pow(n, Q, p);
R=mod_bin_pow(n, ((Q+1)/2), p);


//TESTE USE UM // APÓS O MESMO
//printf("TESTE 3\nM=%li, c=%li, t=%li, R=%li\n", M, c, t, R);


//Loop principal
while(true){
//Condição que determina se uma raíz quadrada módulo p foi encontrada
if(t==0) return 0;
if(t==1){r=R; break; };

//Encontrando um valor de 1 tal que t^(2^i)=1 (mod p) nop intervalo 1, ..., M
for(i=1; i<=M; i++){
//Condição que determina que o número em questão não possui raíz quadrada módulo p
if(i==M)
return 0;

if(mod_bin_pow(t, bin_pow(2, i), p)==1)
break;
                   };

//TESTE USE UM // APÓS O MESMO
//printf("TESTE 4\ni=%li\n", i);


//Atualizando variáveis
b=mod_bin_pow(c, bin_pow(2, (M-i-1)), p);
M=i;
c=(b*b)%p;
t=(t*b*b)%p;
R=(R*b)%p;

//TESTE USE UM // APÓS O MESMO
//printf("TESTE 5\nb=%li, M=%li, c=%li, t=%li, R=%li\n", b, M, c, t, R);

           };

//Resultado
return r;
                                 };


//Função que calcula uma raíz quadrada modular de um número usando o algoritmo de Tonelli-Shanks para o caso p=3 (mod4)
int64_t modular_sqrt2(int64_t n, int64_t p){
//Variáveis locais
int64_t r=pow_mod(n, ((p+1)/4), p);

//Procedimentos
if(((r*r)%p)==n)
return r;
else 
return 0;

                                              };

//Função que calcula uma raíz quadrada modular de um número usando o algoritmo de Tonelli-Shanks
int64_t modular_sqrt(int64_t n, int64_t p){
if((p%4)==3)
return modular_sqrt2(n, p);
if((p%4)==1)
return modular_sqrt1(n, p);
                                            };

//**************************************************************************************************************************
//FIM DO HEADER
#endif
