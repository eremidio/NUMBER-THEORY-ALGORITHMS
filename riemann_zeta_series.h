//VAMOS CRIAR UM PROGRAMA PARA CALCULAR VALORES APROXIMADOS DAFUNÇÃO ZETA DE RIEMANN ζ(s) PARA ARGUMENTOS REAIS USANDO SÉRIES ASSINTÓTICAS

/*
A FUNÇÃO ZETA DE RIEMANN É A FUNÇÃO MAIS IMPORTANTE EM TEORIA ANÁLITICA DOS NÚMEROS, FUNDAMENTAL EM UMA
SÉRIE DE IDENTIDADES IMPORTANTES. ALÉM DISSO OS ZEROS DA FUNÇÃO ZETA (E SUA EXTENSÃO ANALÍTICA) ENCODAM 
PROPRIEDADES ACERCA DE DISTRIBUIÇÃO DE NÚMEROS PRIMOS NO CONJUNTOS DOS INTEIROS.

PARA MAIORES INFORMAÇÕES: Prime Numbers And Computer Methods For Factorization, by Hans Riesel


*/



//********************************************************************************************************
//CABEÇALHO
#ifndef RIEMANN_ZETA_FUNCTION_SERIES_H
#define RIEMANN_ZETA_FUNCTION_SERIES_H
#include<stdlib.h>
#include<math.h>
#include<assert.h>

//********************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
long double riemann_zeta_asymptotic_series(long double);

//********************************************************************************************************
//FUNÇÕES
//Função que calcula o valor aproximado de ζ(s) usando uma série assintótica semiconvergente
long double riemann_zeta_asymptotic_series(long double s){

  //Restrição
  assert(s>1);

  //Variáveis locais
  const int N=10;
  long double sum=0, partial;

  //Procedimentos
    //Somatório principal
    for(int i =1; i<10; ++i){
      partial=(1.0/pow(i, s));
      sum+=partial;
    }

    //Calculando termos de correção
    partial=(1.0/((s-1)*pow(N, s-1))); sum+=partial;
    partial=0.5/pow(N, s); sum+=partial;
    partial=(s/12.0)*(1.0/pow(N, (s+1))); sum+=partial;
    partial=((s*(s+1)*(s+2))/720.0)*(1.0/pow(N, (s+3))); sum-=partial;
    partial=((s*(s+1)*(s+2)*(s+3)*(s+4))/30240.0)*(1.0/pow(N, (s+5))); sum+=partial;


  //Resultado
  return sum;

};




//********************************************************************************************************
//FIM DO HEADER
#endif
