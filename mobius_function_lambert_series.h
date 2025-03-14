//VAMOS CRIAR UM PROGRAMA QUE COMPUTA A FUNÇÃO DE MÖBIUS μ(n) USANDO SÉRIES DE LAMBERT

/*
A FUNÇÃO DE MÖBIUS μ(n) É IGUAL A 0 PARA NÚMEROS QUE TENHAM FATORES PRIMOS REPETIDOS E IGUAL A (-1)^k ONDE
k É O NÚMERO DE FATORES PRIMOS DISTINTOS DE n.

A SEGUINTE IDENTIDADE USANDO SÉRIES DE LAMBERT É ÚTIL PARA COMPUTAR SOMAS DA FUNÇÃO DE MÖBIUS:
Σμ(n)(x^n)/{1-(x^n)} = x. TAL IDENTIDADE PODE TER SOMAS PARCIAIS APROXIMADAS POR POLINÔMIOS E PODE SER
USADA PARA COMPUTAR O VALOR DA FUNÇÃO DE MÖBIUS EM BLOCOS PARA PEQUENOS INTERVALOS.


PARA MAIORES INFORMAÇÕES: https://mathworld.wolfram.com/LambertSeries.html
                          https://metaphor.ethz.ch/x/2021/hs/401-3110-71L/ex/seventh.pdf


*/


//*************************************************************************************************************
//CABEÇALHO
#ifndef MOBIUS_FUNCTION_LAMBERT_SERIES_H
#define MOBIUS_FUNCTION_LAMBERT_SERIES_H
#include<stdint.h>
#include<stdlib.h>


//*************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int8_t * compute_mobius_function(int32_t);

//*************************************************************************************************************
//FUNÇÕES
/*
  NOTA: O somatório do lado direito da identidade fundamental pode ser aproximado pela relação:
        μ(n)(x^n)/{1-(x^n)} ~ μ(n){x^n+x^(2n)+x^(3n)+...} desta forma vemos que exceto pelo termo
        x que tem coeficiente 1 todos os demais termos da relação devem ser identicamente nulos.
        Isto implica que Σμ(d)=0 para os divisores d de um número n (com n incluso).

        No fim das contas o algoritmo final consiste em uma modificação da peneira de Eratóstenes.

*/

int8_t * compute_mobius_function(int32_t n){

  //Variáveis locais
  int8_t* mobius_array=(int8_t*) calloc((n+1), sizeof(int8_t));


  //Procedimentos
    //Inicializando o primeiro elemento array
    mobius_array[1]=1;

    //Loop principal: calculando a função de Möbius em um intervalo
    for(int32_t i=1; i<=(n/2); ++i){
      for(int32_t j=(2*i); j<=n; j+=i){
        mobius_array[j] = mobius_array[j]- mobius_array[i];
      }
    }


  //Resultado
  return mobius_array;


};


//*************************************************************************************************************
//FIM DO HEADER
#endif
