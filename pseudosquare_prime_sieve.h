//VAMOS CRIAR UM PROGRAMA QUE USA CLASSES RESISDUAIS PSEUDOQUADRÁTICAS PARA GERAR NÚMEROS PRIMOS.

/*
CLASSES RESIDUAIS PSEUDOQUDRÁTICAS ESTÃO DIRETAMENTE RELACIONADAS A PRIMALIDADE DE NÚMEROS INTEIROS.
TAIS CLASSES PODEM SER USADAS PARA GERAR NÚMEROS PRIMOS DENTRO DE UM DETERMINADO LIMITE DE FORMA
EFICAZ. UM ALGORITMO DE PENEIRA USANDO TESTES DE  PRIMALIDADE ENVOLVENDO TAIS CLASSES RESIDUAIS TEM
A VANTAGEM DE REQUERER UM ESPAÇO MÍNIMO, AO PASSO QUE PODE SER EFICAZ O SUFICIENTE PARA USO PRÁTICO.

O PRINCIPAL PROBLEMA DE ALGORITMOS COMO A PENEIRA DE ERATÓSTENES TRADICIONAL E SUAS VARIANTES RESIDE
NA COMPLEXIDADE ESPACIAL DE TAIS ALAGORITMOS, QUE REQUER UMA GRANDE QUANTIDADE DE RECURSOS PARA
ESTOCAR OS VALORES A SEREM PROCESSADOS.

PARA MAIORES INFORMAÇÕES: https://digitalcommons.butler.edu/cgi/viewcontent.cgi?article=1095&context=facsch_papers
                          https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/pseudosquare_number.h
*/


//***************************************************************************************************************
//CABEÇALHO
#ifndef PSEUDOSQUARE_PRIME_SIEVE_H
#define PSEUDOSQUARE_PRIME_SIEVE_H
#include"pseudosquare_number.h"
#include<stdlib.h>
#include<stdio.h>


//***************************************************************************************************************
//ESTRUTURAS USADAS NO ALGORITMO

struct pseudoquare_sieve_entry{
  uint64_t number;
  bool is_prime;

};


//***************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void sieve_interval(uint64_t, uint64_t);
void pseudosquare_prime_sieve(uint64_t, uint64_t);

//***************************************************************************************************************
//FUNÇÕES

//Função que seleciona números primos em dado intervalo
/*
Para números superiores a 6.4x10^37 uma etapa adicional para remoção de potências de números primos é necessária.
Tal teste pode ser perfomado em tempo polinomial para cada entrada (ver referências na literatura).

Outra otimização sugerida no artigo é peneirar inteiros removendo múltiplos de primos tais que L(p)<maximum em 
cada intervalo, tal fase não foi implementada usamos uma peneira do tipo 30k+r, para filtrar possíveis candidatos
a números primos em um dado intevalo, com uma estrutura de dados tipo set em Python ou unordered_map em C++ essa 
melhoria pode ser implementada com um custo desprezível no tempo de execução do algoritmo.


*/
void sieve_interval(uint64_t minimum, uint64_t maximum){

  //Variáveis locais
  struct pseudoquare_sieve_entry* segment_sieve=NULL;
  register size_t sieve_size=0;
  uint64_t i;

  //Procedimentos
    //Alocando espaço no intevalo para os valores no intervalo de segmentação
    for(i=minimum; i<=maximum; ++i){
      sieve_size++;
      segment_sieve=(struct pseudoquare_sieve_entry*)realloc(segment_sieve, sieve_size*sizeof(struct pseudoquare_sieve_entry));
      segment_sieve[sieve_size-1].number=i;

      //Teste 1: usando uma roda 30k+r para remover não primos em um determinado intevalo de segmentação
      if(((i%6)==1 || (i%6)==5) && (i%5!=0)) segment_sieve[sieve_size-1].is_prime=true;
      else segment_sieve[sieve_size-1].is_prime=false;

    }
    

    //Teste 2:  usando o teste primalidade de classes residuais pseuquadráticas
    for(i=0; i<sieve_size; ++i){
      if(segment_sieve[i].is_prime==true && pseudosquare_primality_testing(segment_sieve[i].number)==false)
        segment_sieve[i].is_prime=false;
    }


    //Exibindo os primos encontrados em um dado intervalo
     for(i=0; i<sieve_size; ++i){
      if(segment_sieve[i].is_prime==true) printf("%lu, ", segment_sieve[i].number);
    }

  //Limpando o cachê de memória
  if(segment_sieve) free(segment_sieve);
    
};


//Função que implementa o algoritmo da peneira de números primos usando classes residuais pseuquadrática
void pseudosquare_prime_sieve(uint64_t limit, uint64_t sieve_size){

  //Restrição
  assert(limit<pss_pairs[1].least_solution);

  //Variáveis locais
  uint64_t minimum=301, maximum;
  

  //Procedimentos
     //*****
     printf("Eis a lista de números primos até %lu: ", limit);

    //Primos inferiores a 300
    for(int i =0; i<62; ++i){
      if(limit>primes_under300[i]) printf("%i, ", primes_under300[i]);
      else break;
    }

    if(limit<=300) return;


    //Loop principal: peneira segmentada
    while(maximum<limit){

      //Ajuste de variáveis
      maximum=minimum+sieve_size;
      if(maximum>limit) maximum=limit;

      //Filtrando os primos em um dado intervalo
      sieve_interval(minimum, maximum);
      
      //Ajuste de variáveis para a pŕoxima iteração
      minimum=maximum+1;



    }

    printf("...\n");

};

//***************************************************************************************************************
//FIM DO HEADER
#endif
