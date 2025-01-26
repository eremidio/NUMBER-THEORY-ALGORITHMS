// VAMOS IMPLEMENTAR UM PROGRAMA QUE COMPUTA O ALGORITMO DA ARITMÉTICA MODULAR DE MONTGOMERY

/*
O ALGORITMO DE MONTOGOMERY É UM EFICIENTE ALGORITMO USADO PARA IMPLEMENTAR
ARITMÉTICA MODULAR. DADO a (mod N) E b (mod N) O ALGORITMO DE MONTGOMERY NOS
PERMITE CALCULAR DE FORMA EFICIENTE ab (mod N). O ALGORITMO FAZ USO DAS CHAMADAS
FORMAS DE MONTGOMERY E NOS CÁLCULOS EMPREGA UM VALOR R TAL QUE mmc(N, R)=1, NOS
CÁLCULOS INTERMEDIÁRIOS. A IDEIA É QUE A DIVISÃO POR R SEJA FACILMENTE COMPUTADA
(PODEMOS TOMAR R=2^k COM k INTEIRO POR EXEMPLO). ADIÇÃO E SUBTRAÇÃO PERMANECEM
IDÊNTICOS, PORÉM MULTIPLICAÇÃO REQUER O CÁLCULO DE FATORES MULTIPLICATIVOS R' E
N' TAL QUE AS  RELAÇÕES [a (mod N)][b (mod N)] = ab (mod N) SEJAM PRESERVADAS.

TIPICAMENTE O ALGORITMO EXIGEQUE UM INPUT SEJA ESCRITO EM FORMA DE MONTGOMERY E
O RESULTADO FINAL SEJA RECONVERTIDO PARA A REPRESENTAÇÃO USUAL, PORÉM AO EVITAR
O CÁLCULO DE DIVISÕES QUE EXIGEM COMPLEXAS MANIPULAÇÕES BITS NO CÁLCULO DE
DÍGITOS DECIMAIS E AFINS, O ALGORITMO PERFOMA OPERAÇÕES mod N DE MANEIRA MUITO
EFICIENTE. EM PARTICULAR O ALGORITMO É EXTREMAMENTE A APLICAÇÕES QUANDO N É
SUFICIENTEMENTE GRANDE COMO É O CASO DE ALGORITMOS ENVOLVIDOS EM CRIPTOGRAFIA,
NOS  QUAIS AS CONVERSÕES ENVOLVENDO FORMAS DEMONTGOMERY SÓ SÃO NECESSÁRIAS AO
INÍCIO E FIM DOS CÁLCULOS.

VAMOS IMPLEMENTAR A VARIANTE MAIS SIMPLES DO ALGORITMO. PARA INTEIROS DE
PRECISÃO MÚLTIPLA QUE CONTÉM CENTENAS OU MILHARES DE BITS TAIS QUAIS OS USADOS
EM CRIPTOGRAFIA O ALGORITMO REQUER AJUSTES MAIS SOFISTICADOS.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Montgomery_modular_multiplication#Modular_arithmetic
                          Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance

*/

//********************************************************************************************************************************************************************
// CABEÇALHO
#ifndef MONTGOMERY_MODULAR_MULTIPLICATION_H
#define MONTGOMERY_MODULAR_MULTIPLICATION_H
#include <assert.h>
#include <stdio.h>
#include"fast_modular_inverse.h"
#include "mod_bin_exponentiation.h"

//********************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
int64_t gcd_montgomery(int64_t, int64_t);
void select_montgomery_parameters(int64_t*, int*, int64_t*, int64_t);

int64_t montgomery_mul_mod(int64_t, int64_t, int64_t, int64_t, int64_t, int);
int64_t montgomery_pow_mod(int64_t, int64_t, int64_t, int64_t, int64_t, int);


//********************************************************************************************************************************************************************
// FUNÇÕES
//Função que implementa o algoritmo de Euclides
int64_t gcd_montgomery(int64_t a, int64_t b){
  if(b==0) return a;
  else return gcd_montgomery(b, (a%b));

};

//Função que determina os parâmetros R, N' e s usados na redução de Montgomery
void select_montgomery_parameters(int64_t* R, int* s, int64_t* N1,  int64_t N){

  //Variáveis locais
  int64_t R_=1, N_, bits=0;

  //Procedimentos
    //Loop principal
    while(N>R_){
      R_<<=1;
      bits++;
    }

    //Calculando N-¹ mod R
    N_=fast_modular_inverse(N, R_); 
    if(N_<0) N_+=R_ ;

  //Resultado
  (*R)=R_;
  (*s)=bits;
  (*N1)=(R_-N_)&(R_ - 1);

};


//Função que calcula uma expressão do tipo ab (mod N), com as restrições 0≲x<N
int64_t montgomery_mul_mod(int64_t a, int64_t b, int64_t N, int64_t N_, int64_t R, int s){

  //Variáveis locais
  __int128_t x=a*b;
  __int128_t z;

  
  //Procedimentos
    //Calculando o resultado
    z=(x+N*((x*N_)&(R-1)))>>s;
    
    //Ajuste fino
    if(z>=N) z-=N;

  //Resultado
  return ((int64_t)(z));


};


//Função quer calcula uma expressão do tipo x^y mod N
int64_t montgomery_pow_mod(int64_t x, int64_t y, int64_t N, int64_t N_, int64_t R, int s){

  //Variáveis locais
  __int128_t x1=(x*R)%N;  
  int64_t p_= R%N;
  int64_t x_=x1;



  //Procedimentos
    //Loop principal:iterando sobre os bits do expoente
    while(y>0){

      p_ = montgomery_mul_mod(p_, p_, N, N_, R, s);
      if(y&1) p_ = montgomery_mul_mod(p_, x_, N, N_, R, s);
      y>>=1;
    }
  

  //Resultado
  return montgomery_mul_mod(p_, 1, N, N_, R, s);      

};

//********************************************************************************************************************************************************************
// FIM DO HEADER
#endif
