//VAMOS CRIAR UM ARQUIVO QUE IMPLEMENTA A ARIMÉTICA EM CURVAS ELÉIPTICAS DEFINIDAS SOBRE CORPOS FINITOS DO PRIMEIRO TIPO

/*
PONTOS EM CURVAS ELÍPTICAS FORMAM UM GRUPO ABELIANO COM RESPEITO A OPERAÇÃO DE ADIÇÃO PONTOS NA CURVA QUE ASSOCIA A UM PAR DE PONTOS (P, Q)
UM TERCEIRO PONTO R NA CURVA. 

VÁRIOS SISTEMAS DE COORDENADAS E PARAMETRIZAÇÕES DE CURVAS ELÍPTICAS SÃO USADAS, COMO AS PARAMETRIZAÇÕES DE WEIERSTRASS, EDWARDS, QRT, LYNESS
E MONTGOMERY. PARA CADA UMA DESSAS PARAMETRIZAÇÕES HÁ UMA FORMA FUNCIONAL DA EQUAÇÃO DESCREVENDO A CURVA. POR EXEMPLO, NA PARAMETRIZAÇÃO DE
EDWARDS A EQUAÇÃO QUE DESCREVE A CURVA ELÍPTICA POSSUI A FORMA x²+y²=1+dx²y², NA FORMA REDUZIDA DE WEIERSTRASS y²=x³+ax+b. CADA PARAMETRIZAÇÃO
ENVOLVE UM CONJUNTO DE PARÂMETROS DIFERENTES. PARA CADA PARAMETRIZÇÃO HÁ UM CONJUNTO DE REGRAS QUE DEFINE A OPERAÇÃO GEOMÉTRICA DE ADIÇÃO DE
PONTOS NA CURVA.

DE GRANDE INTERESSE PARA APLICAÇÕES É O ESTUDO DE CURVAS ELÍPTICAS DEFINIDAS SOBRE CORPOS FINITOS DO PRIMEIRO TIPO F(p). INTEIROS A MENOS DE
UMA CONGRUÊNCIA QUE FORMAM UM GRUPO Z/Zp COM RELAÇÃO A OPERAÇÃO DE MULTIPLICAÇÃO. EM ALGUNS CASOS COMO NO ALGORITMO DE SCHOOF CURVAS ELÍPTICAS
SOBRE CORPOS NÚMERICOS DE ORDEM SUPERIOR F(p^k) SÃO CONSIDERADAS.

NESTE PROGRAMA USAREMOS A REPRESENTAÇÃO REDUZIDA DE WEIERSTRASS y²=x³+ax+b (mod p), CUJA ARITMÉTICA É DEFINIDA PELAS REGRAS EM COORDENADAS
AFINS (x, y, z=1):
P=(xp, yp) ; Q=(xq, yq); R=(xr, yr).

1. s=(yq -yp)(xq-xp)⁻¹, SE xq≠xp
2. s=(3xp²+a)(2yp)⁻¹, SE xq=xp
3. xr=s²-xp-xq
4. yr=yp-s(xp-xr)
5. O=(0,1,0)/O=(0,-1,0) (PONTO NO INFINITO).
6. P+O=Q+O=O.

NAS FÓRMULAS ACIMA TODAS OPERAÇÕES SÃO PERFORMADAS MÓDULO p E OS INVERSOS SÃO COMPUTADOS COMO INVERSOS MULTIPLICATIVOS MÓDULO p QUE PODE SER
COIMPUTADO VIA ALGORITMO EXTENDIDO DE EUCLIDES.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Elliptic_curve#Elliptic_curves_over_the_real_numbers
                          https://en.wikipedia.org/wiki/Edwards_curve
                          Prime Numbers. A Computational Perspective by R.Crandall & Carl B. Pomerance


*/


//*********************************************************************************************************************************************************
//CABEÇALHO
#ifndef ELLIPTIC_CURVE_ARITHMETIC_AFFINE_COORDINATES_H
#define ELLIPTIC_CURVE_ARITHMETIC_AFFINE_COORDINATES_H
#include<stdint.h>
#include<random>
#include<type_traits>
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/cstdint.hpp>
#include<iostream>
using namespace boost::multiprecision;


//*********************************************************************************************************************************************************
//ESTRUTURAS USADA NOS ALGORITMOS
/* 
Usaremos duas estruturas nos algoritmos uma curva elíptica sobre um corpo fínito do primeiro tipo y²=x³+ax+b (mod p) será
representada pela tripla de parâmetros E=(a,b,p), um ponto na curva será representado pela tripla P=(x,y,z) para curvas
afins z=1. É possível usar tipos inteiros da biblioteca de precisão múltipla Boost para evitar overflow durante os cálculos quando
necessário.
*/


//Curva elíptica
template<typename T>
struct elliptic_curve{
  T a;//Parâmetro da curva
  T b;//Parâmetro da curva
  T p;//Primo correspondendo a caraterística sobre o qual a curva elíptica é definida
};

template<typename T>
struct elliptic_curve_point{//Ponto no  infinito O(0,1,0) ou O(0,-1,0)
  T x;//Coordenada afim
  T y;//Coordenada afim
  T z;//Coordenada afim


  //Construtores
  elliptic_curve_point(){ };

  elliptic_curve_point(T a, T b){
    x=a; y=b; z=1;
  }; 

  elliptic_curve_point(T a, T b, T c){
    x=a; y=b; z=c;
  }; 

  //Métodos
  bool is_infinite(){
    if(z==0) return true;
    else return false;
  }

  bool is_affine(){
    if(z==1) return true;
    else return false;
  }

};


//*********************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
T modular_inverse(T, T, T&);

template<typename T>
struct elliptic_curve_point<T> point_negation(struct elliptic_curve_point<T>);
template<typename T>
struct elliptic_curve_point<T> point_addition(struct elliptic_curve_point<T>, struct elliptic_curve_point<T>, struct elliptic_curve<T>);
template<typename T>
struct elliptic_curve_point<T> point_doubling(struct elliptic_curve_point<T>, struct elliptic_curve<T>);
template<typename T>
struct elliptic_curve_point<T> point_subtraction(struct elliptic_curve_point<T>, struct elliptic_curve_point<T>, struct elliptic_curve<T>);
template<typename T>
struct elliptic_curve_point<T> point_scalar_multiplication(struct elliptic_curve_point<T>, struct elliptic_curve<T>, T);


//*********************************************************************************************************************************************************
//FUNÇÕES
//Funções auxiliares: cálculo de inverso modular via algoritmo de Euclides
template<typename T>
T modular_inverse(T a, T n, T& gcd){

  //Variáveis locais
  T r0,r1, x0, x1, r2, x2;

  //Procedimentos 
    //Ajuste de variáveis
    r0=a;
    r1=n;
    r2=1;
    x0=1;
    x1=0;

    //Calculando os valores finais coeficientes recursivamente
    while(r2>0){
      T quotient= r0/r1;
  
      r2=r0-quotient*r1;
      x2=x0-quotient*x1;

      //Atualizando variáveis para a próxima iteração
      if(r2>0){
       r0=r1; r1=r2;
       x0=x1; x1=x2;
              };
    };

  //Resultado
  gcd=r1;//MDC

  if(x1<0)
    return(x1+n);
  else
    return x1;

};

//*************FUNÇÕES QUE DEFINEM ARITMÉTICA EM CURVAS ELÍPTICAS**************//
//Função que inverte um ponto em uma curva elíptica
template<typename T>
struct elliptic_curve_point<T> point_negation(struct elliptic_curve_point<T> point1){

  //Variáveis locais
  struct elliptic_curve_point<T> result={point1.x, point1.y*(-1),point1.z};

  //Resultado
  return result;

};

//Função que adiciona dois pontos em uma curva elíptica: P+Q->R
template<typename T>
struct elliptic_curve_point<T> point_addition(struct elliptic_curve_point<T> point1, struct elliptic_curve_point<T> point2, struct elliptic_curve<T> e_curve){

  //Variáveis locais
  struct elliptic_curve_point<T> result;
  T gcd, slope;

  //Procedimentos
    //Caso base: um dos pontos em questão é um ponto no infinito
    if(point1.is_infinite()==true){
      result=point2;
      return result;
  
    }

    if(point2.is_infinite()==true){
      result=point1;
      return result;
  
    }

    //Caso 1: x1=x2
    if(point1.x==point2.x){

      //Caso 1.1: pontos simétricos y1=(-y2)
      if((point1.y+point2.y)==0 || (point1.y+point2.y+e_curve.p)==0){
        result={0,1,0};//O-> ponto no infinito
        return result;
      }

      //Caso 1.2: pontos não simétricos em relação ao eixo y
      slope=(3*point1.x)%e_curve.p; slope=(slope*point1.x)%e_curve.p;
      slope=(slope+e_curve.a)%e_curve.p;
      slope=(slope*modular_inverse<T>((2*point1.y), e_curve.p, gcd))%e_curve.p;
      if(gcd>1){
        result={0,1,0};//O-> ponto no infinito
        return result;
      }
      else goto set_coordinates;

    }

    //Caso 2: x1≠x2
    slope=((point2.y-point1.y)*modular_inverse<T>((point2.x-point1.x), e_curve.p, gcd))%e_curve.p;
  
    //Calculando as coordenadas do ponto em questão
    set_coordinates:
      result.z=1;
      result.x=(((slope*slope)%e_curve.p)-point1.x-point2.x)%e_curve.p;
      result.y=((slope*(point1.x-point2.x))-point1.y)%e_curve.p;


  //Resultado
  return result;

};


//Função que duplica um ponto na curva elíptica P->[2]P
template<typename T>
struct elliptic_curve_point<T> point_doubling(struct elliptic_curve_point<T> point1, struct elliptic_curve<T> e_curve){

  //Variáveis locais
  struct elliptic_curve_point<T> result=point_addition<T>(point1, point1, e_curve);

  //Resultado
  return result;

};

//Função que calcula a diferença de dois pontos
template<typename T>
struct elliptic_curve_point<T> point_subtraction(struct elliptic_curve_point<T> point1, struct elliptic_curve_point<T> point2, struct elliptic_curve<T> e_curve){

  //Variáveis locais
  struct elliptic_curve_point<T> p2_neg=point_negation<T>(point2);
  struct elliptic_curve_point<T> result=point_addition<T>(point1, p2_neg, e_curve);

  //Resultado
  return result;

};


//Função que calcula um múltiplo escalar de um ponto na curva elíptica P->[k]P
template<typename T>
struct elliptic_curve_point<T> point_scalar_multiplication(struct elliptic_curve_point<T> point1, struct elliptic_curve<T> e_curve, T scalar){

  //Variáveis locais
  struct elliptic_curve_point<T> result={0,1,0};
  struct elliptic_curve_point<T> adder=point1;

  //Procedimentos
    //Caso base:
    if(scalar==0) return result;


    //Caso geral
    while(scalar>0){
    
      //Checando a paridade dos bits de n
      if((scalar&1)){
        struct elliptic_curve_point<T> temp=point_addition<T>(result, adder, e_curve);
        result=temp;      
      }

      //Atualizando variáveis para a próxima iteração
      scalar>>=1;
      struct elliptic_curve_point<T> temp2=point_doubling<T>(adder, e_curve);    
      adder=temp2;

    }

  //Resultado
  return result;

};


//*********************************************************************************************************************************************************
//FIM DO HEADER
#endif
 
