//VAMOS CRIAR UM PROGRAMA QUE COMPUTA RAÍZES PRIMITIVAS PARA GRUPOS FINITOS DO PRIMEIRO TIPO QUE SÃO CÍCLICOS

/*
AS SEGUINTES PROPOSIÇÕES SÃO ÚTEIS PARA SE COMPUTAR RAÍZES PRIMITIVAS (GERADORES DO GRUPO
DE INTEIROS A MENOS DE UMA CONGRUÊNCIA):

PROPOSIÇÃO 1: SE g FOR UMA RAÍZ PRIMITIVA DE F(p), INTEIROS A MENOS DE UMA CONGRUÊNCIA 
MÓDULO p, COM p PRIMO, ENTÃO g OU (g+p) É UMA RAÍZ PRIMITIVA MÓDULO p^a, PARA TODO a,
INTEIRO.

PROPOSIÇÃO 2: SE g FOR UMA RAÍZ PRIMITIVA MÓDULO p^a, COM p PRIMO E a INTEIRO, ENTÃO
g OU (g+(p^a)), QUALQUER DESTES QUE FOR ÍMPAR É UMA RAÍZ PRIMITIVA MÓDULO 2(p^a).


TAIS PROPOSIÇÕES SÃO ÚTEIS PARA SE COMPUTAR RAÍZES PRIMITIVAS PEQUENAS PARA GRUPOS 
CÍCLICOS. É INTERESSANTE OBSERVAR QUE NO CASO DE q=(2^a), COM a>2, F(q) É 
ISOMÓRFICO A SOMA DIRETA DE Z/2Z COM UM SUBRGUPO CÍCLICO DE ORDEM q'=2^(a-2).

ROTINA ÚLTIL COMO SUBROTINA EM OUTROS ALGORITMOS.

PARA MAIORES INFORMAÇÕES: A Course In Computational Algebraic Number Theory by Henri Cohen


*/


//*********************************************************************************************************
//CABEÇALHO
#ifndef LEAST_PRIMITIVE_ROOT_H
#define LEAST_PRIMITIVE_ROOT_H
#include"factorization_map.h"
#include"prime_power_detection.h"
#include<stdio.h>

//*********************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t primitive_root_prime_module(uint64_t);
uint64_t primitive_root_prime_power_module(uint64_t, uint64_t);
uint64_t primitive_root_double_prime_power_module(uint64_t, uint64_t, uint64_t);
uint64_t find_primitive_root(uint64_t);


//*********************************************************************************************************
//FUNÇÕES
//Função que computauma raíz primitiva em F(p)
uint64_t primitive_root_prime_module(uint64_t prime){

  // Variáveis locais
  uint64_t prime_factor_array[30];
  int multiplicities[30];
  uint64_t exponent=1, tester=1, g=2;


  //Procedimentos
    //Inicializando os arrays de fatores primos
    for(int i=0; i<30; ++i){
      prime_factor_array[i]=1;
      multiplicities[30]=0;
    };

    factorization_map((prime-1), prime_factor_array, multiplicities);

   //Teste loop principal
   restart:
   for(int j=0; j<30; ++j){
    
     if(prime_factor_array[j]==1) break;//Fim do loop
       exponent=(prime-1)/prime_factor_array[j];
       tester=mod_bin_pow(g, exponent, prime);
       if(tester==1){
         g++; goto restart;
       }
     
   }
   

  //Resultado
  return g;

};


//Função que computa uma raíz primitiva em F(p^k)
uint64_t primitive_root_prime_power_module(uint64_t n, uint64_t prime){

  //Variáveis locais
  uint64_t g=primitive_root_prime_module(prime);
  uint64_t g1=mod_bin_pow(g, (prime-1), (prime*prime));


  //Resultado
  if(g1!=1) return g;
  else return (g+prime);

};


//Função que computa uma raíz primitiva em F(2(p^k))
uint64_t primitive_root_double_prime_power_module(uint64_t n, uint64_t prime_power, uint64_t prime){

  //Variáveis locais
  uint64_t g=primitive_root_prime_power_module(prime_power, prime);

  //Resultado
  if(g&1) return g;
  else return (g+prime_power);

};


//Função que calcula raízes primitivas em F(n)
uint64_t find_primitive_root(uint64_t n){

  //Caso 1: n é primo, 2, 4
  if(n==2) return 1;
  if(n==4) return 3;
  if(gauss_euler_primality_test(n)==true) return primitive_root_prime_module(n);
  

  //Variáveis locais
  uint64_t prime_power, prime;
  int power;


  //Caso 2: n é uma potência de número primo
  if(fast_prime_power_detection(n, &prime)==true){
    if(prime==2) return 5;
    else return primitive_root_prime_power_module(n, prime);

  }


  //Caso 3: n é o dobro da potência de um número primo
  if(!(n&1)){
    prime_power=n>>1;
    if(fast_prime_power_detection(prime_power, &prime)==true)
      return primitive_root_double_prime_power_module(n, prime_power, prime);
  }

  //Caso não atenda aos critérios acima não existem raízes primitivas módulo n
  return 0;

};


//*********************************************************************************************************
//FIM DO HEADER
#endif
