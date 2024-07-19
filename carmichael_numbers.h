//VAMOS CRIAR UM PROGRAMA QUE DETECTA NÚMEROS DE CARMICHAEL

/*
OS NÚMEROS DE CARMICHAEL SATISFAZEM A SEGUINTE PROPOSIÇÃO: SENDO n UM NÚMERO COMPOSTO PARA b RELATIVAMENTE PRIMO COM n TÊM-SE
b^(n-1) = 1 (mod n) OU b^n = b (mod n).

ESTA DEFINIÇÃO FAZ COM QUE NÚMEROS DE CARMICHAEL PASSEM PELO TESTE DE PRIMALIDADE DE FERMAT (SÃO OS CHAMADOS PSEUDOPRIMOS DE
FERMAT). POR ESTA RAZÃO OS TESTE PRIMALIDADE DE FERMAT NÃO É UM TESTE 100% DETERMINÍSTICO DE PRIMALIDADE.

PARA DETECTAR SE UM NÚMERO É UM NÚMERO DE CARMICHAEL PODE-SE TESTAR PARA VALORES DE 2 ATÉ (n-1) SE AS IDENTIDADES ACIMAS NA
DEFINIÇÃO SÃO SATISFEITAS. OUTRA POSSIBILIDADE É USAR O TEOREMA DE KORSELTS QUE AFIRMA QUE: UM NÚMERO n É UM NÚMERO DE
CARMICHAEL SE E SOMENTE SE ELE NÃO TIVER FATORES PRIMOS QUADRÁTICOS E PARA TODO FATOR PRIMO p (n-1) DIVIDE (p-1).

NÚMEROS DE CARMICHAEL SÃO UM SUBCONJUNTO (SUBONJUNTO K1) DOS CHAMADOS NÚMERO DE KNÖDEL.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Carmichael_number
                          https://en.wikipedia.org/wiki/Knödel_number

*/ 

//***************************************************************************************************************************
//CABEÇALHO
#ifndef CARMICHAEL_NUMBERS_H
#define CARMICHAEL_NUMBERS_H
#include"factorization_map.h"


//***************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool carmichael_checker(uint64_t);


//***************************************************************************************************************************
//FUNÇÕES
//Função usada para detectar números de Carmichael
bool carmichael_checker(uint64_t n){

  //Caso base: n é primo ou par
  if(n==2 || gauss_euler_primality_test(n)==true) return false;
  if(!(n&1)) return false;
      

  //Variáveis locais
  uint64_t N=(n-1), divisor;
  uint64_t prime_factors[30];
  int multiplicities[30];


  //Procedimentos
    //Fatorando o número em questão
    factorization_map(n, prime_factors, multiplicities);

    //Teste1: o número em questão não deve ter fatores primos repetidos
    for(int i = 0; i<30; ++i){
      if(multiplicities[i]>n) break;
      if(multiplicities[i]>1) return false;

    }

    //Teste 2: para cada fator primo p de n, (p-1) divide (n-1)
    for(int i = 0; i<30; ++i){

      if(prime_factors[i]>=2){

        if(prime_factors[i]>n) break;

        divisor=prime_factors[i]-1;
        if((N%divisor)!=0) return false;

      };

    }

  //Caso passe nos testes acima um número de Carmichael foi encontrado
  return true; 
  
  
};

//***************************************************************************************************************************
//FIM DO HEADER
#endif
