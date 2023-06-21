//VAMOS ESCREVER UM PROGRAMA EM C QUE É USADO PARA COMPUTAR A FUNÇÃO TOTIENTE DE EULER TAMBÉM CONHECIDA COMO FUNÇÃO φ DE EULER
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o euler_totient_function euler_totient_function.c -lm

/*
PARA UM ARGUMENTO n A FUNÇÃO φ(n) CONTABALIZA QUANTOS INTEIROS NO INTERVALO [1, 2, ..., n] SÃO RELATIVAMENTE PRIMOS COM n.
ISTO É, DADO UM NÚMERO a NO INTERVALO 1, 2,..., n, φ(n) CONTABILIZA QUANTOS NÚMEROS SATISFAZEM A CONDIÇÃO mdc(a, n)=1.

A FUNÇÃO φ(n) É MULTIPLICATIVA: φ(n)φ(m)=φ(nm) SE n E m FOREM  REALATIVAMENTE PRIMOS.
PARA UM NÚMERO PRIMO p: φ(p)=p-1 (APENAS 1 É RELATIVAMENTE PRIMO COM n).

ESTA FUNÇÃO PODE SER DETERMINADA POR MEIO DE CONTAGEM DIRETA USANDO O ALGORITMO DE EUCLIDES OU USANDO-SE A FÓRMULA DE EULER, QUE FAZ USO DE UM PRODUTÓRIO ENVOLVENDO FATORES PRIMOS DE n.
PARA MAIORES INFORMAÇÕES:https://en.wikipedia.org/wiki/Euler%27s_totient_function
*/



//*************************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<math.h>

#define PHI_MAX 250000
//*************************************************************************************************************************
//FUNÇÕES

//Função que implementa o algoritmo de Euclides para se calcular o mdc de dois inteiros
uint64_t gdc_euclides(uint64_t a, uint64_t b){
if(a==b)
return a;
if(a>b)
return gdc_euclides((a-b), b);
if(a<b)
return gdc_euclides(a, (b-a));
                                             };

//Função que detecta se um número é quadrado perfeito
bool perfect_square(uint64_t n){
return floor(sqrt(n))-sqrt(n)>=0;
                               };

//Função que checa se um número é primo
bool is_prime(uint64_t n){
//Variáveis
uint64_t i;

//Procedimentos

if (n == 2 || n == 3)
return true;

if (n <= 1 || n % 2 == 0 || n % 3 == 0)
return false;

for(i = 5; i * i <= n; i += 6){
if (n % i == 0 || n % (i + 2) == 0)
return false;
                             };
 return true;
                       }

//Função totiente para pequenos inteiros ≲250000
uint64_t totient_function_small_numbers(uint64_t n){

//Variáveis locais
uint64_t counter=0;
uint64_t i;//Variável de iteração

//Procedimentos
for(i=1; i<n; ++i){
if(gdc_euclides(i, n)==1)
++counter;
                  };

return counter;
                                                  };

//Função totiente de Euler para números grandes (usamos a propriedade multiplicativa da função φ para ≲250000²)
//Essa função não 
uint64_t totient_function_large_numbers(uint64_t n){
//Variáveis locais
uint64_t factor1, factor2;
uint64_t limit=sqrt(n);
uint64_t i;//Variável de iteração

//Procedimentos
//Caso 1: quadrados perfeitos
if(perfect_square(n)==true)
return totient_function_small_numbers(limit)*totient_function_small_numbers(limit);

//Caso 2: Números primos
if(is_prime(n))
return n-1;
 
//Caso 3: Encontrando fatores relativamente primos de um dado número
for(i=1; i<limit; ++i){
if(n%(limit-i)==0){
factor1=limit-i;
factor2=n/factor1;
if(gdc_euclides(factor1, factor2)==1 && factor1<=PHI_MAX && factor2<=PHI_MAX)
break;
                  };
                      };
//Resultado
return totient_function_small_numbers(factor1)*totient_function_small_numbers(factor2);
                                                   };


//Função totiente de Euler
uint64_t euler_totient_function(uint64_t n){
if(n>PHI_MAX)
return totient_function_large_numbers(n);
if(n<=PHI_MAX)
return totient_function_small_numbers(n);
                                           };

//*************************************************************************************************************************
//FUNÇÃO PRINCIPAL

int main(){
//Variáveis
uint64_t number;
//Recebendo input do usuário
printf("Usuário digite um número: ");
scanf("%li", &number);

//Calculando o valor da função totiente de Euler
printf("φ(%li) = %li.\n", number, euler_totient_function(number));

//Finalizando a aplicação
return 0;
          }
