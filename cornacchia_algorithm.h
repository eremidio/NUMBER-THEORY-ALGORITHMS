//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE CONNARCCHIA PARA RESOLVER A EQUAÇÃO DE PELL 

/*
O ALGORITMO DE CONNARTCHIA É UM ALGORITMO USADO PARA RESOLVER EQUAÇÕES DIOFANTINAS DO TIPO
x²+dy²=m, COM m E d INTEIROS TAIS QUE mmc(m, d)=1.
O ALGORITMO USA APENAS RELAÇÕES DE CONGRUÊNCIA PARA DETERMINAR VALORES INTEIROS DE x E y.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Cornacchia%27s_algorithm#References
*/

//*********************************************************************************************************************************
//CABEÇALHO
#ifndef CORNACCHIA_ALGORITHM_H
#define CORNACCHIA_ALGORITHM_H
#include<math.h>
#include"tonelli_shanks.h"
#include"binary_jacobi_symbol.h"
#include"prime_power_detection.h"

//*********************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void cornacchia_algorithm(int64_t, int64_t, int64_t*, int64_t*);

//*********************************************************************************************************************************
//FUNÇÕES

//Função que implementa o algoritmo de Cornachia (para m primo)
/*
NOTA: Se não for primo não existe algoritmo eficientes para computar raízes
      quadradas mod m, isto é equivalente ao problema de se fatorar números
      inteiros.
*/
void cornacchia_algorithm(int64_t d, int64_t m, int64_t* x, int64_t* y){


  //Variáveis locais
  int64_t x0=(-1), a, b, l, r, c, d_=(-1)*d;
  int64_t i=0, trial=0;


  //Procedimentos
    //Etapa 1: encontrando um valor de r0 tal que r0²=-d (mod m)
    if(binary_jacobi(d_, m)==(-1)){
      (*x)=0; (*y)=0;
      return;
    };

    while(d_<0) d_+=m;
    x0=tonelli_shanks(d_, m);
    
    if(x0>0 && x0>(m/2) && x0<m) goto  stage2;
    else{
      if(x0>0) x0*=(-1);
      while(x0<m/2) x0+=m;
    }
  
   

    //Etapa 2: loop euclidiano
    stage2:    
      //Ajuste de variáveis
      a=m; b=x0;
      l=floor(sqrt(m));

      //Loop euclideano
      while(b>l){
        r=(a%b);
        a=b; b=r;
      }


    //Etapa 3: cálculo dos resultados
    c=(m-(b*b));
    if(c%d!=0 || fast_square_detection((c/d), &l)==false){
      (*x)=0; (*y)=0;
      return;
    }
    else{
      (*x)=b; (*y)=l;
    }


};


//*********************************************************************************************************************************
//FIM DO HEADER
#endif
