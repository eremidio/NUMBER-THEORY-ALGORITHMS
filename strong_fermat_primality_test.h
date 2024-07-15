//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA VERSÃO DETERMINÍSTICA DO TESTE DE PRIMALIDADE DE FERMAT IMUNE A NÚMEROS DE CARMICHAEL

/*
O PRESENTE ALGORITMO AO QUE CONSTA (GENTILEZA ENTRAR EM CONTATO CASO CONTRṔARIO) É UMA CONTRIBUIÇÃO
ORIGINAL A TEORIA DE NÚMEROS E FOI BASEADO NO ALGORITMO DESCRITO NO ARTIGO DISPONÍVEL EM:
https://www.researchgate.net/publication/238519187_Carmichael_numbers_and_a_new_primality_test
https://ieeexplore.ieee.org/document/5662138/authors#authors

PARA REFERÊNCIAS SOBRE NÚMEROS DE CARMICHAEL VER REFERÊNCIAS EM:
https://en.wikipedia.org/wiki/Carmichael_number#:~:text=%E2%80%8D.%20Carmichael%20numbers%20are%20composite,it%20is%20not%20actually%20prime


NÚMEROS DE CARMICHAEL SÃO COMPOSTOS QUE SATISFAZEM A IDENTIDADE DO PEQUENO TEOREMA DE FERMAT,
ISTO É, DADO n E a COPRIMOS TÊM-SE QUE: a^(n-1) (mod n)=1. TAIS NÚMEROS IMPEDEM QUE O PEQUENO
TEOREMA DE FERMAT SEJA USADO COMO UM TESTE DETERMINÍSTICO DE PRIMALIDADE. NO PRESENTE ALGORITMO
UMA CONDIÇÃO EXTRA É CHECADA PARA GARANTIR QUE NÚMEROS DE CARMICHAEL SEJAM DETECTADOS: PARA b
VARIANDO DE 2 A 2ln²(n) É CHECADO SE mdc(b, n)=1 E SE b^(n) (mod (b-1)n)=b. NÚMEROS DE 
CARMICHAEL NÃO PASSAM NESTE TESTE PARA TODAS AS BASES NO INTERVALO 2,..., n-1. CONJECTURA-SE
QUE SOB A VALIDADE DE HIPÓTESE DE RIEMANN 2ln²(n) É UM LIMIAR SUPERIOR PARA ATESTAR A 
PRIMALIDADE DE UM INTEIRO. NÚMEROS ATÉ 10^300(~1024) BITS FORAM TESTADOS COM SUCESSO (PROTÓTIPO
PYTHON PURO USANDO FUNÇÕES DA BIBLIOTECA PADRÃO) USANDO-SE ESSE ALGORITMO QUE COM SUCESSO DETECTOU
NÚMEROS DE CARMICHAEL ATÉ 10^15.

O ALGORITMO É COMO SE SEGUE:
1. CHECA-SE A VALIDADE DA IDENTIDADE DO TEOREMA DE FERMAT NAS BASES 2,3,5. (ETAPA NECESSÁRIA PARA
RÁPIDA DETECÇÃO DE COMPOSTOS).
2. PARA b VARIANDO DE 2 A 2ln²(n):
  2.1 SE mdc(b,n)>1, O NÚMERO EM QUESTÃO É COMPOSTO
  2.1 SE A IDENTIDADE b^(n) (mod (b-1)n)=b NÃO FOR SATISFEITA O NÚMERO EM QUESTÃO É COMPOSTO
3. UM NÚMERO QUE PASSA NOS TESTES ANTERIORES É DECLARADO PRIMO.

*/


//*******************************************************************************************
//CABEÇALHO
#ifndef STRONG_FERMAT_PRIMALITY_TEST_H
#define STRONG_FERMAT_PRIMALITY_TEST_H
#include"mod_bin_exponentiation128.h"
#include<math.h>
#include<stdbool.h>


//*******************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t gcd_u64(uint64_t, uint64_t);
bool strong_fermat_primality_test(uint64_t);


//*******************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides
uint64_t gcd_u64(uint64_t a, uint64_t b){

  if(b==0) return a;
  else return gcd_u64(b, (a%b));
};



//Função que implementa uma variante do teste de Fermat de primalidade que detecta pseudoprimos
bool strong_fermat_primality_test(uint64_t n){

  //Casos bases:
  if(n<2) return false;
  if(n==2 || n==3 || n==5 || n==7 || n==11 || n==13) return true;

  //Etapa 1: teste de Fermat nas bases 2,3,5
  if(mod_bin_pow(2,(n-1), n)!=1 || mod_bin_pow(3,(n-1), n)!=1 || mod_bin_pow(5,(n-1), n)!=1)
    return false;

  //Etapa 2: detecção de pseudoprimos de Fermat
    //Variáveis locais
    uint64_t max_mod=(2*log(n)*log(n));

    //Procedimentos
      //Loop principal
      for(uint64_t b=2; b<=max_mod; b++){

        if(gcd_u64(b, n)>1) return false;

        __int128_t mod=(b-1)*n;
        if(mod_bin_pow(b, n, mod)!=b) return false;

      }


  //Caso o número passe nos testes acima um primo foi encontrado
  return true;



};


//*******************************************************************************************
//FIM DO HEADER
#endif
