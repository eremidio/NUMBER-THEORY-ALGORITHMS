//ESTE ARQUIVO CONTÉM A DEFINIÇÃO DA FUNÇÃO ZETA DE RIEMANN PARA NÚMEROS REAIS E NÚMEROS COMPLEXOS

/*
A FUNÇÃO ZETA DE RIEMANN ζ(z) E UMA DAS FUNÇÕES MAIS IMPORTANTES EM MATEMÁTICA.
MATEMATICAMENTE SEU VALOR CORRESPONDE A SOMA DOS RECÍPROCOS DOS NÚMEROS NATURAIS ELEVADO A UM NÚMERO COMPLEXO.
PARA NÚMEROS REAIS OBTEMOS AS CHAMADAS p-SÉRIES QUE DIVERGEM QUANDO p<1 OU p=1 (SÉRIE HARMÔNICA).
PARA NÚMEROS COMPLEXOS COM Re(z)<1 A SÉRIE TAMBÉM DIVERGE. EMBORA POR MEIO DA CONTINUAÇÃO ANALÍTICA SEJA POSSÍVEL
EXTENDER A FUNÇÃO PARA TODO NÚMERO COMPLEXO (POLOS -OS CHAMADOS ZEROS TRIVAIS- OCORREM EM INTEIROS NEGATIVOS).

A FUNÇÃO ZETA DE RIEMANN DESEMPENHA UM PAPEL IMPORTANTE EM TEORIA DE NÚMEROS E OUTRAS ÁREAS IMPORTANTES DA MATEMÁTICA.
ESTANDO RELACIONADA DIRETAMENTE COM AS FUNÇÕES QUE DETERMINAM A DENSIDADE DE NÚMEROS PRIMOS, A FUNÇÃO GAMMA,  A FUNÇÃO
ETA DE DIRICHLET, A FUNÇÃO THETA, ENTRE OUTRAS.

A FUNÇÃO ZETA TAMBÉM OCORRE NATURALMENTE EM MUITOS PROBLEMAS DE FÍSICA.
https://empslocal.ex.ac.uk/people/staff/mrwatkin/zeta/physics2.htm

EXISTEM VÁRIAS REPRESENTAÇÕES ALTERNATIVAS PARA A FUNÇÃO ZETA COMO PRODUTÓRIOS, SÉRIES DE POTÊNCIA, INTEGRAIS E EQUAÇÕES
FUNCIONAIS. DESTAS A MAIS IMPORTANTE SEJA TALVEZ A REPRESENTAÇÃO DE UM PRODUTÓRIO INFINITO ENVOLVENDO NÚMEROS PRIMOS.
A CHAMADA REPRESENTAÇÃO DE EULER QUE FORNECE UMA PROVA SIMPLES DA INFINIDADE DOS NÚMEROS PRIMOS.


A CHAMADA HIPÓTESE DE RIEMANN SOBRE OS ZEROS NÃO TRIVIAIS DESTA FUNÇÃO É UM DOS CHAMADOS PROBLEMAS MILENIAIS DA MATEMÁTICA.
PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Riemann_zeta_function

*/

//**************************************************************************************************************************
//CABEÇALHO
#pragma once
#include<cmath>
#include<assert.h>
#include"complex_numbers.hpp"
#include"gamma_function.hpp"

//**************************************************************************************************************************
//Protótipos de funções
double riemann_zeta_function(double);
double riemann_zeta_function(int);
complex<double> int_complex_pow(long int, complex<double>);
complex<double> riemann_zeta_function(complex<double>);

double riemann_xi_function(double);
complex<double> double_complex_pow(double, complex<double>);
complex<double> riemann_xi_function(complex<double>);
double dirichlet_eta_function(double);
complex<double> dirichlet_eta_function(complex<double>);

double riemann_zeta_function_analytical_continuation(double);
complex<double> complex_sine(complex<double>);
complex<double> riemann_zeta_function_analytical_continuation(complex<double>);

//**************************************************************************************************************************
//DEFINIÇÃO DA FUNÇÃO ZETA DE RIEMANN PARA ARGUMENTOS VARIADOS
//1. Números inteiros positivos
double riemann_zeta_function(int n){

  //Restrição de valores aceitáveis
  assert(n>1);
  //Overload da função para valores reais
  return riemann_zeta_function((double) n);
};

//2. Números reais: usaremos representações via série de potências
double riemann_zeta_function(double x){

  //Restrição de valores aceitáveis
  assert(x>1.0);

  //Variáveis locais
  long int n_max=10000000;
  long int i;//Variável de iteração
  double sum=0.0;
  double parcel;

  //Procedimento : loop principal
  for(i=1; i<n_max; ++i){
    parcel= 1.0/std::pow(i, x);
    sum+=parcel;
    //Definindo um limite de precisão
    if(parcel<1e-9) break;
  };

  return sum;
};

//3.Números complexos: representação via série de potências.
//Necessitaremos de uma função auxiliar para calcular potência de expoentes complexos.
complex<double> int_complex_pow(long int n, complex<double> z){

  //Variáveis locais
  complex<double> real_factor(std::pow(n, z.real), 0);
  complex<double> complex_factor(std::cos(std::log(n)*z.imag), std::sin(std::log(n)*z.imag));


  //Resultado
  return real_factor*complex_factor;
};

//Computando a função ζ para argumentos complexos
complex<double> riemann_zeta_function(complex<double> z){

  //Restrição de valores aceitáveis
  assert(z.real>1.0);

  //Variáveis locais
  complex<double> sum(0.0, 0.0);
  long int n_max=10000000;
  long int i;//Variável de iteração

  //Procedimentos:loop principal
  for(i=1; i<n_max; ++i) sum = sum + int_complex_pow(i, z).inv();

  //Resultado
  return sum;
};

//**************************************************************************************************************************
//APLICAÇÕES DA FUNÇÃO ZETA DE RIEMANN PARA O CÁLCULO DA FUNÇÃO ETA DE DIRICHLET E PARA A FUNÇÃO XI DE RIEMANN

//Função η de Dirichlet (Função zeta de Riemann alternada)
//1.Argumentos reais
double dirichlet_eta_function(double x){
  return (1-std::pow(2, 1-x))*riemann_zeta_function(x);
};


//2.Argumentos complexos
complex<double> dirichlet_eta_function(complex<double> z){

  //Variáveis locais
  complex<double> hum(1.0, 0);

  //Resultado
  return (hum-int_complex_pow(2, z))*riemann_zeta_function(z);
};

//Função χ de Riemann
//1. Argumentos reais
double riemann_xi_function(double x){

  //Variáveis locais
  double result=1;

  //Procedimentos
  result*= 0.5*std::pow(4.0*std::atan(1.0), (-0.5)*x);
  result*=x*(x-1);
  result*=gamma(x/2)*riemann_zeta_function(x);
  return result;

}; 

//2. Argumentos complexos
//Necessitaremos de uma função auxiliar para calcular potência de expoentes complexos.
complex<double> double_complex_pow(double x, complex<double> z){

  //Variáveis locais
  complex<double> real_factor(std::pow(x, z.real), 0);
  complex<double> complex_factor(std::cos(std::log(x)*z.imag), std::sin(std::log(x)*z.imag));

  //Resultado
  return real_factor*complex_factor;
};

//Computando a função χ de Riemann
complex<double> riemann_xi_function(complex<double>z){

  //Variáveis locais
  complex<double> one_half(0.5, 0);
  complex<double> hum(1.0, 0);
  complex<double> pi_power = double_complex_pow(4.0*std::atan(1.0), z*one_half);
  complex<double> result;


  //Procedimentos
  result=one_half*z*(z-hum);
  result=result/pi_power;
  result=result*(gamma(z*one_half)*riemann_zeta_function(z));
  

  //Resultado
  return result;

};

//**************************************************************************************************************************
//CONTNUAÇÕES ANÁLITICAS DA FUNÇÃO ZETA DE RIEMANN

//1.Argumentos reais
double riemann_zeta_function_analytical_continuation(double x){

  //Caso 1:x>1
  if(x>=1) return riemann_zeta_function(x);

  //Caso 2: 0<x<1
  else if(x>=0 && x<1){

  //Variáveis locais
  long int n_max=10000000;
  long int i;//Variável de iteração
  double sum=0.0;
  double parcel;

  //Procedimento 
  for(i=1; i<n_max; ++i){
    parcel= 1.0/std::pow(i, x);
    if(i%2==1) sum-=parcel;
    if(i%2==0) sum+=parcel;
    
    //Definindo um limite
    if(parcel<1e-e) break;
  };

  //Resultado
  return sum/(1-std::pow(2, 1-x));

  }

  //Caso 3: x<0
  else{
    //Zeros triviais ocorrem em -2, -4, ...
    int n=(-1)*x;
    if(n%2==0) return 0;

    //Variáveis locais
    constexpr double pi=4.0*atan(1.0);
  
    //Procedimentos
    return std::pow(2, x)*std::pow(pi, x-1)*std::sin((pi*x)/2)*gamma(1-x)*riemann_zeta_function(1-x);
  };


};

//2. Argumentos complexos
//Função auxiliar para o cálculo do seno complexo
//OBSERVAÇÃO:Usar sin(a+b)=sin(a)cos(b)+sin(b)cos(a) e o fato de que cos(ia)=cosh(a) e sin(ia)=sinh(a)
complex<double> complex_sine(complex<double> z){

  //Váriaveis locais
  complex<double> result;

  //Procedimentos
  result.real = std::sin(z.real)*std::cosh(z.imag);
  result.imag = std::cos(z.real)*std::sinh(z.imag);
  return result; 
};


//Computando a função ζ para argumentos complexos
complex<double> riemann_zeta_function_analytical_continuation(complex<double> z){

  //Restrição de valores aceitáveis
  assert(z.real-floor(z.real)!=0);

  //Caso 1:Re(z)>1
  if(z.real>=1.0) return riemann_zeta_function(z);

  //Caso 2: 0<Re(z)<1
  if(z.real<1.0 && z.real>0){

    //Variáveis locais
    complex<double> sum(0.0, 0.0);
    long int n_max=10000000;
    complex<double> hum(1.0, 0);
    long int i;//Variável de iteração

    //Procedimentos
    for(i=1; i<n_max; ++i){
      if(i%2==0) sum = sum + int_complex_pow(i, z).inv();
      if(i%2==1) sum = sum - int_complex_pow(i, z).inv();
    };

    //Resultado
    return sum/(hum-int_complex_pow(2, hum-z));

  }


  //Caso 3: Re(z)<0
  else{

    //Variáveis locais
    complex<double> result;
    constexpr double pi= 4.0*atan(1.0);
    complex<double> hum(1.0, 0);
    complex<double> complex_half_pi(pi/2, 0);
  
    //Procedimento
    result=int_complex_pow(2, z)*double_complex_pow(pi, z-hum)*complex_sine(complex_half_pi* z);
    result = result*gamma(hum-z)*riemann_zeta_function(hum-z);
    return result;
  };

};
