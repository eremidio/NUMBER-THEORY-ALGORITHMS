//ESTE ARQUIVO CONTERÁ AS ROTINAS USADAS NO PROCESSAMENTO DE DADOS E CÁLCULO DE FATORES PRIMOS 
//**********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef QUADRATIC_SIEVE_DATA_PROCESSING_H
#define QUADRATIC_SIEVE_DATA_PROCESSING_H
#include"quadratic_sieve_class.h"
#include<time.h>

//********************************************************************************************************************************************
//FUNÇÕES
//Função que calcula uma relação de congruência com base nos números peneirados
void quadratic_sieve::congruence_finder_algorithm(){
//Ajuste do vetor usado no cálculo
selection_tester=(dimension+1);
check_vector.reshape(selection_tester, 1);
congruence_vector.reshape(selection_tester, 1);

//Variáveis locais
int64_t k, i, j, odd_count;
__int128_t max_depth=(bin_pow(2, selection_tester)-1);

//Procedimentos
//Loop principal
for(i=1; i<max_depth; ++i){
generate_check_vector(i);
congruence_vector=reduced_matrix*check_vector;

odd_count=0;
for(j=0; j<selection_tester; ++j){
if(((congruence_vector.matrix[j][0])%2)==1){
odd_count++;
break;
                                           };

//Caso uma dependência linear seja encontrada essa parte do algoritmo se encerra
if(odd_count==0)
return;
                                 };

                          };

                                                   };

//Função que calcula um vetor que gera relações de congruência
void quadratic_sieve::generate_check_vector(int64_t k){
//Caso geral: alto número de relações constitutivas
if(selection_tester>126){
//Variáveis locais
int64_t j, random_int;

//Procedimentos
for(j=0; j<selection_tester; ++j){
random_int=rand()%101;

if(random_int&1)
check_vector.matrix[j][0]=1;
else
check_vector.matrix[j][0]=0;
                                 };
                        };

//Caso particular: baixo número de relações constitutivas
//Variáveis locais
int64_t i;
//Procedimentos
for(i=0; i<selection_tester; ++i){
if(k&1)
check_vector.matrix[i][0]=1;
else
check_vector.matrix[i][0]=0;

//Atualizando o valor da chave usada
k>>=1;
                                 };

                                                      };

//Função que calcula fatores primos do número em questão
void quadratic_sieve::factors_calculation(){
//Variáveis locais
int64_t i;

//Procedimentos
//Ajuste de variáveis
a_squared=1;
b_squared=1;

//Calculando o ovalor de a² e b² satisfazendo b² = a² (mod n)
for(i=0; i<selection_tester; ++i){

if(check_vector.matrix[i][0]==0)
continue;
if(check_vector.matrix[i][0]==1){
a_squared=a_squared*a_squared_vector[i];
b_squared=b_squared*b_vector[i];
                                };

                                 };

//Calculando os valores de a e b
selection_square=square_root_checker(a, a_squared);
selection_square=square_root_checker(b, b_squared);

//Calculando os fatores primos
if(a>b)
factor1=euclides_algorithm((a-b), number);
if(a<b)
factor1=euclides_algorithm((b-a), number);

if(factor1>1 && factor1!=number){
factor2=number/factor1;
return;
                                };


factor1=euclides_algorithm((a+b), number);
if(factor1>1 && factor1!=number){
factor2=number/factor1;
                                };


                                           };


//********************************************************************************************************************************************
//FIM DO HEADER
#endif 
