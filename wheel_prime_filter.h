//VAMOS IMPLEMENTAR O ALGORITMO DE RODA PARA FILTRAR NÚMEROS COMPOSTOS EM UM INTERVALO

/*
O MÉTODO DA RODA É USADO PARA GERAR UMA LISTA DE NÚMEROS POSSIVELMENTE PRIMOS A PARTIR DE UMA LISTA DE NÚMEROS PRIMOS
INICIAIS.

SEJAM OS EXEMPLOS QUE ILUSTRAM A APLICAÇÃO DO ALGORITMO:

PARA N=6, OS FATORES PRIMOS DE 6 SÃO 2, 3. NO INTERVALO [1,6] APENAS 1 E 5 SÃO COPRIMOS (NÃO PARTILHAM NENHUM FATOR
PRIMO) COM 6 (TÊM-SE QUE 5=(-1) mod 6), PORTANTO TEMOS DE TESTAR SEOMENTE VALORES DA FORMA 6k+1, 6k-1.


PARA N=30, OS FATORES PRIMOS SÃO 2, 3, 5. OS NÚMEROS COPRIMOS COM 30 NO INTERVALO [0, 30] SÃO 1, 7,11, 13, 17,23, 29.
PORTANTO TEMOS DE TESTAR VALORES DADO UM NÚMERO INTEIRO n QUE SATIZFAZEM: i=[1,7,11,13,17,23,29]+30k, k INTEIRO.

CADA DO INTERVALO DE BUSCA USANDO A RODA CORRESPONDE A UM GIRO DA MESMA NA BUSCA POR POSSÍVEIS NÚMEROS PRIMOS.
RODAS DE CIRCUNFERÊNCIA MAIOR QUE 30 SÃO COMPUTACIONALMENTE DISPENDIOSAS.

NOTE-SE QUE NO ALGORITMO ACIMA OS NÚMEROS COMPOSTOS FORMADOS PELA MULTIPLICAÇÃO DE FATORES PRIMOS ACIMA DO FATOR PRIMO
LIMITANTE NÃO SÃO EXCLUÍDOS DA LISTA, POR EXEMPLO, COM N=6 A LISTA INCLUI NÚMEROS COMPOSTOS COMO 91=7X13 E 143=11X13.
AINDA SIM A LISTA FUNCIONA COMO UM FILTRO PARA DESCATAR NÚMEROS NÃO PRIMOS MÚLTIPLOS DE PRIMOS PEQUENOS.

TAL ALGORITMO É PARTICULARMENTE ÚTIL PARA OTIMIZAR ALGORITMOS COMO A FATORAÇÃO POR DIVISÃO, A PENEIRA DE ERATÓSTENES,
ENTRE OUTROS NOS CASOS EM QUE NÃO FOR POSSÍVEL ESTOCAR UMA LISTA NÚMEROS PRIMOS DEVIDO A RESTRIÇÕES DE HARDWARE, POR
EXEMPLO.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Wheel_factorization

*/ 


//****************************************************************************************************************************
//CABEÇALHO
#ifndef WHEEL_PRIME_FILTER_H
#define WHEEL_PRIME_FILTER_H
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>


//CONSTANTES GLOBAIS
const int initial_primes[10]={2,3,5,7,11,13,17,19,23,29};

//****************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t gcd_u64(uint64_t, uint64_t);
uint64_t* wheel_prime_filter(uint64_t, int, uint64_t*);



//****************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides
uint64_t gcd_u64(uint64_t a, uint64_t b){
  if(b==0) return a;
  else return gcd_u64(b, (a%b));
};



//Função que gera uma lista de números possivelmente primos
uint64_t* wheel_prime_filter(uint64_t bound, int seed, uint64_t* list_size){
  
  //Restyrição
  assert(seed<10);


  //Variáveis locais
  uint64_t prime_product=1, residual_classes_size=0, n, my_size=0;
  uint64_t* filtered_interval=NULL;
  uint64_t* residue_classes=NULL;


  //Procedimentos
    //Ajuste de variáveis
    my_size=seed;
    filtered_interval=(uint64_t*)realloc(filtered_interval, seed*sizeof(uint64_t));


    //Adicionando primos pequenos a lista    
    for(uint64_t i=0; i<seed; ++i){
      filtered_interval[i]=initial_primes[i];
      prime_product = prime_product*initial_primes[i];

    };

    for(uint64_t i=filtered_interval[seed-1]; i<prime_product; i++){
      if(gcd_u64(i, prime_product)==1){
        my_size++;
        filtered_interval=(uint64_t*)realloc(filtered_interval, my_size*sizeof(uint64_t));
        filtered_interval[my_size-1]=i;
    
      }

      if(i>bound) goto final_stage;
    };


    //Calculando classes residuais módulo produto de pequenos primos
    for(uint64_t j=1; j<prime_product; ++j){
      if(gcd_u64(j, prime_product)==1){
        residual_classes_size++;
        residue_classes=(uint64_t*)realloc(residue_classes, residual_classes_size*sizeof(uint64_t));
        residue_classes[residual_classes_size-1]=j;
      }
    };   


    //Adicionando demais elementos a lista
    for(uint64_t  k=prime_product; ; k+=prime_product){
      for(uint64_t l=0; l<residual_classes_size; l++){
        n=k+residue_classes[l];
        if(n>bound) break; //Condição que determina o fim do algoritmo

        my_size++;
        filtered_interval=(uint64_t*)realloc(filtered_interval, my_size*sizeof(uint64_t));
        filtered_interval[my_size-1]=n;

      }

      if(n>bound) break; //Condição que determina o fim do algoritmo
     
    };


    //Limpando o  cachê de memória
    final_stage:
    if(residue_classes) free(residue_classes);
    residue_classes=NULL;


  //Resultado
  (*list_size)=my_size;
  return filtered_interval;
    

};


//****************************************************************************************************************************
//FIM DO HEADER
#endif
