//VAMOS CRIAR UM PROGRAMA QUE COMPUTA LIMITANTES PARA O NÚMERO DE CLASSE DE CORPOS ALGÉBRICOS QUADRÁTICOS IMAGINÁRIOS

/*

PARA CORPOS ALGÉBRICOS QUADRÁTICOS IMAGINÁRIOS EXISTEM UMA SÉRIE DE ESTIMATIVAS HEURÍSTICAS SOBRE O COMPORTAMENTO DO GRUPO DE CLASSE DE IDEAIS cl(D)
E CONSEQUENTEMENTE DO NÚMERO DE CLASSE h(D). TAIS ESTIMATIVAS PODEM SER USADAS PARA DETERMINAR h(D) COM RELATIVA PRECISÃO.

DE ACORDO COM O CHAMADO TEOREMA DE BRAUER-SIEGEL ln(h(D))~ln(√|D|), ISTO DEFINE QUE ASSINTOTICAMENTE h(D))~O(√|D|), h(D) É LIMITADO POR |D|^(1/2+ε)
E |D|^(1/2-ε). UM RESULTADO DEVIDO A GROSS E ZAGIER ESTABELECE O SEGUINTE LIMITANTE INFERIOR PARA h(D): h(D)>[1/K] Π(1-{2√p/p+1})ln(√|D|), ONDE K=55
SE mdc(5077, |D|)=1 E K=7000 CASO CONTRÁRIO, O PRODUTO É TOMADO SOBRE TODOS OS PRIMOS QUE DIVIDEM D EXCETO O MAIOR. UM LIMITANTE SUPERIOR DO VALOR
CORRETO É DADO POR h(D)<{1/π}(√|D|)ln(|D|).

A SEGUINTE FÓRMULA PODE SER APLICADA AO SOMATÓRIO DE NÚMEROS DE CLASSE PARA VALORES DE D TAIS |D|≲x Σh(D)={x^(3/2)C/3π}, ONDE C É UMA CONSTANTE DADA
POR C=Π(1-1/{p²(p+1)}) COM O PRODUTÓRIO EXTENDIDO SOBRE TODOS OS PRIMOS p, C≃0.881538397... COMO O NÚMERO DE DISCRIMINANTES FUNDAMENTAIS ATÉ UM DADO
VALOR x É DA ORDEM DE (3/π²)x TEM-SE QUE NO GERAL h(D)~(Cπ/6)√|D|≃0.461559√|D| ISTO MOSTRA QUE O LIMITANTE SUPERIOR ESTABELECIDO ANTEIORMENTE DIFERE
POR NO MÁXIMO O(ln(|D|)) DO VALOR CORRETO.

LENSTRA E COHEN ESTABELECERAM UMA SÉRIE DE CONJECTURA SOBRE PROPRIEDADES ARITMÉTICAS DE h(D) COMO SUA DIVISIBILIDADE POR PEQUENOS PRIMOS, ENTRE
OUTRAS BASEADO NA HIPÓTESE QUE OS GRUPOS DE CLASSE SE COMPORTAM COMO GRUPOS ALEATÓRIOS. CONJECTURAS DESTA NATUREZA E ESTIMATIVAS PARA CORPOS
ALGÉBRICOS QUADRÁTICOS REAIS SÃO MAIS COMPLICADAS DE SEREM FEITAS DEVIDO A DIFICULDADE EM SE COMPUTAR O REGULADOR R(D) DEVIDO A EXISTÊNCIA DE
UNIDADES FUNDAMENTAIS NÃO TRIVIAIS.


PARA MAIORES INFORMAÇÕES: Introduction to Modern Number Theory, by Yuri I. Manin and Alexei A. Panchishkin
                          A Course In Computational Algebraic Number Theory by Henri Cohen


*/


//*******************************************************************************************************************************
//CABEÇALHO
#ifndef CLASS_NUMBER6_H
#define CLASS_NUMBER6_H
#include"factorization_map.h"
#include"class_number.h"


//CONSTANTES GLOBAIS
const double CLASS_NUMBER_PRIME_CONSTANT1=0.88151383972536;
const double CLASS_NUMBER_PRIME_CONSTANT2=0.46155956715315355;
const double PI_CLASS_NUMBER=4.0*atan(1.0);


//*******************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t gross_zagier_lower_bound(int64_t);
int64_t summation_upper_bound(int64_t);
int64_t summation_approximation(int64_t);


//*******************************************************************************************************************************
//FUNÇÕES
//Função que computa um limitante inferior para o número de classe h(-D) para um discriminante fundamental D
int64_t gross_zagier_lower_bound(int64_t D){

  //Variáveis locais
  uint64_t primes[30];
  int multiplicities[30];
  int64_t K=(D%5077)==0?7000:55;
  double product=1.0, parcel=0.0;
  double lnD=log(D);
  

  //Procedimentos
    //Fatorando D
    for(int i=0; i<30; ++i){
      primes[i]=1;
      multiplicities[i]=0;
    };//Ajuste de variáveis
  
    factorization_map(D, primes, multiplicities);

    //Calculando o limitante inferior para o número de classe
    for(int i=0; i<30; ++i){

      if(primes[i+1]==1) break; //Excluindo o maior fator primo de |D|
      double p=primes[i];
      parcel=lnD*(1-((2.0*sqrt(p))/(p+1)));
      product*=parcel;

    }

    
  //Resultado
  int64_t result=round(product/K);
  return result;
  
};


//Função que computa um limitante superior para h(-D) para um discriminante fundamental D
int64_t summation_upper_bound(int64_t D){

  //Variáveis locais
  double lnD=log(D);
  double sqrt_D=sqrt(D);

  
  //Resultado
  return round((lnD*sqrt_D)/PI_CLASS_NUMBER);

};


//Função que computa uma aproximação para h(-D) para um discriminante fundamental D
int64_t summation_approximation(int64_t D){

  //Variáveis locais
  double sqrt_D=sqrt(D);

  
  //Resultado
  return round(sqrt_D*CLASS_NUMBER_PRIME_CONSTANT2);

};

//*******************************************************************************************************************************
//FIM DO HEADER 
#endif
