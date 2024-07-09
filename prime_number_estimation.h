//VAMOS CRIAR UM PROGRAMA QUE CALCULA O VALOR DO N-ÉSIMO NÚMERO PRIMO

/*
SUBJACENTE A HIPÓTESE DE RIEMANN, VÁRIAS FÓRMULAS PODEM SER DERIVADAS PARA ESTIMAR 
A FUNÇÃO π(x) DE CONTAGENS DE NÚMEROS PRIMOS E O VALOR p(n) DO n-ÉSIMO NÚMERO
PRIMO.

UM COMPÊNDIO DESTAS FÓRMULAS ENCONTRA-SE NOS ARTIGOS LISTADO NAS REFERÊNCIAS.

PARA MAIORES INFORMAÇÕES: https://arxiv.org/pdf/1002.0442v1
                          https://link.springer.com/article/10.1007/s11139-016-9839-4



*/


//***********************************************************************************************************
//CABEÇALHO
#ifndef PRIME_NUMBER_CALCULATOR_H
#define PRIME_NUMBER_CALCULATOR_H
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

//***********************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void get_nth_prime_bounds(uint64_t, uint64_t*, uint64_t*);
void prime_counting_function_bounds(uint64_t, uint64_t*, uint64_t*);

//***********************************************************************************************************
//FUNÇÕES
//Função que calcula limitantes superiores e inferiores para o n-ésimo número primo
void get_nth_prime_bounds(uint64_t n, uint64_t* upper_bound, uint64_t*lower_bound){
  //Restrição
  assert(n>=6);

  //Variáveis locais
  uint64_t bound1=n*(log(n*log(n))-1.0);
  uint64_t bound2=n*log(n*log(n));
  uint64_t bound3= n*( log(n) +log(log(n)) -1 + (log(log(n))-2.1)/log(n));
  uint64_t bound4=n*( log(n) +log(log(n)) -1 + (log(log(n))-2)/log(n));
  uint64_t upper, lower;

  //Procedimentos
    //Ajuste dos intervalos de valores do n-ésimo número primo
    if(n>=6 && n<688383){
      (*lower_bound)=bound1, (*upper_bound)=bound2;
    }
    else{
      (*lower_bound)=bound3, (*upper_bound)=bound4;
    }

}


//Função que calcula limitantes superiores para a função de contagem de primos π(x)
void prime_counting_function_bounds(uint64_t limit, uint64_t* upper_bound, uint64_t* lower_bound){

  //Variáveis locais
  long double asymptotic_constant=(limit*1.0)/log(limit);
  uint64_t  bound1=asymptotic_constant*(1.0+(1/(log(limit)))+(2.0/(log(limit)*log(limit))));
  uint64_t  bound2=asymptotic_constant*(1.0+(1/(log(limit)))+(2.0/(log(limit)*log(limit)))+(7.59/(log(limit)*log(limit)*log(limit))));


  //Procedimentos
    //Ajuste dos limites da função π(x)
    if(limit>=88789) (*lower_bound)=bound1;
    (*upper_bound)=bound2;

};

//***********************************************************************************************************
//FIM DO HEADER
#endif
