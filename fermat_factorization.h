//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE FATORAÇÃO DE FERMAT

/*

O ALGORITMO DE FATORAÇÃO DE FERMAT É UM DOS MAIS ANTIGOS ALGORITMOS PARA FATORAR NÚMEROS INTEIROS, SENDO
EXTREMAMENTE EFICIENTE QUANDO OS FATORES PRIMOS DO NÚMERO EM QUESTÃO SÃO SUFICIENTEMENTE PRÓXIMOS A RAÍZ
QUADRADA DO NÚMERO A SER FATORADO.

SE n FOR O PRODUTO DE DOIS PRIMOS n=pq, O ALGORITMO DE FERMAT CONSISTE EM ENCONTRAR INTEIROS a,b TAIS QUE
p=(a+b), q=(a-b), DE MODO QUE n=a²-b². DESTA EQUAÇÃO SEGUE-SE QUE b²=a²-n. A IDEIA DO ALGORITMO É
ENCONTRAR NÚMEROS a,b SATISFAZENDO ESTA INDENTIDADE.

VARIANTES DESTE MÉTODO EXISTEM QUE OTIMIZAM A BUSCA POR INTEIROS a,b  SATISFAZENDO A IDENTIDADE ACIMA.
NO ALGORITMO DE LAWRENCE SE UMA ESTIMATIVA DA RAZÃO p/q=c/d, COM c,d INTEIROS FOR CONHECIDA. A BUSCA PODE
SER OTIMIZADA TOMANDO-SE (cdn)^(1/2) NO LUGAR DE n^(1/2). 



PARA MAIORES REFERÊNCIAS: Prime Numbers And Computer Method For Factorization by Hans Riesel
                          The Joy Of Factoring by Samuel Wagstaff Jr.

*/


//*************************************************************************************************************
//CABEÇALHO
#ifndef FERMAT_FACTORIZATION_H
#define FERMAT_FACTORIZATION_H
#include"prime_power_detection.h"
#include<stdio.h>

//*************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void fermat_factorization_method(int64_t);

//*************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Fermat para fatorar números inteiros
void fermat_factorization_method(int64_t n){

  //Variáveis locais
  int64_t a, b, b_squared;
  int64_t root=sqrt(n);
  int64_t p, q;


  //Procedeimento
    //Loop principal    
    for(a=root; a<n; a++){
      b_squared=(a*a)-n;
        if(fast_square_detection(b_squared, &b)==true) break;

    }

    //Cálculo dos fatores primos do número a ser fatorado
    p=(a-b);
    q=n/p;

    printf("Fatores primos de %li encontrados: %li e %li\n", n, p, q);



};



//*************************************************************************************************************
//FIM DO HEADER
#endif
