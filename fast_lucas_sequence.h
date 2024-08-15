//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ROTINAS EFICIENTES PARA COMPUTAR AS SEQUÊNCIAS DE LUCAS USANDO INTEIROS DE 64 BITS

/*
PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/lucas_sequence_matrix.h
*/

//*******************************************************************************************************************
//CABEÇALHO
#ifndef FAST_LUCAS_SEQUENCE_H
#define FAST_LUCAS_SEQUENCE_H
#include"mod_bin_exponentiation128.h"


//*******************************************************************************************************************
//DECLARAÇÃO
void fast_lucas_sequence(int64_t, int64_t, int64_t, __int128_t*, __int128_t*);
void fast_modular_lucas_sequence(int64_t, int64_t, int64_t,  int64_t, __int128_t*, __int128_t*);

//*******************************************************************************************************************
//FUNÇÕES 
//Função que computa os termos U(n) e V(n) das sequências de Lucas usando recursão
/*
NOTA: usaremos inteiros de 128 bits para evitar integer overflow.
*/
void fast_lucas_sequence(int64_t p, int64_t q, int64_t n, __int128_t* u, __int128_t* v){

  //Casos bases   
  if(n == 0){
    (*u) = 0;
    (*v) = 2;
        return;
  }

  if(n == 1){
    (*u) = 1;
    (*v) = p;
    return;
  }

  if(n == 2){
    (*u) = p;
    (*v) = p * p - 2 * q;
        return;
  }


  //Variáveis locais
  int64_t n_half = n / 2;
  __int128_t un, vn, unp1, vnp1;


  //Procedimentos
    //Chamada recursiva do algoritmo
    fast_lucas_sequence(p, q, n_half, &un, &vn);

    //Aplicando as fórmulas de duplicação
    if(!(n&1)){
      (*u) = un * vn;
      (*v) = vn * vn - (2 * bin_pow(q, n_half));
    }
    else {
      fast_lucas_sequence(p, q, (n_half+1), &unp1, &vnp1); //Chamada recursiva do algoritmo
      (*u) = (unp1 * vn) - bin_pow(q, n_half);
      (*v) = (vnp1 * vn) - (p * bin_pow(q, n_half));
    }
}

//Função que computa os termos U(n) e V(n) das sequências de Lucas a menos de uma relação de congruência
/*
NOTA: usaremos inteiros de 128 bits para evitar integer overflow.
*/
void fast_modular_lucas_sequence(int64_t p, int64_t q, int64_t n, int64_t mod, __int128_t* u, __int128_t* v){

  //Casos bases   
  if(n == 0){
    (*u) = (0%mod);
    (*v) = (2%mod);
        return;
  }

  if(n == 1){
    (*u) = (1%mod);
    (*v) = (p%mod);
    return;
  }

  if(n == 2){
    (*u) = (p%mod);
    (*v) = (((p*p)%mod) - ((2*q)%mod));
    return;
  }


  //Variáveis locais
  int64_t n_half = n / 2;
  __int128_t un, vn, unp1, vnp1;


  //Procedimentos
    //Chamada recursiva do algoritmo
    fast_modular_lucas_sequence(p, q, n_half, mod, &un, &vn);

    //Aplicando as fórmulas de duplicação
    if(!(n&1)){
      (*u) = (un * vn)%mod;
      (*v) = ((vn * vn)%mod - (2 * mod_bin_pow(q, n_half, mod)))%mod;
    }
    else {
      fast_modular_lucas_sequence(p, q, (n_half+1), mod, &unp1, &vnp1); //Chamada recursiva do algoritmo
      (*u) = ((unp1 * vn)%mod - mod_bin_pow(q, n_half, mod))%mod;
      (*v) = ((vnp1 * vn)%mod - (p * mod_bin_pow(q, n_half, mod)))%mod;
    }
}




//*******************************************************************************************************************
//FIM DO HEADER
#endif
