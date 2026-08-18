//VAMOS CRIAR UM PROGRAMA QUE COMPUTA INVERSOS MODULARES DE UM CONJUNTO DE INTEIROS A MENOS DE UMA RELAÇÃO DE CONGRUÊNCIA

/*

  SUBROTINA ÚTIL QUANDO MÚLTIPLAS INVERSÕES MODULARES SÃO NECESSÁRIAS EM UM DETERMINADO ALGORITMO. NO LUGAR DE PERFORMAR O ALGORITMO
  ESTENDIDO DE EUCLIDES PARA CADA CICLO DE EXECUÇÃO DO ALGORITMO, PARA MÚLTIPLOS CICLOS O PRESENTE ALGORITMO PERMITE EXECUTAR A
  OPERAÇÃO DE INVERSÃO MÓDULO UM INTEIRO EM Z/nZ PARA UM CONJUNTO DE VALORES OU RETORNAR UM FATOR NÃO TRIVIAL DE n CASO ELE SEJA
  COMPOSTO.

  PARA MAIORES INFORMAÇÕES: A Course In Computational Algebraic Number Theory by Henri Cohen

*/


//*****************************************************************************************************************************************
//CABEÇALHO
#ifndef PARALLEL_MODULAR_INVERSE_H
#define PARALLEL_MODULAR_INVERSE_H
#include<stdint.h>
#include<stdlib.h>
#include<inttypes.h>
#include<stdbool.h>
#include<stdio.h>


//*****************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void extended_euclidean_algorithm(int64_t, int64_t, int64_t*, int64_t*, int64_t*);
int64_t gcd_s64(int64_t, int64_t);
bool parallel_modular_inverse(int64_t[], int64_t[], int64_t[], size_t, int64_t*, int64_t);


//*****************************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides estendido
void extended_euclidean_algorithm(int64_t a, int64_t b, int64_t* u, int64_t* v, int64_t* gcd){

  //Variáveis locais
  int64_t r0,r1, x0, x1, y0, y1, r2, x2, y2;

  //Procedimentos 
    //Ajuste de variáveis
    r0=a;
    r1=b;
    r2=1;
    x0=1;
    x1=0;
    y0=0;
    y1=1;

    //Calculando os valores finais coeficientes recursivamente
    while(r2>0){
      int64_t quotient= r0/r1;
      r2=r0-quotient*r1;
      x2=x0-quotient*x1;
      y2=y0-quotient*y1;

      //Atualizando variáveis para a próxima iteração
      if(r2>0){
        r0=r1; r1=r2;
        x0=x1; x1=x2;
        y0=y1; y1=y2;
      };

    };

  //Resultado
  (*gcd)=r1;
  (*u)=x1;
  (*v)=y1;

};


//Função que implementa o algoritmo de Euclides para inteiros de 64 bits
int64_t gcd_s64(int64_t a, int64_t b){

  if(b==0) return a;
  else return gcd_s64(b, (a%b));

};


//Função que calcula o innverso modular de um conjunto de valores módulo inteiro ou um fator não trivial do inteiro congruente
bool parallel_modular_inverse(int64_t a[],  int64_t b[], int64_t c[], size_t set_size, int64_t* factor, int64_t N){


  //Variáveis locais
  int64_t u=0, v=0, d=0, f=1;
  bool result=true;


  //Procedimento
    //Preenchendo o array de produtos de classes residuais módulo N
    c[0]=a[0];
    
    for(size_t i=1; i<set_size; ++i){
      __int128_t t=((__int128_t)a[i]*c[i-1])%N;
      c[i]=(int64_t)t;
    };

    //Checando se o conjunto de {a(0); ...; a(k-1)} contém um fator não trivial de N 
    extended_euclidean_algorithm(c[set_size-1], N, &u, &v, &d);


    if(d>1 && d<N){//As classes residuais módulo N contém um fator não trivial de N
      (*factor)=d;
      result=false;
    }

    if(d==N){//O produto das classes residuais em Z/nZ contém um fator não trivial de N

      for(size_t j=0; j<set_size; ++j){
        f=gcd_s64(N, c[j]);
        if(f>1){
          (*factor)=f;
          result=false;
          break;
        }
      }

    }


    //Cálculando os inversos modulares 
    if(result){

      for(size_t k=(set_size-1); k>0; --k){
        __int128_t t=((__int128_t)u*c[k-1])%N;      
        if(t<0) t+=N;
        b[k]=(int64_t)t; 
        t=((__int128_t)u*a[k])%N; u=t;
      }

    }    

    if(u<0) u+=N;
    b[0]=u;


  //Resultado
  return result;

};


//*****************************************************************************************************************************************
//FIM DO HEADER
#endif
