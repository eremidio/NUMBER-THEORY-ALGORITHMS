//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE FRÖBENIUS PARA TESTAR A PRIMALIDADE DE UM NÚMERO INTEIRO

/*
O TESTE DE PRIMALIDADE DE FRÖBENIUS É UM TESTE PROBABILÍSTICO QUE USA POLINÔMIOS DO SEGUNDO GRAU E OS CHAMADOS ENDOMORFISMOS DE FRÖBENIUS PARA TESTAR A PRIMALIDADE DE
UM INTEIRO.

NÚMEROS COMPOSTOS QUE PASSAM ESSE TESTES SÃO DENOMINADOS PSEUDOPRIMOS DE FRÖBENIUS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Quadratic_Frobenius_test#Concept

ARTIGO ORIGINAL DISPONÍVEL EM: https://www.sciencedirect.com/science/article/pii/S0022314X98922478?via%3Dihub

*/ 


//********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef QUADRATIC_FROBENIUS_PRIME_TEST_H
#define QUADRATIC_FROBENIUS_PRIME_TEST_H
#include"jacobi_symbol.h"
#include<stdint.h>
#include<math.h>
#include<stdbool.h>

//********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool is_integer_prime(int64_t);
bool trial_division_test(int64_t);
bool perfect_square_check(int64_t);
int jacobi_symbol_extension(int64_t, int64_t);
void find_quadratic_coefficients(int64_t*, int64_t*, int64_t);
bool quadratic_polynomial_test1(int64_t, int64_t, int64_t);
bool quadratic_polynomial_test2(int64_t, int64_t, int64_t);
bool quadratic_polynomial_test3(int64_t, int64_t, int64_t);
bool quadratic_frobenius_primality_test(int64_t);

//********************************************************************************************************************************************************************
//FUNÇÕES
//Função que detemina se um número é primo ou não
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

//Loop principal com otmização 6k+1
for(i=5; i<(limit+10); i+=6){
if((n%i)==0 || (n%(i+2))==0)
return false;
                            };

return true;

                                };

//Função que testa por divisão 
bool trial_division_test(int64_t n){
//Variáveis locais
int64_t root=sqrt(n);
int64_t upper_bound, i;
int64_t B=50000;

//Procedimentos
//Determinando o limite do teste de divisão
if(B<=root)
upper_bound=B;
else
upper_bound=root;

//Teste de divisão por pequenos primos
for(i=2; i<=upper_bound; ++i){
if(is_integer_prime(i)==true && (n%i)==0)
return false;
                             };

return true;
                                   };

//Função que checa se um número é quadrado  perfeito
bool perfect_square_check(int64_t n){
//Variáveis locais
int64_t odd=1;

//Procedimentos 
//Loop principal
while(n>0){
n-=odd;
odd+=2;

if(n<0)
return false;
          };

return true;
                                    };

//Função que extende o simbolo de jacobi para números negativos (a<0)
int jacobi_symbol_extension(int64_t a, int64_t n){
//Restrição
assert(a<0);

//Variáveis locais
int64_t positive_a=(-1)*a;
int64_t power2=0;
int result;

//Procedimentos
//Determinando a paridade do numerador
while((positive_a%2)==0){
positive_a/=2;
power2++;
                        };

//Definindo o símbolo de jacobi para |a|>0
result=jacobi(positive_a, n);

//DEterminando o sinal do resultado
//Caso 1: |a| é par
if(power2>0 && (power2%2)==1)
result=(-1)*jacobi(positive_a, n);
if(power2>0 && (power2%2)==0)
return result;

//Caso 2: |a| é ímpar
if(power2==0)
result=(-1)*jacobi(positive_a, n);

//Resultado
return result;
                                                 };

//Função que calcula os coeficientes do polinômion x²-bx-c usado no teste de Fröbenius (b<0, c<0)
void find_quadratic_coefficients(int64_t* b, int64_t* c, int64_t n){
//Variáveis locais
int64_t i, j, tester;

//Procedimentos 
//Cálculo do coeficiente c
for(i=(-2); ; --i){
if(jacobi_symbol_extension(i, n)==1){
*c=i;
break;
                                    };
                  };

//Cálculo do coeficiente b
for(j=2; ;++j){
tester=(j*j)+((*c)*4);

if(tester<0 && jacobi_symbol_extension(tester, n)==(-1)){
*b=(-1)*j;
break;
                                                        };
if(tester>0 && jacobi(tester, n)==(-1)){
*b=(-1)*j;
break;
                                       };
              };
                                                                   };

/*
NOTA: nos testes abaixo usaremos x²+(-b)x+(-c), b e c possuem sinal negativo.
*/

//Teste de congruência x^((n+1)/2) (mod n, x²-bx-c)
bool quadratic_polynomial_test1(int64_t b, int64_t c, int64_t n){
//Variáveis locais
int64_t divisor_polynomial[3]={1, b, c};
int64_t dividend_polynomial[3]={1, 0, 0};
int64_t degree=((n+1)/2);
int64_t temp;

//Procedimento
//Primeira iteração
degree--;
temp=1;
dividend_polynomial[0]=0;
dividend_polynomial[1]=dividend_polynomial[1]-(temp*divisor_polynomial[1]);
dividend_polynomial[2]=dividend_polynomial[2]-(temp*divisor_polynomial[2]);

//Demais iterações
while(degree>1){
temp=dividend_polynomial[1];
dividend_polynomial[1]=(dividend_polynomial[2]-(temp*divisor_polynomial[1]))%n;
dividend_polynomial[2]=(temp*divisor_polynomial[2])%n;
degree--;
               };

//Resultado (o resultado deve ser um inteiro)
if(dividend_polynomial[1]==0)
return true;
else 
return false;


                                                                };


//Teste de congruência x^(n+1) (mod n, x²-bx-c)
bool quadratic_polynomial_test2(int64_t b, int64_t c, int64_t n){
//Variáveis locais
int64_t divisor_polynomial[3]={1, b, c};
int64_t dividend_polynomial[3]={1, 0, 0};
int64_t degree=(n+1);
int64_t temp;

//Procedimento
//Primeira iteração
degree--;
temp=1;
dividend_polynomial[0]=0;
dividend_polynomial[1]=dividend_polynomial[1]-(temp*divisor_polynomial[1]);
dividend_polynomial[2]=dividend_polynomial[2]-(temp*divisor_polynomial[2]);

//Demais iterações
while(degree>1){
temp=dividend_polynomial[1];
dividend_polynomial[1]=(dividend_polynomial[2]-(temp*divisor_polynomial[1]))%n;
dividend_polynomial[2]=(temp*divisor_polynomial[2])%n;
degree--;
               };

//Resultado (o resultado deve ser um c)
if(dividend_polynomial[1]==0 && dividend_polynomial[2]==(n+c))
return true;
else 
return false;
                                                                };

//Função que realiza um teste de congruência estilo teste de Miller-Rabin
bool quadratic_polynomial_test3(int64_t b, int64_t c, int64_t n){
//Variáveis locais
__int128_t divisor_polynomial[3]={1, b, c};
__int128_t dividend_polynomial[3]={1, 0, 0};
__int128_t degree, temp;
__int128_t j=0;
__int128_t r=0, s,  n_squared;


//Procedimentos
//Calculando os coeficientes r e s
n_squared = (n*n)-1;

while((n_squared%2)==0){
r++;
n_squared/=2;
                       };

s=n_squared;

//Teste 1: congruência x^s (mod n, x²-bx-c)
//Ajuste de variáveis 
degree=s;

//Primeira iteração
degree--;
temp=1;
dividend_polynomial[0]=0;
dividend_polynomial[1]=dividend_polynomial[1]-(temp*divisor_polynomial[1]);
dividend_polynomial[2]=dividend_polynomial[2]-(temp*divisor_polynomial[2]);

//Demais iterações
while(degree>1){
temp=dividend_polynomial[1];
dividend_polynomial[1]=(dividend_polynomial[2]-(temp*divisor_polynomial[1]))%n;
dividend_polynomial[2]=(temp*divisor_polynomial[2])%n;
degree--;
               };

//Resultado
if(dividend_polynomial[1]!=0 || dividend_polynomial[2]!=1)
return false;

//Teste 2: congruência x^[(2^j)s] (mod n, x²-bx-c) para 0 ≲j≲(r-2)
//Restrição
if(r<3)
return true;

//Ajuste de variáveis
degree=s;

//Loop principal
while(j<(r-2)){
//Ajuste de variáveis
if(j>0)
degree*=2;

++j;

dividend_polynomial[0]=1;
dividend_polynomial[1]=0;
dividend_polynomial[2]=0;

//Primeira iteração
degree--;
temp=1;
dividend_polynomial[0]=0;
dividend_polynomial[1]=dividend_polynomial[1]-(temp*divisor_polynomial[1]);
dividend_polynomial[2]=dividend_polynomial[2]-(temp*divisor_polynomial[2]);

//Demais iterações
while(degree>1){
temp=dividend_polynomial[1];
dividend_polynomial[1]=(dividend_polynomial[2]-(temp*divisor_polynomial[1]))%n;
dividend_polynomial[2]=(temp*divisor_polynomial[2])%n;
degree--;
               };

//Resultado
if(dividend_polynomial[1]!=0 || dividend_polynomial[2]!=(n-1))
return false;


              };


//Resultado em caso de sucesso nos testes acima
return true;

                                                                };

//Teste de Fröbenius
bool quadratic_frobenius_primality_test(int64_t n){
//Caso base
if(n<50000 && is_integer_prime(n)==true)
return true;

//Teste 1: divisão por primos pequenos
if(trial_division_test(n)==false)
return false;

//Teste 2: checando se o número em questão é um quadrado perfeito
if(perfect_square_check(n)==true)
return false;

//Etapa 3: calculando valores dos coeficientes b e c usados no teste
int64_t b, c; //Variáveis locais
find_quadratic_coefficients(&b, &c, n);

//Teste 4: teste de congruência x^((n+1)/2) (mod n, x²-bx-c)
if(quadratic_polynomial_test1(b, c, n)==false)
return false;

//Teste 5: teste de congruência x^(n+1) (mod n, x²-bx-c)
if(quadratic_polynomial_test2(b, c, n)==false)
return false;

//Teste 6: teste de congruência estilo teste de Miller Rabin
if(quadratic_polynomial_test3(b, c, n)==false)
return false;

//Caso passe nos testes acima um provável primo foi encontrado
return true;
                                                  };

//********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
