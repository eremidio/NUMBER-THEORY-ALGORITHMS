//VAMOS CRIAR UM PROGRAMA PARA COMPUTAR O NÚMERO DE CLASSE DE CORPOS QUADRÁTICOS IMAGINÁRIOS USANDO FÓRMULAS ANÁLITICAS


/*
O NÚMERO DE CLASSE DE CORPOS QUADRÁTICOS IMAGINÁRIOS PODE SER COMPUTADO ANALITICAMENTE PARA CORPOS QUADRÁTICOS 
IMAGINÁRIOS CUJO DISCRIMINANTE É FUNDAMENTAL USANDO-SE A SEGUINTE FÓRMULA ANÁLITICA:
h(D) = Σ(D|n){erfc(n√(π/D))+ (1/nπ)e^(-πn²/|D|)}; erfc(x) DENOTA A FUNÇÃO DE ERRO COMPLEMENTAR E (|) DENOTA O
SÍMBOLO DE KRONECKER, A SOMA É FEITA SOBREVALORES DE n=1,2,..., |_√|D|ln|D|/(2π)_|


TAL FÓRMULA FUNCIONA PARA DISCRIMINANTES DA ORDEM DE 10^15. PARA CORPOS QUADRÁTICOS REAIS EXISTE UMA FÓRMULA
SIMILAR ENVOLVENDO A FUNÇÃO EXPONENCIAL INTEGRAL Ei(x). 


PARA MAIORES INFORMAÇÕES: A Course In Computational Algebraic Number Theory by Henri Cohen

*/


//*********************************************************************************************
//CABEÇALHO
#ifndef CLASS_NUMBER_ANALYTICAL_FORMULAE_H
#define CLASS_NUMBER_ANALYTICAL_FORMULAE_H
#include"complementary_error_function.h"
#include"class_number.h"
#include<assert.h>
#include<stdio.h>


//*********************************************************************************************
//DECLARAÇÃO
int64_t class_number_analytical(int64_t);

//*********************************************************************************************
//FUNÇÕES
int64_t class_number_analytical(int64_t d){
  
  //Restrição
  assert(d<0);
  int64_t D=(-d);//Valor absoluto do discriminante
  if(is_fundamental_discriminant(d)==false) return (-1);//Não se aplica


  //Variáveis locais
  const long double pi=4.0*atan(1.0);
  const long double c0=sqrt(pi/D);
  const long double c1=sqrt(D);

  long double power, arg1, arg2, partial;
  long double sum=0.0;
  int64_t bound=floor(sqrt((D*log(D)/(2*pi))));


  //Procedimento
    //Calculando os termos da soma
    for(int64_t i=1; i<=bound; ++i){

      int k=kronecker(D, i);
      if(k==0) continue;
  
      arg1=i*c0; 
      arg2=c1/(pi*i);
      power=(pi*i*i)/D;

      sum=sum+k*(complementary_error_function(arg1)+ arg2/exp(power));

    }
  

  //Resultado
  return round(sum);


}



//*********************************************************************************************
//FIM DO HEADER
#endif
