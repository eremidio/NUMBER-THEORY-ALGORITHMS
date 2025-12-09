//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA VERSÃO DETERMINÍSTICA DO TESTE DE PRIMALIDADE DE SOLOVAY-STRASSEN

/*
O ALGORITMO DE SOLOVAY-STRASSEN É BASEADO NA SEGUINTE PROPOSIÇÃO: PARA n INTEIRO POSITIVO n É PRIMO
SE E SOMENTE a^((n-1)/2)= (a|n) mod(n) ONDE (a|n) DENOTA O SÍMBOLO DE LEGENDRE. 

TAL TESTE É A PRINCÍPIO PROBABILÍSTICO, PORÉM TESTANDO-SE UM NÚMERO SUFICIENTE DE BASES TAL TESTE
PASSA A SER DETERMINÍSTICO, CONDICIONADO A VERACIDADE DA HIPÓTESE DE RIEMANN.

PARA MAIORES INFORMAÇÕES: Algorithmic Number Theory vol. 1 by E. Bach, J. Shallit

*/


//********************************************************************************************************************
//CABEÇALHO
#ifndef SOLOVAY_STRASSEN_H
#define SOLOVAY_STRASSEN_H
#include"mod_bin_exponentiation128.h"
#include"binary_jacobi_symbol.h"
#include<math.h>
#include<stdbool.h>
#include<stdlib.h>


//********************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t gcd_s64(int64_t, int64_t);
bool solovay_strassen(int64_t);

//********************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides para inteiros de 64 bits
int64_t gcd_s64(int64_t a, int64_t b){

  if(b==0) return a;
  else return gcd_s64(b, (a%b));

};

//Função que implementa uma versão determinística do teste de primalidade de Solovay-Strassen
bool solovay_strassen(int64_t n){

  //Casos triviais: números pares
  if(n<2) return false;
  if(n==2) return true;
  if(!(n&1)) return false;


  //Variáveis locais
  int64_t log_value=(2*log(n)*log(n));
  int64_t bound=((n-1)>log_value)?log_value:(n-1);
  int64_t a, mod_power;
  int l_symbol;


  //Procedimentos
    //Loop principal
    for(a=2; a<bound; ++a){
      //Teste 1: pequenos fatores primos
      if(gcd_s64(a, n)>1) return false;

      //Teste 2 computando os símbolos de Legendre(Jacobi) e checando a relação de congruência
      l_symbol=binary_jacobi(a, n);
      mod_power= mod_bin_pow(a, (n-1)/2, n);
      if(l_symbol==mod_power) continue;
      else if (l_symbol==(-1) && mod_power==(n-1));
      else return false;
  
    }

  //Caso passe no teste acima um primo foi encontrado
  return true;

};

//********************************************************************************************************************
//FIM DO HEADER
#endif
