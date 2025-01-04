//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE CONNARCCHIA PARA RESOLVER A EQUAÇÃO DE PELL 

/*
O ALGORITMO DE CONNARTCHIA É UM ALGORITMO USADO PARA RESOLVER EQUAÇÕES DIOFANTINAS DO TIPO x²+dy²=m, COM m E d INTEIROS TAIS QUE mmc(m, d)=1.
O ALGORITMO USA APENAS RELAÇÕES DE CONGRUÊNCIA PARA DETERMINAR VALORES INTEIROS DE x E y.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Cornacchia%27s_algorithm#References
*/

//*********************************************************************************************************************************
//CABEÇALHO
#ifndef CONNARCCHIA_ALGORITHM_H
#define CONNARCCHIA_ALGORITHM_H
#include<stdint.h>
#include<stdbool.h>
#include<math.h>
#include<stdio.h>

//*********************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void connarchia_algorithm(int64_t, int64_t, int64_t*, int64_t*);

//*********************************************************************************************************************************
//FUNÇÕES
void connarchia_algorithm(int64_t d, int64_t m, int64_t* x, int64_t* y){


  //Variáveis locais
  int64_t r0=(-1), r1, r2, s;
  int64_t i=0, trial=0;


  //Procedimentos
    //Etapa 1: encontrando um valor de r0 tal que r0²=-d (mod m)
    restart:
    trial++;
    if(trial>10000) return;

    for(; i<=m; i++){
      if((((i*i)+d)%m==0)){
        r0=i;
        break;
      };
    };


  //Etapa 2: iterando sobre valores de r até obter r<m^(1/2)
    //1ª iteração:
    r1=(m%r0);


    //Condição que encerra o loop
    if((r1*r1)<m){
      r2=r1;
      goto stage3;
   };

    //Demais iterações
    while(true){
      r2=(r0%r1);

      //Condição que encerra o loop
      if((r2*r2)<m) break;

      //Atualizando variáveis para a próxima iteração
      r0=r1;
      r1=r2;
    };

    //Etapa 3: cálculo de s
    stage3:
    s=sqrt((m-(r2*r2))/d);
    if(floor(s)==ceil(s) && ((r2*r2)+d*(s*s))==m){
      *x=r2;
      *y=s;
      return;
    }
    else{
      ++i;
      goto restart;
    };

};


//*********************************************************************************************************************************
//FIM DO HEADER
#endif
