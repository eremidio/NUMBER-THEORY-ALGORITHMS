//VAMOS CRIAR UM PROGRAMA QUE TESTA A PRIMALIDADE DE UM INTEIRO USANDO PONTOS EM UMA TRELIÇA (LATTICE)

/*
UMA TRELIÇA CONSISTE EM UMA DISTRIBUIÇÃO REGULAR DE PONTOS EM UM ESPAÇO n-DIMENSIONAL. TRELIÇAS FORMAM
UM GRUPO NO QUAL A OPERAÇÃO CONSTISTE NO DESLOCAMENTO DE PONTOS AO LONGO DE VETORES QUE FORMAM UMA
BASE PARA O ESPAÇO n-DIMENSIONAL.

SEJA UMA TRELIÇA FORMADAS POR PONTOS P=(x,y), COM CORDERNADAS INTEIRAS EM UM ESPAÇO n-DIMENSIONAL.
DOIS PONTOS P1=(x1,y1) E P2=(x2,y2) SÃO DITOS SEREM MUTUAMENTE VISÍVEIS SE A RETA QUE CONECTA ESTES
PONTOS NÃO CONTÉM NENHUM OUTRO PONTO DA TRELIÇA. TAL CONDIÇÃO É EXPRESSA POR MEIO DA RELAÇÃO:
mcd(x1-X2, y1-y2)=1. SELECIONANDO DE FORMA ALEATÓRIA DOIS PONTOS EM UMA TRELIÇA EM UM ESPAÇO n-
DIMENSIONAL A PROBABILIDADE DE AMBOS SEREM VÍSIVEIS EM RELAÇÃO A ORIGEM É DADA POR 1/ζ(n), ONDE ζ(n) É
A FUNÇÃO ZETA DE RIEMANN. PARA n=2, ISTO É, 6/π², VALOR QUE TAMBÉM REPRESENTA A PROBABILIDADE DE QUE
DOIS NÚMEROS GERADOS ALEATÓRIAMENTE SEJAM RELATIVAMENTE PRIMOS.

A SEGUINTE PROPOSIÇÃO GEOMÉTRICA É FACILMENTE VERIFICÁVEL: SEJAM x,y NÚMEROS INTEIROS E AMBOS POSITIVOS.
UM INTEIRO n É POSITIVO SE E SOMENTE PONTOS P=(x,y) COM COORDENADAS INTEIRAS TAIS QUE x+y=n SÃO
VÍSIVEIS DA ORIGEM.

TAL OBSERVAÇÃO PODE SER USADA PARA CHECAR A PRIMALIDADE DE UM INTEIRO EM O(nlog(n)) OPERAÇÕES. O TESTE É
NA VERDADE UMA VARIANTE MAIS LENTA DO TESTE POR TENTATIVA POR DIVISÃO E ERRO.

PARA MAIORES INFORMAÇÕES: https://mathworld.wolfram.com/VisiblePoint.html
                          https://math.stackexchange.com/questions/2272536/lattice-points-on-a-line-y-x-p-visible-from-the-origin
                          https://math.stackexchange.com/questions/3970614/is-this-a-new-primality-test
                          https://math.stackexchange.com/questions/3979118/speedup-primality-test?noredirect=1&lq=1

*/

//***********************************************************************************************************************
//CABEÇALHO
#ifndef INTEGER_LATTICE_POINT_PRIMALITY_TEST_H
#define INTEGER_LATTICE_POINT_PRIMALITY_TEST_H
#include<stdbool.h>
#include<stdint.h>
#include<math.h>
#include<stdio.h>


//***********************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t gcd_u64(uint64_t, uint64_t);
bool integer_lattice_point_primality_test(uint64_t);

//***********************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides 
uint64_t gcd_u64(uint64_t a, uint64_t b){

  if(b==0) return a;
  else return gcd_u64(b, (a%b));

};

//Função que determina se um inteiro é primo ou não usando pontos de coordenadas inteiras em R²
bool integer_lattice_point_primality_test(uint64_t n){

  //Casos bases: 
  if(n<2) return false;
  if(n==2 || n==3 || n==5) return true;
  if(n%2==0 || n%3==0 || n%5==0) return false;


  //Variáveis locais
  uint64_t y, x;
  uint64_t min=((n/2)+1), max=min+sqrt(n);


  //Procedimentos
    //Loop principal: checando acondição de visibidade dos pontos em questão em relação a origem O=(0,0)
    for(x=min; x<max; ++x){
      y=n-x;
      if(gcd_u64(x, y)>1){
        printf("Fator de %lu encontrado:%lu\n", n, gcd_u64(x, y));
        return false;
      }
    }

  //Caso passe no teste acima um primo foi encontrado
  return true;

};


//***********************************************************************************************************************
//FIM DO HEADER
#endif
