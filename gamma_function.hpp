//ESTE ARQUIVO CONTÉM UMA IMPLEMENTAÇÃO DA FUNÇÃO GAMA USANDO FUNCTION OVERLOADING EM C++

/*
A FUNÇÃO GAMA Γ(z) PARA UM ARGUMENTO COMPLEXO z É DEFINIDA COMO A INTEGRAL DEFINIDA DE exp(-x).x^(z-1) DE 0 A INFINITO.
COM A RESTRIÇÃO DE QUE Re(z)>1. 
ESTA É UMA DAS FUNÇÕES MAIS IMPORTANTES EM MATEMÁTICA TENDO APLICAÇÕES EM TEORIAS DOS NÚMEROS, PROBABILIDADE E NÚMEROS  COMPLEXOS. 

PARA ARGUMENTOS INTEIROS POSITIVOS Γ(n) = (n-1)!. A FUNÇÃO GAMA É UMA EXTENSÃO DA DEFINIÇÃO DE FATORIAL.
A FUNÇÃO GAMA APARECE EM IMPORTANTES IDENTIDADES MATEMÁTICAS E PODE SER USADA PARA COMPUTAR OUTRAS FUNÇÕES IMPORTANTES COMO A FUNÇÃO BETA β, A FUNÇÃO ZETA DE RIEMANN ζ, ENTRE OUTROS.

NESTE ARQUIVO ESTÃO ALGUMAS ROTINAS PARA O CÁLCULO DE OUTRAS FUNÇÕES ÚTEIS EM TEORIA DOS NÚMEROS
ALGUNS LINKS ÚTEIS:
https://jaketae.github.io/study/gamma-zeta/
https://en.wikipedia.org/wiki/Gamma_function
https://en.wikipedia.org/wiki/Beta_function

*/

//**************************************************************************************************************************
//CABEÇALHO
#pragma once
#include<cmath>
#include<assert.h>
#include<stdint.h>
#include"complex_numbers.hpp"

//**************************************************************************************************************************
//Protótipos de funções
long long int gamma(int);
double gamma(double);
complex<double> gamma(complex<double>);
double beta(double, double);
complex<double> beta(complex<double>, complex<double>);

//**************************************************************************************************************************
//DEFINIÇÃO DA FUNÇÃO GAMA PARA ARGUMENTOS VARIADOS 
//1. Inteiros: VAMOS USAR A DEFINIÇÃO DE FATORIAL
long long int gamma(int n){

  //Números menores que 1 não são argumentos válidos
  assert(n>=1);

  //Variáveis 
  long long int result;

  //Procedimentos
  //Definindo a função gama recursivamente
  if(n==1 || n==2) return 1;
  else return (n-1)*gamma(n-1);
                          };

//2. Números reais: vamos usar a definição de Euler usando produtório
double gamma(double x){

  //Variáveis locais
  long double result,  parcel; 
  int i = 1;//Variável de iteração


  //Procedimentos
    //Ajuste de variáveis
    result =1; 

    //Calculando a função gama como um produto infinto
    while(i<10000000){
      parcel= pow(1.0+(1.0/i), x);
      parcel=parcel/(1.0+(x/i));
      result*=parcel;
      ++i;
    };

  //Resultado
  return (result/x);

};


//3. Números complexos com parte real maior que 1: vamos usar a aproximação de Stirling
//Usamos o métodos .pow(double) e .exp() definido para a classe de números complexos no arquivo complex_numbers.hpp

//Aproximação de ordem O(z^(35/2))
complex<double> gamma (complex<double> z){

  //Restrição dos argumentos a números complexos cuja parte real é superior a 1
  assert(z.real>1.0);

  //Variáveis 
  complex<double> log_result, result;
  complex<double> log_z(std::log(z.norm()), z.polar());
  complex<double> power_part, factor;
  complex<double> log_2pi(log(8*atan(1.0)), 0), hum(1, 0),one_half(0.5, 0);


  //Procedimentos
    //Calculando a parte principal
    log_result=z*(log_z-hum)+one_half*(log_2pi-log_z);
   
    //Calculando a série de potências
    //1
    factor.real=(1.0/12.0);
    factor.imag=0.0;
    power_part=z.pow(1);
    log_result=log_result + (factor*power_part.inv());
    //3
    factor.real=(1.0/360.0);
    factor.imag=0.0;
    power_part=z.pow(3);
    log_result = log_result - (factor*power_part.inv());
    //5
    factor.real=(1.0/1260.0);
    factor.imag=0.0;
    power_part=z.pow(5);
    log_result=log_result + (factor*power_part.inv());
    //7
    factor.real=(1.0/1680.0);
    factor.imag=0.0;
    power_part=z.pow(7);
    log_result=log_result - (factor*power_part.inv());
    //9
    factor.real=(1.0/1188.0);
    factor.imag=0.0;
    power_part=z.pow(9);
    log_result=log_result + (factor*power_part.inv());
    //11
    factor.real=(691.0/360360.0);
    factor.imag=0.0;
    power_part=z.pow(11);
    log_result=log_result - (factor*power_part.inv());
    //13
    factor.real=(1.0/156.0);
    factor.imag=0.0;
    power_part=z.pow(13);
    log_result=log_result + (factor*power_part.inv());
    //15
    factor.real=(3617.0/122400.0);
    factor.imag=0.0;
    power_part=z.pow(15);
    log_result=log_result - (factor*power_part.inv());
    //17
    factor.real=(43867.0/244188.0);
    factor.imag=0.0;
    power_part=z.pow(17);
    log_result=log_result + (factor*power_part.inv());

  //Resultado
  return log_result.exp();
};

//**************************************************************************************************************************
//APLICAÇÕES CÁLCULO DA FUNÇÃO BETA PARA ARGUMENTOS REAIS E PARA NÚMEROS COMPLEXOS

//Calculando a função β
//1.Números reais
double beta(double x, double y){
  return (gamma(x)*gamma(y))/gamma(x+y);
};

//2. Números complexos
complex<double> beta(complex<double> z1, complex<double> z2){
  return (gamma(z1)*gamma(z2))/gamma(z1+z2);
};

