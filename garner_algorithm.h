//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE GARNER PARA RESOLVER RELAÇÕES DE CONGRUÊNCIAS LINEARES

/*
DADO RELAÇÕES DE CONGRUÊNCIA DO TIPO x= a(i) mod m(i), PARA i= 1,..., n; SE OS CONGRUENTES m(i)'S
FOREM COPRIMOS ENTRE SI, O TEOREMA DO RESTO CHINÊS AFIRMA QUE x É ÚNICO A MENOS DE UMA
CONGRUÊNCIA MÓDULO M= Π[m(i)].

O ALGORITMO DE GARNER USA LISTA PRÉ COMPUTADA DE VALORES INTERMEDIÁRIOS PARA A CALCULAR O VALOR DE
x. ESTE ALGORITMO É EM PARTICULAR ÚTIL QUANDO m(i) PERMANECE FIXO E OS VALORES DE a(i) VARIAM,
NESTA SITUAÇÃO NÃO É NECESSÁRIO FICAR REPETINDO A ETAPA DE PRÉCOMPUTAÇÃO PARA CADA CONJUNTO DE 
VALORES a(i).

PARA MAIORES INFORMAÇÕES: Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance

*/ 

//*******************************************************************************************************
//CABEÇALHO
#ifndef GARNER_ALGORITHM_H
#define GARNER_ALGORITHM_H
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>

//*******************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
__int128_t modular_inverse(__int128_t, __int128_t);
__int128_t garner_algorithm(int64_t[], int64_t[], int);

//*******************************************************************************************************
//FUNÇÕES
// Função que calcula o inverso modular de um número inteiro a (mod n) usando o algoritmo extendido de Euclides
__int128_t modular_inverse(__int128_t a, __int128_t n){
  // Variáveis locais
  __int128_t r0, r1, x0, x1, r2, x2;

  // Procedimentos
    // Ajuste de variáveis
    r0 = a;
    r1 = n;
    r2 = 1;
    x0 = 1;
    x1 = 0;

    // Calculando os valores finais dos coeficientes recursivamente
    while (r2 > 0) {
      __int128_t quotient = r0 / r1;
      r2 = r0 - quotient * r1;
      x2 = x0 - quotient * x1;
  
      // Atualizando variáveis para a próxima iteração
      if (r2 > 0) {
        r0 = r1;
        r1 = r2;
        x0 = x1;
        x1 = x2;
      };
    };

  // Resultado
  if (x1 < 0) return (x1 + n);
  else return x1;

};

//Função que implementa o algoritmo de Garner para resolver sistema de congruências lineares
__int128_t garner_algorithm(int64_t a[], int64_t m[], int r_size){

  //Variáveis locais
  __int128_t* mi_array=NULL;
  __int128_t* ci_array=NULL;
  __int128_t M=1;
  __int128_t n, u;
  int k=0;

  //Procedimentos
    //Ajuste inicial de variáveis
      k++;
      mi_array=(__int128_t*)realloc(mi_array, k*sizeof(__int128_t));
      ci_array=(__int128_t*)realloc(ci_array, k*sizeof(__int128_t));
      mi_array[0]=1;
      ci_array[0]=1;

    //Etapa de précomputação
    for(int i=1; i<r_size; ++i){
      k++;
      mi_array=(__int128_t*)realloc(mi_array, k*sizeof(__int128_t));
      ci_array=(__int128_t*)realloc(ci_array, k*sizeof(__int128_t));
  
      mi_array[i]=1;
      for(int j=0; j<i; j++) mi_array[i] *= m[j];
      ci_array[i]=modular_inverse(mi_array[i], m[i]);

    }
    M=mi_array[r_size-1]*m[r_size-1];
  
  
    //Etapa principal:
    n=a[0];

    for(int j=1; j<r_size; ++j){
      u=((a[j]-n)*ci_array[j])%m[j];
      if (u < 0) u += m[j];
      n=n+(mi_array[j]*u);
      
    }

    //Limpando o cachê de memória
    if(mi_array) free(mi_array);
    if(ci_array) free(ci_array);

  //Resultado
  return (n%M);
  

};

//*******************************************************************************************************
//FIM DO HEADER
#endif
