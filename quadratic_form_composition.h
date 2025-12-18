//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE COMPOSIÇÃO DE FORMAS QUADRÁTICA REDUZIDAS PRIMITIVAS POSITIVAS DEFINIDAS

/*

DADO DUAS FORMAS QUADRÁTICAS BINÁRIAS f(x,y)=a1x²+b1xy+c1y² E g(x,y)=a2x²+b2xy+c2y² DE MESMO DETERMINANTE, É POSSÍVEL COMBINÁ-LAS DE MODO A
OBTER UMA NOVA FORMA QUADRÁTICA s(x,y)=a3x²+b3xy+c3y². UMA FORMA QUADRÁTICA É DITA PRIMITIVA SE mdc(a, b, c)=1. A COMPOSIÇÃO DE FORMAS
QUADRÁTICAS PRIMITIVAS É ASSOCIATIVA POSSUI ELEMENTOS INVERSOS DE FORMA QUE O CONJUNTO DE FORMAS QUADRÁTICAS PRMITIVAS DE DISCRIMINANTE
NEGATIVO FORMAM UM GRUPO DENOTADO POR cl(D). NO CASO DE CORPOS ALGÉBRICOS QUADRÁTICOS IMAGINÁRIOS DE DISCRIMINANTE FUNDAMENTAL ESTE GRUPO É
ISOMÓRFICO AO GRUPO DE CLASSES DE IDEAIS (QUOCIENTE DO GRUPO DE IDEAIS FRACIONÁRIOS MÓDULO IDEAIS PRINCIPAIS). PARA FORMAS QUADRÁTICAS DE
DISCRIMINANTE POSITIVO ESTE GRUPO É ISOMÓRFICO AO CHAMADO GRUPO DE CLASSE REDUZIDO.

O ESTUDO DA ESTRUTURA DO GRUPO cl(D) FORNECE INFORMAÇÕES IMPORTANTES SOBRE O GRUPO DE CLASSES DE IDEAIS DE UM CORPO ALGÉBRICO. SENDO h(D) O
NÚMERO DE CLASSE DE UM CORPO ALGÉBRICO, h(D) É EXATAMENTE A ORDEM DO GRUPO cl(D). ALGORITMOS ENVOLVENDO GRUPOS DE CLASSES IDEAIS EM CORPOS
ALGÉBRICOS QUADRÁTICOS USAM A COMPOSIÇÃO DE FORMAS QUADRÁTICAS.

FORMAS QUADRÁTICAS REDUZIDAS QUE SÃO SEU PRÓPRIO INVERSO MULTIPLICATIVO SOB A OPERAÇÃO DE COMPOSIÇÃO DE FORMAS QUADRÁTICAS SÃO CHAMADAS DE
FORMAS AMBÍGUAS. USANDO AS CHAMADAS FORMAS PRIMAS f(p)={p, b, (b²-D)/(4p)} COM b²=D (mod 4p) COM E UM RESULTADO ACERCA DA NATUREZA DE FORMAS
AMBÍGUAS EM cl(D) É POSSÍVEL ELABORAR UM EFICIENTE (DO PONTO DE VISTA TEÓRICO) MÉTODO DE FATORAÇÃO DE NÚMEROS INTEIROS (O ALGORITMO DE
SCHNORR-SEYSEN-LENSTRA UM APRIMORAMENTO EM RELAÇÃO AO ALGORITMO DE SHANKS QUE USA FORMAS AMBÍGUAS). ESTE ALGORITMO EMBORA SEJA
ASSINTOTICAMENTE RÁPIDO E USE UM ESPAÇO POLINOMIAL, ELE NÃO É USADO PARA FINS PRÁTICOS, POIS AS OPERAÇÕES REQUERIDAS ENVOLVENDO FORMAS
QUADRÁTICAS SÃO COMPUTACIONALMENTE DISPENDIOSAS E O ALGORITMO TEM COMPLEXIDADE EXPONENCIAL PARA CERTOS VALORES.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Integer_factorization#Rigorous_running_time
                          https://en.wikipedia.org/wiki/Ideal_class_group
                          A Course In Computational Algebraic Number Theory by Henri Cohen

*/


//**********************************************************************************************************************************************
// CABEÇALHO
#if !defined BINARY_QUADRATIC_FORMS_COMPOSITION_H
#define BINARY_QUADRATIC_FORMS_COMPOSITION_H
#include "quadratic_form_reduction.h"


//**********************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
void extended_euclidean_algorithm(int64_t, int64_t, int64_t*, int64_t*, int64_t*);
struct binary_quadratic_form quadratic_form_composition(struct binary_quadratic_form, struct binary_quadratic_form);


//**********************************************************************************************************************************************
// FUNÇÕES
// Algoritmo extendido de Euclides para computar o mmc de dois inteiros mmc(a,b) e os coeficientes da identidade de Bézout ax+by=mmc(a,b)
void extended_euclidean_algorithm(int64_t a, int64_t b, int64_t* gcd, int64_t* x, int64_t* y) {

  // Variáveis locais
  int64_t x0 = 1, y0 = 0;
  int64_t x1 = 0, y1 = 1;

  // Procedimentos
    //Loop euclidiano
    while (b!=0) {
  
      int64_t q = a / b;
      int64_t r = a % b;
      int64_t xt = x0 - q * x1;
      int64_t yt = y0 - q * y1;

        a = b;  b = r;
        x0 = x1; y0 = y1;
        x1 = xt; y1 = yt;

    };


  // Resultado
  (*gcd) = a;
  (*x) = x0;
  (*y) = y0;

};


//Algoritmo que computa a operação de composição de duas formas quadráticas primitivas de dicriminantes iguais
struct binary_quadratic_form quadratic_form_composition(struct binary_quadratic_form f1, struct binary_quadratic_form f2){

  //Variáveis locais
  int64_t a1, a2, a3, b1, b2, b3, c1, c2, c3;
  int64_t n, s;
  int64_t x2, y1, y2, u, v, d, d1, v1, v2;
  int64_t delta=binary_quadratic_form_discriminant(f1);

  //Procedimentos
    //Ajuste de variáveis
    if(f1.a>f2.a){
      struct binary_quadratic_form t=f1;
      f1=f2; f2=t;
    }

    a1=f1.a; b1=f1.b; c1=f1.c;
    a2=f2.a; b2=f2.b; c2=f2.c;
    s=(b1+b2)/2;
    n=b2-s;

    //Loop euclidiano 1: definição de parâmetros
    if(a2%a1==0){
      y1=0; d=a1;
    }
    else{
      extended_euclidean_algorithm(a1, a2, &d, &u, &v);
      y1=u;
    };

    //Loop euclidiano 2: definição de parâmetros
    if(s%d==0){
      y2=(-1); x2=0; d1=d;
    }
    else{
      extended_euclidean_algorithm(s, d, &d1, &u, &v);
      x2=u; y2=(-v);
    }


    //Cálculo dos resultados da composição das formas
    v1=a1/d1; v2=a2/d1;
    __int128_t r = (((y1*y2)%v1)*n)%v1-(x2*c2)%v1;
    r=(r%v1+v1)%v1;

    b3=b2+((v2*r)<<1);
    a3=v1*v2;
    c3=((b3*b3)-delta)/(4*a3);


  //Resultado
  struct binary_quadratic_form result={a3,b3,c3};
  if(is_reduced(result)==false) result=reduce_quadratic_form(result);
  return result;

};



//******************************************************************************************************************************************************************
// FIM DO HEADER
#endif
