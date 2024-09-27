//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE ADLEMAN-MANDERS-MILLER PARA CALCULAR RAÍZES DE ORDEM SUPERIOR A MENOS DE UMA CONGRUÊNCIA

/*
O ALGORITMO DE ADLEMAN-MANDERS-MILLER É UMA GENERALIZAÇÃO DO ALGORITMO DE
TONELLI-SHANKS QUE PERMITE COMPUTAR SOLUÇÕES DA EQUAÇÃO DIOFANTINA 
x^n=a (mod p), COM p PRIMO E n>2.


PARA MAIORES INFORMAÇÕES: https://arxiv.org/pdf/1111.4877

*/


//***************************************************************************************************
//CABEÇALHO
#ifndef ADLEMAN_MANDERS_MILLER_ALGORITHM_H
#define ADLEMAN_MANDERS_MILLER_ALGORITHM_H
#include"mod_bin_exponentiation128.h"
#include<math.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<time.h>


//***************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t modular_inverse(int64_t, int64_t);
int64_t discrete_logarithm(int64_t, int64_t, int64_t);
int64_t modular_nth_root(int64_t, int64_t, int64_t);


//***************************************************************************************************
//FUNÇÕES
//Função que calcula o inverso modular de um número inteiro a (mod n) usando o algoritmo extendido de Euclides
int64_t modular_inverse(int64_t a, int64_t n) {
  // Variáveis locais
  int64_t r0, r1, x0, x1, r2, x2;

  // Procedimentos
  // Ajuste de variáveis
  r0 = a;
  r1 = n;
  r2 = 1;
  x0 = 1;
  x1 = 0;

  // Calculando os valores finais dos coeficientes recursivamente
  while (r2 > 0) {
    int64_t quotient = r0 / r1;
    r2 = r0 - quotient * r1;
    x2 = x0 - quotient * x1;

    // Atualizando variáveis para a próxima iteração
    if (r2 > 0) {
      r0 = r1;
      r1 = r2;
      x0 = x1;
      x1 = x2;
    };
  };

  // Resultado
  if (x1 < 0)
    return (x1 + n);
  else
    return x1;
};


//Função para computar logaritmos dsicretos por força bruta
int64_t discrete_logarithm(int64_t base, int64_t log, int64_t p){

  //Procedimentos: loop principal
  for(int64_t i=1; i<p; ++i){
    if(mod_bin_pow(base, i, p)==log)
      return  i;
  }
 
  //Em caso de falha
  return 0;   

};

//Função nque implamenta o algoritmo de Adleman-Manders_Miller para calcular raízes de ordem superior a menos de uma relação de congruência
int64_t modular_nth_root(int64_t root, int64_t r, int64_t p){ /*raiz, ordem, característica de F(p)*/

  //Restrições
  if((p-1)%r!=0) return 0;
  if(root>p) root%=p;

  //Semente para geração de números alatórios
  srand(time(NULL));

  //Variáveis locais
  int64_t a, b, c, h;
  int64_t d, j;
  int64_t rho;
  int64_t p_even=(p-1), t=0, s=p_even, alpha=1,  k=1;
  int trials=0;

  //Procedimentos
    //Calculando uma classe não residual de ordem r em F(p)
    rho=2+rand()%(p-2);
    while(mod_bin_pow(rho, ((p-1)/r), p)!=1){
      rho=1+rand()%(p-1);
      trials++;
      if(trials>25000) return 0;//Falha não foram encontradas classes residuais de ordem desejada em F(p)
    };



     //Calculando parâmetros s, t tais que (p-1)=s(r^t)
     while(s%r==0){
      s/=r; t++;
     }  

     //Calculando o menor parâmetro α tal que s|rα-1
     while ((k * s + 1) % r != 0) k++;
     alpha = (k * s + 1) / r;


    //Calculando os parâmetros a, b, c, d, h usados no algoritmo
    a = mod_bin_pow(rho, (mod_bin_pow(r, (t-1), (p-1)) * s) % (p-1), p);
    b = mod_bin_pow(root, (r * alpha - 1), p);
    c = mod_bin_pow(rho, s, p);
    h = 1;


    //Loop principal
    for(int64_t i = 1; i < t; i++) {
      d = mod_bin_pow(b, mod_bin_pow(r, (t - 1 - i), (p-1)), p);
      j = (d == 1) ? 0 : discrete_logarithm(a, d, p);
      b = (b * mod_bin_pow(c, j * r, p)) % p;
      h = (h * mod_bin_pow(c, j, p)) % p;
      c = mod_bin_pow(c, r, p);
    }


  //Resultado
  __int128_t result = (mod_bin_pow(root, alpha, p) * h) % p;
  if(mod_bin_pow(result, r,  p)==root)
    return (int64_t)(result);
  else return 0;//Algoritmo falhou
    
};

//***************************************************************************************************
//FIM DO HEADER
#endif
