//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE MAPES QUE É UMA SUBROTINA USADA PARA COMPUTAR AFUNÇÃO π(x)


/*
SEJA π(x) A FUNÇÃO  PARA A CONTAGEM DE PRIMOS. DADO UM DETERMINADO INTERVALO {1, 2,..., x},
CONTENDO PRIMOS {p(1), ..., p(a)} O PRINCÍPIO DE INCLUSÃO-EXCLUSÃO AFIRMA QUE:
π(x)=|_x_|-|_x/p(i)_|+|_x/p(i)p(j)_|-|_x/p(i)p(j)p(k)_|+....
(AQUI |_x_| DENOTA O INTEIRO MENOR MAIS PRÓXIMO DE x)

DIVERSOS ALGORITMOS PARA COMPUTAR EFICIENTEMENTE A FUNÇÃO π(x) CONSISTEM EM REDEFINIÇÃO DO SOMATÓRIO EM
PARCELAS QUE SÃO FACILMENTE COMPUTÁVEIS. É POSSÍVEL MOSTRAR QUE O SOMATÓRIO ACIMA PODE SER REESCRITO
COMO π(x)-π(√x)-1=φ(x, π(√x)) ONDE φ(m, n) É UMA FUNÇÃO QUE CONTABILIZA O NÚMERO DE INTEIROS MENORES
QUE m NÃO DIVISÍVEIS PELOS n-ÉSIMOS PRIMEIROS NÚMEROS PRIMOS. ESTA FUNÇÃO É DEFINIDA RECURSIVAMENTE
PELAS IDENTIDADES φ(m, 0)= |_x_| e φ(m, n)=φ(m, n-1)-φ(m/p(n), n-1).

O ALGORTITMO DE MAPES COMPUTA A FUNÇÃO φ USANDO UMA PEQUENA LISTA DE NÚMEROS PRIMOS PRÉ-COMPUTADA E
UMA SÉRIE DE FUNÇÕES T(k, x, a) QUE USA A EXPANSÃO DE k EM DIGITOS BINÁRIOS. O ALGORITMO DE MAPES
PODE SER USADO PARA COMPUTAR A FUNÇÃO DE CONTAGEM DE PRIMOS COMO UMA SUBROTINA AUXILIAR GUARDANDO-SE
UMA TABELA DE VALORES φ(m, n) PARA LIMITES DE m, n FIXOS (UMA TABELA DE NÚMEROS PRIMOS DEVE ESTAR
DISPONÍVEL). DE GRANDE UTILIDADE É ESTOCAR PARES DO TIPO (m, φ(m, n)) PARA n FIXO DIGA-SE n=10.
REGISTRA-SE VALORES DE m TAIS QUE φ(m, n) VARIE, POIS PARA n FIXO φ(m, n) PERMANECE CONSTANTE DENTRO
DE UM INTERVALO a1 ≲ m ≲ a2 . PARA UM DADO VALOR n, O NÚMERO DE REDUÇÕES DAS CHAMADAS RECURSIVAS NO
CÁLCULO DE  φ(m, n) É DA ORDEM DE 2^n.

PARA MAIORES INFORMAÇÕES: https://mathworld.wolfram.com/MapesMethod.html
                          https://mathworld.wolfram.com/LegendresFormula.html
                          https://en.wikipedia.org/wiki/Prime-counting_function
                          Prime Numbers And Computer Methods For Factorization, by Hans Riesel

O ARITGO ORIGINAL ESTÁ DISPONÍVEL EM: https://www.ams.org/journals/mcom/1963-17-082/S0025-5718-1963-0158508-8/S0025-5718-1963-0158508-8.pdf

*/


//***************************************************************************************************************************************************
//CABEÇALHO
#ifndef MAPES_ALGORITHM_H
#define MAPES_ALGORITHM_H
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


//***************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t tka(int64_t, int64_t, int64_t[]);
int64_t mapes_algorithm(int64_t, int64_t, int64_t[]);


//***************************************************************************************************************************************************
//FUNÇÕES
//Função que computa a expressão T(k,x,a)
int64_t tka(int64_t x, int64_t k, int64_t prime_array[]){

  //Caso bases
  if(k==0) return x;

  //Variáveis locais
  int64_t tk=1;
  int bit_parity=0, b=0;


  //Procedimentos
    //Loop principal
    while(k>0){

      //Checando o bit do parâmetro k
      if(k&1){
        bit_parity++;
        tk*=prime_array[b];
        if(tk>x) return 0;
      }

      //Atualizando variáveis para a próxima iteração
      k>>=1;
      b++;
  
    }

   //Computando o resultado final
   tk=floor(x/tk);
  
  //Resultado
  if(bit_parity&1) return (-1)*tk;
  else return tk;


};

// Função auxiliar Φ(m, n) via método de Mapes
int64_t mapes_algorithm(int64_t m, int64_t n, int64_t prime_array[]){

  //Variáveis locais
  int64_t phi=0;
  int64_t max_k = pow(2, n);


  //Procedimentos
    //Loop principal
    for(int64_t k=0; k<max_k; ++k) phi=phi+tka(m, k, prime_array);

  //Resultado
  return phi;

};


//***************************************************************************************************************************************************
//FIM DO HEADER
#endif
