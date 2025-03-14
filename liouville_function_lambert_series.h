//VAMOS CRIAR UM PROGRAMA QUE COMPUTA A FUNÇÃO DE LIOUVILLE λ(n) USANDO SÉRIES DE LAMBERT

/*

A FUNÇÃO DE LIOUVILLE λ(n) É DEFINIDA PELA RELAÇÃO λ(n)=(-1)^Ω(n), ONDE Ω(n) É A FUNÇÃO QUE COMPUTA O NÚMERO
DE (NÃO NECESSARIAMENTE DISTINTOS) FATORES PRIMOS QUE DIVIDEM n. A FUNÇÃO L(n) É DEFINIDA COMO O SOMATÓRIO
DE λ(k) PARA TODO k NO INTERVALO k=1,2,...n. EXISTEM IMPORTANTES IDENTIDADES ENVOLVENDO ESTAS FUNÇÕES COM
OUTRAS CLASSES DE FUNÇÕES ARITMÉTICAS.

A FUNÇÃO DE LIOUVILLE PODE SER COMPUTADA EM BLOCOS DE FORMA EFICIENTE USANDO A SEGUINTE IDENTIDADE 
ENVOLVENDO SÉRIES DE LAMBERT: Σ λ(n)(x^n)/{1-(x^n)} = Σ x^(n^2).

PARA MAIORES INFORMAÇÕES: https://mathworld.wolfram.com/LambertSeries.html
                          https://mathworld.wolfram.com/LiouvilleFunction.html
                          https://oeis.org/A008836

*/


//*************************************************************************************************************
//CABEÇALHO
#ifndef MOBIUS_FUNCTION_LAMBERT_SERIES_H
#define MOBIUS_FUNCTION_LAMBERT_SERIES_H
#include<stdint.h>
#include<stdlib.h>


//*************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int8_t * compute_liouville_function(int32_t);


//*************************************************************************************************************
//FUNÇÕES
//Função que computa a função λ(n) em um intervalo usando somas parciais de séries de Lambert
/*
NOTA : O somatório do lado direito da identidade fundamental pode ser aproximado pela relação:
       λ(n)(x^n)/{1-(x^n)} ~  λ(n){x^n+x^(2n)+x^(3n)+...}, desta forma vemos que os coeficientes
       dos termos x^n correspondem a soma dos valores de λ(d) para os divisores de um número n
       (n incluso). Tais elementos são identicamente nulos se n não for um quadrado perfeito e 
       identicamente igual a 1 em caso contrário.

      O algoritmo final resultante é uma variante do mesmo algoritmo para computar a função de 
      Möbius.

*/

int8_t * compute_liouville_function(int32_t n){

  //Variáveis locais
  int8_t* liouville_array=(int8_t*) calloc((n+1), sizeof(int8_t));


  //Procedimentos
    //Inicializando os elementos do array
   for(int32_t k=1; (k*k)<=n; ++k) liouville_array[k*k]=1;

    //Loop principal: calculando a função de Möbius em um intervalo
    for(int32_t i=1; i<=(n/2); ++i){
      for(int32_t j=(2*i); j<=n; j+=i){
        liouville_array[j]=liouville_array[j]-liouville_array[i];
      }
    }


  //Resultado
  return liouville_array;

};


//*************************************************************************************************************
//FIM DO HEADER
#endif
