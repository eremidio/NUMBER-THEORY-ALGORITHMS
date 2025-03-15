//VAMOS CRIAR UM PROGRAMA QUE CALCULA A FUNÇÃO DE SOMA DE DIVISORES σ(n) USANDO SÉRIES DE LAMBERT 

/*

SÉRIES DE LAMBERT SÃO SOMAS INFINITAS DO TIPO S(x)=Σ a(n){x^n/(1-x^n)} COM n=1,2,3,....
PARA |x|<1 TEMOS QUE 1/{1-x^n}=Σx^(kn) COM k=0,1,2,3,.... DE FORMA QUE SOMAS PARCIAIS DAS SÉRIES
PODEM SER APROXIMADAS POR POLINÔMIOS.

AS SÉRIES DE LAMBERT PODEM SER REPRESENTADAS VIAS CONVOLUÇÕES DE DIRICHLET COM A FUNÇÃO IDENTIDADE 
f(n)=1 PARA n INTEIRO, DE FORMA QUE SÃO UMA FERRAMENTA MUITO ÚTIL NO ESTUDO DE FUNÇÕES ARITMÉTICAS.
EM GERAL FUNÇÕES ARITMÉTICAS MULTIPLICATIVAS PODEM SER APROXIMADAS OU SOMADAS POR SÉRIES DE LAMBERT.

PARA A FUNÇÃO DE SOMAS DE DIVISORES DE UM INTEIRO σ(n) TEMOS A SEGUINTE IDENTIDADE:
Σ{x^n}σ(n)=Σ n{x^n/(1-x^n)} QUE PODE SER USADA PARA COMPUTAR RAPIDAMENTE VALORES DE σ(n) EM UM 
INTERVALO.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Lambert_series#
                          https://en.wikipedia.org/wiki/Divisor_function 


*/


//****************************************************************************************************
//CABEÇALHO
#ifndef SUM_OF_DIVISORS_LAMBERT_SERIES_H
#define SUM_OF_DIVISORS_LAMBERT_SERIES_H
#include<stdint.h>
#include<stdlib.h>



//****************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int32_t * compute_sum_of_divisors_function(int32_t);


//****************************************************************************************************
//FUNÇÕES
/*
  NOTA: O somatório do lado direito da identidade fundamental pode ser aproximado pela relação:
        n(x^n)/{1-(x^n)} ~ n{x^n+x^(2n)+x^(3n)+...}.
        O algoritmo em sua forma final consiste em uma modificação da peneira de Eratóstenes.

*/

int32_t * compute_sum_of_divisors_function(int32_t n){


  //Variáveis locais
  int32_t* sum_of_divisors_array=(int32_t*) calloc((n+1), sizeof(int32_t));


  //Procedimentos
    //Inicializando o array de coeficientes de somas parciais da séries de Lambert
    for(int32_t k=1; k<=n; ++k) sum_of_divisors_array[k]=k+1;//1 e n são divisores triviais de qualquer número


    //Computando os valores da função de somas de divisores
    for(int32_t i=2; i<=(n/2); ++i){
      for(int32_t j=(2*i); j<=n; j+=i){
        sum_of_divisors_array[j]=sum_of_divisors_array[j]+i;

      }
    };
  
  
  //Resultado 
  return sum_of_divisors_array;


};



//****************************************************************************************************
//FIM DO HEADER
#endif
