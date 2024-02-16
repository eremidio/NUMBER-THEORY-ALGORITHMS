//VAMOS CRIAR UM PROGRAMA PARA FATORAR NÚMEROS INTEIROS

/*
NÚMEROS SEMIPRIMOS SÃO NÚMEROS COMPOSTOS PELO PRODUTOS DE DOIS NÚMEROS PRIMOS. SEMIPRIMOS DE PRIMOS COMPOSTO POR FATORES APROXIMADAMENTE O MESMO TAMANHO (Nº DE BITS)
ESTÃO OS MAIS COMPLEXOS DE SEREM DECOMPOSTO EM FATORES PRIMOS.

O PRESENTE PROGRAMA IMPLEMENTA UM ALGORITMO SIMPLES DESCRITO NO SEGUINTE ARTIGO: https://dl.acm.org/doi/10.1145/2393216.2393246
*/


/*
NOTA: O algoritmo as vezes produz resultados incorretos ou fica preso num loop infinito. O mesmo parece funcionar bem quando os fatores primos estão próximos da raíz quadrada do número a ser fatorado.

*/

//*********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef SPECIAL_PURPOSE_FACTORIZATION_ALGORITHM1_H
#define SPECIAL_PURPOSE_FACTORIZATION_ALGORITHM1_H
#include<stdint.h>
#include<inttypes.h>
#include<stdbool.h>
#include<math.h>
#include<stdio.h>

//*********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void special_purpose_factorization_algorithm(int64_t);


//*********************************************************************************************************************************************************************
//FUNÇÕES
//Função que fatora um número inteiro semiprimo
void special_purpose_factorization_algorithm(int64_t N){
//Variáveis locais
int64_t n=floor(sqrt(N));//(step2.1)
int64_t p, q, n0, q0, r0, n1, r1, q1, d, k, nk, rk, qk;
int64_t iteration=1;

//Procedimentos
//Ajuste de variáveis (step2.2, step2.3)
q0=(int64_t)((1.0*N)/n);
r0=(N%n);
n0=n;

printf("Iteração    Divisor    Quociente   Resto\n-------------------------------------------------------------\n");
//Loop principal
while(true){
printf("%li     %li     %li     %li\n", iteration, n0, q0, r0);
iteration+=1;

//Cálculo da decomposição de N em fatores primos (step2.4)
if(r0==0){
p=n0;
q=q0;
break;
         };

if(r0==q0){
p=(n0+1);
q=q0;
break;
         };

//Ajuste no valor de variáveis (step2.5)
step2_5:
if(r0>q0){
n0+=floor((r0*1.0)/q0);
r0-=(floor((r0*1.0)/q0)*q0);
q0=q0;
         };

//Cálculo dos possíveis divisores de N (step 2.6)
if(r0<q0){
n1=(n0+1);
q1=(q0-1);
r1=(n0-q0+r0+1);
         };

//(step 2.7)
if(q1<=r1){
r0=r1-q1;
q0=q1;
n0+=1;
goto step2_5;
          };

//(step 2.8)
d=r1-r0;
k=ceil( (d/(-2.0)) +((sqrt((d*d)+(4.0*(d+q0-r1))))/2.0) );

//(step 2.9)
rk=r1+((k-1)*(d+k));
nk=n0+k;
qk=q0-k;

//Ajuste de variáveis para a próxima iteração (step 2.10)
n0=nk+1;
q0=qk;
r0=rk-qk;
           };

//Resultado da execução do algoritmo
printf("------------------------------------------------------------\n");
printf("Fatores de %li encontrados: %li, %li.\n", N, p, q);
                                                      };


//*********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
