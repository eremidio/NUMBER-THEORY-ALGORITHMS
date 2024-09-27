//VAMOS CRIAR UM PROGRAMA QUE CALCULA RAÍZES CÚBICAS A MENOS DE UMA RELAÇÃO DE CONGRUÊNCIA

/*

UM INTEIRO a É DITO SER UAM CLASSE RESIDUAL CÚBICA MÓDULO UM PRIMO p SE A EQUAÇÃO DIOFANTINA
x³= a (mod p), TIVER UMA SOLUÇÃO EM F(p). O CÁLCULO DE RAÍZES CÚBICAS MODULARES É DE GARNDE
INTERESSE EM CRIPTOGRAFIA DE CURVAS ELÍPTICAS COMO SUBROTINAS EM ALGORITMOS DE COMPRESSÃO DE
PONTOS EM CURVAS E SISTEMAS BASEADO NO PAREAMENTO DE PONTOS.

A TEORIA DE CLASSES RESÍDUAIS DE ORDEM SUPERIOR É UMA EXTENSÃO DIRETA DA TEORIA DE CLASSES
RESIDUAIS QUADRÁTICAS MÓDULO p. POR EXEMPLO, O CRITÉRIO DE EULER PARA RAÍZES CÚBICAS SE
TORNA x^[(p-1)/3]=1 mod p. 

RAÍZES DE ORDEM SUPERIOR PODEM SER  CALCULADOS USANDO-SE O ALGORITMO DE ADLEMAN-MANDERS-
MILLER. O SEGUINTE ALGORITMO É BASEADO NAS PROPRIEDADES DE RAÍZES PRIMITIVAS DE F(p);

PARA MAIORES INFORMAÇÕES: https://www.researchgate.net/publication/349487108_An_Algorithms_for_Finding_the_Cube_Roots_in_Finite_Fields


*/


//***************************************************************************************************************************
//CABEÇALHO
#ifndef MODULAR_CUBIC_ROOT_H
#define MODULAR_CUBIC_ROOT_H
#include"mod_bin_exponentiation128.h"
#include<math.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<time.h>

//***************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t modular_inverse(int64_t, int64_t);
int64_t modular_cubic_root(int64_t, int64_t);

//***************************************************************************************************************************
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

//Função que calcula raízes cúbicas modulares
int64_t modular_cubic_root(int64_t a, int64_t p){

  //Casos bases: p=0 (mod 3) ou p=2 (mod 3)
  if((p%3)==0) return mod_bin_pow(a, (p/3), p);
  if((p%3)==2){

    //Variáveis locais
    int64_t y= mod_bin_pow(a, ((p-2)/3), p);
    int64_t root= modular_inverse(y, p);
    
    //Resultado
    return root;
  };

  //Caso geral: p=1 (mod 3)

  //Variáveis locais
  int64_t g0, g, k=1;
  int64_t t, x;
  int trials=0;

  //Procedimentos
    //Escolhendo uma classe residual cúbica 
    g=2+rand()%(p-2);
    while(mod_bin_pow(g, ((p-1)/3), p)!=1){
      g=1+rand()%(p-1);
      trials++;
      if(trials>25000) return 0;//Falha não foram encontradas classes residuais de ordem desejada em F(p)
    };

    //Checando se g³=a mod p
    g0=mod_bin_pow(g, 3, p);
    if(g0==a) return g;


    //Loop principal
    while(mod_bin_pow(g0, k, p)!=a){
      
      k++;
      t=mod_bin_pow(g0, k, p);
      x=mod_bin_pow(g, k, p);

      //Condição que determina o fim do loop principal
      if(k==((p-1)/3)) break;

    }
    

  //Checando se a não é uma classe resídual cúbica módulo um primo
  if(t!=a) return 0;
  else return x;


};


//***************************************************************************************************************************
//FIM DO HEADER
#endif
