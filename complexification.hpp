//VAMOS CRIAR UM ARQUIVO QUE IMPLEMENTA ROTINAS PARA CONSERVSÃO DE NÚMEROS COMPLEXOS EM NÚMEROS REAIS E VICE-VERSA

//********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef COMPLEXIFICATION_H
#define COMPLEXIFICATION_H
#include"complex_numbers.hpp"
#include<stdint.h>

//********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
complex<double> complexification(int64_t, int64_t);
complex<double> complexification(int64_t);
complex<double> complexification(double, double);
complex<double> complexification(double);
void realification(complex<double>, int64_t&, int64_t&);
void realification(complex<double>, double&, double&);

//********************************************************************************************************************************************************************
//FUNÇÕES
//Funções auxiliares que convertem números inteiros e reais em números complexos
complex<double> complexification(int64_t a, int64_t b){
//Variáveis locais
complex<double> result;
//Procedimentos
result.real=a;
result.imag=b;
return result;
                                                      };

complex<double> complexification(int64_t a){
//Variáveis locais
complex<double> result;
//Procedimentos
result.real=a;
result.imag=0;
return result;
                                          };

complex<double> complexification(double a, double b){
//Variáveis locais
complex<double> result;
//Procedimentos
result.real=a;
result.imag=b;
return result;
                                                   };

complex<double> complexification(double a){
//Variáveis locais
complex<double> result;
//Procedimentos
result.real=a;
result.imag=0.0;
return result;
                                         };

//Funções que convertem números complexos em inteiros e reais
void realification(complex<double> z, int64_t& a, int64_t& b){
//Procedimentos
a=z.real;
b=z.imag;
                                                             };

void realification(complex<double> z, double& a, double& b){
//Procedimentos
a=z.real;
b=z.imag;
                                                           };
//********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
