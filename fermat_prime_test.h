//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE PRIMALIDADE DE FERMAT

/*

O TESTE DE FERMAT É UM TESTE DA PRIMALIDADE DE UM NÚMERO INTEIRO FUNDAMENTADO NO CHAMADO PEQUENO TEOREMA DE FERMAT
QUE AFIRMA QUE PARA UM DADO NÚMERO PRIMO p E UM INTEIRO a COPRIMO COM ELE a^(p-1) = 1(mod p).

EXISTEM UM CLASSE DE NÚMEROS DENOMINADAS NÚMEROS DE CARMICHAEL QUE SÃO COMPOSTOS SATISFAZENDO A IDENTIDADE ACIMA,
POR ISSO O TESTE DE FERMAT NÃO É UM TESTE DETERMINÍSTICO DE PRIMALIDADE. O ALGORITMO PODE SER TRANSFORMADO EM UM
TESTE DETERMINÍSTICO POR MEIO DE UMA DAS SEGUINTES ABORDAGENS: AUMENTANDO-SE O NÚMERO DE BASES TESTADAS a OU POR
MEIO DE UM REGISTRO DE PSEUDOPRIMOS QUE PASSAM NO TESTE PARA BASES ESPECÍFICADAS. COMO UM TESTE DE COMPOSIÇÃO O 
TESTE DE PRIMALIDADE DE FERMAT, NO ENTANTO, É DETERMINÍSTICO.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Fermat_primality_test

*/ 


//********************************************************************************************************************
//CABEÇALHO
#include"mod_bin_exponentiation128.h"
#include<stdbool.h>
#include<math.h>

//CONSTANTES GLOBAIS
const int prime_bases[25]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

//********************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t gcd_u64(uint64_t, uint64_t);
bool fermat_primality_test(uint64_t);


//********************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides para inteiros de 64 bits
uint64_t gcd_u64(uint64_t a, uint64_t b){

  if(b==0)
    return a;
  else
    return gcd_u64(b, (a%b));

};


//Função que implementa o teste de primalidade de Fermat
bool fermat_primality_test(uint64_t n){

  //Teste 1: usando o pequeno teorema de Fermat em uma pequena base de primos
  for(int j = 0; j<25; ++j){
    
    if(n==prime_bases[j])
      return true;

    if(mod_bin_pow(prime_bases[j], (n-1), n)!=1)
      return false;
  }  

  //Teste 2: aplicando o pequeno teorema de Fermat a n^(1/2) e a n^(1/3)
  if(n>1000000){
    uint64_t sqrt_n=sqrt(n);
    uint64_t cbrt_n=cbrt(n);

     if(gcd_u64(sqrt_n, n)>1 || gcd_u64(cbrt_n, n)>1)
      return false;

    if(mod_bin_pow(sqrt_n, (n-1), n)!=1 || mod_bin_pow(cbrt_n, (n-1), n)!=1 )
      return false;
  
  }


  //Caso passe nos testes acimaum forte candidato a primo foi encontrado
  return true;

};

/*
NOTA : A VARIANTE AQUI PROPOSTA É DETERMINÍSTICA ATÉ 10^6. PARA 10^7 HÁ DOIS PSEUDOPRIMOS QUE PASSAM NO TESTE.

*/


//********************************************************************************************************************
//FIM DO HEADER

