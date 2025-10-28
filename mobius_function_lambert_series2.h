//VAMOS CRIAR UM PROGRAMA QUE COMPUTA A FUNÇÃO DE MÖBIUS μ(n) USANDO SÉRIES DE LAMBERT

/*
A FUNÇÃO DE MÖBIUS μ(n) EM UM INTERVALO PODE SER COMPUTADA POR MEIO DA SEGUINTE FÓRMULA ENVOLVENDO SÉRIES DE LAMBERT
Σ μ(n)(x^n)/{1+(x^n)}= x-2x², PARA n INTEIRO POSITIVO.
TAL IDENTIDADE PODE TER SOMAS PARCIAIS APROXIMADAS POR POLINÔMIOS E PODE SER USADA PARA COMPUTAR O VALOR DA FUNÇÃO
DE MÖBIUS EM BLOCOS PARA PEQUENOS INTERVALOS.


PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/mobius_function_lambert_series.h

*/


//*************************************************************************************************************
//CABEÇALHO
#ifndef MOBIUS_FUNCTION_LAMBERT_SERIES2_H
#define MOBIUS_FUNCTION_LAMBERT_SERIES2_H
#include<stdint.h>
#include<stdlib.h>


//*************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int8_t * compute_mobius_function(int32_t);


//*************************************************************************************************************
//FUNÇÕES
/*
  NOTA: O somatório do lado direito da identidade fundamental pode ser aproximado pela relação:
        (x^n)/{1+(x^n)} ~ (x^n){1-(x^n)+(x^2n)-(x^3n)+(x^4n)-...} = (x^n)-(x^2n)+(x^3n)-(x^4n)+(x^5n)-...
        

*/

int8_t * compute_mobius_function(int32_t n){

  //Variáveis locais
  int8_t* mobius_array=(int8_t*) calloc((n+1), sizeof(int8_t));


  //Procedimentos
    //Inicializando os primeiros elementos no array
    mobius_array[1]=1;
    mobius_array[2]=(-2);

    //Loop principal: calculando a função de Möbius em um intervalo
    for(int32_t i=1; i<=(n/2); ++i){

        int32_t step=(i*2);

        //Loop ímpar
        for(int32_t j=(i+step); j<=n; j+=step)
          mobius_array[j]=mobius_array[j]-mobius_array[i];

        //Loop par
        for(int32_t j=(step); j<=n; j+=step)
          mobius_array[j]=mobius_array[j]+mobius_array[i];

    }


  //Resultado
  return mobius_array;

};


//*************************************************************************************************************
//FIM DO HEADER
#endif
