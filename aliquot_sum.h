//VAMOS CRIAR UM PROGRAMA PARA COMPUTAR A FUNÇÃO ARTIMÉTICA DE SOMA DE ALIQUOTAS s(n) DE UM INTEIRO

/*

A FUNÇÃO SOMA DE ALIQUOTA DE UM INTEIRO n DENOTADA POR s(n) É DEFINIDA COMO A SOMA DOS DIVISORES PRÓPRIOS DE n, ISTO É,COMO A SOMA DE
SEUS DIVISORES EXCLUINDO O PRÓPRIO n. TAL FUNÇÃO ARITMÉTICA É RELACIONADO A FUNÇÃO ARIMÉTICA SOMA DE DIVISORES σ(n) PELA RELAÇÃO
s(n) = σ(n)-n. TAL FUNÇÃO ARITMÉTICA É FORTEMENTE RELACIONADA COM A SEQUÊNCIA NÚMERICA DE ALIQUOTAS DEFINIDAS PELA RELAÇÕES:
a(0)=n, a(1)=s(n), a(2)=s(s(n)), ....

ESTA FUNÇÃO ARITMÉTICA É USADA PARA CLASSIFICAR NÚMEROS INTEIROS EM CLASSES COMO NÚMEROS PERFEITOS (SE s(n)=n), NÚMEROS DEFEITUOSOS
(SE s(n)<n), ABUNDANTES (SE s(n)>n), PRIMOS (SE s(n)=1), INTOCÁVEIS (SE NÃO EXISTIR k TAL QUE s(k)=n), ENTRE OUTROS. TAIS CLASSES
REFLETEM DIRETAMENTE A PROPRIEDADE DE DIVISIBILIDADE DO NÚMERO EM QUESTÃO.

AS SEGUINTES FÓRMULAS SÃO ÚTEIS PARA COMPUTAR SOMAS DA FUNÇÃO s(n) EM UM INTERVALO ONDE O INDEX i ASSUME OS VALORES i=1,2,3,..., n:
Σs(i)={{n(n-1)}/2}-Σ (n mod i)
Σs(i)=Σ i|_n/i_|-{{n(n+1)}/2} (|_x_| DENOTA A FUNÇÃO MENOR INTEIRO).

TAIS FÓRMULAS PERMITEM COMPUTAR s(n) USANDO TÉCNICA SIMILARES A PENEIRA DE ERATÓSTENES E SÃO ÚTEIS PARA COMPUTAR O VALOR DESTA FUNÇÃO
EM UM INTERVALO.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Aliquot_sum
                          https://oeis.org/A001065
                          https://www.parabola.unsw.edu.au/sites/default/files/2024-02/vol56_no2_3.pdf
                          https://mathworld.wolfram.com/AliquotSequence.html
                          https://en.wikipedia.org/wiki/Deficient_number
                          https://en.wikipedia.org/wiki/Abundant_number

*/


//******************************************************************************************************************************
//CABEÇALHO
#ifndef ALIQUOT_SUM_H
#define ALIQUOT_SUM_H
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>


//******************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int32_t* compute_aliquot_sum_array(int32_t);
bool is_perfect_number_aliq(int32_t, int32_t[]);
bool is_prime_number_aliq(int32_t, int32_t[]);
bool is_abundant_number_aliq(int32_t, int32_t[]);
bool is_defective_number_aliq(int32_t, int32_t[]);


//******************************************************************************************************************************
//FUNÇÕES
//Função que computa a função s(n) em um intervalo
int32_t* compute_aliquot_sum_array(int32_t n){

  //Variáveis locais
  int32_t* aliquot_sum_array = malloc((n+1)*sizeof(int32_t));


  //Procedimentos
    //Ajustando elementos no array: index 'n' --> n(n-1)/2
    for(int32_t i=0; i<=n; ++i) aliquot_sum_array[i]=((i*(i-1))>>1);

    //Ajustando o valor da soma dos elementos no array: reduzindo a parcela Σ (n mod i)
    for(int32_t i=2; i<n; ++i){
      for(int32_t j=1; j<i; ++j){

       for(int32_t k=(i+j); k<=n; k+=i){
         aliquot_sum_array[k]=aliquot_sum_array[k]-j;
       }

      }
    };


    //Computando os valores finais
    for(int32_t i=2; i<=n; i++){
      for(int32_t j=(i+1); j<=n; ++j) aliquot_sum_array[j] = aliquot_sum_array[j]-aliquot_sum_array[i];
    }


  //Resultados
  return aliquot_sum_array;

};


//Função que checa se um número é perfeito usando o valor da função aritmética s(n)
bool is_perfect_number_aliq(int32_t n, int32_t aliquot_sum_array[]){

  //Resultado
  if(aliquot_sum_array[n]==n) return true;
  else return false;  

};

//Função que checa se um número é primo usando o valor da função aritmética s(n)
bool is_prime_number_aliq(int32_t n, int32_t aliquot_sum_array[]){

  //Resultado
  if(aliquot_sum_array[n]==1) return true;
  else return false;  

};


//Função que checa se um número é abundante usando o valor da função aritmética s(n)
bool is_abundant_number_aliq(int32_t n, int32_t aliquot_sum_array[]){

  //Resultado
  if(aliquot_sum_array[n]>n) return true;
  else return false;  

};

//Função que checa se um número é defectivo usando o valor da função aritmética s(n)
bool is_defective_number_aliq(int32_t n, int32_t aliquot_sum_array[]){

  //Resultado
  if(aliquot_sum_array[n]<n) return true;
  else return false;  

};


//******************************************************************************************************************************
//FIM DO HEADER
#endif
