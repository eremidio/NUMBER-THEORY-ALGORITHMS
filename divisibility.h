//VAMOS ESCREVER UMAS ROTINAS EM C PARA TESTAR A DIVISIBILIDADE DE UM INTEIRO POR NÚMEROS PRIMOS MEENORES QUE 30
//ESTE ARQUIVO CONTÉM TAMBÉM ROTINAS ÚTEIS NA MANIPULAÇÃO DE INTEIROS EM C
//USANDO AS ROTINAS BÁSICAS DISPONIBILIZADAS AQUI É FÁCIL ESCREVER RÓTINAS PARA TESTAR A DIVISIBILIDADE POR OUTROS PRIMOS.
//UMA LISTA MAIS COMPLETA ESTÁ DISPONÍVEL EM:https://en.wikipedia.org/wiki/Divisibility_rule

//**************************************************************************************************************************
//CABEÇALHO
#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<stdint.h>
#include<math.h>
#include<assert.h>

//**************************************************************************************************************************
//FUNÇÕES ÚTEIS

//Função que calcula quantos digitos decimais um número possui
int digits_counter (uint64_t number){
return (int)log10(number)+1;
                                    };

//Função que extrai o valor posicional de um algarismo em um número inteiro
uint64_t positional_value(uint64_t number, int position){

//Variáveis locais
int digit_number=digits_counter(number);
uint64_t result;


//Procedomentos
//Checando se os argumentos são válidos 
assert(digit_number>=position);

//Reduzindo um número a um valor
//Removendo casas decimais a esquerda
uint64_t power10_left = pow(10, digit_number-position+1);
number=number%power10_left;
//Removendo casas decimais a direita
uint64_t power10_right = pow(10, digit_number-position);
//Reajustando a variável
number=number - (number%power10_right);

return number;
                                                        };

//TODO:Funções de extração de dígitos de um inteiro
//1. Dígitos entre um intervalo qualquer
uint64_t extract_digits_interval(uint64_t number, int start_digit, int end_digit){
//Variáveis locais
int digit_number=digits_counter(number);
int i; //Variável de iteração
uint64_t extracted_value=0;
//Procedimento
//Checando se os argumentos são válidos 
assert(digit_number>=start_digit && digit_number>=start_digit);

//Extraindo valores dos dígitos
for(i=start_digit; i<=end_digit; ++i){
extracted_value+=positional_value(number, i);
                                     };

//Ajustando o valor extraído removendo zeros a direita
uint64_t power10_right = pow(10, digit_number-end_digit);
return(extracted_value/power10_right);
                                                                                 };

//2. Extraindo os últimos dígitos de um número
uint64_t extract_last_digits(uint64_t number, int last_digits){
//Variáveis locais
int digit_number=digits_counter(number);
//Procedimentos
//Checando se os argumentos são válidos 
assert(digit_number>=last_digits);

//Calculando o valor dos digitos a serem estraídos
return extract_digits_interval(number, digit_number-last_digits+1, digit_number);

                                                              };

//3. Extraindo os primeiros dígitos de um número
uint64_t extract_first_digits(uint64_t number, int first_digits){
//Variáveis locais
int digit_number=digits_counter(number);
//Procedimentos
//Checando se os argumentos são válidos 
assert(digit_number>=first_digits);

//Calculando o valor dos digitos a serem estraídos
return extract_digits_interval(number, 1, first_digits);

                                                               };

//**************************************************************************************************************************
//CRITÉRIOS DE DIVISIBILIDADE
//2
bool divisible_by_2(uint64_t number){
//Variáveis locais
int last = extract_last_digits(number, 1);
int digits_number=digits_counter(number);

//Teste
if(last==0 && digits_number>2)
return true;
else if(last==2 || last==4 || last== 6 || last== 8) 
return true;
else 
return false;
                                    };

//3
bool divisible_by_3(uint64_t number){
//Váriáveis locais
int sum_3=0;
int digits_number=digits_counter(number);
int i;//Variável de iteração

//Teste
for(i=1; i<=digits_number; ++i)
sum_3+= extract_digits_interval(number, i, i);

if(sum_3>100)
return divisible_by_3(sum_3);

if(sum_3%3==0)
return true;
else
return false;
                                    };

//5
bool divisible_by_5(uint64_t number){
//Variáveis locais
int last = extract_last_digits(number, 1);
int digits_number=digits_counter(number);

//Teste
if(last==0 && digits_number>2)
return true;
else if(last==5) 
return true;
else 
return false;
                                    };

//7
bool divisible_by_7(uint64_t number){
//Variáveis locais
int digits_number=digits_counter(number);
uint64_t last2, rest, residue_7;

//Teste
last2=extract_last_digits(number, 2);
rest=extract_first_digits(number, digits_number-2);

if(((rest*2)+last2)%7==0)
return true;
else
return false;
                                    };

//11
bool divisible_by_11(uint64_t number){
//Variáveis locais
int digits_number=digits_counter(number);
uint64_t sum_11=0;
int i;//Variável de iteração

//Teste
for(i=1; i<=digits_number; ++i){
if(i%2==1)
sum_11+=extract_digits_interval(number, i, i);
if(i%2==0)
sum_11-=extract_digits_interval(number, i, i);
                               };

if(sum_11%11==0)
return true;
else if(sum_11%11!=0)
return false;
                                     };

//13
bool divisible_by_13(uint64_t number){
//Variáveis locais
int digits_number=digits_counter(number);
uint64_t sum_13;
uint64_t last = extract_last_digits(number, 1);
uint64_t rest=extract_first_digits(number, digits_number-1);
int i;//Variável de iteração

//Teste
sum_13=rest+4*last;
if(sum_13>100)
return divisible_by_13(sum_13);

if(sum_13%13==0)
return true;
else 
return false;
                                     };

//17
bool divisible_by_17(uint64_t number){
//Variáveis locais
int digits_number=digits_counter(number);
uint64_t sum_17;
uint64_t last2=extract_last_digits(number, 2);
uint64_t rest=extract_first_digits(number, digits_number-2);

//Teste
sum_17=2*rest-last2;

if(sum_17>1000)
return divisible_by_17(sum_17);

if(sum_17%17==0)
return true;
else
return false;
                      };

//19
bool divisible_by_19(uint64_t number){
//Variáveis locais
int digits_number=digits_counter(number);
uint64_t sum_19;
uint64_t last = extract_last_digits(number, 1);
uint64_t rest=extract_first_digits(number, digits_number-1);

//Teste
sum_19=rest+2*last;
if(sum_19>1000)
return divisible_by_19(sum_19);

if(sum_19%19==0)
return true;
else
return false;
                      };

//23
bool divisible_by_23(uint64_t number){
//Variáveis locais
int digits_number=digits_counter(number);
uint64_t sum_23;
uint64_t last = extract_last_digits(number, 1);
uint64_t rest=extract_first_digits(number, digits_number-1);

//Teste
sum_23=rest+7*last;
if(sum_23>100)
return divisible_by_23(sum_23);

if(sum_23%23==0)
return true;
else
return false;
                                     };


//29
bool divisible_by_29(uint64_t number){
//Variáveis locais
int digits_number=digits_counter(number);
uint64_t sum_29;
uint64_t last2=extract_last_digits(number, 2);
uint64_t rest=extract_first_digits(number, digits_number-2);

//Teste
sum_29=rest+9*last2;

if(sum_29>1000)
return divisible_by_29(sum_29);

if(sum_29%29==0)
return true;
else
return false;
                                    };




