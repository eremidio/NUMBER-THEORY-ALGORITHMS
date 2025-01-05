//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE CIPOLLA PARA ENCONTRAR RAÍZES QUADRADAS CONGRUENTE MÓDULO UM NÚMERO PRIMO

/*
O ALGORITMO DE CIPOLLA É UM ALGORITMO EFICIENTE PARA RESOLVER EQUAÇÕES DO TIPO:
x² = N (mod p), COM p PRIMO. ESTE ALGORITMO USA ARITMÉTICA BÁSICA EM CORPOS
NÚMERICOS ALGÉBRICOS Q(√n), COM ELEMENTOS z=(a+b√n) (n>0 OU n<0). USANDO A
NOTAÇÃO ω=√n, TEMOS PARA z1=a1+b1ω e z2=a2+b2ω, AS SEGUINTES OPERAÇÕES:
z1+z2=(a1+a2)+(b1+b2)ω e
z1.z2=(a1.a2+b1.b2.ω²)+(a1.b2+a2.b1)ω=(a1.a2+b1.b2.n)+(a1.b2+a2.b1)ω.

NESTE ALGORITMO A ARIMÉTICA É FEITA SOBRE O CORPO FINITO GF(p²), NÚMEROS
ALGÉBRICOS A MENOS DE UMA CONGRUÊNCIA MÓDULO p.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Cipolla%27s_algorithm
                          Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance

*/


//****************************************************************************************************
//CABEÇALHO
#ifndef CIPOLLA_ALGORITHM_H
#define CIPOLLA_ALGORITHM_H
#include <stdio.h>
#include <assert.h>
#include "kronecker_symbol.h"
#include "mod_bin_exponentiation128.h"



//****************************************************************************************************
// ESTRUTURAS E FUNÇÕES AUXILIARES USADAS NO ALGORITMO
//Estrutura que representa um número algébrico Q(ω), ω=√n, z=a+bω
struct algebraic_quadratic_number{

  __int128_t a;//Usaremos inteiros de 128bits para evitar integer overflow
  __int128_t b;
  __int128_t d;

};

//Função que executa a multiplicação de números algebricos em GF(p²)
   //z1.z2=(a1.a2+b1.b2.ω²)+(a1.b2+a2.b1)ω=(a1.a2+b1.b2.n)+(a1.b2+a2.b1)ω (mod p)
struct algebraic_quadratic_number algebraic_quadratic_mul_mod(struct algebraic_quadratic_number z1, struct algebraic_quadratic_number z2, int64_t prime){

  //Restrição
  assert(z2.d==z1.d);

  //Variáveis locais
  struct algebraic_quadratic_number z;

  //Procedimentos
    //Ajustes do resultado
    z.d=z1.d;
    z.a=((z1.a*z2.a)%prime) + ((z1.b*z2.b)%prime)*z2.d;
    z.b=(z1.a*z2.b) + (z1.b*z2.a);

    z.a%=prime;
    z.b%=prime;
    
    

  //Resultado
  return z;

};


//Função que executa a exponenciação de números algebricos em GF(p²)
struct algebraic_quadratic_number algebraic_quadratic_pow_mod(struct algebraic_quadratic_number z1, int64_t power, int64_t prime){

  //Variáveis locais
  struct algebraic_quadratic_number z={1,0, z1.d}, q={z1.a, z1.b, z1.d};


  //Procedimento
    //Loop sobre os bits do expoente
    while(power>0){

      //Checando a paridade do bit do expoente
      if(power&1) z=algebraic_quadratic_mul_mod(z, q, prime);

      //Atualizando avariáveis para a próxima iteração
      q=algebraic_quadratic_mul_mod(q, q, prime);
      power>>=1;

    }

  //Resultado
  return z;

};

//****************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t cipolla_algorithm(int64_t, int64_t);


//****************************************************************************************************
//FUNÇÕES
int64_t cipolla_algorithm(int64_t n, int64_t p){

  // Teste se n é uma classe residual quadrático módulo p usando o critério de Euler
  if(kronecker(n, p)!= 1) return 0;


  //Variáveis locais
  struct algebraic_quadratic_number z, zp;
  int64_t a=2, root;
  int64_t max_power = ((p + 1)>>1); 
  int64_t result;

  // Procedimento
    //Seleção do parâmetro tal que (a²-n|p)=(-1)
    while(1){
      root=(a*a)-n;
      if(kronecker(root, p)==(-1)) break;  
      else a++;
  
    }; 

    //Ajuste de variáveis
    z.a=a; z.b=1; z.d=root;
    zp=algebraic_quadratic_pow_mod(z, max_power, p);
    

  //Resultado
  result=zp.a;
  return result;

};


//****************************************************************************************************
//FIM DO HEADER
#endif
