//VAMOS CRIAR UM PROGRAMA QUE COMPUTA A FUNÇÃO TOTIENTE DE EULER φ(n) USANDO SÉRIES DE LAMBERT


/*

A FUNÇÃO TOTIENTE DE EULER φ(n) COMPUTA O NÚMERO DE INTEIROS NO INTERVALO {1,...,(n-1)} QUE SÃO COPRIMOS
COM n (NÃO POSSUEM FATORES PRIMOS COMUNS COM n).

A SEGUINTE IDENTIDADE USANDO SÉRIES DE LAMBERT É ÚTIL PARA COMPUTAR SOMAS DA FUNÇÃO TOTIENTE DE EULER:
Σφ(n)(x^n)/{1-(x^n)} = {x/(1-x)²}. TAL IDENTIDADE PODE TER SOMAS PARCIAIS APROXIMADAS POR POLINÔMIOS E 
PODE SER USADA PARA COMPUTAR O VALOR DA FUNÇÃO TOTIENTE DE EULER EM BLOCOS PARA PEQUENOS INTERVALOS.


PARA MAIORES INFORMAÇÕES: https://mathworld.wolfram.com/LambertSeries.html
                          https://metaphor.ethz.ch/x/2021/hs/401-3110-71L/ex/seventh.pdf
 


*/


//*************************************************************************************************************
//CABEÇALHO
#ifndef EULER_TOTIENT_FUNCTION_LAMBERT_SERIES_H
#define EULER_TOTIENT_FUNCTION_LAMBERT_SERIES_H
#include<stdint.h>
#include<stdlib.h>



//*************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int32_t * compute_totient_function(int32_t);

//*************************************************************************************************************
//FUNÇÕES
//Função que computa a função φ(n) para um determinado intervalo
/*
  NOTA: Seja x/(1-x)²=x/(1-2x+x²)=x/{1-f(x)} com f(x)=-x²+2x, temos que a soma final pode ser aproximada por
        polinômios como x/(1-x)²~ x(1+f(x)+f²(x)+...).


        Computando os primeiros termos da série até ordem 4 temos que xf(x)=-x³+2x²,  xf²(x)=4x³-4x⁴+...,
        xf³(x)=8x⁴+....  e assim por diante de forma que até ordem 4 temos:
        x/(1-x)²~ x(1+f(x)+f²(x)+f³(x)+...) ~ x+2x²+3x³+4x⁴+....

        A forma geral de um termo da soma é n(x^n).

        Os coeficientes do polinômio calculado são na verdade a soma dos valores de φ(n) para os divisores de
        um número, por exemplo: o coeficiente do termo x^6 é φ(1)+φ(2)+φ(3)+φ(6), ao passo que o coeficiente
        do termo x^4 é φ(1)+φ(2)+φ(4). Comparando as identidades dos dois lados da equação para o exemplo
        anterior temos que: φ(1)=1, φ(1)+φ(2)=2, φ(1)+φ(3)=3, φ(1)+φ(2)+φ(4)=4. Resolvendo esse sistema
        podemos obter os valores individuais da função φ(n).

        No final o algoritmo em questão se reduz a uma variante do crivo de Eratóstenes para computar valores
        de φ(n) em um bloco.

*/

int32_t * compute_totient_function(int32_t n){

  //Variáveis locais
  int32_t* totient_array=(int32_t*) malloc((n+1)*sizeof(int32_t));


  //Procedimentos
    //Inicializando o array de coeficientes de somas parciais da séries de Lambert
    for(int32_t k=2; k<=n; ++k) totient_array[k]=(k-1);//φ(1)=1
    totient_array[1]=1;

    //Computando os valores da função totiente de Euler
    for(int32_t i=2; i<=(n/2); ++i){
      for(int32_t j=(2*i); j<=n; j+=i){
        totient_array[j]=totient_array[j]-totient_array[i];

      }
    };
  
  
  //Resultado 
  return totient_array;

};


//*************************************************************************************************************
//FIM DO HEADER
#endif
