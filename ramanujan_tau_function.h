//VAMOS CRIAR UM PROGRAMA EM C QUE IMPLMENTA A FUNÇÃO TAU DE RAMANUJAN
/*
A FUNÇÃO TAU DE RAMANUJAN τ(n) É UMA FUNÇÃO MULTIPLICATIVA τ(mn)=τ(m)τ(n) SE m E n FOREM RELATIVAMENTE PRIMOS ENTRE SI.
PARA NÚMEOS PRIMOS p E r>0 AS SEGUITES RELAÇÕES SÃO VÁLIDAS: |τ(p)|≲ 2(p^(11/2)), τ(p^(r+1)) = τ(p)τ(p^r)-(p^11)τ(p^(r-1)).

ESTA FUNÇÃO CORRESPONDE AOS COEFICIENTES DE EXPANSÃO DA SÉRIE DE FOURIER DA FUNÇÃO DISCRIMANTE MODULAR Δ (UMA FÓMULA MODULAR DE PESO 12 CONGRUENTE MÓDULO 1).
ELA APARECE ASSOCIADA A UM TERMO DE ERRO ASSOCIADO AO CÁLCULO DO NÚMERO DE MANEIRAS DIFERENTES DE EXPRESSAR UM INTEIRO COMO A SOMA DE 24 QUADRADOS PERFEITOS E É
RECORRENTE EM ALGUMAS IDENTIDADES ENVOLVENDO FORMAS MUDULARES.

VÁRIAS RELAÇÕES DE CONGRUÊNCIA SÃO SATISFEITAS POR ESTA FUNÇÃO QUE É DIRETAMENTE RELACIONADA COM A FUNÇÃO σ(k,n) QUE EXPRESSA A SOMA DA k-ÉSIMA POTÊNCIA DOS DIVISORES DE
UM INTEIRO n. UMA FÓRMULA EXPLÍCITA PARA O CÁLCULO DE τ(n) EXISTE EM TERMOS DE σ(n) = σ(1,n).

A FUNÇÃO DE L DE RAMANUJAN É DEFINIDA COMO L=Στ(n)/(n^s), PARA s UM NÚMERO COMPLEXO.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Ramanujan_tau_function

*/
 
//*********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef RAMANUJAN_TAU_FUNCTION_H
#define RAMANUJAN_TAU_FUNCTION_H
#include<stdint.h>
#include<stdbool.h>
#include<math.h>

//CONSTANTES GLOBAIS
#define MAX_TAU_N 10000

//*********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t euclides_algorithm(int64_t, int64_t);
int64_t ramanujan_tau_small_integers(int64_t);
int64_t ramanujan_tau_large_integers(int64_t);
int64_t ramanujan_tau_function(int64_t);
bool perfect_square_checker(int64_t);
bool is_prime(int64_t);

//*********************************************************************************************************************************************************************
//FUNÇÕES
//Função que calcula se um número é primo ou não
bool is_prime(int64_t n){
//Casos triviais
//0,1
if(n<=1)
return false;

if(n==2 || n==3)
return true;

if(n%2==0 || n%3==0)
return false;

//Variáveis locais
int64_t sqrt_n =sqrt(n);

//Procedimento usando uma otimização 6k+1
for(uint64_t i=5; i<sqrt_n+1; i+=6){
if((n%i)==0 || (n%(i+2))==0)
return false;
                                   };
return true;
                         };

//Função que detecta se um número é quadrado perfeito
bool perfect_square_checker(int64_t n){
//Variáveis locais
int64_t odd=1;

//Procedimento
while(n>0){
n-=odd;
odd+=2;
if(n<0)
return false;
          };

return true;
                                      };

//Função que implementa o algoritmo de Euclides
int64_t euclides_algorithm(int64_t a, int64_t b){
if(b==0)
return a;
else
return euclides_algorithm(b, a%b);
                                                 };

//Função que calcula a soma dos divisores de um número inteiro
int64_t sum_of_divisors(int64_t n){
//Casos triviais
if(n==0)
return 0;
if(n==1)
return 1;
if(is_prime(n)==true)
return (n+1);

//Variáveis locais
int64_t sum=0;
int64_t i;//Variável de iteração
int64_t limit = sqrt(n);

//Procedimento
for(i=1; i<=limit; ++i){
//Caso particular de quadrados perfeitos
if((i*i)==n){
sum+=i;
continue;
            };

if((n%i)==0)
sum+=(i+(n/i));
                      };
return sum;
                                  };


//Função que calcula o valor da função de Ramanujan para pequenos inteiros e primos
int64_t ramanujan_tau_small_integers(int64_t n){
//Variáveis locais
int64_t i=0, sum=0;

//Procedimentos
//Cálculo do somátorio
for(i=1; i<n; ++i)
sum+=((i*i)*((35*(i*i))-(52*i*n)+(18*(n*n)))*sum_of_divisors(i)*sum_of_divisors(n-i));

//Resultado                  
return (((n*n*n*n)*sum_of_divisors(n))-(24*sum));
                                               };

//Função que calcula o valor da função de Ramanujan para grandes inteiros
int64_t ramanujan_tau_large_integers(int64_t n){
//Variáveis locais
int64_t factor1=sqrt(n), factor2=0;
int64_t i=0;

//Procedimentos
//Checando se o número é primo
if(is_prime(n)==true)
return ramanujan_tau_small_integers(n);

//Caso o número em questão não seja primo fatores menores relativamente primos são cálculados
for(;factor1>0; factor1--){
if((n%factor1)==0){
factor2=n/factor1;
if(euclides_algorithm(factor1, factor2)==1)
break;
//Quadrados perfeitos
if(factor1==factor2)
break;
                  };

                          };

//Resultado
return ramanujan_tau_small_integers(factor1)*ramanujan_tau_small_integers(factor2);

                                               };
//Função tau de Ramanujan τ(n)
int64_t ramanujan_tau_function(int64_t n){
if(n> MAX_TAU_N)
return ramanujan_tau_large_integers(n);
else
return ramanujan_tau_small_integers(n);
                                         };


//*********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
