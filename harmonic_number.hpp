//VAMOS CRIAR UM ARQUIVO QUE IMPLEMENTA A CLASSE DOS NÚMEROS HARMÔNICOS 

/*
O n-ÉSIMO NÚMERO HARMÔNICO É DEFINIDO PELA RELAÇÃO: H(n)=1+(1/2)+(1/3)+ ... +(1/n).
AS SEGUINTES RELAÇÕES DE RECORRÊNCIA SÃO UTÉIS EM COMPUTAR OS NÚMEROS HARMÔNICOS:
H(n+1)=H(n)+1/(n+1); H(n-1)=H(n)-(1/n).
DONDE 
H(n+k)=H(n)+1/(n+1)+1/(n+2)+ ... +1/(n+k)

PARA n TENDENDO A INFINITO TEMOS: H(n) ~ H(n+1) ~ H(n+2) ~ ... ~ H(n+k), COM k INTEIRO.
ADMITINDO QUE TAL RELAÇÃO SEJA VÁLIDA PARA NÚMEROS REAIS. PODE-SE EXTENDER A DEFINIÇÃO DE
NÚMEROS HARMÔNICOS PARA NÚMEROS REAIS E COMPLEXOS.

DE FATO PARA n SUFICIENTEMENTE GRANDE E x REAL TÊM-SE:
H(n+x)-H(x)~0 --> H(x)~(H(n)-(H(n+x)-H(x))) 

USANDO AS RELAÇÕES DE RECORRÊNCIA ACIMA OBTÉM-SE:
H(x)=Σ (1/k)-(1/(x+k))=x.Σ(1/(k(x+k))

O MESMO RACIOCÍNIO SE PALICA ANÚMEROS COMPLEXOS.

A INTEGRAL DEFINIDA DE 0 A 1 DE H(x) NOS DÁ A CONSTANTE DE EULER-MASCHERONI, CUJO VALOR É
 γ≃ 0.57721566490153286060651209008240243104215933593992.
ESTA CONSTANTE PODE SER DEFINIDA COMO:
γ = H(n) -ln(n) COM n TENDENDO A INFINITO.

OS NÚMEROS HARMÔNICOS POSSUEM RELAÇÃO DIRETA COM FUNÇÕES IMPORTANTES EM MATEMÁTICA COMO
A FUNÇÃO DIGAMA (DERIVADA DO LOGARITMO DA FUNÇÃO GAMA) E A FUNÇÃO ZETA DE RIEMANN (DE FATO,
NÚMEROS HARMÔNICOS SÃO SOMAS PARCIAIS DA SÉRIE HARMÔNICA QUE É  NUMERICAMENTE IGUAL A ζ(1)).

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Harmonic_number
                          https://en.wikipedia.org/wiki/Euler%27s_constant
                          https://en.wikipedia.org/wiki/Digamma_function


*/

//**************************************************************************************************************************
//CABEÇALHO
#if !defined HARMONIC_NUMBER_H
#define HARMONIC_NUMBER_H
#include<cmath>
#include<stdint.h>
#include<assert.h>
#include"complex_numbers.hpp"


//CONSTANTES_GLOBAIS
const double euler_mascheroni = 0.5772156649015328606065121;

//**************************************************************************************************************************
//PROTÓTIPO DE FUNÇÕES
double harmonic_number(int);
double harmonic_number(uint64_t);
double harmonic_number(double);
complex<double> harmonic_number(complex<double>);
double digamma(int);
double digamma(uint64_t);
double digamma(double);
complex<double> digamma(complex<double>);

//**************************************************************************************************************************
// FUNÇÕES
//Argumentos inteiros
double harmonic_number(uint64_t n){

  //Variáveis locais
  uint64_t i;
  double soma=0.0;

  //Procedimentos
  for(i=1; i<=n; ++i)
  soma+=(1.0/i);

  //Resultado
  return soma;

};

double harmonic_number(int n){
  uint64_t n_=static_cast<uint64_t>(n);
  return harmonic_number(n_);

};


//Argumentos reais não inteiros
double harmonic_number(double x){

  //Variáveis locais
  uint64_t i;
  double soma=0.0;

  //Procedimentos
  for(i=1; i<=100000000; ++i)
    soma+=(1.0/(i*(i+x)));

  //Resultado
  return soma*x;

};

//Argumentos complexos
complex<double> harmonic_number(complex<double> z){

  //Variáveis locais
  complex<double> complex_int;
  complex<double> parcel;
  complex<double> complex_sum(0.0, 0.0);
  uint64_t i;


  //Procedimentos
  for(i=1; i<=100000000; ++i){
    complex_int.real=i;
    complex_int.imag= 0.0;
    parcel = (complex_int*(complex_int+z)).inv();
    complex_sum=complex_sum+parcel;

  };

  //Resultado
  return complex_sum*z;

};

//**************************************************************************************************************************
//APLICAÇÕES NO CÁLCULO DA FUNÇÃO Digama Ψ
//Argumento inteiro,
double digamma(uint64_t n){
  return harmonic_number(n-1)-euler_mascheroni;
};

double digamma(int n){
  uint64_t n_=static_cast<uint64_t>(n);
  return digamma(n_);
};

//Argumento real (usaremos uma aproximação via série de Taylor)
double digamma(double x){

  //Aproximação para pequenos valores de x
  if(x<6.0) return digamma(x+1.0)-(1.0/x);

  //Aproximação para grandes valores de x
  double parcel1=(1.0/(2.0*x));
  double parcel2=(1.0/(12.0*x*x));
  double parcel3=(1.0/(120.0*x*x*x*x));
  double parcel4=(1.0/(252.0*x*x*x*x*x*x));
  double parcel5=(1.0/(240.0*x*x*x*x*x*x*x*x));
  double parcel6=(1.0/(132.0*x*x*x*x*x*x*x*x*x*x));
  double parcel7=(691.0/(32760.0*x*x*x*x*x*x*x*x*x*x*x*x));
  double parcel8=(1.0/(12.0*x*x*x*x*x*x*x*x*x*x*x*x*x*x));
  return (std::log(x)-parcel1-parcel2+parcel3-parcel4+parcel5-parcel6+parcel7-parcel8);
 
} ;

//Argumentos complexos
complex<double> digamma(complex<double> z){

  //Constante
  const complex<double> hum(1.0, 0.0);


  //Caso base
  if(z.real<6.0) return digamma(z+hum)-z.inv();

  //Caso geral
  complex<double>  log_z(std::log(z.norm()), z.polar());
  complex<double> coefficient;
  complex<double> parcel1, parcel2, parcel3, parcel4, parcel5, parcel6, parcel7, parcel8;
  complex<double> result=log_z;


  //Procedimento
    //Computando a expansão em séries de potências
    //1
    coefficient.real= (1.0/2.0); coefficient.imag=0.0; 
    result= result-(coefficient*(z.pow(1)).inv());

    //2
    coefficient.real= (1.0/12.0); coefficient.imag=0.0; 
    result= result-(coefficient*(z.pow(2)).inv());

    //3
    coefficient.real= (1.0/120.0); coefficient.imag=0.0; 
    result= result+(coefficient*(z.pow(4)).inv());

    //4
    coefficient.real= (1.0/252.0); coefficient.imag=0.0; 
    result= result-(coefficient*(z.pow(6)).inv());

    //5
    coefficient.real= (1.0/240); coefficient.imag=0.0; 
    result= result+(coefficient*(z.pow(8)).inv());

    //6
    coefficient.real= (1.0/132.0); coefficient.imag=0.0; 
    result= result-(coefficient*(z.pow(10)).inv());

    //7
    coefficient.real= (691.0/32760.0); coefficient.imag=0.0; 
    result= result+(coefficient*(z.pow(12)).inv());

    //8
    coefficient.real= (1.0/12.0); coefficient.imag=0.0; 
    result= result-(coefficient*(z.pow(14)).inv());

  //Resultado
  return result;

};

//**************************************************************************************************************************
//APROXIMANDO AO VALOR DA CONSTANTE DE EULER MASCHERONI
double euler_mascheroni_approximation(uint64_t n){

  //Restrição a valores grandes de n
  assert(n>=100000);

  //Procedimento
  return harmonic_number(n)-log(n);

};


//**************************************************************************************************************************
//FIM DO HEADER
#endif
