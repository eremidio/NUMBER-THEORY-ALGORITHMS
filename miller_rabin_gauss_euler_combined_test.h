//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UM TESTE DE PRIMALIDADE DETERMINÍSTICO PARA INTEIROS DE 64 BITS

/*
COMBINANDO OS TESTES DE PRIMALIDADES DE MILLER-RABIN (BASEADO NA EXISTÊNCIA DE RAÍZES NÃO TRIVIAIS DA UNIDADE
EM CORPOS FINITOS DO PRIMEIRO TIPO) E O TESTE DE PRIMALIDADE DE GAUSS-EULER (ESTE BASEADO NA LEI DA
RECIPROCIDADE QUADRÁTICA), EFICIENTES TESTES DETERMINÍSTICOS DE PRIMALIDADE PODEM SER CRIADOS PARA INTEIROS
DE ATÉ 2048 BITS. O TESTE MISTO FORNECE UMA RESPOSTA CORRETA USANDO UM NÚMERO REDUZIDO DE BASES SE COMPARADO
A UM TESTE DE MILLER-RABIN COMUM.


PARA MAIORES INFORMAÇÕES: https://arxiv.org/pdf/2311.07048

*/

//***************************************************************************************************************
//CABEÇALHO
#ifndef MILLER_RABIN_GAUSS_EULER_COMBINED_TEST_H
#define MILLER_RABIN_GAUSS_EULER_COMBINED_TEST_H
#include"mod_bin_exponentiation128.h"
#include<math.h>
#include<stdbool.h>
#include<stdio.h>

//***************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int legendre(uint64_t, uint64_t);
uint64_t gcd_u64(uint64_t, uint64_t);
bool miller_rabin_one_run(uint64_t, uint64_t);
bool mr_ge_combined_test(uint64_t);

//***************************************************************************************************************
//FUNÇÕES

//Função que calcula o símbolo de Legendre usando o critério de Euler
int legendre(uint64_t n, uint64_t p){

  if((n%p)==0) return 0;
  else if(mod_bin_pow(n, ((p-1)/2), p)==1) return 1;
  else return (-1);

};

//Função que implementa o algoritmo de Euclides para inteiros de 64 bits
uint64_t gcd_u64(uint64_t a, uint64_t b){

  if(b==0) return a;
  else return gcd_u64(b, (a%b));

};

//Função que implementa o teste de Miller-Rabin para uma base
bool miller_rabin_one_run(uint64_t a, uint64_t n){
  
  //Restrição
  if(gcd_u64(a, n)>1) return false;

  //Variáveis locais
  uint64_t n_even, s , d;
  __int128_t x;

  //Procedimentos
    // Cálculo dos parâmetros s e d usados no algoritmo
    n_even = (n - 1);
    s = 0;

    while ((n_even % 2) == 0) {
      n_even = n_even / 2;
      s++;
    };

    d = n_even;

    //Teste 1: testando se a^d mod n = 1, (n-1)
    x=mod_bin_pow(a, d, n);
    if(x==1 || x==(n-1)) return true;
                        
    //Teste 2: checando se a unidade possuí raízes não triviais em F(n)
    for(uint64_t j = 0; j <s ; ++j) {
      x= (x*x)%n;
        if (x == (n - 1)) return true; 
 
    };

  //Caso não passe nos testes acima o número é composto
  return false;   

};


//Função que implementao test combinado de Miller-Rabin-Gauss-Euler para inteiros de 64 bits
bool mr_ge_combined_test(uint64_t n){

  //Teste 1: primos inferiores a 200
  uint64_t prime200[46]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199};

    //Teste de divisibilidade
    for(int i=0; i<46; ++i){
      if(n==prime200[i]) return true;
      if(n%prime200[i]==0) return false;
    };


  //Variáveis locais
  uint64_t mr_bases[5];
  uint64_t root=floor(sqrt(n)), half_root=floor(sqrt(n/2));
  uint64_t prime_3mod4;


  //Procedimentos

    //Selecionando bases para o teste de Miller-Rabin
    mr_bases[0]=2;
    mr_bases[1]=root-1;
    mr_bases[2]=root+1;
    mr_bases[3]=half_root-1;
    mr_bases[4]=half_root+1;


    //Realizando o teste de Miller-Rabin nas bases pré-definidas
    for(int j=0; j<5; ++j){
      if(miller_rabin_one_run(mr_bases[j], n)==false)
        return false;
    }


    //Selecionando bases para o teste de reciprocidade quadrática
    for(int k=0; k<46; ++k){
      if(prime200[k]&3==3 && legendre(n, prime200[k])==(-1)){
        prime_3mod4=prime200[k];


      //Teste da reciprocidade quadrática
      if((n&3)==1 && mod_bin_pow(prime_3mod4, ((n-1)/2), n)==(n-1)) return true;
      else if((n&3)==3 && mod_bin_pow(prime_3mod4, ((n-1)/2), n)==1) return true;

      }

    };


  //Caso não passe no teste acima o número é composto
  return false;
  
};



//***************************************************************************************************************
//FIM DO HEADER
#endif
