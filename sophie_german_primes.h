//VAMOS CRIAR UM PROGRAMA PARA IDENTIFICAR NÚMEROS PRIMOS DE SOPHIE-GERMAIN PARA INTEIROS DE 64 BITS

/*
NÚMEROS PRIMOS DE SOPHIE-GERMAIN SÃO INTEIROS p QUE SÃO PRIMOS E TAIS QUE (2p+1) SÃO
PRIMOS TAMBÉM.

TAIS CLASSES DE NÚMEROS PRIMOS SÃO IMPORTANTES DO PONTO DE VISTA TEÓRICO E PRÁTICO.
POR EXEMPLO, NÚMEROS DE MERSENNE M(n)=(2^n)-1, SÃO PRIMOS SE E SOMENTE SE n SÃO
PRIMOS. EXISTE UM TEOREMA QUE AFIRMA SE p FOR PRIMO E p= 3 (mod 4), ENTÃO (2p+1) É
PRIMO SE E SOMENTE SE (2p+1) FOR DIVISOR DE M(p). TAL TEOREMA FORNECE UM RÁPIDO
TESTE DE PRIMALIDADE PARA CERTAS CLASSES DE NÚMEROS DE MERSENNE.

O SEGUINTE TEOREMA PODE SER USADO PARA TESTAR SE UM INTEIRO p É UM PRIMO DE SOPHIE-
GERMAIN: SE p FOR PRIMO E 2^(q-1)=1 (mod q) PARA q=2p+1 E q NÃO É DIVISIVEL POR 3,
ENTÃO p É UM PRIMO DE SOPHIE-GERMAIN. 

PARA MAIORES INFORMAÇÕES: A Guide To Elementary Number Theory by U. Dudley

*/

//*******************************************************************************************************
//CABEÇALHO
#ifndef SOPHIE_GERMAIN_PRIMES_H
#define SOPHIE_GERMAIN_PRIMES_H
#include"gauss_euler_primality_test.h"


//*******************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool is_sophie_germain_prime(uint64_t);


//*******************************************************************************************************
//FUNÇÕES
//Função que determina se um inteiroé um primo de Sophie Germain
bool is_sophie_germain_prime(uint64_t n){

  //Checando se n primo
  if(gauss_euler_primality_test(n)==false) return false;

  //Variáveis locais
  uint64_t q=((n<<1)+1);


  //Procedimentos
    //Testando se (2p+1) é um pseudoprimo de Fermat e não é divisível por 3
    if((n%3)!=0 && mod_bin_pow(2, (q-1), q)==1) return true;
    else return false;


};

//*******************************************************************************************************
//FIM DO HEADER
#endif
