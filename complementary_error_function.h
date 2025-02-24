//VAMOS CRIAR UM PROGRAMA QUE CALCULA A FUNÇÃO DE ERRO COMPLEMENTAR erfc(x)

/*

A FUNÇÃO DE ERRO COMPLEMENTAR erfc(x) É DEFINIDA COMO A INTEGRAL DEFINIDA DE x ATÉ ∞ DA FUNÇÃO
e^(-t²) A MENOS DE UMA CONSTANTE MULTIPLICATIVA IGUAL A (2/√π). TAL FUNÇÃO PODE SER EXPRESSA
EM TERMOS DE UMA SÉRIE CONVERGENTE E EM TERMOS DE FRAÇÕES CONTINUADAS.

PARA MAIORES INFORMAÇÕES: https://link.springer.com/content/pdf/bbm:978-94-91216-37-4/1 
                          A Course In Computational Algebraic Number Theory by Henri Cohen


*/ 


//***********************************************************************************************
//CABEÇALHO
#ifndef COMPLEMENTARY_ERROR_FUNCTION_H
#define COMPLEMENTARY_ERROR_FUNCTION_H
#include<stdint.h>
#include<math.h>


//CONSTANTES GLOBAIS
#define ERRFC_BOUND 2.0
#define ERRFC_PI_ROOT 1.1283791670955126

//***********************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
long double factorial_float(int64_t);
long double bin_pow_float(long double, int64_t);

long double complementary_error_function_small(long double);
long double complementary_error_function_large(long double);
long double complementary_error_function(long double);



//***********************************************************************************************
//FUNÇÕES 
//Funções auxiliares para computara exponencial e o fatorial como float point numbers
long double factorial_float(int64_t n){
    
  //Caso base 
  if(n<2) return 1.0;

  //Variáveis  locais
  long double result=1.0;

  //Procedimento
    //Loop principal
    while(n>1){
      result=result*n;
      n--;
    };

  //Resultado
  return result;

};


long double bin_pow_float(long double x, int64_t n){

  //Variáveis  locais
  long double result=1, q=x;

  //Procedimento
    //Loop principal
    while(n>0){

      if(n&1) result=result*q;

      q=q*q;
      n>>=1;

    };

  //Resultado
  return result;

};

//Função que computa a função erfc(x) para pequenos valores de x
long double complementary_error_function_small(long double x){

  //Variáveis locais
  long double sum=0.0, partial; 


  //Procedimento
    //Computando a função erfc(x)usando série de potências
    for(int64_t i=0; i<40; i++){
      int64_t e=(2*i)+1;
      partial=bin_pow_float(x, e)/(factorial_float(i)*e);
      if(!(i&1)) sum=sum+partial;
      else sum=sum-partial;

    }

  //Resultado
  return (1-(ERRFC_PI_ROOT*sum));

};


//Função que computa a função erfc(x) para grandes valores de x usando frações continuadas
long double complementary_error_function_large(long double x){

  //Variáveis locais
  long double x2=(2*x*x);
  long double num[16]={x, 2, 12, 30, 56, 90, 132, 182, 240, 306, 380, 462, 552, 650, 752, 870};
  long double den[16]={1+x2, 5+x2, 9+x2, 13+x2, 17+x2, 21+x2, 25+x2, 29+x2, 33+x2, 37+x2, 41+x2, 45+x2, 49+x2, 53+x2, 59+x2, 63+x2};
  long double  partial=num[11]/den[11];



  //Procedimentos
    //Calculando a aproximação da fração continuada de da função erfc(x)
    for(int i=10; i>=0; --i) partial=num[i]/(den[i]-partial);


  //Resultado
  return partial*ERRFC_PI_ROOT*exp((-1)*x*x);
};


//Função que computa a função erfc(x)
long double complementary_error_function(long double x){

  if(x<=ERRFC_BOUND)  return complementary_error_function_small(x);
  else  return complementary_error_function_large(x);

};

//***********************************************************************************************
//FIM DO HEADER
#endif
