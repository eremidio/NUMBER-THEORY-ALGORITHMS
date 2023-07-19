//MÓDULO QUE IMPLEMENTA AS FUNÇÕES BÁSICAS DE ANÁLISE COMBINATÓRIA
//Usar o tipo uin64_t ao usar estas funções para evitar erros de precisão

//***************************************************************************************************************************
//CABEÇALHO
#include<inttypes.h>
#include<stdint.h>
#include<assert.h>


//***************************************************************************************************************************
//PROTÓTIPOS DE FUNÇÕES
uint64_t factorial(uint64_t);
uint64_t permutation(uint64_t);
uint64_t repeated_permutation(uint64_t, uint64_t[], uint64_t);
uint64_t arrangement(uint64_t, uint64_t);
uint64_t combination(uint64_t, uint64_t);

//***************************************************************************************************************************
//FUNÇÕES

//**********************
//Fatorial
uint64_t factorial(uint64_t n){
if(n==1 || n==0)
return 1;
else
return n*factorial(n-1);
                              };


//**********************
//Permutação simples
uint64_t permutation(uint64_t n){
return factorial(n);
                                };

//**********************
//Permutação simples com elementos repetidos
uint64_t repeated_permutation(uint64_t n, uint64_t repetition_number_array[], uint64_t size){
//Variáveis locais
uint64_t result, i;
//Procedimentos
result=factorial(n);

for(i=0;i<size; ++i)
result/=factorial(repetition_number_array[i]);

return result;
                                                                                            };
                                                                       

//**********************
//Arranjo simples
uint64_t arrangement(uint64_t n, uint64_t k){
//Restrição
assert(n>=k);
//Procedimntos
return factorial(n)/factorial(n-k);
                                            };

//**********************
//Combinação simples
uint64_t combination(uint64_t n, uint64_t k){
//Restrição
assert(n>=k);
//Procedimntos
return factorial(n)/(factorial(k)*factorial(n-k));
                                            };
















