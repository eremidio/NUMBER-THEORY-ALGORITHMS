//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA A VARIANTE MAIS ROBUSTA DO TESTE PRIMALIDADE USANDO SEQUÊNCIAS DE LUCAS

/*

DENTRE OS VÁRIOS TESTES DE PRIMALIDADE ENVOLVENDO SEQUÊNCIAS DE LUCAS OU ALGUMA ESPECIALIZAÇÃO DESSAS SEQUÊNCIAS,
A VARIANTE MAIS ROBUSTA USA CRITÉRIOS SIMILARES AO DO TESTE DE MILLER-RABIN PARA VERIFICAR A PRIMALIDADE DE UM
INTEIRO.

SEJA U(n) E V(n) SEQUÊNCIAS DE LUCAS DO PRIMEIRO E SEGUNDO TIPOS. UM INTEIRO n É DENOMINADO UM FORTE PSEUDOPRIMO
DE LUCAS SE UMA DAS SEGUINTES CONDIÇÕES FOREM SATISFEITAS:

SEJA δ(n)=n-(D|n) ONDE D É UM DISCRIMINANTE DE UM POLINÔMIO DO SEGUNDO GRAU p(x)=x²+Px+Q E (|) DENOTA
O SÍMBOLO DE JACOBI. ESCREVEMOS δ(n)=d(2^s).

1. U(d)=0 (mod n)
2. V([d(2^r)])=0 (mod n) PARA ALGUM 0≲r<s.

NA VARIANTE EXTRA-FORTE DO ALGORITMO PODE-SE IMPOR A CONDIÇÃO ADICIONAL:
1'. U(d)=0 (mod n) E V(d)= 2,(-2) (mod n) PARA Q=1

ALGUMAS ESPECIALIZAÇÕES EXISTEM PARA VALORES ESPECIFICOS DOS PARÂMETROS P E Q QUE DEFINEM AS
SEQUÊNCIAS DE LUCAS. TESTES ADICIONAIS PODEM SER PERFORMADOS PARA DETECTAR RAPIDAMENTE COMPOSTOS.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Lucas_pseudoprime#Strong_Lucas_pseudoprimes


*/


//***************************************************************************************************************
//CABEÇALHO
#ifndef STRONG_LUCAS_PSEUDOPRIME_TEST_H
#define STRONG_LUCAS_PSEUDOPRIME_TEST_H
#include"binary_jacobi_symbol.h"
#include"lucas_sequence_matrix.h"
#include"prime_power_detection.h"
#include<cmath>
#include<stdlib.h>
#include<time.h>


//CONSTANTE GLOBAL
enum Show_Lucas_Certificate{Yes, No};

//***************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t gcd_s64(int64_t, int64_t);
void set_lucas_sequence_paramaters(int64_t&, int64_t&, int64_t&, int64_t);
bool strong_lucas_primality_test(int64_t, enum Show_Lucas_Certificate);


//***************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides para inteiros de 64 bits
uint64_t gcd_s64(int64_t a, int64_t b){
  
  if(b==0) return a;
  else return gcd_s64(b,(a%b));

};



//Função que define padrão para o teste via sequências de Lucas
void set_lucas_sequence_paramaters(int64_t& P, int64_t& delta, int64_t& D, int64_t n){

  //Semente para geração de números aleátórios
  srand(time(NULL));


  //Variáveis locais
  int64_t root=std::sqrt(n);
  int64_t p_=5+rand()%1000;
  int64_t d_=(p_*p_)-4;
  int jacobi=binary_jacobi(d_, n);
  

  //Resultado 
  P = p_; D = d_;
  delta = (n-jacobi);
  
};

//Função que implementa a variante extra-forte do teste de primalidade envolvendo sequências de Lucas
bool strong_lucas_primality_test(int64_t n, enum Show_Lucas_Certificate x){

  //Caso base: n<2
  if(n<2) return false;

  //Teste 1: primos inferiores a 100
  int primes100[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};

  for(auto p:primes100){
    if(n==p) return true;
    if(n%p==0){
    std::cout<<"Fator de "<<n<<" encontrado: "<<p<<'\n';
    return false;
    }

  };

  //Teste 2: descartando quadrados perfeitos e potências
  int64_t t=0;
  if(fast_square_detection(n, &t) ==true || (fast_prime_power_detection(n, &t)==true && t<n))
    return false;


  //Variáveis locais
  int64_t P=0, Q=1, D=0, delta=0;//Parâmetros da sequência de Lucas
  int64_t s=0, d=0, N=0;
  bool result=false;


  //Procedimentos
    //Ajuste dos parâmetros da sequência de Lucas
    set_lucas_sequence_paramaters(P, delta, D, n);

    //Teste 3: busca por algum fator primo comum com os parâmetros da sequência de Lucas
    if(gcd_s64(n, D)>1 || gcd_s64(n, delta)>1 || gcd_s64(n, P)>1){
      if(x==Yes) std::cout<<"Parâmetros da sequência de Lucas compartilham fatores primos comuns com"<<n<<".\n P: "<<P<<", D: "<<D<<", δ: "<<delta<<'\n'; 
      return false;
    }

    //Cálculo dos parâmetros d, s
    while(!(delta&1)){
      delta>>=1;
      s++;
    }
    d=delta; 
  
    //Teste 4: teste de sequências de Lucas
      //Teste 4.1: chcando a condição 1. U(d)=0 (mod n) OU V(d)= 2,(-2) (mod n) PARA Q=1
      Matrix<__int128_t> d_lucas_matrix=lucas_sequence_modular_matrix<__int128_t, __int128_t>(P, Q, d, n);
      if(d_lucas_matrix.matrix[1][0]<0) d_lucas_matrix.matrix[1][0]+=n;
      if(d_lucas_matrix.matrix[1][1]<0) d_lucas_matrix.matrix[1][1]+=n;

      if(d_lucas_matrix.matrix[1][0]==0 && (d_lucas_matrix.matrix[1][1]==2 || d_lucas_matrix.matrix[1][1]==(n-2))){
        result=true;
        goto yield_result;
      }


     //Teste 4.2: checando a condição 2. V([d(2^r)])=0 (mod n) PARA ALGUM 0≲r<s.
     while(s>=1){
      
       //Ajuste de parâmetros
       s--; d<<=1;
       Matrix<__int128_t> dr_lucas_matrix=lucas_sequence_modular_matrix<__int128_t, int64_t>(P, Q, d, n);
       if(dr_lucas_matrix.matrix[1][1]==0){
         result=true;
         goto yield_result;
       }

     }


  //Resultado do algoritmo
  yield_result:
  if(x==Yes){
    std::cout<<"Parâmetros da sequência de Lucas Q: 1, P: "<<P<<", D: "<<D<<'\n'; 
  }  

  return result;

};

//***************************************************************************************************************
//FIM DO HEADER
#endif
