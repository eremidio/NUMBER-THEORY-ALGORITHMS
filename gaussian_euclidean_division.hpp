//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE EUCLIDES PARA INTEIROS GAUSSIANOS

//********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef GAUSSIAN_EUCLIDEAN_DIVISION_H
#define GAUSSIAN_EUCLIDEAN_DIVISION_H
#include"complex_numbers.hpp"
#include<cmath>
#include<stdint.h>

//CONSTANTES GLOBAIS
complex<int64_t> zero(0,0);

//********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
complex<int64_t> gaussian_euclides_algorithm(complex<int64_t>, complex<int64_t>);

//********************************************************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides
complex<int64_t> gaussian_euclides_algorithm(complex<int64_t> z1, complex<int64_t> z2){
//Restrição
if(z2.norm()>z1.norm())
return gaussian_euclides_algorithm(z2, z1);

//Variáveis locais
complex<int64_t> quotient, remainder;
double real1, imag1, real2, imag2, int_norm;

//Procedimentos
//Calculando o quociente de dois inteiros gaussianos
int_norm=(z2.real*z2.real)+(z2.imag*z2.imag);
quotient.real=std::floor(((z1.real*z2.real)+(z1.imag*z2.imag))/int_norm);
quotient.imag=std::floor(((z1.imag*z2.real)-(z1.real*z2.imag))/int_norm);

//Calculando resto da divisão
remainder=z1-(quotient*z2);
if(remainder.real==0 && remainder.imag==0)
return z2;
else
return gaussian_euclides_algorithm(z2, remainder);



                                                                                      };

//********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
