//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE PRIMALIDADE (n+1)

/*
O TESTE DE PRIMALIDADE (n+1) É UM EFICIENTE TESTE DE PRIMALIDADE PARA TESTAR A PRIMALIDADE UM INTEIRO n, QUE REQUER A FATORAÇÃO DE (n+1) E USA SEQUÊNCIAS DE LUCAS.
O ALGORITMO SE BASEIA NOS SEGUINTES LEMAS:

SEJAM x²+px+q UM POLINÔMIO COM ((p²-q)|n) =(-1) (SÍMBOLO DE JACOBI), ISTO É, (p²-q) NÃO É UM QUADRADO PERFEITO MÓDULO. O POLINÔMIO EM QUESTÃO POSSUI DUAS RAÍZES REAIS
UMA DAS QUAIS r=(p+[(p²-q)^(1/2)])/2. E SEJAM V(m) E U(m) AS SEQUÊNCIAS DE LUCAS DO PRIMEIRO E SEGUNDO TIPOS.

LEMA 1:r^m=(V(m)+U(m)[(p²-q)^(1/2)])/2.
LEMA 2: SEJAM a, b INTEIROS DE MESMA PARIDADE E 2r=a+b[(p²-q)^(1/2)] (mod n), SE n FOR PRIMO ENTÃO 2(r^n)=a-b[(p²-q)^(1/2)](mod n)
LEMA 3: SE n FOR PRIMO ENTÃO U(n+1)=0 (mod n).

COMBINANDO OS RESULTADOS ACIMA É POSSIVEL DEMONSTRAR O SEGUINTE TEOREMA:
SEJA d=(p²-q) TAL QUE ((p²-q)|n)=(-1) , UM NÚMERO n É PRIMO SE E SOMENTE SE U(n+1)=0 (mod n) E U((n+1)/r)≠0 (mod n) PARA CADA FATOR PRIMO DE (n+1).

SE TOMARMOS s(k)=V(k)[2^(2^k)], OBTEMOS O TESTE DE LUCAS-LEHMER PARA NÚMEROS DE MERSENNE n=(2^k)-1 QUE AFIRMA n É PRIMO SE E SOMENTE SE s(k-2)=0 (mod n), PARA A
SEQUÊNCIA s(0)=4, s(k+1)=[s(k)]²-2. NA LISTA DOS MAIORES PRIMOS JÁ COMPUTADOS OS PRIMOS DE MERSENNE SÃO OS MAIS ABUNDANTES.

PARA MAIORES INFORMAÇÕES: https://t5k.org/prove/prove3_2.html

*/

//********************************************************************************************************************************************************
//CABEÇALHO
#if !defined N_PLUS_ONE_PRIMALITY_TEST_H
#define N_PLUS_ONE_PRIMALITY_TEST_H
#include"jacobi_symbol.h"
#include"mod_bin_exponentiation.h"
#include<stdbool.h>
#include<stdio.h>
#include<math.h>

//********************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool lucas_lehmer_test(uint64_t);
void set_lucas_sequence_parameters(int64_t*, int64_t*, int64_t);
int64_t* partial_factorization(int64_t, int64_t*, int64_t*);
bool n_plus_one_primality_test(int64_t);

//********************************************************************************************************************************************************
//FUNÇÕES
//Função que realiza o teste de Lucas Lehmer para a primalidade dos chamados números de Mersenne da forma n=(2^p)-1
bool lucas_lehmer_test(uint64_t n){
//Parte 1: Checando se o número em questão é um número de Mersenne
//Variáveis locais
uint64_t p=2;
uint64_t mersenne;

//Procedimentos
//Loop principal
while(true){
mersenne=bin_pow(2, p)-1;

if(mersenne==n)
break;


if(mersenne<n){
p++;
continue;
              };

//Se o número em questão não é um número de Mersenne, o teste é inconclusivo
if(mersenne>n){
printf("%lu não é um número de Mersenne.\n", n);
return false;
              };
           };

//Parte2: O teste de Lucas - Lehmer.
//Variáveis locais
uint64_t i;
__int128_t lucas_lehmer=4;

//Procedimentos
//Loop principal
for(i=0; i<(p-2); ++i)
lucas_lehmer=(lucas_lehmer*lucas_lehmer)-2;

if((lucas_lehmer%mersenne)==0)
return true;
else
return false;
                                  };

//Função que calcula os parâmetros p, q a serem usados para computar as sequências de Lucas no teste de primalidade (n+1)
void set_lucas_sequence_parameters(int64_t* P, int64_t* Q, int64_t n){
//Variáveis locais
int64_t i=3, j=2;
int64_t d, tester;

//Procedimentos 
//Calculando um valor de d adequado
for(d=5; ; d++){
if((jacobi(d, n)*(-1))==1)
break;
               };

//Calculando o valor dos parâmetros P e Q usados no teste
while (true){
tester=((i*i)-(4*j));

if(tester==d)
break;
if(tester>d)
++j;
if(tester<d)
++i;
            };

(*P)=i;
(*Q)=j;
                                                                     };

//Função que calcula uma fatoração parcial de (n+1)
int64_t* partial_factorization(int64_t n, int64_t* factor_array, int64_t* array_size){
//Restrição
if(factor_array!=NULL)
return factor_array;

//Variáveis locais
int64_t N=(n+1);
int64_t counter=0;
int64_t root=sqrt(N);

//Procedimentos
//Busca por fatores 2,3
if((N%2)==0){
counter++;
factor_array=(int64_t*)realloc(factor_array, counter*sizeof(int64_t));
factor_array[counter-1]=2;
while((N%2)==0)
N/=2;
            };

if((N%3)==0){
counter++;
factor_array=(int64_t*)realloc(factor_array, counter*sizeof(int64_t));
factor_array[counter-1]=3;
while((N%3)==0)
N/=3;
            };

//Loop até N^(1/2)com otimização 6k+1
for(int64_t i=5; i<(root+1); i+=6){
if((N%i)==0){
counter++;
factor_array=(int64_t*)realloc(factor_array, counter*sizeof(int64_t));
factor_array[counter-1]=i;
while((N%i)==0)
N/=i;
            };

if((N%(i+2))==0){
counter++;
factor_array=(int64_t*)realloc(factor_array, counter*sizeof(int64_t));
factor_array[counter-1]=(i+2);
while((N%(i+2))==0)
N/=(i+2);
               };

                                  };


//Fatores maiores que N^(1/2)
if(N>1){
counter++;
factor_array=(int64_t*)realloc(factor_array, counter*sizeof(int64_t));
factor_array[counter-1]=N;
       };

//Ajustando o contador de fatores primos encontrados
(*array_size)=counter;

//Resultado
return factor_array;
                                                   };

//Função que implementa o teste de primalidade (n+1)
bool n_plus_one_primality_test(int64_t n){
//Variáveis locais
int64_t* factor_array=NULL;
int64_t* divisor_array=NULL;
int64_t factor_array_size=0, divisor_counter=0;
int64_t index=0, current_factor;
int64_t P, Q, U0, U1, U2;
bool result=true;

//Procedimentos 
//Computando uma fatoração parcial de (n+1) e  uma lista de divisores
factor_array=partial_factorization(n, factor_array, &factor_array_size);

//TESTE USE UM /**/  APÓS O MESMO
/*for(int64_t t=0; t<factor_array_size; t++)
printf("Fator: %li\n", factor_array[t]);*/


//Computando uma fatoração parcial de uma lista de divisores
for(int64_t i=0; i<factor_array_size; ++i){
divisor_counter++;
divisor_array=(int64_t*)realloc(divisor_array, divisor_counter*sizeof(int64_t));
divisor_array[divisor_counter-1]=((n+1)/factor_array[i]);
                                          };

//TESTE USE UM /**/  APÓS O MESMO
/*for(int64_t t=0; t<factor_array_size; t++)
printf("Fator: %li\n", divisor_array[t]);*/

//Computando os parâmetros P e Q usados no algoritmo
set_lucas_sequence_parameters(&P, &Q, n);


//Teste 1: checando se U((n+1)/r)≠0 para cada divisor r de (n+1)
//Inicializando variáveis
U0=0;
U1=1;

//Computando o (n+1)-ésimo termo da sequência de Lucas a menos de uma relação de congruência
index= (factor_array_size-1);

for(int64_t k=2; k<=(n+1); k++){
U2=(((P*U1)%n)-((Q*U0)%n))%n;

//Teste de primalidade
if(index>=0){

if((k-1)==divisor_array[index]){
if(U2==0){
result=false;
break;
         };
index--;
                           };

            };

//Atualizando variáveis para a próxima iteração
U0=U1;
U1=U2;
                               };


//Limpando o cachê de memória
free(factor_array);
free(divisor_array);

//Resultado da primeira etapa do teste
if(result==false)
return false;

//Teste 2: checando se U(n+1)=0 (mod n)
if((U1%n)==0)
return true;
else
return false;
                                         };



//********************************************************************************************************************************************************
//FIM DO HEADER
#endif
