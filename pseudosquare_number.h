//VAMOS CRIAR UM PROGRAMA QUE COMPUTA CLASSES RESIDUAIS PSEUQUADRÁTICAS

/*
UM INTEIRO n É DITO SER UMA CLASSE QUADRÁTICA RESIDUAL MÓDULO p SE EXISTIR UM INTEIRO r TAL QUE
r² = n (mod p).

UM NÚMERO INTEIRO L(p) É DENOMINADO UMA CLASSE RESIDUAL PSEUDOQUADRÁTICA MÓDULO UM PRIMO p, SE
ELES ATISFAZ AS SEGUINTES CONDIÇÕES:
1. L(p) = 1 (mod 8)
2. PARA TODOS OS PRIMOS p(i)<p O SÍMBOLO DE LEGENDRE (L(p)|p)=1.

CLASSE RESIDUAIS PSEUDOQUADRÁTICAS ESTÃO RELACIONADAS COM A QUESTÃO DA TESTAGEM DE PRIMALIDADE
DE NÚMEROS INTEIROS. ALGORITMOS DE PENEIRA PARA SELEÇÃO DE NÚMEROS PRIMOS USAM ESTAS CLASSES
(VER REFERÊNCIAS) TAIS ALGORITMOS EM GERAL SÃO MENOS EFICIENTES QUE TÉCNICAS MAIS TRADICIONAIS
COMO A PENEIRA DE ERASTOTÉNES, PORÉM GERAM ECONOMIA DE ESPAÇO.

PARA MAIORES INFORMAÇÕES: https://digitalcommons.butler.edu/cgi/viewcontent.cgi?article=1095&context=facsch_papers
                          https://cr.yp.to/bib/1996/lukes.pdf
                          https://digitalcommons.butler.edu/cgi/viewcontent.cgi?article=1095&context=facsch_papers
                          https://oeis.org/A002189


*/ 

//**************************************************************************************************************************
//CABEÇALHO
#ifndef PSEUDOSQUARE_NUMBER_H
#define PSEUDOSQUARE_NUMBER_H
#include<assert.h>
#include<stdbool.h>
#include"mod_bin_exponentiation128.h"

//CONSTANTES 

const int primes_under300[62]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
  101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
  233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293};

//**************************************************************************************************************************
//ESTRUTURAS USADAS NO ALGORITMO

struct pseudosquare_pair{
  int prime;
  uint64_t least_solution;

};

//CONSTANTES
const struct pseudosquare_pair pss_pairs[2]={{37, 1083289}/*32 bit*/,{229, 196640248121928601}/*64 bit*/};


//**************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int legendre(uint64_t, uint64_t);
uint64_t find_least_pseudosquare(int);
bool pseudosquare_primality_testing(uint64_t);

//**************************************************************************************************************************
//FUNÇÕES
//Função que calcula o símbolo de Legendre usando o critério de Euler
int legendre(uint64_t n, uint64_t p){

  if((n%p)==0) return 0;
  else if(mod_bin_pow(n, ((p-1)/2), p)==1) return 1;
  else return (-1);

};


//Função que calcula o menor L(p) que satisfaz as condições que definem classes residuais pseudoquadráticos módulo um primo
uint64_t find_least_pseudosquare(int prime){

  //Variáveis locais
  int64_t result=1;
  int k;
  bool lp_check;


  //Procedimentos
    //Ajuste de variáveis
    restart:
    result+=8;

    //Teste 1: Loop sobre o array de números primos
      for(k=1; ;++k){
        int p=primes_under300[k];
        int tester=legendre(result, p);
        
          if(tester!=1){
            lp_check=false;
            goto restart;
                       };

        if(p==prime) break;        

      };

    //Teste 2: checando se o argumento da função é o menor primo ímpar tal que (Lp|p)=1
    ++k;
    int p=primes_under300[k];
    int tester=legendre(result, p);
    if(tester==1  || tester==0) goto restart;


  //Resultado
  return result;

};


//Função que executa o teste de primalidade usando classes resisduais pseudoquadráticas módulo p
/*
NOTA: POTÊNCIAS DE NÚMEROS PRIMOS PODEM PASSAR NESTE TESTE, UM TESTE DE DETECÇÃO DE POTÊNCIAS DE
NÚMEROS PRIMOS OPCIONALMENTE DEVE SER PERFORMADO, PARA GARANTIR QUE O RESULTADO ESTEJA 100% CORRETO.
*/
bool pseudosquare_primality_testing(uint64_t n){

  //Restrição
  assert(n<pss_pairs[1].least_solution);

  //Variáveis locais
  uint64_t exponent=((n-1)/2);
  int current_prime=0;
  int negative_checks=0;
  int upper_prime_bound=(n<pss_pairs[0].least_solution)?pss_pairs[0].prime:pss_pairs[1].prime;


  //Procedimentos
    //Teste 1: teste para pseudoprimos base 2
    if(mod_bin_pow(2, (n-1), n)!=1) return false; //Teste de Fermat na base 2
    if((n&7)==5 && mod_bin_pow(2, exponent, n)!=(n-1)) return false;

    //Teste 2: teste envolvendo primos tais que  L(p)>n
    for(int k=0; ;++k){
      current_prime=primes_under300[k];
      if(n==current_prime) return true;

      uint64_t tester=mod_bin_pow(current_prime, exponent, n);
      if(tester==(n-1)) negative_checks++;
      if(tester!=1 && tester!=(n-1)) return false;

      if(current_prime==upper_prime_bound) break;
 
    }
    
    //Teste 3: teste de possíveis primos da forma p=1 (mod 8)
    if((n&7)==1 && negative_checks==0) return false;

    //Caso passe nos testes acima um primo ou potência de nprimo foi encontrado
    return true;
};

//**************************************************************************************************************************
//FIM DO HEADER
#endif
