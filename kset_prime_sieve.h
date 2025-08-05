//VAMOS CRIAR UM PROGRAMA PARA GERAR NÚMEROS PRIMOS USANDO TEORIA DE CONJUNTOS 

/*

SEJAM m, i, k NÚMEROS INTEIROS. DEFINIMOS PARA 1≲i≲k, O CONJUNTO A(i)={(2i+1)(2i+2n+1): O≲n(i)≲|_(m-(2i+1))/(4i+2)_|}
(|_x_| DENOTA A FUNÇÃO MENOR INTEIRO). SE n(k+1)<0, ENTÃO A(k+1)={} (COJUNTO VÁZIO) COMO (2i+1)(2i+2n+1) É UM INTEIRO
COMPOSTO E ÍMPAR. PODE-SE CONCLUIR QUE OCONJUNTO DE PRIMOS INFERIORES A P(m) É DADO POR P(m)={2}U(B-A), ONDE B É O 
CONJUNTO DEFINIDO POR B={2j+1: 1≲i≲|_(m-1)/2_|}.

DE TAIS OBSERVAÇÕES OBTÉM-SE UM ALGORITMO QUE SIMILAR A UMA VARIANTE OTIMIZADA DO CRIVO DE SUNDARAM, COM ECONOMIA DE 
MEMÓRIA E TEMPO DE EXECUÇÃO. O ALGORITMO PODE SER ACELERADO SE PARALELIZADO.

PARA MAIORES INFORMAÇÕES: https://www.mdpi.com/2073-8994/14/12/2527

*/


//***********************************************************************************************************************************
//CABEÇALHO
#ifndef KSET_PRIME_SIEVE_H
#define KSET_PRIME_SIEVE_H
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

//***********************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int32_t* kset_prime_sieve(int32_t, size_t*);


//***********************************************************************************************************************************
//FUNÇÕES
//Função que gera números primos usando conjuntos k
int32_t* kset_prime_sieve(int32_t m, size_t* p_size){

  //Variáveis locais
  int32_t Bsize=(m-1)/2, prime_index=0;
  int32_t k = (int32_t)((sqrt(m)-1)/2); 
  bool* B=(bool*)malloc(Bsize*sizeof(bool));//Cada index marca um inteiro ímpar i->2i+1
  int32_t* prime_array=NULL;


  //Procedimentos
    //Ajuste de variáveis
    prime_index++;
    prime_array=(int32_t*)realloc(prime_array, prime_index*sizeof(int32_t));
    prime_array[prime_index-1]=2; //Único primo par

    for(int32_t i=0; i<Bsize; ++i) B[i]=true;//Array que será peneirada
    
    //Loop principal: descartando ímpares compostos
    for (int32_t i = 1; i <= k; ++i) {

      int32_t d = (m-(2*i+1)*(2*i+1))/(4*i+2);
      int32_t n = 0;

      while (d!=0 && n<=d) {
        int32_t index = ((2*i+1)*(2*i+2*n+1))/2;
        if (index < Bsize) B[index] = 0; 
        n++;
      }

    }//Fim do loop principal


    //Preenchendo um buffer de números primos
    for(int32_t j=1; j<Bsize; ++j){
      if(B[j]==true){
        prime_index++;
        prime_array=(int32_t*)realloc(prime_array, prime_index*sizeof(int32_t));
        prime_array[prime_index-1] = (2*j+1);
      }
    }
    
    //Limpando cachê de memória
    if(B) free(B); B=NULL;

    //Resultado
    (*p_size)=prime_index;
    return prime_array;

}




//***********************************************************************************************************************************
//FIM DO HEADER
#endif
