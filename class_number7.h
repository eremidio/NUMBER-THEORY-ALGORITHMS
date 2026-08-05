//VAMOS CRIAR UM PROGRAMA QUE COMPUTA UNIDADES FUNDAMENTAIS E O NÚMERO DE CLASSE DE CORPOS ALGÉBRICOS QUADRÁTICOS REAIS

/*

PARA CORPOS ALGÉBRICOS QUADRÁTICOS REAIS Q(√D) COM DISCRIMINANTE POSITIVO HÁ UM ISORMORFIRMO ENTRE ELEMENTOS DE Q(√D) E FORMAS QUADRÁTICAS DE
DISCRIMINANTE REDUZIDO (a,b,c) --> f(x, y)=ax²+bxy+cy². UMA FORMA QUADRÁTICA POSITIVA DE DISCRIMINANTE 'D' POSITIVO É REDUZIDA SE A SEGUINTES
DESIGUALDADES FOREM SATISFEITAS |√D -2|a||< b < √D.

SEJA r(a, b) = r, O MENOR INTEIRO TAL QUE r= b (mod 2a);  √D -2|a| < b < √D. SEJA PARA UMA FORMA QUADRÁTICA f=(a, b, c), A TRANSFORMAÇÃO
DEFINIDA PELA RELAÇÃO ρ(a, b, c)=(c, r(-b, c), [(r²(-b, c)-Δ)/(4c)]). EXISTE UM TEOREMA QUE GARANTE QUE APÓS UM NÚMERO FINITO DE PASSOS
A TRANSFORMAÇÃO ρ SEMPRE PRODUZ UMA FORMA QUADRÁTICA REDUZIDA, ALÉM DISSO SE f FOR REDUZIDA PARA QUALQUER n INTEIRO SUFICIENTEMENTE GRANDE
(ρ^n)f TAMBÉM É REDUZIDA. O NÚMERO DE CLASSE h(D) PODE SER IDENTIFICADO COM A ORDEM DO GRUPO DE CICLOS (ÓRBITAS) DE FORMAS QUADRÁTICAS 
REDUZIDAS SOBRE A TRANSFORMAÇÃO ρ (AO CONTRÁRIO DE CORPOS QUADRÁTICOS IMAGINÁRIOS, NO QUAL A CONTAGEM DE FORMAS REDUZIDAS É PERFORMADA DE
FORMA DIRETA).

O NÚMERO DE ORBITAS LEVANDO EM CONTA A TRANSFORMAÇÃO ρ DEFINE O NÚMERO DE CLASSE REDUZIDO h+(Δ) (O GRUPO DE CLASSES DE IDEAIS, REDUZIDO LEVA
EM CONSIDERAÇÃO IMERSÕES DE UM CORPO ALGÉBRICO NO CONJUNTO DOS NÚMEROS REAIS). IDENTIFICANDO AS FORMAS (a, b, c) COM (-a, b, -c) É POSSÍVEL
COMPUTAR O NÚMERO DE CLASSE h(D). O PROCESSO DE ENUMERAÇÃO DE FORMAS QUADRÁTICAS REDUZIDAS É MUITO MAIS LABOROSO PARA Q(√D) SE D>0, POR ESTA
RAZÃO USUALMENTE OUTROS MÉTODOS SÃO PREFERÍVEIS PARA SE COMPUTAR h(D). ESTES MÉTODOS USUALMENTE ENVOLVEM O CÁLCULO DO REGULADOR R(D) COMO
ETAPA PRELIMINAR.

SEJA τ=(-b+√D)/2|a| O INTEIRO ALGÉBRICO ASSOCIADO A FORMA (a,b,c), É POSSÍVEL DEMONSTRAR ESTA FORMA É REDUZIDA SE E SOMENTE o<τ<1 E -σ(τ)>1,
ONDE σ(τ) É A TRANSFORMAÇÃO τ=(-b+√D)/2|a| --> σ(τ) = (b+√D)/2|a| (EQUIVALENTEMENTE σ(a,b,c)=(c,b,a)). AS EXPANSÕES EM FRAÇÕES CONTINUADAS DE
-σ(τ) E τ SÃO O REVERSO UMA DA OUTRA. A AÇÃO DAS TRANSFORMAÇÕES  ρ E ρ⁻¹ CORRESPONDE ÀS EXPANSÕES EM FRAÇÕES CONTINUADAS -σ(τ) E τ, ESSA
ASSOCIAÇÃO PERMITE QUE A UNIDADE FUNDAMENTAL η E O REGULADOR R(D) EM TEMPO O(D^{1/2}). SE R(D)=ln(η) FOR SUFICIENTEMENTE GRANDE É POSSÍVEL
OBTER O VALOR DE h(D) COM RAZOÁVEL CHANCE DE ACERTO POR MEIO DA APROXIMAÇÃO DA SÉRIE-L DE DIRICHLET L(1, χ(D)) (ESTA SÉRIE CONVERGE
LENTAMENTE, PORÉM COMO h(D) É USUALMENTE MUITO MENOR QUE O VALOR CORRESPONDENTE PARA CORPOS QUADRÁTICOS IMAGINÁRIOS DE DISCRIMINANTES DA
MESMA ORDEM DE MAGNITUDE, É POSSÍVEL ALCANÇAR UMA CONVERGÊNCIA ACEITÁVEL RAPIDAMENTE).

MÉTODOS MAIS ROBUSTOS COMO O ALGORITMO DE INFRAESTRUTURA DE SHANKS E O ALGORITMO SUBEXPONENCIAL DE BUCHMAN PERMITEM COMPUTAR A ESTRUTURA DO
GRUPO DE CLASSE ALÉM DE h(D).


PARA MAIORES INFORMAÇÕES: A Course In Computational Algebraic Number Theory by Henri Cohen
                          https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/class_number3.h


*/



//*******************************************************************************************************************
//CABEÇALHO
#ifndef CLASS_NUMBER_CONTINUED_FRACTIONS_H
#define CLASS_NUMBER_CONTINUED_FRACTIONS_H
#include"int128.h"
#include"kronecker_symbol.h"
#include<math.h>


//CONSTANTES GLOBAIS
int32_t PRIME_ARRAY[664579];//Lista de primos até 10^7


//*******************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void fill_prime_buffer();
void compute_fundamental_unit(__int128_t*, __int128_t*, int32_t);
int32_t class_number_dirichlet_l_series_heuristic(int32_t, double);


//*******************************************************************************************************************
//FUNÇÕES
//Função que preenche um buffer de primos até 10^7
void fill_prime_buffer(){

  //Variáveis locais
  FILE* primefile;
  int32_t p=0, counter=0;

  
  //Procedimentos 
    //Abrindo o arquivo para leituta
    primefile=fopen("prime_list.txt", "r");
    
    //Lendo o conteúdo do arquivo estocando os primos em um array
    while(fscanf(primefile, "%i", &p)==1){
      PRIME_ARRAY[counter]=p;
      counter++;
    }

    //Fechando o arquivo
    fclose(primefile);

};


//Função que computa a unidade fundamental de um corpo quadrático real Q(√D) usando a expansão em frações continuadas de -σ(τ)
void compute_fundamental_unit(__int128_t* T, __int128_t* U, int32_t D){

  //Variáveis locais
  __int128_t u=0, v=0;
  int32_t d=floor(sqrt(D));
  __int128_t b=(((D-d)&1)==0)?d:(d-1); //Testando se d=D (mod 2)
  __int128_t A=0, t=0, u1 = (-b), u2=2, v1=1, v2=0, p=b, q=2;


  //Procedimento
    //Loop principal
    while(1){

      //Redução euclidiana
      A=floor((1.0*(p+d))/q); t=p; p=A*q-p;
      if(t==p && v2!=0) break;
      t=A*u2+u1; u1=u2; u2=t;
      t=A*v2+v1; v1=v2; v2=t;
      t=q; q=(D-p*p)/q;
 
      //Cálculo da unidade fundamental para ciclos de ordem ímpar na expansão de -σ(τ)
      if(q==t && v2!=0){
        u=(u1*u2+D*v1*v2)/q; if(u<0) u=(-u);
        v=(u1*v2+u2*v1)/q; if(v<0) v=(-v);
        break;
      }


    }; //Fim do loop principal

    //Cálculo da unidade fundamental para ciclos de ordem par na expansão de -σ(τ)
    if(u==0){
      u=(u2*u2+D*v2*v2)/q; if(u<0) u=(-u);
      v=(2*u2*v2)/q;  if(v<0) v=(-v);
    };

  //Resultado 
  (*U)=u; (*T)=v;

};
/*
  NOTA: O VALORES DE U E T SÃO USUAKLMENTE GRANDES ln(U) E ln(T) PODEM SER DA ORDEM DE √D EM ALGUNS CASOS EXTREMOS.
        UMA MODIFICAÇÃO DO ALGORITMO ACIMA PERMITE COMPUTAR R(D) DIRETAMENTE SEM COMPUTAR η. ISTO EVITA PROBLEMAS
        DEVIDO A INTEGER OVERFLOW SE D > 10^9 AO SE USAR A ARITMÉTICA DE INTEIROS DE 128 BITS.
*/


//Função que computa um valor (possivelmente) correto do número de classe baseado na convergência de séries-L de Dirichlet
int32_t class_number_dirichlet_l_series_heuristic(int32_t D, double RD){

  //Restrição: Se R(D) < D^{1/4} o algoritmo provavelmente não produz um resultado correto
  double root4=sqrt(sqrt((double)D));
  if(RD<root4) return 0;

  //Preenchendo um buffer de números primos
  fill_prime_buffer();


  //Variáveis locais
  double h1=sqrt((double)D)/(2.0*RD), diff=0.0, factor=1.0;
  int32_t c=0, h=0, m=0, k=0, min=0, max=0, p=0;


  //Procedimentos: loop principal
  while(1){

    //Computando a série L(1, χ(D)) em blocos
    min=500*k;
    max=min+499;
    if(max>=664579) max=664578;

    //Aproximação parcial da série de Dirichlet L(1, χ(D))
    for(int32_t i=min; i<=max; ++i){
      p=PRIME_ARRAY[i];
      factor=((double)p)/((double)p-(double)kronecker(D,p));
      h1*=factor;
    }

    //Computando um valor inteiro próximo de h1
    m=(int32_t)llround(h1);

    //Testando a convergência da série
    diff=fabs(h1-(double)m);
    if(diff>0.1){
      c=0;
      k++;

      if(max==664578) break;
      continue;
    }

    //Computando um valor provável para o número de classe
    if(m!=h){
      h=m;
      c=1;
    }
    else
      c++;

    //Critério de parada
    if(c>5) break;

    //Próximo bloco
    k++;
    if(max==664578) break;

  };//Fim do loop principal


  //Resultado
  return h;

};



//*******************************************************************************************************************
//FIM DO HEADER
#endif
