//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ROTINAS PARA O CÁLCULO DOS NÚMEROS DE LUCAS

/*
OS NÚMEROS DE LUCAS SÃO DEFINIDOS PELA SEQUÊNCIA: L(0)=2, L(1)=1 E L(n)=L(n-1)+L(n-2).
NÚMEROS DE LUCAS SÃO UM CASO PARTICULAR DE SEQUÊNCIAS DE LUCAS DOP SEGUNDO TIPO.

TAIS NÚMEROS SATISFAZEM UM NÚMERO DE PROPRIEDADES INTERESSANTES E ESTÃO DIRETAMENTE RELACIONADOS AS SEQUÊNCIAS DE FIBONACCI E A RAZÃO DE OURO φ=(1+√5)/2.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Lucas_number


*/


//********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef LUCAS_NUMBER_H
#define LUCAS_NUMBER_H
#include<stdint.h>
#include<math.h>

//********************************************************************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
int64_t recursive_lucas_number(int64_t);
int64_t lucas_number_golden_ratio(int64_t);
int64_t fibonacci_number(int64_t);


//********************************************************************************************************************************************************************
//FUNÇÕES 

//Função que calcula números de Lucas usando relações recursivas
int64_t recursive_lucas_number(int64_t n){
//Variáveis locais
int64_t l0=2, l1=1, l2;
int64_t i;

//Procedimentos 
//Casos triviais: n=0,1
if(n==0)
return l0;
if(n==1)
return l1;

//Caso geral: n>=2
for(i=1; i<n; i++){
l2=l0+l1;

//Atualizando variáveispara a próxima iteração
l0=l1;
l1=l2;
                  };


//Resultado
return l2;

                                         };


//Função que calcula o n-ésimo número de Lucas usando a relação L(n)=(φ^n)+(-φ)^(-n)
int64_t lucas_number_golden_ratio(int64_t n){

//Variáveis locais
const double golden_ratio=(1.0+sqrt(5))/2.0;
double phi_power=pow(golden_ratio, n);
int64_t parity=(n%2);

//Resultado
if(parity==0)
return (int64_t)(phi_power+(1.0/phi_power));
else
return (int64_t)(phi_power-(1.0/phi_power));

                                            };

//Função que calculao n-ésimo número de Fibonacci em termos do n-ésimo número de Lucas
int64_t fibonacci_number(int64_t n){
//Variáveis locais
const double root5=sqrt(5);
const double golden_ratio=(1.0+sqrt(5))/2.0;
double phi_power=pow(golden_ratio, n);
int64_t lucas=recursive_lucas_number(n);


//Resultado 
return (int64_t)(((2.0*phi_power)-lucas)/root5);

                                   };

//********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
