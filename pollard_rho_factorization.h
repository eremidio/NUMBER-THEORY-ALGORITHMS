//VAMOS CRIAR UMPROGRAMA QUEIMLEMENTA O ALGORIMO DE POLLARD-RHO PARA FATORAR NÚMEROS INTEIROS

/*

O ALGORITMO DE POLLARD ρ É UMA  EFICIENTE ALGORITMO PARA DECOMPOR UM NÚMERO INTEIRO EM FATORES PRIMOS.
O ALGORITMO BASEIA-SE NA GERAÇÃO GERAÇÃO DE UMA SEQUÊNCIA PSEUDO-ALEATÓRIA USANDO UM POLONÔMIO COMO
p(x)=x²+a mod(n), ONDE n É UM NÚMERO A SER FATORADO E a É UM INTEIRO.

O ALGORITMO DE POLLARD É EXECUTADO NAS SEGUINTES ETAPAS:
1. PROVIDO UMA SEMENTE INICIAL x E y O VALOR DE p(x) E p(p(y)) É COMPUTADO.
2. OS VALORES DE x E y SÃO ATUALIZADOS x=p(x) E y = p(p(y)).
3. O VALOR DE d = mmc(|x-y|, n) É COMPUTADO.
4. CASO 1<d<n, d É UM FATOR NÃO TRIVIAL DE n. EM CASO DE d=n O TESTE FALHOU.

PARA OTIMIZAR O TESTE DIVERSAS BASES INICIAIS PODEM SER TESTADAS.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm

*/

//*********************************************************************************************************************
//CABEÇALHO
#ifndef POLLARD_RHO_FACTORIZATION_H
#define POLLARD_RHO_FACTORIZATION_H
#include<stdint.h>
#include<stdlib.h>
#include<gmp.h> 


//CONSTANTES GLOBAIS
const int POLLARD_RHO_CYCLE=2047;  //2^11-1
const int POLLARD_RHO_CYCLE_MAX=100000000;


//*********************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void pollard_rho_factorization(mpz_t, mpz_t, int);


//*********************************************************************************************************************
//FUNÇÕES
//Função que fatora um inteiro usando o algoritmo de Pollard ρ
void pollard_rho_factorization(mpz_t n, mpz_t factor, int a){

  //Variáveis locais
  uint64_t counter=0;
  mpz_t stock, c, x, y;
  mpz_t v1, v2;

  //Inicializando as variáveis
  mpz_init(v1); mpz_init(v2);
  mpz_init(stock); mpz_init(c); mpz_init(x); mpz_init(y);


  //Procedimentos
    //Ajuste de variáveis
    mpz_set_ui(c, a); mpz_set_ui(stock, 1);
    mpz_set_ui(x, a);
    mpz_mul(v1, x, x); mpz_add(v2, v1, c); mpz_mod(y, v2, n); //y(0)=x²(0)+c

    //Loop principal: usaremos o polinômio p(x)=x²+c
    while(counter<POLLARD_RHO_CYCLE_MAX){
      
      //Atualizando o contador e o parâmetro c 
      counter++;
    
      //Atualizando variáveis: x->p(x) mod n, y->p(p(y)) mod n
      mpz_mul(v1, x, x); mpz_add(v2, v1, c); mpz_mod(x, v2, n);

      mpz_mul(v1, y, y); mpz_add(v2, v1, c); mpz_mod(y, v2, n);
      mpz_mul(v1, y, y); mpz_add(v2, v1, c); mpz_mod(y, v2, n);

      //Estocando o valor de |x-y|
      mpz_sub(v1, x, y); mpz_abs(v1, v1); 
      mpz_mul(stock, stock, v1);


      //Checando se um fator primo foi encontrado
      if( (counter&POLLARD_RHO_CYCLE)==0){
        mpz_gcd(factor, stock, n);
        mpz_set_ui(stock, 1); 
    
        int t1=mpz_cmp_ui(factor, 1);
        int t2=mpz_cmp(factor, n);

        if(t1>0 && t2<0) break; //Fator primo encontrado
        if(t2==0) break; //Algoritmo falhou

      }


    };//Fim do loop principal


    //Limpando o cachê de memória
    mpz_clear(v1); mpz_clear(v2);
    mpz_clear(stock); mpz_clear(c); mpz_clear(x); mpz_clear(y);

};

//*********************************************************************************************************************
//FIM DO HEADER
#endif
