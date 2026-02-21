//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO POLLARD (P-1) PARA FATORAR NÚMEROS INTEIROS

/*

O ALGORITMO DE POLLARD (p-1) FAZ USO DO CHAMADO PEQUENO TEOREMA DE FERMAT SENGUNDO O QUAL PARA QUAISQUER NÚMEROS COPRIMOS a E p, ISTO É,
TAL QUE mdc(a, p) = 1, TEMOS QUE a^(p-1)≡1 (mod p). COMO EXEMPLO SEJAM a=2, p=3, a^(p-1)=2^(3-1)=4≡1 (mod 3). SIMILARMENTE PARA a=4,
p=7 TEMOS QUE a^(p-1)=4^(7-1)=4096≡1 (mod 7). 

SEJA n UM NÚMERO COMPOSTO, PELO MENOS UM FATOR f NÃO TRIVIAL DE n OBEDECE AS RELAÇÕES f < n E f<n^(1/2). SEJAM p, q DOIS NÚMEROS NO
INTERVALO [0, n-1]. p≡q (mod n) APENAS NOS CASOS EM QUE p E q SÃO IDÊNTICOS. SEJAM p E q DOIS NÚMEROS PRIMOS E SUPONHA QUE n SEJA UM
PRODUTO DESTES DOIS FATORES PRIMOS. SEJA (p-1) UM FATOR PRIMO DE UM NÚMERO l DE MODO QUE l=k(p-1), ONDE k É UM INTEIRO QUALQUER. PELO
TEOREMA DE FERMAT TEMOS QUE: a^l≡(a^(p-1))^k (mod p)≡1. USANDO ESTES RESULTADOS OBTEMOS QUE p DIVIDE a^l, E POR SUPOSIÇÃO p É UM FATOR
PRIMO DE n. ASSIM O mdc(a^l-1, n) INCLUIRÁ p COM CERTEZA. O PROBLEMA RESIDE ENTÃO EM ENCONTRAR UM VALOR DE l ADEQUADO.

O ALGORITMO É EFICIENTE PARA ENCONTRAR UM FATOR PRIMO PRIMO p SE (p-1) FOR UM NÚMERO SUAVE EM RELAÇÃO A UM LIMITANTE B, ISTO É, SE (p-1)
NÃO TIVER FATORES PRIMOS MAIORES QUE B. A DISTRIBUIÇÃO DE NÚMEROS SUAVES É DETERMINADA PELA FUNÇÃO DE DICKMAN-DEBRUIJN. EXISTEM VÁRIOS
MÉTODOS DE ESTENDER O ALGORITMO PARA CAPTURAR FATORES PRIMOS TAIS QUE PELO MENOS UM DOS FATORES PRIMOS PRIMOS DE (p-1) SEJA SUPERIOR AO
LIMITE B USADO NO ESTÁGIO 1 DO ALGORITMO. O ALGORITMO FATORAÇÃO VIA CURVAS ELÍPTICAS É UMA EXTENSÃO NATURAL DO ALGORITMO DE POLLARD
(p-1) QUE USA PONTOS DE COODERNADAS RACIONAIS (CORPO FINITO) EM CURVAS ALGÉBRICAS.

                                                                                                          
PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Pollard%27s_p_−_1_algorithm
                          https://en.wikipedia.org/wiki/Dickman_function
                          https://en.wikipedia.org/wiki/Buchstab_function
                          https://math.mit.edu/classes/18.783/2013/LectureNotes12.pdf
                          Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance
                          Prime Numbers And Computer Methods For Factorization, by Hans Riesel

*/


//***********************************************************************************************************************************
//CABEÇALHO
#ifndef POLLARD_P_MINUS_ONE_FACTORIZATION_H
#define POLLARD_P_MINUS_ONE_FACTORIZATION_H
#include"pseudosquare_number.h"
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<gmp.h> 


//CONSTANTES GLOBAIS
const int POLLARD_P_CYCLE=127;  //2^7-1
const int POLLARD_P_MAX_DIFF=50001; //Gaps entre primos até 10^5


//***********************************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
bool* prime_sieve_setup(int64_t);
void pollard_p_minus_1_factorization_stage2(mpz_t, mpz_t, mpz_t, int64_t);
void pollard_p_minus_1_factorization(mpz_t, mpz_t, int64_t, int);


//***********************************************************************************************************************************
//FUNÇÕES
//Função que computa uma lista de números primos usando a peneira de Eratóstenes
bool* prime_sieve_setup(int64_t n){

  //Variáveis locais
  bool* number_array=(bool*)malloc((n+1)*sizeof(bool));
  

  //Procedimentos
    //Inicializando o array de booleanos
    number_array[0]=false; number_array[1]=false;
    for(int64_t i=2; i<=n; ++i) number_array[i]=true;

    //Loop principal
    for(int64_t i=2; (i*i)<=n; ++i){

      if(number_array[i]==false) continue;
      for(int64_t j=(i*i); j<=n; j+=i) number_array[j]=false;

    }


  //Resultado
  return number_array;  

};

//------------------------
//Função que implementa o estágio 2 do algoritmo
void pollard_p_minus_1_factorization_stage2(mpz_t n, mpz_t factor, mpz_t H, int64_t B){

  //Variáveis locais
  int coprime_30[8]={1,7,11,13,17,19,23,29};
  int64_t B2 = B * 1000;
  mpz_t H30, H_cp30[8];
  mpz_t Hq, Q, one, v1; 

  //Inicialização de variáveis
  mpz_init(Hq); mpz_init(Q);  mpz_init(one);  mpz_init(v1);
  mpz_init(H30);
  for(int i=0; i<8; ++i){
    mpz_init(H_cp30[i]);
  };


  //Procedimentos
    //Ajuste de variáveis
    while(B%30>0) B--;
     

    for(int i=0; i<8; ++i)
      mpz_powm_ui(H_cp30[i], H, coprime_30[i], n);
   
    mpz_powm_ui(Hq, H, B, n); mpz_set_ui(Q, 1); mpz_powm_ui(H30, H, 30, n);
    mpz_set_ui(one, 1); mpz_set_ui(v1, 1);
    
    

    //Loop principal
    while(B<B2){

      //Loop sobre possíveis primos no intervalo 30k e 30(k+1)
      for(int i=0; i<8; ++i){
  
        mpz_mul(Hq, Hq, H_cp30[i]);
        mpz_mod(Hq, Hq, n);
        mpz_sub(v1, Hq, one);

        mpz_mul(Q, Q, v1);
        mpz_mod(Q, Q, n);

      }
      
      //Testando se um fator primo foi encontrado
      mpz_gcd(factor, Q, n);
      int t1=mpz_cmp_ui(factor, 1);
      int t2=mpz_cmp(factor, n);

      if(t1>0 && t2<0){
        gmp_printf("Fator encontrado no estágio 2!\n");
        goto memory_cache_cleaning; //Fator primo encontrado
      }
      if(t2==0) goto memory_cache_cleaning; //Algoritmo falhou   
      

      //Ajuste de variáveis para a apróxima iteração
      mpz_mul(Hq, Hq, H30); //[30k, 30(k+1)] ---> [30(k+1), 30(k+2)]
      mpz_mod(Hq, Hq, n);
      B+=30;

    };//Fim do loop principal


    //Limpando o cachê de memória
    memory_cache_cleaning:

    mpz_clear(Hq); mpz_clear(Q);
    mpz_clear(one); mpz_clear(v1);
    mpz_clear(H30);
    for(int i=0; i<8; ++i){
      mpz_clear(H_cp30[i]);
    };

};

//------------------------
//Função que implementa (o estágio 1) do algoritmo de fatoração de Pollard (p-1) para fatorar números inteiros
void pollard_p_minus_1_factorization(mpz_t n, mpz_t factor, int64_t B, int stage2){

  //Variáveis locais
  bool* prime_array=prime_sieve_setup(B); //Buffer de números primos até B
  mpz_t  base, one, stock, v1;
  size_t log2B = log2(B), log2p=0, counter=0;
  
  //Inicializando variáveis
  mpz_init(base); mpz_init(one); mpz_init(stock); mpz_init(v1);
  
  
  //Procedimentos
    //Ajuste de variáveis
    mpz_set_ui(base, 2); mpz_set_ui(one, 1); mpz_set_ui(stock, 1); mpz_set_ui(v1, 1);

    //Loop principal
    for(uint64_t i=2; i<=B; ++i){
      
      if(prime_array[i]==false) continue; //Loop apenas sobre os primos ≲ B
      counter++;

      //Atualizando o expoente
      log2p=floor(log2(i));
      uint64_t s = floor(log2B/log2p);

      mpz_ui_pow_ui(v1, i, s); //v(p)=p^(|_log(B)/log(p)_|
      mpz_powm(base, base, v1, n); //M=Πv(p)
  
      mpz_sub(v1, base, one);//v1=a^M-1 (mod n)
      mpz_mul(stock, stock, v1);

      //Testando se um fator primo foi encontrado no estágio 1
      if( (counter&POLLARD_P_CYCLE) == 0){
        mpz_gcd(factor, stock, n);
        mpz_set_ui(stock, 1); 
    
        int t1=mpz_cmp_ui(factor, 1);
        int t2=mpz_cmp(factor, n);

        if(t1>0 && t2<0) goto memory_cache_cleaning; //Fator primo encontrado
        if(t2==0) goto memory_cache_cleaning; //Algoritmo falhou
      }

    };

    //Testando se um fator primo foi encontrado no estágio 1
    mpz_gcd(factor, stock, n);
    
    int t1=mpz_cmp_ui(factor, 1);
    int t2=mpz_cmp(factor, n);

    if(t1>0 && t2<0) goto memory_cache_cleaning; //Fator primo encontrado
    if(t2==0) goto memory_cache_cleaning; //Algoritmo falhou

    //Limpando o cachê de memória antes do estágio 2
    if(prime_array){
     free(prime_array); prime_array=NULL;
    }

    //Estágio 2 do algoritmo
    mpz_add(v1, v1, one);
    if(stage2>0)
      pollard_p_minus_1_factorization_stage2(n, factor, v1, B);    

    //Limpando o cachê de memória
    memory_cache_cleaning:

    if(prime_array){
     free(prime_array); prime_array=NULL;
    }
    mpz_clear(base); mpz_clear(one);  mpz_clear(stock); mpz_clear(v1);  

};

//***********************************************************************************************************************************
//FIM DO HEADER
#endif
