//VAMOS CRIAR UM PROGRAMA QUE COMPUTA A FUNÇÃO ARITMÉTICA DE PILLAI EM UM INTERVALO

/*

A FUNÇÃO DE PILLAI É DEFINIDA POR MEIO DA RELAÇÃO P(n)= Σ mdc(n, i) PARA i=1,2,...,n. ESTA FUNÇÃO ARITMÉTICA É
MULTIPLICATIVA, ISTO É, SE mdc(m,n)=1 ENTÃO P(mn)=P(m)P(n).

ELA PODE SER EXPRESSA POR MEIO DE UMA CONVOLUÇÃO DE DIRICHLET DA FUNÇÃO IDENTIDADE id(n)=n COM A FUNÇÃO
TOTIENTE DE EULER φ(n) id*φ=P, EXPLICITAMENTE P(n)= Σ {d.φ(n/d)}, ONDE A SOMA É FEITA SOBRE OS DIVISORES DE n.

A FUNÇÃO P(n) SATIFAZ A SEGUINTE PROPOSIÇÃO: UM INTEIRO n É PRIMO SE E SOMENTE SE P(n)=(2n-1).


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Pillai%27s_arithmetical_function
                          https://oeis.org/A018804


*/ 


//****************************************************************************************************************
//CABEÇALHO
#ifndef PILLAI_ARITHMETIC_FUNCTION_H
#define PILLAI_ARITHMETIC_FUNCTION_H
#include"euler_totient_function_lambert_series.h"
#include<stdbool.h>


//****************************************************************************************************************
//DECLARAÇÃO
int32_t* compute_pillai_arithmetic_function(int32_t);
bool pillai_primality_test(int32_t[], int32_t);


//****************************************************************************************************************
//FUNÇÕES
//Função que computa a função P(n) em um intervalo
int32_t* compute_pillai_arithmetic_function(int32_t n){

  //Ajuste variáveis
  n++;

  //Variáveis locais
  int32_t* pillai_array=(int32_t*) calloc((n+1), sizeof(int32_t));
  int32_t* euler_array=compute_totient_function(n);


  //Procedimentos
    //Loop principal: interando sobre o array da função totiente de Euler
    for(int32_t i=1; i<=n; ++i){
      for(int32_t j=i; j<=n; j+=i){
        pillai_array[j] = pillai_array[j]+i*euler_array[j/i];

      }    
    };//Fim do loop principal
 

    
    //Limpando o cachê de memória
    if(euler_array) free(euler_array); euler_array=NULL;


  //Resultado
  return pillai_array;

};


//Função que testa se um inteiro é primo usando a identidade P(n)=2n-1
bool pillai_primality_test(int32_t pillai_array[], int32_t n){

  //Resultado
  if(n>1 && (pillai_array[n]+1)==(n<<1)) return true;
  else return false;

};

//****************************************************************************************************************
//FIM DO HEADER
#endif
