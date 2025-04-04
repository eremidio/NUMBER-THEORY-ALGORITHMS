//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ROTINAS PARA CHECAR A CONJECTURA DE CLOITRE PARA GERAR NÚMEROS PRIMOS

/*

UMA CONJECTURA DEVIDO A BENOIT CLOITRE AFIRMA QUE A SEQUÊNCIA DEFINIDA RECURSIVAMENTE PELA IDENTIDADE
a(n)=a(n-1)+mmc(n, a(n-1)) COM a(1)=1, EM QUE mmc DENOTA O MÍNIMO MÚLTIPLO COMUM DE 2 INTEIROS, GERA
NÚMEROS 1 OU NÚMEROS PRIMOS PARA a(n)≳2 QUANDO SE CONSIDERA OS VALORES DAS RAZÕES a(n)/a(n-1)-1.


PARA MAIORES INFORMAÇÕES: https://ericrowland.github.io/talks/Formulas_for_primes.pdf
                          https://learn-codes.org/javascript/424671-c-gcd-function-c-header

*/ 


//*************************************************************************************************************
//CABEÇALHO
#ifndef CLOITRE_CONJECTURE_H
#define CLOITRE_CONJECTURE_H
#include<stdio.h>
#include<stdint.h>
#include<gmp.h>



//*************************************************************************************************************
//DECLARTAÇÃO DE FUNÇÕES
void gmp_lcm(mpz_t, mpz_t, mpz_t);
void cloitre_recursive_prime_generation(uint64_t);


//*************************************************************************************************************
//FUNÇÕES
//Função que calcula ommc de dois inteiros de precisão
void gmp_lcm(mpz_t lcm, mpz_t a, mpz_t b){

  //Variáveis locais
  mpz_t gcd, t0, t1;
  mpz_init(gcd); mpz_init(t0); mpz_init(t1);

  //Procedimentos
    //Calculando o mmc de dois inteiros
    mpz_gcd(gcd, a, b);
    mpz_mul(t0, a, b);
    mpz_div(t1, t0, gcd);

    mpz_set(lcm, t1);

    //Limpando o cachê de memória    
    mpz_clear(gcd); mpz_clear(t0); mpz_clear(t1);

};


//Função que gera números primos baseados em relações recursivas
void cloitre_recursive_prime_generation(uint64_t n){

  //Variáveis locais
  mpz_t lcm, an1, N, an, t0, t1, one;
  mpz_init(lcm); mpz_init(t0); mpz_init(t1); mpz_init(one);
  mpz_init(an1); mpz_init(an); mpz_init(N);  
  uint64_t prime, counter=1;

  
  //Procedimentos
     //1ºelemento da sequência
     mpz_set_ui(an1, 1);

     //Loop principal computando a relação recursiva de Cloitre
     while(counter<n){
     
       //Computando o mmc de dois inteiros
       mpz_set_ui(N, counter);
       gmp_lcm(lcm, an1, N);

       //Computando o próximo termo da sequência e echecando se um primo foi obtido
       mpz_add(an, an1, lcm);
       mpz_div(t0, an, an1);
       mpz_sub(t1, t0, one);
       prime=mpz_get_ui(t1); prime--;

       if(prime>1) printf("%lu, ", prime);
       
       //Atualizando variáveispara a próxima iteração
       counter++;
       mpz_set(an1, an);
     
     }

     printf("...\n");

    //Limpando o cachê de memória
    mpz_clear(lcm); mpz_clear(t0); mpz_clear(t1); mpz_clear(one);
    mpz_clear(an1); mpz_clear(an); mpz_clear(N);


};


//*************************************************************************************************************
//FIM DO HEADER
#endif
