//VAMOS CRIAR UM PROGRAMA QUE COMPUTA A FUNÇÃO TOTIENTE DE JORDAN USANDO CONVOLUÇÃO DE DIRICHLET

/*

A FUNÇÃO TOTIENTE DE JORDAN É UMA FUNÇÃO ARITMÉTICA J(k,n) QUE COMPUTA O NÚMERO DE k-TUPLAS DE INTEIROS MENORES DO QUE
n, QUE JUNTO COM n FORMAM UM CONJUNTO DE (k+1) ELEMENTOS COPRIMOS ENTRE SI. TAL FUNÇÃO É UMA GENERALIZAÇÃO DA FUNÇÃO
TOTIENTE DE EULER E DE FATO J(1,n) = φ(n) PELA DEFINIÇÃO.

ESTA FUNÇÃO É RECORRENTE EM TEORIA DE GRUPOS, NA QUAL A ORDEM DE DIVERSOS GRUPOS DE MATRIZES COMO O GRUPO DE MATRIZES
LINEARES (E LINEARES ESPECIAIS COM DETERMINANTE 1), MATRIZES SIMPLÉTICAS, ETC; COM ELEMENTOS EM UM CORPO FINITO DO
PRIMEIRO TIPO POSSUEM ORDENS DETERMINADAS PELO PRODUTO DE VALORES DA FUNÇÃO J(k,n) PARA ELEMENTOS DESTE CORPO FINITO A
MENOS DE UMA CONSTANTE MULTIPLICATIVA.

ESTA FUNÇÃO É MULTIPLICATIVA E SATISFAZ A SEGUINTE RELAÇÃO ENVOLVENDO CONVOLUÇÃO DE DIRIRCHLET J(k,n)*1=(n^k). USANDO
A FÓRMULA DE INVERSÃO DE MÖBIUS TEMOS QUE J(k,n)=μ(n)*(n^k) OU EXPLICITAMENTE J(k,n)= Σμ(n/d)(d^k), ONDE A SOMA É FEITA
SOBRE TODOS OS DIVISORES d DE n. TAIS IDENTIDADES SÃO ÚTEIS PARA SE COMPUTAR A FUNÇÃO J(k,n) EM UM INTERVALO.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Jordan%27s_totient_function#
                          https://en.wikipedia.org/wiki/Arithmetic_function#Dirichlet_convolution


*/ 


//*********************************************************************************************************************
//CABEÇALHO
#ifndef JORDAN_TOTIENT_FUNCTION_H
#define JORDAN_TOTIENT_FUNCTION_H
#include"mobius_function_lambert_series.h"
#include"mod_bin_exponentiation128.h"


//*********************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t* compute_jordan_totient_array(int32_t, int);


//*********************************************************************************************************************
//FUNÇÕES

//Função que gera um array de valores da função J(n, k) em um intervalo
int64_t* compute_jordan_totient_array(int32_t n, int k){

  //Variáveis locais
  int8_t * mobius_array = compute_mobius_function(n);
  int64_t* jordan_totient_array=(int64_t*)calloc((n+1), sizeof(int64_t));
  int64_t int_power=0;


  //Procedimentos
    //Loop principal
    for(int32_t i=1; i<=n; ++i){

      int_power=bin_pow(i, k);
      for(int32_t j=i; j<=n; j+=i){
        if(mobius_array[j/i]==0) continue;
        jordan_totient_array[j] = jordan_totient_array[j] + (mobius_array[j/i]*int_power);
      }

    };//Fim do loop principal


    //Limpando o cachê de memória
    if(mobius_array) free(mobius_array); mobius_array=NULL;


  //Resultado
  return jordan_totient_array;

};

//*********************************************************************************************************************
//FIM DO HEADER
#endif
