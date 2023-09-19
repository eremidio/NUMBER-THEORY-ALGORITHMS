//VAMOS CRIAR UMA ROTINA PARA O CÁLCULO DE FUNÇÕES ARITMÉTICAS QUE ESTÃO RELACIONADAS COM A FUNÇÃO LOGARÍTMICA NATURAL

/*
PARA MAIORES REFERÊNCIAS:
https://en.wikipedia.org/wiki/Arithmetic_function
https://en.wikipedia.org/wiki/Von_Mangoldt_function
https://en.wikipedia.org/wiki/Chebyshev_function

*/

//**********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef LOGARITHMIC_FUNCTIONS_H
#define LOGARITHMIC_FUNCTIONS_H
#include<math.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>

//**********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool is_integer_prime(uint64_t);
bool prime_power_check(uint64_t);
double von_mangoldt_function(uint64_t);
double first_chebyshev_function(uint64_t);
double second_chebyshev_function(uint64_t);
double pi_weight_function(uint64_t);

//**********************************************************************************************************************************************************************
//FUNÇÕES
//Função que testa a primalidade de um númeiro inteiro
bool is_integer_prime(uint64_t n){
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

//Função que checa se um número é da forma
bool prime_power_check(uint64_t n){
//Procedimento
//Caso trivial
if(is_integer_prime(n)==true)
return true;

//Loop principal
for(uint64_t i=2; i<n; ++i){
if(is_integer_prime(i)==true){
uint64_t tester=i;

while(true){
if(tester==n)               
return true;

tester*=i;

if(tester>n)
break;
           };
                            };
                          };
return false;
                                  };

//Função Λ de von Mangoldt
double von_mangoldt_function(uint64_t n){
//Variáveis locais
double result=log(n);

//Resultado
if(prime_power_check(n)==false)
return 0.0;
else
return result;
                                        };

//Função Θ de Chebyshev do primeiro tipo
double first_chebyshev_function(uint64_t n){
//Variáveis locais
uint64_t i=0;
double result=0.0;

//Procedimentos
for(i=2; i<=n; ++i){
if(is_integer_prime(i)==true)
result+=log(i);
                   };
return result;
                                           };

//Função ψ de Chebyshev do segundo tipo
double second_chebyshev_function(uint64_t n){
//Variáveis locais
uint64_t i=0;
double result=0.0;

//Procedimentos
for(i=2; i<=n; ++i){
result+=von_mangoldt_function(i);
                   };
return result;
                                           };
//Função Π 
double pi_weight_function(uint64_t n){
//Variáveis locais
uint64_t i, j, tester;
double sum=0.0;

//Procedimentos
//Fatores 2
tester=1;
for(j=1; j<n; ++j){
tester*=2;
if(tester<=n)
sum+=(1.0)/j;
else
break;

                  };

//Loop principal
for(i=3; i<=sqrt(n); i++){
tester=i;
if(is_integer_prime(tester)){

for(j=1; j<n; ++j){
tester*=i;
if(tester<=n)
sum+=(1.0)/j;
else
break;
                  };
                            };

                         };

//Resultado
return sum;
                                     };

//**********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
