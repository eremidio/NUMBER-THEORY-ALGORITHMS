//VAMOS CRIAR UM PROGRAMA QUE COMPUTA O NÚMERO DE CLASSE PARA CORPOS ALGÉBRICOS QUADRÁTICOS USANDO A FÓRMULA DO NÚMERO DE CLASSE

/*

EM UM CORPO ALGÉBRICO NUMÉRICO AS UNIDADES (ELEMENTOS DE NORMA 1) FORMAM UM GRUPO EM RELAÇÃO A OPERAÇÃO
DE MULTIPLICAÇÃO. GERADORES DESTE GRUPO SÃO DENOMINADOS UNIDADES FUNDAMENTAIS, O NÚMERO DE GERADORES
PODE SER COMPUTADO EM TERMOS DO NÚMEROS DE IMERSÕES DO CORPO ALGÉBRICO CONSIDERADO NO CONJUNTO DOS REAIS
E COMPLEXOS. UNIDADES FUNDAMENTAIS SÃO DIRETAMENTE RELACIONADOS AO REGULADOR DE UM CORPO ALGÉBRICO
NÚMERICO.

CORPOS ALGÉBRICOS QUADRÁTICOS IMAGINÁRIOS NÃO POSSUEM UNIDADES FUNDAMENTAIS. CORPOS QUADRÁTICOS REAIS
E CORPOS CÚBICOS POSSUEM APENAS UMA UNIDADE FUNDAMENTAL.

COMPUTAR UNIDADES FUNDAMENTAIS PARA CORPOS ALGÉBRICOS NÚMERICOS NOS CASOS GERAIS É COMPLICADO. MAS NO CASO
DE CORPOS ALGÉBRICOS QUADRÁTICOS REAIS Q(√d) COM d>0, A UNIDADE FUNDAMENTAL É DADA POR η=(1/2)(T+U√d), ONDE
T E U SÃO SOLUÇÕES DA EQUAÇÃO T²-dU²= ∓4.


PODEMOS USAR TAIS FATOS PARA COMPUTAR NÚMEROS DE CLASSES h(d) EM CORPOS ALGÉBRICOS QUADRÁTICOS REAIS PARA
PEQUENOS VALORES DE d USANDO A FÓRMULA DE NÚMERO DE CLASSE QUE NESSE CONTEXTO ASSUME UMA FORMA SIMPLES EM
TERMOS DE SÍMBOLOS DE KRONECKER DE ELMENTOS EM GF(d) PARA OS QUAIS ELE É DEFINIDO.


PARA MAIORES INFORMAÇÕES: https://mathworld.wolfram.com/ClassNumber.html
                          https://mathworld.wolfram.com/FundamentalUnit.html
                          https://mathworld.wolfram.com/Regulator.html

*/


//***********************************************************************************************************
//CABEÇALHO
#ifndef CLASS_NUMBER_FORMULA_REAL_QUADRATIC_FIELD_H
#define CLASS_NUMBER_FORMULA_REAL_QUADRATIC_FIELD_H
#include"kronecker_symbol.h"
#include"fast_perfect_square_detection.h"
#include<math.h>

//CONSTANTES GLOBAIS
const double pi=4.0*atan(1.0);
const uint64_t MAX_TU=1E9;

//***********************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void compute_fundamental_unit(int64_t*, int64_t*, int64_t);
int64_t class_number_formula_positive_discriminant(int64_t);


//***********************************************************************************************************
//FUNÇÕES
//Função que computa uma unidade fundamental em um corpo quadrático real η=(1/2)(T+U√d) por força bruta
void compute_fundamental_unit(int64_t* T, int64_t* U, int64_t d){

  //Variáveis locais
  int64_t T_, U_, T_squared;
  
  //Procedimento
    //Restrição: d não deve ser quadrado perfeito
    if(perfect_square_detection_64bits(d, &T_))
      return;  

    //Loop principal
    for(U_=1; U_<MAX_TU; ++U_){
      //Loop 1: iterando sobre soluções de T²-DU=(-4)
      T_squared=(d*U_*U_)-4;
      if(T_squared>0 && perfect_square_detection_64bits(T_squared, &T_)){
        (*T)=T_; (*U)=U_;
        return;
      }
      //Loop 2: iterando sobre soluções de T²-DU=4
      T_squared=(d*U_*U_)+4;
      if(T_squared>0 && perfect_square_detection_64bits(T_squared, &T_)){
        (*T)=T_; (*U)=U_;
        return;
      }
    }

    //Resultado em caso de falha
    (*T)=0; (*U)=0;

};


//Função que computa o número de classe de um corpo algébrico quadrático real
int64_t class_number_formula_positive_discriminant(int64_t d){

  //Restrição: d não deve ser quadrado perfeito
  int64_t root=0;
  if(perfect_square_detection_64bits(d, &root))
    return (-1);  

  //Variáveis locais
  double fundamental_unit, sum=0;
  int64_t T, U;

  
  //Procedimento
    //Computando uma unidade fundamental
    compute_fundamental_unit(&T, &U, d);
    fundamental_unit=0.5*(T+sqrt(d)*U);

    //Loop principal
    for(int64_t r=1; r<d; ++r){
      int k= kronecker(d, r);
      if(k==0) continue;
      else sum=sum+(k*log(sin((pi*r)/d)));
  
    }
    
    //Ajuste fino do resultado
    sum=(sum*(-1))/(2*log(fundamental_unit));
  

  //Resultado
  return round(sum);

};

//***********************************************************************************************************
//FIM DO HEADER
#endif
