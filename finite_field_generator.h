//VAMOS CRIAR UM PROGRAMA PARA COMPUTAR GERADORES DE UM GRUPO FINITO DO PRIMEIRO TIPO

/*
O GRUPO F(p) FORMADO POR INTEIROS A MENOS DE UMA RELAÇÃO CONGRUÊNCIA mod p FORMA UM GRUPO
CICLICO EM RELAÇÃO A OPERAÇÕES DE MULTIPLICAÇÃO E ADIÇÃO. SENDO UM GRUPO CÍCLICO, EXISTE
UM TEOREMA QUE GARANTE QUE TAL GRUPO TENHA UM GERADOR g TAL QUE CADA ELEMENTO f DE F(p)
POSSA SER ESCRITO NA FORMA f=g^i, COM i=0,1,..,(p-1). 

NÃO EXISTEM ALGORITMOS COM TEMPO DE EXECUÇÃO POLINOMIAL PARA ENCONTRAR GERADORES EM F(p),
EMBORA ALGORITMOS RAZOALVELMENTE EFICAZES PRODUZAMUM GERADOR g SE A DECOMPOSIÇÃO DE p EM
FATORES PRIMOS ESTIVER DISPONÍVEL.

PARA MAIORES INFORMAÇÕES: A Computational Introduction to Number Theory and Algebra by Victor Shoup

*/ 


//*****************************************************************************************************
//CABEÇALHO
#ifndef FINITE_FIELD_GENERATOR_H
#define FINITE_FIELD_GENERATOR_H
#include"factorization_map.h"
#include"mod_bin_exponentiation128.h"
#include<time.h>

//*****************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t finite_field_generator(uint64_t);

//*****************************************************************************************************
//FUNÇÕES
//Função que computa um gerador para um número corpo finito do primeiro tipo
uint64_t finite_field_generator(uint64_t prime){

  //Semente para geração de números aleatórios
  srand(time(NULL));

  //Variáveis locais
  uint64_t prime_factors[30];
  int multiplicities[30];
  __int128_t result=1;
  uint64_t random_number, beta=1;
  int r=0;

  //Procedimentos
    //Inicializando os arrays de fatores primos
    for(int i=0; i<30; ++i){
      prime_factors[i]=1;
      multiplicities[i]=0;
    };

    //Fatorando (n-1)
    factorization_map((prime-1), prime_factors, multiplicities);
    for(int j=0; j<30; ++j){
      if(prime_factors[j]>1) r++;
    };


    //Loop principal
    for(int k=0; k<=r; ++k){

      //Fim do loop
      if(prime_factors[k]==1) break;

      //Gerando um número aleatório cuja ordem multiplicativa é inferior a (p-1)
      while(beta==1){   
        random_number=1+rand()%(prime-1);
        beta=mod_bin_pow(random_number, ((prime-1)/prime_factors[k]), prime);
      };
  

      result=(result*mod_bin_pow(random_number, ((prime-1)/bin_pow(prime_factors[k], multiplicities[k])), prime))%prime;
    }


  //Resultado
  return  ((uint64_t) result);


};


//*****************************************************************************************************
//FIM DO HEADER
#endif
