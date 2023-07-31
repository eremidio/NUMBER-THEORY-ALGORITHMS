//VAMOS IMPLEMENTAR A FUNÇÃO DE MÖBIUS μ

/*
Α FUNÇÃO DE MÖBIUS É UMA FUNÇÃO MULTIPLICATIVA QUE É DEFINIDA PARA TODO INTEIRO n:

μ(n)={ 0, SE n CONTÉM ALGUM FATOR PRIMO REPETIDO
     { +1, SE n CONTÉM UM NÚMERO PAR DE FATORES PRIMOS
     { -1, SE n CONTÉM UM NÚMERO ÍMPAR DE FATORES PRIMOS

A FUNÇÃO DE MÖBIUS É MULTIPLICATIVA SE m E n SÃO RELATIVAMENTE PRIMOS ENTRE SI: μ(nm) = μ(n).μ(m)

A APLICAÇÃO MAIS IMPORTANTE DA FUNÇÃO DE MÖBIUS É A CHAMADA FÓRMULA DE INVERSÃO:
SEJAM f E g DUAS FUNÇÕES ARITMÉTICA TAIS QUE 
g(n)= Σf(d), ONDE n É UM INTEIRO QUALQUER E d REPRESENTA O CONJUNTO DOS DIVISORES DE n
ENTÃO VALE A RELAÇÃO:
f(n)= Σμ(d)g(n/d)

A FÓRMULA DE INVERSÃO É UM CASO PARTICULAR DE UMA CONVOLUÇÃO DE DIRICHLET.

ALGUMAS GENERALIZAÇÕES DA FUNÇÃO DE MÖBIUS SÃO TAMBṔEM DENOTADAS POR μ(n).

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Möbius_inversion_formula
https://en.wikipedia.org/wiki/Möbius_function#cite_note-FOOTNOTEBostConnes1995411–457-6
https://en.wikipedia.org/wiki/Dirichlet_convolution

*/

//*************************************************************************************************************************
//CABEÇALHO
#ifndef MOBIUS_FUNCTION_H
#define MOBIUS_FUNCTION_H
#include<stdint.h>
#include<stdbool.h>
#include<math.h>
#include<assert.h>

//CONSTANTES GLOBAIS
const unsigned int MOBIUS_BOUND = 50000;

//*************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool is_prime(uint64_t);
bool is_square(uint64_t);
int mobius_small_integer(uint64_t);
int mobius_large_integer(uint64_t);
int mobius_function(uint64_t);
int64_t mertens_function(uint64_t);
uint64_t euclides_check(uint64_t, uint64_t);

//*************************************************************************************************************************
//FUNÇÕES
//Função que calcula se um número é primo ou não (usaremos uma otimização 6k+1)
bool is_prime(uint64_t n){
//Casos triviais
//0,1
if(n<=1)
return false;

//Casos básicos
if(n==2 || n==3)
return true;
if((n%2)==0 || (n%3)==0)
return false;


//Loop principal
for(uint64_t i=5; i<sqrt(n); i+=6){
if((n%i)==0 || (n%(i+2))==0)
return false;
                                  };

//Caso fatores primos não sejam encontrados
return true;

                         };

//Função que calcula de um número é um quadrado perfeito
bool is_square(uint64_t n){
//Procedimentos
for(uint64_t i=10000; i<n; ++i){
if(i*i==n)
return true;
if(i*i>n)
return false;
                               };
                          };

//Função de Möbius para pequenos valores
int mobius_small_integer(uint64_t n){
//Caso trivial 
if(n==1)
return 1;

//Variáveis locais
uint64_t prime_factor_number=0;
int result = 1;
uint64_t n1=n;

//Procedimentos
//Testando a divisibilidade por 2
if((n%2)==0){
n1/=2;
if(n1==1)
return (-1)*result;
prime_factor_number++;
if((n1%2)==0)
return 0;
            };

//Testando a divisibilidade por números primos ímpares
for(uint64_t i=3; n1>1; i+=2){
if((n1%i)==0){
n1/=i;
prime_factor_number++;
if(n1==1)
break;
if((n1%i)==0)
return 0;
            };
                             };
//Resultado
if((prime_factor_number%2)==0)
return result;
if((prime_factor_number%2)==1)
return (-1)*result;

                                    };

//Função que implementa o algoritmo de Euclides para se calcular o mdc de dois inteiros
uint64_t euclides_check(uint64_t a, uint64_t b){
if(b==0)
return a;
else
return euclides_check(b, a%b);
                                               };

//Função de Möbius para grandes valores
int mobius_large_integer(uint64_t n){
//Variáveis locais
int result = 1;
//Caso 1: quadrados perfeitos
if(is_square(n)==true)
return 0;
//Caso2 : números primos
if(is_prime(n)==true)
return (-1)*result;

//Caso 3: explorando a propriedade multiplicativa da função de Möbius 
//Variáveis
uint64_t factor1, factor2;
uint64_t sqrt_n=sqrt(n);

//Procedimentos
//Loop principal encontrando fatores relativamente primos entre si
for(uint64_t i=2; i<=sqrt_n; ++i){
factor1=i;
factor2=n/i;
if(euclides_check(factor1, factor2)==1)
break;
                                 };
//Restrição de valores 
assert(factor1<=MOBIUS_BOUND && factor2<=MOBIUS_BOUND);

//Resultado
return(mobius_small_integer(factor1)*mobius_small_integer(factor2));

                                    };

//Função de Möbius
int mobius_function(uint64_t n){
if(n<=MOBIUS_BOUND)
return mobius_small_integer(n);
else
return mobius_large_integer(n);

                               };


//*************************************************************************************************************************
//APLICAÇÃO NO CÁLCULO DA FUNÇÃO DE MERTENS
int64_t mertens_function(uint64_t n){
//Variáveis locais
int64_t result=0;

//Procedimento
for(uint64_t i=1; i<=n; ++i)
result+= mobius_function(i);

//Resultado
return result;
                                    };

//*************************************************************************************************************************
//FIM DO HEADER
#endif
