//VAMOS CRIAR UM PROGRAMA PARA COMPUTAR A FUNÇÃO DE MERTENS DE FORMA RECURSIVA

/*

PARA UM INTEIRO n A FUNÇÃO DE MERTENS É DEFINIDA COMO A SOMA M(n)= Σ{μ(i)}, ONDE μ(i) DENOTA A 
FUNÇÃO DE MÖBIUS E i=1,2,...,(n-1), n.

A FUNÇÃO DE MERTENS É DE GRANDE INTERESSE EM TEORIA DOS NÚMEROS, O TEOREMA DE NÚMEROS PRIMOS
QUE ESTABELECE UMA FORMA ASSINTÓTICA PARA A FUNÇÃO π(x) DE CONTAGEM DE NÚMEROS PRIMOS PODE SER 
EXPRESSO EM TERMOS DA FUNÇÃO DE MERTENS M(x) DA SEGUINTE FORMA NO LIMITE: x-> ∞ VALE M(x)/x->0.

A FUNÇÃO DE MERTENS PODE SER COMPUTADA DE FORMA EFICIENTE USANDO VARIANTES DA PENEIRA DE 
ERATÓSTENES PARA COMPUTAR VALORES DE μ(i) EM BLOCOS E USANDO CERTAS RELAÇÕES DE RECORRÊNCIA PARA
REDUZIR OS NÚMEROS DE TERMOS NA SOMA.

VAMOS USAR UMA ABORDAGEM MAIS SIMPLES BASEADOS NA SOMA DE O(n/2) PARCELAS, ALGORITMOS MAIS
ELABORADOS PODEM SER EMPREGADOS PARA REDUZIR AINDA MAIS A COMPLEXIDADE DO CÁLCULO DE M(n).

A FUNÇÃO DE MERTENS PARA UM ARGUMENTO n PODE SER COMPUTADA POR MEIO DA SEGUINTE RELAÇÃO RECURSIVA
M(n)=1-Σ M(n/a) PARA a=2,..., |_n_|. TAL FÓRMULA PODE SER REESCRITA DA SEGUINTE FORMA PARA n≳3
M(n)=-{ΣM(N/(2a+1))} PARA a=2,..., |_(n-1)/2_|.

PARA MAIORES INFORMAÇÕES: Introduction To Analytic Number Theory by Tom M. Apostol
                          https://www.unirioja.es/cu/jvarona/downloads/Benito-Varona-TOMATJ-Mertens.pdf
                          https://arxiv.org/pdf/1612.01394
                          https://arxiv.org/pdf/2101.08773

*/ 


//******************************************************************************************************
//CABEÇALHO
#ifndef MERTENS_FUNCTION_RECURSIVE_H
#define MERTENS_FUNCTION_RECURSIVE_H
#include"mobius_function.h"
#include<stdlib.h>

//CONSTANTES GLOBAIS
const int32_t MERTENS_BOUND=10000;


//******************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t* compute_mertens_array(int64_t);


//******************************************************************************************************
//FUNÇÕES
//Função que computa valores da função de Mertens M(n) em blocos
int64_t* compute_mertens_array(int64_t n){

  //Variáveis locais
  int64_t* mertens_array=(int64_t*)calloc((n+1), sizeof(int64_t)); 
  int small_primes[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
  register int64_t sum, bound;
  

  //Procedimentos
    //Computando valores da função de Mertens até 3x10^5
    mertens_array[0]=0; mertens_array[1]=1; mertens_array[2]=0;
    for(int64_t i=3; i<=MERTENS_BOUND; ++i){
      if(i>=n) break;
      mertens_array[i]=mertens_function(i);
    }
    if(n<=MERTENS_BOUND) return mertens_array;

  
    //Computando os demais elementos usando as relações recursivas
    for(int64_t j=(MERTENS_BOUND+1); j<=n; ++j){
      
      //Descartando números com pequenos fatores primos quadráticos inferiores a 30
      if(j%4==0 || j%9==0 || j%25==0 || j%49==0 || j%121==0 || j%169==0 || j%289==0 || j%361==0 || j%529==0 || j%841==0){
        mertens_array[j]=mertens_array[j-1];
        continue;
      }
      
      //Ajuste de variáveis
      sum=0;
      bound=floor((j-1)/2.0);

      //Loop secundário
      for(int64_t a=1; a<=bound; ++a) sum+=mertens_array[j/((2*a)+1)];
      mertens_array[j]=(-1)*sum;

    };

    
  //Resultado
  return mertens_array;


};

//******************************************************************************************************
//FIM DO HEADER
#endif
