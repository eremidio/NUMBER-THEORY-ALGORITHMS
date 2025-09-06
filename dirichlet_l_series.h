//VAMOS CRIAR UM PROGRAMA QUE COMPUTA SOMAS PARCIAIS DE SÉRIES-L DE DIRICHLET USANDO CARACTÉRES QUADRÁTICOS REAIS (SÍMBOLOS DE KRONECKER)

/*

SÉRIES DE DIRICHLET SÃO SÉRIES INFINITAS DO TIPO Σ a(n)e^{λ(n)s} COM n INTEIRO, ONDE s E a(n) SÃO NÚMEROS COMPLEXOS, QUANDO
λ(n)=ln(n) (LOGARÍTMO NATURAL) TEM-SE AS CHAMADAS SÉRIES-L DE DIRICHLET DO TIPO Σ a(n){n^(-s)}. DE GRANDE INTERESSE TEÓRICO 
SÃO SÉRIES DO TIPO L(s,χ(k))=Σχ(k,n){n^(-s)}, ONDE χ(k,n) DENOTA UM CARACTÉRE DE DIRICHLET MÓDULO k. CASOS PARTICULARES DE
SÉRIES-L DE DIRICHLET INCLUEM A FUNÇÃO ZETA DE RIEMANN ζ(s)=Σ1/{n^s}, A FUNÇÃO LAMBDA DE DIRICHLET λ(s)= Σ1/{(2n+1)^s} = 
= (1-2^s)ζ(s) E A FUNÇÃO BETA DE DIRICHLET β(s)= Σ{(-1)^s}/{(2n+1)^s}, ENTRE OUTRAS.

SÉRIES-L DE DIRICHLET SÃO USADAS COMO FUNÇÕES GERADORAS DE OBJETOS COM FUNÇÕES DE PESO APROPRIADAS a(n). DE PARTICULAR
INTERESSE SÃO MANIPULAÇÕES FORMAIS DE SÉRIES DESTA NATUREZA. NO CASO DE a(n) SER UMA FUNÇÃO MULTIPLICATIVA, POR EXEMPLO, AS
CHAMADAS CONVOLUÇÕES DE DIRICHLET PERMITEM OBTER IDENTIDADES ENTRE FUNÇÕES DESTE TIPO E ASSIM COMPUTAR VALORES NÚMERICOS DE
TAIS FUNÇÕES POR MEIO DE TÉCNICAS SIMILARES AO CRIVO DE ERATÓSTENES. SÉRIES-L DE DIRICHLET POSSUEM CONEXÃO DIRETA COM
FORMAS MODULARES (ADMITINDO REPRESENTAÇÕES EM TERMOS DE SEUS COEFICIENTES NUMA EXPANSÃO EM SÉRIES DE FOURIER) E COM OUTRAS
FUNÇÕES RECORRENTES EM TEORIA ANALÍTICA DE NÚMEROS COMO A FUNÇÃO ZETA DE HURWITZ ζ(s, a)= =Σ1/{(n+a)^s} (EXISTE UMA FÓRMULA
DE EXPANSÃO DE SÉRIES-L EM TERMOS DE ζ(s, a)), ENTRE OUTRAS.

DO PONTO DE VISTA TEÓRICO SÉRIES-L DE DIRICHLET SÃO ÚTEIS NA DEMONSTRAÇÃO DE PROPOSIÇÕES IMPORTANTES COMO O TEOREMA DE
DIRICHLET SOBRE A OCORRÊNCIA DE PRIMOS EM PROGRESSÕES ARIMÉTICAS an+b, COM a, b FIXOS E COPRIMOS ENTRE SI E n=1,2,3,....

PARA CARACTÉRES QUADRÁTICOS REAIS (SÍMBOLOS DE KRONECKER) MUITOS VALORES DE SÉRIES-L PARA s=1 PODEM SER EXPRESSOS EM TERMOS
DE NÚMEROS TRANSCENDENTAIS COMO π. POR EXEMPLO PARA k=(-4) (UM DISCRIMINANTE FUNDAMENTAL) O SÍMBOLO DE KRONECKER É
PERIÓDICO (-4|n)=1 SE n=1 (mod 4) E (-4|n)=(-1) SE n=3 (mod 4), DE MODO QUE OBTEMOS NESTE CASO A SÉRIE DE LEIBNITZ PARA O 
CÁLCULO DE π: (π/4)=1-(1/3)+(1/5)-(1/7)+(1/9)-(1/11)+...

SÉRIES DE DIRICHLET SÃO CASOS PARTICULARES DAS CHAMADAS TRANSFORMADAS DE LAPLACE-STIELTJES E PODEM SER AVALIADAS
NUMERICAMENTE USANDO-SE OS CHAMADOS TRASCENDENTES DE LERCH.

VALORES DE REFERÊNCIA ESTÃO TABELADOS NO ARTIGO: https://arxiv.org/pdf/1008.2547

PARA MAIROES REFERÊNCIAS: https://mathworld.wolfram.com/DirichletSeries.html
                          https://en.m.wikipedia.org/wiki/General_Dirichlet_series
                          https://en.m.wikipedia.org/wiki/Dirichlet_series
                          https://mathworld.wolfram.com/DirichletL-Series.html
                          https://en.m.wikipedia.org/wiki/Dirichlet_L-function
                          https://mathworld.wolfram.com/DirichletStructureConstant.html   
                          https://mathworld.wolfram.com/NumberTheoreticCharacter.html
                          https://en.wikipedia.org/wiki/Dirichlet_character
                          https://en.wikipedia.org/wiki/Hurwitz_zeta_function    
                          https://mathworld.wolfram.com/LerchTranscendent.html
                          https://mathworld.wolfram.com/FreyCurve.html
                          https://mathworld.wolfram.com/LerchTranscendent.html        
                          https://mast.queensu.ca/~murty/L-series.pdf
                          https://mathworld.wolfram.com/Laplace-StieltjesTransform.html
                          https://en.wikipedia.org/wiki/Dirichlet%27s_theorem_on_arithmetic_progressions 

*/


//********************************************************************************************************************************
//CABEÇALHO
#ifndef DIRICHLET_L_SERIES_H
#define DIRICHLET_L_SERIES_H
#include"class_number.h"
#include"kronecker_symbol.h"


//CONSTANTES GLOBAIS
const double DIRICHLET_L_BOUND = 1E-2;
const double DIRICHLET_L_MULTIPLIER = 1000000;
int kronecker_array[10000];


//********************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool is_primitive_dirichlet_series(int32_t);
void fill_kronecker_array(int32_t);
long double compute_l_series(int32_t, double);


//********************************************************************************************************************************
//FUNÇÕES
//Função que determina se uma série-L com respeito a um caractére númerico real é primitiva ou não
bool is_primitive_dirichlet_series(int32_t k){

  if(is_fundamental_discriminant(k)) return true;
  else return false;

};

//Função que pré-computa valores dos símbolos de Kronecker para discriminantes fundamentais
void fill_kronecker_array(int32_t d){

  //Procedimentos
    //Loop principal
    for(int32_t i=0; i<abs(d); ++i){
      int kr=kronecker(d, i);
      kronecker_array[i]=kr;
    }

};

//Função que computa uma aproximação de uma série-L de dirichlet
long double compute_l_series(int32_t k, double s){
  

  //Váriáveis locais  
  long double result = 0.0;
  double parcel=0.0;
  int abs_k=abs(k);
  bool is_primitive_series = is_primitive_dirichlet_series(k);


  //Procedimento
   //Prechendo um buffer de símbolos de Kronecker
    if(is_primitive_series) fill_kronecker_array(k);

    //Aproximando o resultado da soma parcial da série para discriminantes fundamentais
    if(is_primitive_series){

      //Loop principal
      for(int32_t i=1; ; ++i){
        
      
        int kr=kronecker_array[i%k];
        if(kr==0) continue;
        parcel = (DIRICHLET_L_MULTIPLIER*kr)/pow(i, s);
        if(fabs(parcel) <= DIRICHLET_L_BOUND) return (result/DIRICHLET_L_MULTIPLIER);
        result+=parcel;
      }

    };


    //Aproximando o resultado da soma parcial da série até a precisão desejada para discriminantes não-fundamentais
    for(int32_t i=1; ; ++i){

      int kr=kronecker(k, i);
      
      if(kr==0) continue;
      parcel = (DIRICHLET_L_MULTIPLIER*kr)/pow(i, s);
      if(fabs(parcel) <= DIRICHLET_L_BOUND) break;
      result+=parcel;

    }

  //Resultado
  return (result/DIRICHLET_L_MULTIPLIER);

};


//********************************************************************************************************************************
//FIM DO HEADER
#endif
