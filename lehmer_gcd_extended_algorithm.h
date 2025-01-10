//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE LEHMER PARA CALCULAR O MDC DE DOIS INTEIROS DE 128 BITS


/*
PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/lehmer_gcd_algorithm.h

*/


//**********************************************************************************
//CABEÇALHO
#ifndef LEHMER_GCD_EXTENDED_H
#define LEHMER_GCD_EXTENDED_H
#include"lehmer_gcd_algorithm.h"


//**********************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void extended_euclidean_algorithm(int64_t, int64_t);
void lehmer_extended_algorithm(__int128_t, __int128_t);

//**********************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides extendido para inteiros de 64 bits
void extended_euclidean_algorithm(int64_t a, int64_t b){

  //Variáveis locais
  int64_t r0,r1, x0, x1, y0, y1, r2, x2, y2;

  //Procedimentos 
    //Ajuste de variáveis
    r0=a;
    r1=b;
    r2=1;
    x0=1;
    x1=0;
    y0=0;
    y1=1;
    //Calculando os valores finais coeficientes recursivamente
    while(r2>0){
      int64_t quotient= r0/r1;
      r2=r0-quotient*r1;
      x2=x0-quotient*x1;
      y2=y0-quotient*y1;

      //Atualizando variáveis para a próxima iteração
      if(r2>0){
        r0=r1; r1=r2;
        x0=x1; x1=x2;
        y0=y1; y1=y2;
      };

    };


   //Ajuste de sinal
   if(x2<0) x2*=(-1);
   if(y2<0) y2*=(-1);


  printf("mdc= %li\n", r1);
  printf("Coeficiente da identidade de Bézout: %li, %li\n", x1, y1);
  printf("Razão pelo mdc: %li, %li\n", y2, x2);

};


//Função que implementa o algoritmo de Lehmer extendidopara inteiros de 128 bits
void lehmer_extended_algorithm(__int128_t a, __int128_t b){

  //Restrição
  if(a < b){
    __int128_t temp = a;
    a = b;
    b = temp;
  };


  //Variáveis locais
  __int128_t t, u=1, r, v1=0, v3;
  int64_t a_, b_;
  int64_t A=1, B=0, C=0, D=1, T=0, q=0;


  //Procedimentos
    //Loop principal
    while(b>=M){

      //Ajuste de variáveis
      a_ = a >> 62;//Computando o digito mais signficativo de a
      b_ = b >> 62;//Computando o digito mais signficativo de b
      A = 1; B = 0; C = 0; D = 1;

      //Loop euclidiano
      while(1){
         
        if((b_ + C)==0 || (b_ + D)==0) break;
        q=floor(1.0*(a_ + A)/(b_ + C));
        if(q!=floor(1.0*(a_ + B)/(b_ + D))) break;

        //Recalculando variáveis
        T = A - (q*C); A=C; C=T; 
        T = B - (q*D); B=D; D=T;
        T=  a_ - (q*b_);
        a_ = b_; b_ = T;
      };

      //Etapa de precisão múltipla
      if(B==0){
        __int128_t Q=a/b;
        q=Q; t=(a%b);
        a=b; b=t;
        t = u - (q*v1);
        u=v1; v1=t;
      }
      else{
        t=(A*a)+(B*b); r=(C*a)+(D*b);
        a=t; b=r;
        t = (A*u)+(B*v1); r=(C*u)+(D*v1);
        u=t; v1=r;


      };



    };//Fim do loop principal


    //Caso base: envolvendo apenas operações de precisão simples()
    extended_euclidean_algorithm((int64_t)a, (int64_t)b);

};


//**********************************************************************************
//FIM DO HEADER 
#endif
