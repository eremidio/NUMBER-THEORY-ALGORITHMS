//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA AS  FUNÇÕES TOTIENTE DE JORDAN E DE CARMICHAEL

/*
A FUNÇÃO TOTIENTE DE JORDAN E A FUNÇÃO TOTIENTE DE CARMICHAEL SÃO GENERALIZAÇÕES DA FUNÇÃO TOTIENTE DE EULER.

A FUNÇÃO λ DE CARMICHAEL OU FUNÇÃO TOTIENTE REDUZIDA É DEFINIDA COMO O MENOR INTEIRO λ(n) TAL QUE TODOS OS
NÚMEROS COPRIMOS a COM n NO INTERVALO 2,..., (n-1); SATISFAZEM
A RELAÇÃO a^λ(n)=1 (mod n). 

O TEOREMA DE CARMICHAEL AFIRMA QUE PARA n= 8, 16, 32, 64, ..., (2^r) COM r>3 λ(n)=(1/2)φ(n). SE n=2, 4 OU
p^r COM p PRIMO E λ(n)=φ(n). SE n PUDER SER DECOMPOSTO EM FATORES PRIMOS DESTA NATUREZA
n=(p(1)^r(1))...(p(k)^r(k)), ENTÃO λ(n)=mmc(λ(p(1)^r(1)), ..., λ(p(n)^r(n))).

A FUNÇÃO TOTIENTE DE JORDAN É DEFINIDA PELA RELAÇÃO J(k, n)=(n^k)Π(1-(1/(p^k))).
A FUNÇÃO TOTIENTE DE JORDAN É UMA FUNÇÃO MULTIPLICATIVA DADO m E n COPRIMOS J(k, mn)=J(k, m)J(k, n).


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Carmichael_function
                          https://en.wikipedia.org/wiki/Dedekind_psi_function
                          https://en.wikipedia.org/wiki/Jordan%27s_totient_function

*/


//***********************************************************************************************************************
//CABEÇALHO
#ifndef TOTIENT_FUNCTIONS_H
#define TOTIENT_FUNCTIONS_H
#include"factorization_map.h"
#include"mod_bin_exponentiation128.h"
#include"prime_power_detection.h"
#include<stdlib.h>
#include<stdio.h>


//CONSTANTES GLOBAIS
uint64_t prime_powers[30]={0,};


//***********************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
uint64_t gcd_u64(uint64_t, uint64_t);
uint64_t lcm_prime_power_array(uint64_t[]);
uint64_t euler_totient_function_prime_power(uint64_t, int);
uint64_t carmichael_function(uint64_t);
uint64_t jordan_totient_function(uint64_t, uint64_t);
uint64_t dedekind_psi_function(uint64_t, uint64_t);


//***********************************************************************************************************************
//FUNÇÕES
//Função que calcula o gcd de dois inteiros de 64 bits
uint64_t gcd_u64(uint64_t a, uint64_t b){

  if(b==0) return a;
  else return gcd_u64(b, (a%b));

};

//Função que calcula o mínimo múltiplo comum  de um array de inteiros de 64 bits
uint64_t lcm_prime_power_array(uint64_t prime_power_array[]){

  //Caso base: potência de números primos
  if(prime_power_array[1]==0) return prime_power_array[0];


  //Caso geral:
  //Variáveis locais
  __int128_t temp=0;
  uint64_t result=1, gcd_=1;


  //Procedimento
    //Loop principal: iterando sobre elementos do array
    for(int64_t i=0; i<30; ++i){
      temp=result*prime_power_array[i];
      if(temp==0) break;
      else{
        gcd_=gcd_u64(result, prime_power_array[i]);
        result=temp/gcd_;
      }

    };///Fim do loop principal

    
  //Resultado
  return result;

};

//Função que calcula afunção totiente de Euler para potências de números primos 
uint64_t euler_totient_function_prime_power(uint64_t prime, int power){
 
 //Resultado
 return (prime-1) * bin_pow(prime,(power - 1));

};


//Função que computa o valor da função totiente de Carmichael λ(n)
uint64_t carmichael_function(uint64_t n){

  //Caso base: n é primo
  if(baillie_psw_test(n)==true) return (n-1);


  //Variáveis locais
  uint64_t prime_powers[30];
  uint64_t primes[30];
  int multiplicities[30];
  

  //Procedimentos
    //Ajuste de variáveis
    for(int k=0;  k<30; ++k){
      prime_powers[k]=0;
      primes[k]=0;
      multiplicities[k]=1;
    }
    
    //Calculando a decomposição de n em fatores primos
    factorization_map(n, primes, multiplicities);
    
    //Cálculo das potências de números primos
    for(int i=0;  i<30; ++i){
      if(primes[i]==0) break;
      else{
        prime_powers[i]=euler_totient_function_prime_power(primes[i], multiplicities[i]);
        if(primes[i]==2 && multiplicities[i]>2) prime_powers[i]=prime_powers[i]/2;
      }
    }
    

  //Resultado
  uint64_t result=lcm_prime_power_array(prime_powers);
  return result;


};


//Função que computa o valor da função totiente de Jordan J(k, n)
uint64_t jordan_totient_function(uint64_t n, uint64_t k){

  //Caso base:
  if(n==1) return 1;


  //Variáveis locais
  uint64_t primes_[30];
  int multiplicities_[30];
  __int128_t J=1;
  

  //Procedimentos
    //Ajuste de variáveis
    for(int m=0;  m<30; ++m){
      primes_[m]=0;
      multiplicities_[m]=1;
    }


    //Calculando a decomposição de n em fatores primos
    factorization_map(n, primes_, multiplicities_);
 

    //Interando sobre fatores primos distintos de n
    for(int i=0; i<30; ++i){

      if(primes_[i]<2) break;
      else{
        __int128_t j0=bin_pow(primes_[i], k*multiplicities_[i]);
        __int128_t j1=bin_pow(primes_[i], (multiplicities_[i]-1)*k);
        J=J*(j0-j1);

      }

    };//Fim do loop principal

  
  //Resultado
  return J;

};


//Função Ψ de Dedekind
uint64_t dedekind_psi_function(uint64_t n, uint64_t k){
  return jordan_totient_function((2*k),n)/(jordan_totient_function(k,n));
};


//***********************************************************************************************************************
//FIM DO HEADER
#endif
