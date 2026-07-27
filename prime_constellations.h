//VAMOS CRIAR UM PROGRAMA QUE COMPUTA CONSTELAÇÕES DE PRIMOS ADMISSÍVEIS

/*

SEJAM UM CONJUNTO DE INTEIROS {a(1), ..., a(n)}. UMA CONSTELAÇÃO DE PRIMOS É UMA SEQÛENCIA DE INTEIROS PRIMOS DA FORMA {p+a(1), ..., p+a(n)}
COM p INTEIRO. POR EXEMPLO, OS PRIMOS GÊMEOS CONSISTEM NA SEQUÊNCIA {0,2}, ISTO É, DE PRIMOS DA FORMA (p, p+2) COMO OS PARES ORDENADOS
(3, 5); (5, 7); (11, 13); (17,19); (29, 31); (41,43); (59, 61); (71,73); etc.

DE FORMA GERAL O INTERESSE É EM N-UPLAS DE VALORES a(i)'S (i INTEIRO) TAIS QUE EXISTAM INFINITAS N-UPLAS POSSÍVEIS DE NÚMEROS PRIMOS DA FORMA
{p+a(1), ..., p+a(n)}. UM CONJUNTO DE VALORES {a(1), ..., a(n)} QUE SATISFAZEM ESSE CRITÉRIO FORMAM UMA CONSTELAÇÃO ADMISSÍVEL. POR EXEMPLO:
OS CONJUNTOS (0, 2); (0, 4) E (0, 6) FORMAM CONSTELAÇÕES ADMISSÍVEIS; AO PASSO QUE O CONJUNTO (0,1) NÃO, DE FATO SE p=(p+0) FOR UM PRIMO 
ÍMPAR, ENTÃO NECESSÁRIAMENTE (p+1) É PAR E PORTANTO DIVISÍVEL POR 2. UM RACIOCÍNIO SIMILAR PERMITE INFERIR QUE AS TRIPLAS {p, p+2; p+4} NÃO
FORMAM UMA CONSTELAÇÃO ADMISSÍVEL, POIS EXCETO PELA TRIPLA (3,5,7) TODAS AS DEMAIS TRIPLAS DESTA FORMA INCLUEM UM MÚLTIPLO DE 3. A SEGUINTE
PROPOSIÇÃO PODE SER USADA PARA VERIFICAR SE UMA N-UPLA DE INTEIROS FORMAM UMA CONSTELAÇÃO ADMISSÍVEL:

PROPOSIÇÃO: SEJA {a(1), ..., a(n)} UM CONJUNTO DE INTEIROS NÃO NEGATIVOS. ESTE CONJUNTO FORMA UMA CONSTELAÇÃO ADMISSÍVEL SE E SOMENTE SE
NÃO HOUVER NENHUM PRIMO p TAL QUE AS RELAÇÕES a(i) mod p PARA i=1,...,n ASSUMAM TODOS OS VALORES POSSÍVEIS NO CONJUNTO
Z/pZ ={0, 1, ..., p-1}.

DE GRANDE INTERESSE TEÓRICO É A ESTIMATIVA DO NÚMERO DE OCORRÊNCIAS DE N-UPLAS DE PRIMOS EM CONSTELAÇÕES ATÉ UM DETERMINADO VALOR x. ESSES
VALORES PODEM SER APROXIMADAMENTE COMPUTADOS USANDO-SE AS CONJECTURAS DE HARDY-LITLEWOOD. BASEADOS NA IDEIA DE QUE A PROBABILIDADE DE 
NÚMEROS INTEIROS SEREM PRIMOS EM TORNO DE UM VALOR x É DE 1/ln(x), O NÚMERO DE OCORRÊNCIAS DE CONSTELAÇÕES DE UM DETERMINADA CONSTELAÇÃO
CONTENDO N-UPLAS COM 'N' ELEMENTOS É DEFINIDA POR MEIO DE EXPRESSÕES DO TIPO Cp.I(x), ONDE I(x) É A INTEGRAL DEFINIDA DE 2 A x DA FUNÇÃO
f(x)=ln(x)^{-N} E Cp SÃO AS CHAMADAS CONSTANTES DE HARDY-LITTLEWOOD. AS CONSTANTES Cp PARA {a(1), ..., a(n)}  PODEM SER COMPUTADAS
USANDO-SE A FÓRMULA Cp = {2^n}.Π [1-w(p; a(1), ..., a(n))]/p}/[(1-1/p)^{n+1}], ONDE O PRODUTÓRIO É FEITO SOBRE TODOS OS PRIMOS p E
w(p; a(1), ..., a(n)) É O VALOR DO PRODUTO DO NÚMERO DE CLASSES RESIDUAIS a(i) mod p (IGUAL A p-n PARA PRIMOS SUFICIENTEMENTE GRANDES).
A INTEGRAL INDEFINIDA DE f(x)=ln(x)^{-N} É DADA A MENOS DE UMA CONSTANTE PELA FÓRMULA POR I(x) = li(x) - x.Σ[k!/ln(x)^{k+1}] COM
k=1, .., (N-2); ONDE li(x) É A FUNÇÃO LOGARÍTMICA INTEGRAL.

PARA MAIORES INFORMAÇÕES: Prime Numbers And Computer Methods For Factorization, by Hans Riesel
                          https://mathworld.wolfram.com/PrimeConstellation.html
                          https://mathworld.wolfram.com/LogarithmicIntegral.html
                          http://www.primerecords.dk/constellations.htm
                          https://t5k.org/glossary/page.php?sort=primeconstellation
                          https://en.wikipedia.org/wiki/Prime_k-tuple
                          https://en.wikipedia.org/wiki/First_Hardy%E2%80%93Littlewood_conjecture
                          https://en.wikipedia.org/wiki/Second_Hardy%E2%80%93Littlewood_conjecture
                          https://en.wikipedia.org/wiki/Bateman%E2%80%93Horn_conjecture
                        
                    
*/


//**********************************************************************************************************************************************
//CABEÇALHO
#ifndef PRIME_CONSTELLATIONS_H
#define PRIME_CONSTELLATIONS_H
#include"baillie_psw_prime_test.h"
#include<stdio.h>
#include<stdbool.h>
#include<inttypes.h>
#include<assert.h>


//CONSTANTES GLOBAIS (VARIÁVEIS USADAS EM MAIS DE UMA FUNÇÃO)
int K_TUPLE_SIZE=0;
int K_TUPLE_HIGHEST=0;


//**********************************************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
int* setup_ktuple();
bool is_admissible_constellation(int[]);


//**********************************************************************************************************************************************
//FUNÇÕES 
//Função que gera uma enupla de números inteiros
int* setup_ktuple(){

  //Variáveis locais
  int n, k;


  //Procedimentos
    //Recebendo input do usuário e alocando espaço na memória
    printf("[Números de termos na constelação de primos] n:");
    if(scanf("%d", &n));
    int* ktuple=(int*)calloc(n, sizeof(int));


    //Definindo os elementos da enupla
    for(; K_TUPLE_SIZE<n; ++K_TUPLE_SIZE){
      printf("[Coeficientes da constelação de primos] a(%d): ", K_TUPLE_SIZE);
      if(scanf("%d", &k));
      ktuple[K_TUPLE_SIZE]=k;
    }

  
  //Resultado
  return ktuple;

};


//Função que checa se uma constelação de primos é admssível ou não
bool is_admissible_constellation(int ktuple[]){

  //Variáveis locais
  int hits=0;
  

  //Procedimentos
    //Determinando o maior elemento da enupla e alocando um array de classes residuais
    for(int k=0; k<K_TUPLE_SIZE; ++k){
      if(ktuple[k]>K_TUPLE_HIGHEST) K_TUPLE_HIGHEST=ktuple[k];
    }
    if(K_TUPLE_HIGHEST<2) K_TUPLE_HIGHEST++;

    int* residual_class=(int*)calloc(K_TUPLE_HIGHEST, sizeof(int));
    for(int k=0; k<K_TUPLE_HIGHEST; ++k) residual_class[k]=0;

    //Teste principal: verificando se para algum primo todas as classes residuais são ocupadas pelos elementos da enupla
    for(int t=2; t<=K_TUPLE_HIGHEST; ++t){
      if(baillie_psw_test(t)==false) continue; //t não é primo

      for(int u=0; u<K_TUPLE_SIZE; ++u){

        int r=ktuple[u]%t;//Calculando as classes residuais módulo o primo 't'
        if(residual_class[r]<1){ 
          residual_class[r]=1;
          hits++;
        };

      }


      //Testando se a enupla define uma constelação válida de números primos
      if(hits==t) return false; //Condição que define constelações não admissíveis
      else{ //Resetando variáveis de teste
      hits=0;
      for(int v=0; v<K_TUPLE_HIGHEST; ++v) residual_class[v]=0;
      };

      
    };

    //Limpando o cachê de memória
    if(residual_class) free(residual_class);
    residual_class=NULL;


  //Resultado 
  return true;

};


//**********************************************************************************************************************************************
//FIM DO HEADER
#endif
