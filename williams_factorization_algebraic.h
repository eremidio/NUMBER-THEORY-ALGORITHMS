//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA VARIANTE DO ALGORITMO (p+1) DE WILLIAMS USANDO ARITMÉTICA EM CORPOS FINITOS DO SEGUNDO TIPO

/*

O ALGORITMO DE FATORAÇÃO (p+1) PODE SER REEXPRESSO EM TERMOS DE ARITMÉTICA USANDO CORPOS NÚMERICOS QUADRÁTICOS Q(√n) CUJOS ELEMENTOS
SÃO DA FORMA z=a+b√n.

ESTE ALGORITMO É PARTICULARMENTE ÚTIL PARA SEMIPRIMOS (PRODUTOS DE DOIS FATORES PRIMOS). GENERALIZAÇÕES INCLUEM A FATORAÇÃO VIA
POLINÔMIOS CICLOTÔMICOS.


PARA MAIORES INFORMAÇÕES: https://www.semanticscholar.org/paper/Factoring-with-cyclotomic-polynomials-Bach-Shallit/b47948d1d665cb8276bc638d5fca6eabd23806c7
                          https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/williams_factorization.c

*/

//******************************************************************************************************************************************************************
// CABEÇALHO
#ifndef WILLIAM_FACTORIZATION_ALGEBRAIC_H
#define WILLIAM_FACTORIZATION_ALGEBRAIC_H
#include"cipolla_algorithm.h"
#include"fast_perfect_square_detection.h"
#include<stdlib.h>
#include<time.h>


//******************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
void setup_williams_parameters(int64_t*, int64_t*, int64_t*, int64_t);
struct algebraic_quadratic_number algebraic_quadratic_number_rationalization(struct algebraic_quadratic_number, int64_t);
int64_t  gcd_s64(int64_t, int64_t);
void williams_factorization_algebraic(int64_t);


//******************************************************************************************************************************************************************
// FUNÇÕES
//Função que define os parâmetros usados no algoritmo
void setup_williams_parameters(int64_t* a, int64_t*  b, int64_t* d, int64_t N){

  //Semente para  geração de números aletórios
  srand(time(NULL));


  //Procedimentos
    //Gerando números aleatórios usados no algoritmo
      reselect_parameters:
    int64_t a_=rand()%N;
    int64_t b_=rand()%N;
    int64_t d_=rand()%N ;
    
    int64_t r=0;    
    if(perfect_square_detection_64bits(d_, &r)) goto reselect_parameters;
    else{
      (*a)=a_; (*b)=b_; (*d)=d_;
      return;
    };

};


//Função que racionaliza um número algébrico quadrático
struct algebraic_quadratic_number algebraic_quadratic_number_rationalization(struct algebraic_quadratic_number z0, int64_t N){

  //Variáveis locais
  struct algebraic_quadratic_number z1; 
  __int128_t den=(z0.a*z0.a)-(z0.b*z0.b*z0.d);

  //Procedimentos
    //Ajuste de variáveis
    z1.a=(z0.a*z0.a)+(z0.b*z0.b*z0.d); z1.b=(-2)*z0.a*z0.b; z1.d=z0.d;
    z1.a=z1.a/den;  z1.b=z1.b/den;
    z1.a=z1.a%N;  z1.b=z1.b%N;
    if(z1.a<0)  z1.a=z1.a+N;
    if(z1.b<0)  z1.b=z1.b+N;  

  //Resultado
  return z1;

};


//Função que calcula o mdc de dois números inteiros de 128 bits
int64_t gcd_s64(int64_t a, int64_t b){

  //Resultado
  if(b==0) return a;
  else return gcd_s64(b, a%b);

};


//Função nque fatora um minteiro de 64 bits usando a variante algébrica do algoritmo (p+1) de Williams
void williams_factorization_algebraic(int64_t N){

  //Variáveis locais
  struct algebraic_quadratic_number zN, z;
  int64_t a, b, d, factor;
  int64_t logN=2*log2(N)*log2(N)*log2(N);
  int trials=0;

  
  //Procedimento
    //Determinando os paramêtros usados no algoritmo
    restart:
    setup_williams_parameters(&a, &b, &d, N);
    z.a=a; z.b=b; z.d=d; 

    zN=algebraic_quadratic_pow_mod(z, N+1, N);
    factor=gcd_s64(N, zN.a-1);
    if(factor>1 && factor<N) goto print_factor;
    factor=gcd_s64(N, zN.b);
    if(factor>1 && factor<N) goto print_factor;


    //Teste2: testando potências de 
    for(int64_t i=0; i<logN; ++i){
    
      zN=algebraic_quadratic_mul_mod(zN, zN, N);

      factor=gcd_s64(N, zN.a-1);
      if(factor>1 && factor<N) goto print_factor;
      factor=gcd_s64(N, zN.b);
      if(factor>1 && factor<N) goto print_factor;

    }

     
  //Resultado
  trials++;
  if(trials<1000) goto restart;

  print_factor:   
  printf("Fator de %li encontrado: %li.\n", N, factor);

};

//******************************************************************************************************************************************************************
// FIM DO HEADER
#endif
