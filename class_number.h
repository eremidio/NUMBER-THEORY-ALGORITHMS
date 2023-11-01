//VAMOS CRIAR UM PROGRAMA QUE COMPUTA O NÚMERO DE CLASSE PARA CORPOS ALGÉBRICOS QUADRÁTICOS IMAGINÁRIOS

/*
CORPOS ALGÉBRICOS NÚMERICOS SÃO EXTENSÕES DOS CORPOS DOS RACIONAIS FECHADOS EM RELAÇÃO AS OPERAÇÕES ARITMÉTICAS.
CONCEITOS ORIGINALMENTE DEFINIDOS NOS CORPOS DOS RACIONAIS E INTEIROS COMO NÚMEROS PRIMOS E FATORACÃO EM NÚMEROS PRIMOS PODEM SER FACILMENTE EXTENDIDOS PARA CORPOS
ALGÉBRICOS MAIS GERAIS.

O NÚMERO DE CLASSE DENOTADO POR h É UM IMPORTANTE INVARIANTE QUE ESTÁ ASSOCIADO A UM CORPO ALGÉBRICO E DETERMINA O QUÃO LONGE UM CORPO ALGÉBRICO SE DIFERE DE UM DOMÍNIO 
DE FATORAÇÃO ÚNICO, ISTO É, DE QUANTAS MANEIRAS DISTINTAS UM ELEMENTO NESTE CORPO ALGÉBRICO PODE SER DECOMPOSTO EM FATORES PRIMOS.
POR EXEMPLO: NO CORPO ALGÉBRICO Q(√-5) COMPOSTO POR NÚMEROS DA FORMA a+(√-5)b, COM a E b RACIONAIS O NÚMERO 6 (a=6, b=0) ADMITE DUAS FORMAS DISTINTAS DE DECOMPOSIÇÃO EM FATORES PRIMOS 6=(2+(√-5)0)(3+(√-5)0) E 6=(1+(√-5)1)(1-(√-2)1).

PARA CORPOS QUADRÁTICOS IMAGINÁRIOS Q(√-n) UMA POSSISIBILIDADE É CONTABILIZAR O NÚMERO DE FORMAS QUADRÁTICAS  REDUTÍVEIS COM DISCRIMINANTE -n, PARA ax²+bxy+cy²,
Δ=b²-4ac. POR EXEMPLO: Q(√-23) TEMOS AS TRIPLAS (a, b, c)=(1, 1, 6); (2, -1, 3); (2, 1, 3) DE MODO QUE h(-23)=3. ESTE MÉTODO, PÓRÉM, É EXTREMAMENTE INEFICIENTE.


EM GERAL É EXTREMAMENTE COMPLEXO COMPUTAR NÚMEROS DE CLASSE PARA CORPOS ALGEBRICOS GERAIS. PORÉM EM ALGUNS CASOS COMO É O CASO DE CORPOS QUADRÁTICOS IMAGINÁRIOS DA FORMA
Q(√-n), COM n INTEIRO E NÃO CONTENDO FATORES QUADRÁTICOS ESTE CÁLCULO PODE SER EXTREMAMENTE SIMPLIFICADO. EM PARTICULAR, EXPRESSO EM TERMOS DOS SÍMBOLOS DE KRONECKER,
DOS DISCRIMINANTES Δ (QUE MENSURAM O QUANTO INTEIROS ALGÉBRICOS SÃO DISTINGUÍVEIS, ISTO É, UNICAMENTE DECOMPOSTOS EM FATORES PRIMOS NESTE DOMÍNIO, PARA n CONTENDO
FATORES QUADRÁTICOS O DISCRIMINANTE NÃO É BEM DEFINIDO, UMA VEZ QUE O POLINÔMIO CARACTERIZANDO O DOMÍNIO PODE TER RAÍZES REPETIDAS, O DISCRIMINANTE DETERMINA SE OS 
INTEIROS ALGÉBRICOS FORMAM UMA EXTENSÃO SEPARÁVEL DO CONJUNTO DOS INTEIROS).

PARA MAIORES INFORMAÇÕES:
https://en.wikipedia.org/wiki/Arithmetic_function
https://en.wikipedia.org/wiki/Ideal_class_group
https://en.wikipedia.org/wiki/Class_number_formula
https://numberworld.blogspot.com/2018/05/methods-to-compute-class-number.html
https://people.reed.edu/~jerry/361/lectures/iqclassno.pdf
https://mathworld.wolfram.com/ClassNumber.html

*/


//*********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef CLASS_NUMBER_QUADRATIC_FIELD_H
#define CLASS_NUMBER_QUADRATIC_FIELD_H
#include"kronecker_symbol.h"//Inclui os headers <stdint.h>, <stdbool.h>, <math.h> e <stdint.h>
#include<assert.h>

//*********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool is_square_factor_free(int64_t);
bool is_integer_prime(int64_t);
bool is_fundamental_discriminant(int64_t);
int64_t substitution_number(int64_t);
int64_t class_number_negative_discriminant(int64_t);

//*********************************************************************************************************************************************************************
//FUNÇÕES 
//Função que determina se um inteiro contém fatores quadráticos
bool is_square_factor_free(int64_t n){
//Variáveis locais
int64_t i, limit=sqrt(n);

//Procedimentos 
//Casos triviais
if(n<4)
return true;

//Fatores 2 e 3
if((n%2)==0){
n/=2;
if((n%2)==0)
return false;
            };

if((n%3)==0){
n/=3;
if((n%3)==0)
return false;
            };

//Loop principal com otimização 6k+1
for(i=5; i<(limit+2); ++i){
if((n%i)==0){
n/=i;
if((n%i)==0)
return false;
            };

if((n%(i+2))==0){
n/=(i+2);
if((n%(i+2))==0)
return false;
                };
                          };

//Caso passe nos testes acima
return true;
                                     };

//Função que calcula de um número é primo ou não
bool is_integer_prime(int64_t n){
//Variáveis locais
int64_t limit=sqrt(n);
int64_t i;

//Procedimentos
//Casos triviais
if(n<2)
return false;
if(n==2 || n==3)
return true;
if((n%2)==0 || (n%3)==0)
return false;

//Loop principal
for(i=5; i<(limit+2); ++i){
if((n%i)==0 || (n%(i+2))==0)
return false;

                          };

return true;
                                };


//Função que determina se um inteiro corresponde a um discrimante fundamental
bool is_fundamental_discriminant(int64_t n){
//Caso base
if(n==1)
return false;

//Números negativos
if(n<0){
//Variáveis locais
int64_t minus_n=(-1)*n;

//Testes
if((minus_n%16)==4 || (minus_n%16)==8)
return true;

while(n<0)
n+=4;

if((n%4)==1)
return true;
       };

//Números positivos
if(is_square_factor_free(n)==true && (n%4)==1 && n!=1)
return true;

if((n%4)==0){
//Variável local
int64_t m=n/4;

//Teste
if(is_square_factor_free(m)==true && (n%4)>1)
return true;
            };

//Caso o número não passe nos testes acima 
return false;
                                           };

//Função que calcula o número de substituições que deixam uma forma quadrática invariante
int64_t substitution_number(int64_t n){
if((n*(-1))==3)
return 6;
else if((n*(-1))==4)
return 4;
else
return 2;

                                      };

//Função que calcula o número de classe para um discriminante fundamental negativo (d<0) usando a fórmula de Dirichlet
int64_t class_number_negative_discriminant(int64_t d){
//Variáveis locais
int64_t w=substitution_number(d);
int64_t minus_d=(-1)*d;
int64_t sum=0;
int64_t i;

//Procedimentos
//Loop principal
for(i=1; i<minus_d; ++i)
sum+=(kronecker(d, i)*i);

//Resultado
return round((w*sum)/(2*d));
                                                     };

//*********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
