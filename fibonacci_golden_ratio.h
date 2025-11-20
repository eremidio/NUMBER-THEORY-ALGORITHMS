//VAMOS CRIAR UM PROGRAMA QUE COMPUTA A RAZÃO DE OURO

/*

A RAZÃO DE OURO É DEFINIDA PELA EQUAÇÃO φ=a/b, ONDE (a+b)/a=a/b, DONDE φ²+φ+1=0 E TEMOS QUE φ=(1+√5)/2.
O N-ÉSIMO TERMO DA SEQUÊNCIA DE FIBONACCI É DADO POR: F(n)=|⁻(φ^n)/(√5)_|, onde |⁻x_| DENOTA A FUNÇÃO
INTEIRO MAIS PRÓXIMO.

ESTA É UMA DAS CONSTANTES MAIS IMPORTANTES EM MATEMÁTICA SENDO RECORRENTE EM PROBLEMAS DE GEOMETRIA,
COMO EM CERTOS PROBLEMAS DE TESSELAGEM, ALÉM DE APARECER EM ALGUMAS IDENTIDADES ENVOLVENDO FUNÇÕES
MODULARES E A FRAÇÃO CONTINUADA DE ROGERS-RAMANUJAN. 


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Golden_ratio
                          https://www.researchgate.net/publication/322416133_A_New_Method_of_Golden_Ratio_Computation_for_Faster_Cryptosystems

*/

//*******************************************************************************************************************************************
//CABEÇALHO
#ifndef GOLDEN_RATIO_H
#define GOLDEN_RATIO_H
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>
#include<gmp.h>


//*********************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void compute_golden_ratio(mpf_t);
void compute_nth_fibonnaci_number(uint64_t, mpf_t);


//*********************************************************************************************************************************
//FUNÇÕES
//Função que computa a razão de ouro
void compute_golden_ratio(mpf_t golden_ratio){

  //Varíaveis locais
  mpf_t one, two, sqrt5, v1;
  mpf_init2(one, 8192);
  mpf_init2(two, 8192);
  mpf_init2(sqrt5, 8192);
  mpf_init2(v1, 8192);


  //Procedimento
    //Ajuste de variáveis
    mpf_set_d(v1, 5.0);
    mpf_sqrt(sqrt5, v1);
    mpf_set_d(one, 1.0);
    mpf_set_d(two, 2.0);
    
    //Computando a razão de ouro
    mpf_add(v1, sqrt5, one);
    mpf_div(golden_ratio, v1, two);

    //Limpando o cachê de memória
    mpf_clear(one);
    mpf_clear(two);
    mpf_clear(sqrt5);
    mpf_clear(v1);

};


//Função que computa o n-ésimo termo da sequência de Fibonacci
void compute_nth_fibonnaci_number(uint64_t n, mpf_t golden_ratio){

  //Variáveis locais
  mpf_t power_phi, sqrt5, five, ratio;
  mpz_t fib;
  mpf_init2(power_phi, 8192);
  mpf_init2(five, 8192);
  mpf_init2(sqrt5, 8192);
  mpf_init2(ratio, 8192);
  mpz_init(fib);


  //Procedimentos
    //Computando o n-ésimo número de Fibonacci
    mpf_pow_ui(power_phi, golden_ratio, n);
    mpf_set_d(five, 5.0);
    mpf_sqrt(sqrt5, five);
    mpf_div(ratio, power_phi, sqrt5);

    mpf_set_d(five, 0.5);
    mpf_add(ratio, ratio, five);
    mpz_set_f(fib, ratio);
  
    //Resultado  
    printf("F(%lu): ", n); gmp_printf("%.Zd\n", fib);

    //Limpando o cachê de memória
    mpf_clear(power_phi);
    mpf_clear(five);
    mpf_clear(sqrt5);
    mpf_clear(ratio);
    mpz_clear(fib);

};

//*********************************************************************************************************************************
//FIM DO HEADER
#endif
