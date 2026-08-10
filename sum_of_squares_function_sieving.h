//VAMOS CRIAR UM PROGRAMA QUE COMPUTA A FUNÇÃO DE SOMA DE QUADRADOS USANDO ALGORITMOS DE PENEIRAS SIMILAR AO CRIVO DE ERATÓSTENES


/*

  EXISTEM VARIAS IDENTIDADES RELACIONANDO A FUNÇÃO DE SOMAS DE QUADRADOS r(k,n) COM OUTRAS FUNÇÕES ARITMÉTICAS COMO A FUNÇÃO DE 
  SOMA DE DIVISORES σ(k, n), A FUNÇÃO DE CONTAGEM DE DIVISORES d(k, n) E A FUNÇÃO DE NÚMERO DE CLASSE h(-n) PARA CORPOS
  QUADRÁTICOS IMAGINÁRIOS, A FUNÇÃO ZETA DE DEDEKIND ζK(n), ENTRE OUTRAS. TAIS RELAÇÕES PERMITEM EM MUITOS CASOS COMPUTAR A
  FUNÇÃO r(k,n), EM ESPECIAL PARA k = 2, 3, 4, 5, 6, 8, 10, 12, 16, 24; USANDO TÉCNICAS SIMILAR AO CRIVO DE ERATÓSTENES. ESTAS
  IDENTIDADES SÃO ÚTEIS PARA SE COMPUTAR A FUNÇÃO r(k,n) EM BLOCOS.

 
  PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/sum_of_squares_function.h
                            https://en.wikipedia.org/wiki/Sum_of_squares_function
                            https://mathworld.wolfram.com/SumofSquaresFunction.html
                            A Course In Computational Algebraic Number Theory by Henri Cohen
                            https://www.numdam.org/article/SDPP_1975-1976__17_1_A1_0.pdf

*/


//**********************************************************************************************************************************
//CABEÇALHO
#ifndef SUM_OF_SQUARE_FUNCTION_SIEVING_H 
#define SUM_OF_SQUARE_FUNCTION_SIEVING_H
#include"kronecker_symbol.h"
#include"hurwitz_class_number_sieving.h"
#include"class_number.h"
#include<inttypes.h>


//**********************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t* compute_sum_of_square_function_k2(int64_t);
int64_t* compute_sum_of_square_function_k3(int64_t);
int64_t* compute_sum_of_square_function_k4(int64_t);
int64_t* compute_sum_of_square_function_k5(int64_t);
int64_t* compute_sum_of_square_function_k6(int64_t);
int64_t* compute_sum_of_square_function_k8(int64_t);



//**********************************************************************************************************************************
//FUNÇÕES
//Função que computa a função r(2, n) que computa o número de representações como a soma de 2 quadrados perfeitos
/*
  IDENTIDADE: r(2, n) = Σ(d(1, n)-d(3,n)) = 4Σ(-1)^{(d-1)/2} (d=1,3 mod 4) 
              d denota divisores de n.
*/

int64_t* compute_sum_of_square_function_k2(int64_t n){

  //Variáveis locais
  int64_t* rk2_array = (int64_t*)malloc((n+1)*sizeof(int64_t));
  const int adder=4;

  //Procedimentos
    //Inicializando o array de elementos
    for(int64_t i=0; i<=n; ++i) 
      rk2_array[i]=0;
    rk2_array[0]=1;

    //Computando a função r(2,n)
    for(int64_t k=1; k<=n; ++k){
      for(int64_t l=k; l<=n; l+=k){

        if(!(k&1)) continue;
      
        if( (((k-1)>>1)&1)==0) rk2_array[l]+=adder;
        else rk2_array[l]-=adder;


      }
    }
    

  //Resultado 
  return rk2_array;
    
};


//Função que computa a função r(3, n) que computa o número de representações como a soma de 3 quadrados perfeitos
/*
  IDENTIDADE: r(3, n) = 24h(-n) se n=3 (mod 8)
                        0       se n=7 (mod 8)
                        12(-4n) nos demais casos
*/
int64_t* compute_sum_of_square_function_k3(int64_t n){

  //Pré-computando números de classe:
  struct hurwitz_fraction*  hurwitz_lambda_array = hurwitz_lambda_function(4*n+1);
  struct hurwitz_fraction*  H_array = hurwitz_class_number_recursive(4*n, hurwitz_lambda_array);

  //Variáveis locais
  int64_t* rk3_array = (int64_t*)malloc((n+1)*sizeof(int64_t));
  uint64_t r=0;

  //Procedimentos
    //Inicializando o array de elementos
    for(int64_t i=0; i<=n; ++i) rk3_array[i]=0;
    rk3_array[0]=1; rk3_array[1]=6; rk3_array[2]=12; rk3_array[3]=8; rk3_array[4]=6;


    //Computando a função r(3,n)
    for(uint64_t k=5; k<=n; ++k){

      r=(k&7); // mod 8
      if(k==7 || is_square_free(k)==false) continue;
      if(k==3){
        rk3_array[k]=24*H_array[k].num/H_array[k].den;
        continue;
      }

      rk3_array[k]=12*H_array[4*k].num/H_array[4*k].den;

    }
    


    //Limpando o cachê de memória
    if(hurwitz_lambda_array) free(hurwitz_lambda_array); hurwitz_lambda_array=NULL;
    if(H_array) free(H_array); H_array=NULL;
    

  //Resultado 
  return rk3_array;  

};


//Função que computa a função r(4, n) que computa o número de representações como a soma de 4 quadrados perfeitos
/*
  IDENTIDADE: r(4, n) = 8 Σd (d ≠ 0 mod 4) 
              d denota divisores de n.

*/
int64_t* compute_sum_of_square_function_k4(int64_t n){

  //Variáveis locais
  int64_t* rk4_array = (int64_t*)malloc((n+1)*sizeof(int64_t));
  int64_t adder=0;

  //Procedimentos
    //Inicializando o array de elementos
    for(int64_t i=0; i<=n; ++i) 
      rk4_array[i]=0;
    rk4_array[0]=1;

    //Computando a função r(2,n)
    for(uint64_t k=1; k<=n; ++k){

      if((k%4==0)) continue; //k=0 mod 4
      adder = 8*k;
      for(uint64_t l=k; l<=n; l+=k) rk4_array[l]=rk4_array[l]+adder;
    }
    

  //Resultado 
  return rk4_array;
    
};


//Função que computa a função r(5, n) que computa o número de representações como a soma de 5 quadrados perfeitos
/*
  IDENTIDADE: r(5, n) = 480(5-(n|2))ζK(-1), (|) denota o símbolo de Kronecker e ζK(s) a função zeta de Dedekind
              para um corpo algébrico quadrático real de discriminante d
              ζK(-1)=(1/60)Σσ((n-s²)/4) com s = n (mod 2), σ(n) denota a função de soma de divisores com σ(n)=0
              se n≲0,

*/
int64_t* compute_sum_of_square_function_k5(int64_t n){

  //Pré-computando a função de soma de divisores σ(n)
  int32_t* sum_of_divisors_array = compute_sum_of_divisors_function(n);

  //Variáveis locais
  int64_t* rk5_array = (int64_t*)malloc((n+1)*sizeof(int64_t));
  uint64_t sum=0;
  int64_t s=0;

  //Procedimentos
    //Inicializando o array de elementos
    for(int64_t i=0; i<=n; ++i)
      rk5_array[i]=0;

    rk5_array[0]=1;
    if(n>=1) rk5_array[1]=10;
    if(n>=2) rk5_array[2]=40;
    if(n>=3) rk5_array[3]=80;
    if(n>=4) rk5_array[4]=90;


    //Calculando a soma de divisores Σσ((k-s²)/4) com s = k (mod 2)
    for(int64_t k=5; k<=n; ++k){
      if(is_fundamental_discriminant(k)==false) continue;

      s=(k%2);
      sum=0;

      for(; s*s<k; s+=2){

       int64_t q=(k-s*s)/4;

       if(s==0)
         sum+=sum_of_divisors_array[q];// Para k par, o termo s=0 aparece uma única vez.
       else
         sum+=2*sum_of_divisors_array[q];//A soma sobre s deve considerar os valores positivos e negativos de s.
     }

      //Ajustede valores
      rk5_array[k]=8*(5-2*kronecker(k, 2))*sum;

    }


    //Limpando o cachê de memória
    if(sum_of_divisors_array) free(sum_of_divisors_array); sum_of_divisors_array=NULL;


  //Resultado
  return rk5_array;

};


//Função que computa a função r(6, n) que computa o número de representações como a soma de 6 quadrados perfeitos
/*
  IDENTIDADE: r(6, n) = 4Σd²[4(-4|(n/d))-(-4|d)], (|) denota o símbolo de Kronecker  
              d denota divisores de n.
*/
int64_t* compute_sum_of_square_function_k6(int64_t n){

  //Variáveis locais
  int64_t* rk6_array = (int64_t*)malloc((n+1)*sizeof(int64_t));
  int64_t adder=0;

  //Procedimentos
    //Inicializando o array de elementos
    for(int64_t i=0; i<=n; ++i) rk6_array[i]=0;
    rk6_array[0]=1;

    //Computando a função r(6,n)
    for(int64_t k=1; k<=n; ++k){
      for(int64_t l=k; l<=n; l+=k){

        int64_t q=l/k;
        adder=(4*k*k)*(4*kronecker((-4), q)-kronecker((-4), k));
        rk6_array[l]+=adder;

      }
    }  


  //Resultado
  return rk6_array;

};


//Função que computa a função r(8, n) que computa o número de representações como a soma de 8 quadrados perfeitos
/*
  IDENTIDADE: r(8, n) = 16Σ[(-1)^{n+d}]d³
              d denota divisores de n.
*/

int64_t* compute_sum_of_square_function_k8(int64_t n){

  //Variáveis locais
  int64_t* rk8_array = (int64_t*)malloc((n+1)*sizeof(int64_t));
  int64_t adder=0;

  //Procedimentos
    //Inicializando o array de elementos
    for(int64_t i=0; i<=n; ++i) rk8_array[i]=0;
      rk8_array[0]=1;

    //Computando a função r(8,n)
    for(int64_t k=1; k<=n; ++k){

      adder=((k*k*k)<<4);
      for(int64_t l=k; l<=n; l+=k){
        
        if(((k+l)&1)==1) rk8_array[l]-=adder;
        else rk8_array[l]+=adder;

      }
    }  


  //Resultado
  return rk8_array;

};


/*
  NOTA: As identidades para r(10, n), r(12, n), r(16, n) e r(24, n) estão nas referências. Tais formulas envolvem funções de somas
        de divisores σ(k, n) e contagem de divisores d(k, n) de ordem 'k' elevada; além da função tau de Ramanujan τ(n) e certas
        somas parciais de séries cujo valor cresce rapidamente e portanto não são adequadas a aartimética de inteiros de 64 bits.
*/


//**********************************************************************************************************************************
//FIM DO HEADER
#endif

