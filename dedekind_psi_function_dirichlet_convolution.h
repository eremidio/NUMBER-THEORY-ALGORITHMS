//VAMOS CRIAR UM PROGRAMA QUE COMPUTA A FUNÇÃO ψ(n) DE DEDEKIND USANDO CONVOLUÇÕES DE DIRICHLET

/*

A FUNÇÃO ψ(n) DE DEDEKIND É FUNÇÃO MULTIPLICATVA DEFINIDA PELA RELAÇÃO ψ(n)= n[Π(1+1/p)], ONDE O PRODUTÓRIO É FEITO DOBRE TODOS OS
PRIMOS p QUE DIVIDEM n. PARA n PRIMO ψ(n)=n+1 E EM GERAL SE n FOR POTÊNCIA DE NÚMEROS PRIMOS ψ(p^k)=[p+1][p^(k-1)]. SE n NÃO TIVER
FATORES PRIMOS REPETIDOS ENTÃO ψ(n)=σ(n), ONDE σ(n) É A FUNÇÃO SOMA DE DIVISORES. TAL FUNÇÃO ARITMÉTICA É RECORRENTE NA TEORIA DE 
FORMAS MODULARES.

A FUNÇÃO ψ(n) PODE SER EXPRESSA POR MEIO DE UMA SÉRIE DE DIRICHLEΤ Σψ(n)/(n^s) = [ζ(s-1)ζ(s)]/ζ(2s). TAL FUNÇÃO PODE SER COMPUTADA 
EM BLOCOS USANDO-SE A RELAÇÃO ENVOLVENDO CONVOLUÇÕES DE DIRICHLERT ψ(n)=Id*|μ|.

TAL FUNÇÃO PODE SER GENERALIZADA PARA ORDENS SUPERIORES POR MEIO DA DEFINIÇÃO ψ(k,n)= [n^k][Π(1+1/p)]. TAL GENERALIZAÇÃO PODE SER
EXPRESSA EM TERMOS DA FUNÇÃO TOTIENTE DE JORDAN ψ(k,n)=J(2k,n)/J(k, n) E SATISFAZ RELAÇÕES ANÁLOGAS A FUNÇÃO ψ(n), A SABER:
Σψ(k, n)/(n^s) = [ζ(s-k)ζ(s)]/ζ(2s), ψ(k, n)=[n^k]*[μ²(n)] ε2(n)*ψ(k, n)=σ(k, n), ONDE ε2(n) É A FUNÇÃO CARACTERÍSTICA DOS
NÚMEROS QUADRADOS PERFEITOS.


PARA MAIORES INFORMAÇÕES: https://mathworld.wolfram.com/DedekindFunction.html
                          https://en.wikipedia.org/wiki/Dedekind_psi_function
                          https://oeis.org/A001615
                          https://mathoverflow.net/questions/422010/a-definition-related-to-pseudoprimes-and-the-dedekind-psi-function
                          https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/jordan_totient_function.h

*/


//*************************************************************************************************************************************
//CABEÇALHO
#ifndef DEDEKIND_PSI_FUNCTION_DIRICHLET_CONVOLUTION_H
#define DEDEKIND_PSI_FUNCTION_DIRICHLET_CONVOLUTION_H
#include"mobius_function_lambert_series.h"


//*************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int32_t* compute_dedekind_psi_function(int32_t);


//*************************************************************************************************************************************
//FUNÇÕES
//Função que computa a função psi de Dedekind usando convoluções de Dirichlet
int32_t* compute_dedekind_psi_function(int32_t n){

  //Ajuste de variáveis
  ++n;
 
  //Variáveis locais
  int8_t * mobius_array = compute_mobius_function(n);
  int32_t* dedekind_psi_array=(int32_t*) calloc((n+1), sizeof(int32_t));


  //Procedimentos
    //Ajuste do valorres iniciais
    dedekind_psi_array[0]=0; dedekind_psi_array[1]=1;

    //Ajuste dos coeficientes do array
    for(int32_t k=2; k<=n; ++k) dedekind_psi_array[k]+=k;

    //Computando os valores da função ψ(n) em um intervalo
    for(int32_t i=2; i<=n; ++i){

      //Restrição a inteiros não divisíveis por quadrados perfeitos
      if(mobius_array[i]==0) continue;

      //Loop principal
      int32_t l=1;
      for(int32_t j=i; j<=n; j+=i){
        dedekind_psi_array[j]+=l;
        ++l;
      } 

    }  


  //Resultado
  return dedekind_psi_array;

};


//*************************************************************************************************************************************
//FIM DO HEADER
#endif
