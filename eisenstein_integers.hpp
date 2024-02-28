//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA A CLASSE DOS INTEIROS DE EISENSTEIN

/*
OS INTEIROS DE EISENSTEIN (TAMBÉM CONHECIDOS COMO INTEIROS DE EULER)SÃO NÚMEROS COMPLEXOS DA FORMA z=a+bω, ΟΝDE ω=e^(i2π/3)=(-1+i√3)/2. ω É UMA RAÍZ CÚBICA PRIMITIVA
(NÃO REAL) DA UNIDADE. OS INTEIROS DE EISENSTEIN FORMAM UM ANEL COMUTATIVO DE INTEIROS ALGÉBRICOS NO CORPO ALGÉBRICO Q(ω) O TERCEIRO CORPO CICLOTÔMICO. INTEIROS DE 
EISENSTEIN SÃO SOLUÇÕES DO POLINÔMIO P(x)=x²-(2a-b)x+(a²-ab+b²), EM PARTICULAR ω²+ω+1=0. O GRUPO DE UNIDADES NESTE ANEL É O GRUPO CÍCLICO FORMADO POR:
{1, -1, ω, -ω, ω², -ω²}.

SEJA ω* O COMPLEXO CONJUGADO DE ω NO CORPO DOS NÚMEROS COMPLEXOS, ENTÃO ω*ω=|ω|²=1 E ω²=ω*. DESTA RELAÇÕES SEGUEM-SE AS SEGUINTES FÓRMULAS PARA AS OPERAÇÕES USUAIS, COM
w=c+dω: 

z+w=(a+c)+(b+d)ω
z-w=(a-c)+(b-d)ω
zw=(ac-bd)+(bc+ad-bd)ω

A NORMA DE z=a+bω É DEFINIDA POR N(z)=|a+bω|²=(a²-ab+b²).

O DOMÍNIO DOS INTEIROS DE EISENSTEIN FORMAM UM DOMÍNIO DE FATORAÇÃO ÚNICA. PRIMOS DE EISENSTEIN SÃO NÚMEROS PRIMOS (INTEIROS RACIONAIS) DA FORMA p=2 (mod 3). PARA PRIMOS
DA FORMA p=1 (mod 3), p CORRESPONDE A NORMA DE UM INTEIRO DE EISENSTEIN, DE FORMA QUE p=(x²-xy+y²)=(x+ωy)((x-y)-yω), (x+ωy) E ((x-y)-yω) SÃO CONSIDERADOS PRIMOS DE
EISENSTEIN TAMBÉM. OS INTEIROS DE EISENSTEIN FORMAM UM DOMÍNIO EUCLIDIANO.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Eisenstein_integer
                          https://digitalworks.union.edu/cgi/viewcontent.cgi?article=1161&context=theses
                          https://thekeep.eiu.edu/cgi/viewcontent.cgi?article=3459&context=theses
                          https://mathworld.wolfram.com/EisensteinInteger.html

*/

//**********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef EISENSTEIN_INTEGERS_H
#define EISENSTEIN_INTEGERS_H
#include"polynomials.h"
#include"complex_numbers.hpp"
#include<stdint.h>
#include<inttypes.h>
#include<iostream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<cmath>


//**********************************************************************************************************************************************************************
//CLASSE DOS INTEIROS DE EISENSTEIN
template<typename T>
class eisenstein_integer{
public:
//MEMBROS DA CLASSE
T a;
T b;

//CONSTRUTORES E DESTRUIDORES
eisenstein_integer(){ };
eisenstein_integer(T  x, T y){
a=x;
b=y;
                             };

~eisenstein_integer(){ };

//MÉTODOS DA CLASSE
void set(); //Função que ajusta os coeficientes de um inteiro de Eisenstein
T norm();//Função que calcula a norma de um inteiro de Eisentein
std::string algebraic();//Função que expressa um inteiro de Eisenstein usando notação algébrica z=a+bω
polynomial<T>  generate_monic_irreducible_polynomial();//Função que gera um polinômio mônico irredutível associado a um inteiro de Eisenstein

eisenstein_integer<T> operator +(eisenstein_integer<T>);//Função que implementa a operação de soma no anel de inteiros de Eisenstein
eisenstein_integer<T> operator -(eisenstein_integer<T>);//Função que implementa a operação de subtração no anel de inteiros de Eisenstein
eisenstein_integer<T> operator *(eisenstein_integer<T>);//Função que implementa a operação de multiplicação no anel de inteiros de Eisenstein
eisenstein_integer<T> operator /(eisenstein_integer<T>);//Função que implementa a operação de divisão no anel de inteiros de Eisenstein

                        };

//**********************************************************************************************************************************************************************
//MÉTODOS DA CLASSE

//---------------------
//Função que ajusta os coeficientes de um inteiro de Eisenstein
template<typename T>
void eisenstein_integer<T>::set(){
std::cout<<"Coeficiente a de Z[ω]:a+bω: ";
std::cin>>a;
std::cout<<"Coeficiente b de Z[ω]:a+bω: ";
std::cin>>b;
                                 };

//---------------------
//Função que calcula a norma de um inteiro de Eisentein
template<typename T>
T eisenstein_integer<T>::norm(){
//Variáveis locais
T result=((a*a)-(a*b)+(b*b));

//Resultado
return result;
                               };


//---------------------
//Função que expressa um inteiro de Eisenstein usando notação algébrica z=a+bω
template<typename T>
std::string eisenstein_integer<T>::algebraic(){
//Variáveis locais
std::string number_string="";

//Procedimentos
number_string+=std::to_string(a);

if(b>=0)
number_string+="+";

number_string+=std::to_string(b);

number_string+="ω";

//Resultado
return number_string;
                                              };



//---------------------
//Função que gera um polinômio mônico irredutível associado a um inteiro de Eisenstein
template<typename T>
polynomial<T>  eisenstein_integer<T>::generate_monic_irreducible_polynomial(){
//Variáveis locais
polynomial<T> irreducible_polynomial;

//Procedimentos
//Ajuste do polinômio irredutível associado a z=a+bω
irreducible_polynomial.degree=2;
irreducible_polynomial.polynomial_powers={2,1,0};
irreducible_polynomial.polynomial_coefficients={1,((2*a)-b), norm()};

//REsultado
return irreducible_polynomial;
                                                                            };


//---------------------
//Operação de adição
template<typename T>
eisenstein_integer<T> eisenstein_integer<T>::operator +(eisenstein_integer<T> z1){
//Variáveis locais
eisenstein_integer<T> z2;

//Procedimentos
z2.a=a+z1.a;
z2.b=b+z1.b;

//Resultado
return z2;
                                                                                };


//---------------------
//Operação de subtração
template<typename T>
eisenstein_integer<T> eisenstein_integer<T>::operator -(eisenstein_integer<T> z1){
//Variáveis locais
eisenstein_integer<T> z2;

//Procedimentos
z2.a=a-z1.a;
z2.b=b-z1.b;

//Resultado
return z2;
                                                                                 };

//---------------------
//Operação de multiplicação
template<typename T>
eisenstein_integer<T> eisenstein_integer<T>::operator *(eisenstein_integer<T> z1){
//Variáveis locais
eisenstein_integer<T> z2;

//Procedimentos
z2.a=(a*z1.a)-(b*z1.b);
z2.b=(b*z1.a)+(a*z1.b)-(b*z1.b);

//Resultado
return z2;
                                                                                 };

//---------------------
//Operação de divisão
template<typename T>
eisenstein_integer<T> eisenstein_integer<T>::operator /(eisenstein_integer<T> z1){
//Variáveis locais
eisenstein_integer<T> result;
complex<double> c1, c2, quotient;
constexpr double half_sqrt3=std::sqrt(3)/2.0;
constexpr double sqrt3=std::sqrt(3);

//Procedimentos
//1: Covertendo os elementos os inteiros de Eisenstein em números complexos
c1.real=(a-(0.5*b));
c1.imag=b*half_sqrt3;

c2.real=(z1.a-(0.5*z1.b));
c2.imag=z1.b*half_sqrt3;

//2: Calculando os  elementos do resultado
quotient=c1/c2;

result.a=std::round(quotient.real+(quotient.imag/sqrt3));
result.b=std::round(2.0*(quotient.imag/sqrt3));

//Resultado
return result;
                                                                                };


//**********************************************************************************************************************************************************************
//FIM DO HEADER
#endif

