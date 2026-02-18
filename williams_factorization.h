//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE WILLIAMS (p+1) PARA FATORAR NÚMEROS INTEIROS

/*

O ALGORITMO DE WILLIAMS (p+1) USA SEQUÊNCIAS DE LUCAS DO SEGUNDO TIPO PARA FATORAR NÚMEROS INTEIROS. 
A SEQUÊNCIAS DE LUCAS DE SEGUNDO TIPO SÃO DEFINIDAS POR: V(0)=2, V(1)=A, E V(i)=AV(i-1)-V(i-2).


PARA UMA DADA ESCOLHA DE UM PARÂMETRO 'A' FATORES NÃO TRIVIAIS p PODEM SER ENCONTRADOS CALCULANDO-SE
mdc([V(m)-2], n) ONDE n É O NÚMERO A SER FATORADO E m É UM INTEIRO QUE É MÚLTIPLO DE p-(D|p), ONDE
(D|p) É O SÍMBOLO DE JACOBI E D=A²-4. NO CASO (D|p)=1 ESTE ALGORITMO SE REDUZ A UM VERSÃO MAIS
LENTA DO ALGORITMO POLLARD (p-1). COMO DE ANTEMÃO NÃO É POSSÍVEL SABER SE PARA O FATOR A SER
ENCONTRADO (D|p)=(-1), EM GERAL, VÁRIAS ESCOLHAS DE PARÂMETRO DA SEQUÊNCIA DE LUCAS COSTUMAM SER
FEITAS.

O ALGORITMO É EFICIENTE EM ENCONTRAR UM FATOR PRIMO QUANDO A CONDIÇÃO SOBRE O SÍMBOLO DE JACOBI É
SATISFEITA E (p+1) SE DECOMPÕE EM FATORES PRIMOS PEQUENOS. PARA O PARÂMETRO m A ESCOLHA USUAL É DOS
SUCESSIVOS FATORIAIS (2!, 3!, ...) OU POTÊNCIAS DE PRIMOS PEQUENOS.

COMO NO ALGORITMO DE POLLARD (p-1), QUANDO (p+1) TIVER UM FATOR ACIMA DO LIMITE ESPECIFICADO B, É
POSSÍVEL DEFINIR UMA CONTINUAÇÃO DO ALGORITMO DE FORMA A OBTER MAIOR PROBABILIDADE DE SUCESSO NA
DETECÇÃO DE FATORES PRIMOS.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Williams%27s_p_%2B_1_algorithm
                          https://inria.hal.science/inria-00188192/file/pm1fft-final.pdf
                          https://rieselprime.de/ziki/P%2B1_factorization_method

*/



//**************************************************************************************************************************
//CABEÇALHO
#ifndef WILLIAMS_FACTORIZATION_H
#define WILLIAMS_FACTORIZATION_H
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<gmp.h> 



//**************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void williams_factorization(mpz_t, mpz_t, int32_t, int32_t);


//**************************************************************************************************************************
//FUNÇÕES
//Função que implementa o (estágio 1) do algoritmo de Williams para fatorar números inteiros
void williams_factorization(mpz_t n, mpz_t factor, int32_t a, int32_t B){

  //Variáveis locais
  mpz_t factorial, fact_temp, A, x, y, Vm, two;
  mpz_t v1, v2;
  int t1=0, t2=0;

  //Inicialização de variáveis
  mpz_init(factorial); mpz_init(fact_temp); mpz_init(A); mpz_init(x); mpz_init(y); mpz_init(Vm); mpz_init(two);
  mpz_init(v1); mpz_init(v2);


  //Procedimentos
     //Ajustando valores iniciais de variáveis
     mpz_set_ui(factorial, 1); mpz_set_ui(fact_temp, 1); mpz_set_si(A, a); mpz_set_ui(two, 2);
     mpz_set_ui(x, 1); mpz_set_ui(y, 1); mpz_set_ui(Vm, 1); 
     mpz_set_ui(v1, 1); mpz_set_ui(v2, 1); //Variáveis temporárias

     //Loop principal
     for(int32_t m=2; m<=B; ++m){

      //Computando m!
      mpz_mul_si(factorial, factorial, m);
      mpz_set(fact_temp, factorial);

      //Ajuste de variáveis
      mpz_set(x, A); //x=A
      mpz_mul(y, A, A); mpz_sub(y, y, two); mpz_mod(y, y, n);//y=(A*A)-2 (mod N)


      //Iterando sobre os bits de m!: computando os termos da sequência de Lucas V(m!) (mod n)
      while(mpz_cmp_ui(fact_temp, 1)>0){
    
        //Checando a paride do bit de m!
        if(mpz_odd_p(fact_temp)>0){
          mpz_mul(v1, x, y); mpz_sub(v1, v1, A); mpz_mod(v1, v1, n); // x=((x*y)-A) (mod n);
          mpz_mul(v2, y, y); mpz_sub(v2, v2, two); mpz_mod(v2, v2, n); //y=((y*y)-2) (mod n);
          mpz_set(x, v1); mpz_set(y, v2);
        }
        else{
          mpz_mul(v1, x, x); mpz_sub(v1, v1, two); mpz_mod(v1, v1, n); // x=((x*x)-2) (mod n);
          mpz_mul(v2, x, y); mpz_sub(v2, v2, A); mpz_mod(v2, v2, n); //y=((x*y)-A) (mod n);
          mpz_set(x, v1); mpz_set(y, v2);
        }

        //Atualizando variáveis
        mpz_fdiv_q_2exp(fact_temp, fact_temp, 1); //Shift de 1 bit >>=1


      };//Loop secundário sobre os bits de m!factorial

      mpz_set(Vm, x); //V(m!)
      mpz_sub(Vm, Vm, two);

      //Checando se um fator primo foi encontrado
      mpz_gcd(factor, Vm, n);
      t1=mpz_cmp_ui(factor, 1);
      t2=mpz_cmp(factor, n);

      if(t1>0 && t2<0) goto memory_cache_cleaning; //Fator primo encontrado

    };


    //Limpeza do cachê de memória
    memory_cache_cleaning:

    mpz_clear(factorial); mpz_clear(fact_temp); mpz_clear(x); mpz_clear(y); mpz_clear(Vm); mpz_clear(two);
    mpz_clear(v1); mpz_clear(v2);


};

/*

  NOTA: Neste código implementamos apenas o estágio 1 do algoritmo, que é executada em um tempo razoável para B~10^6.
        Uma possibilidade de extensão do algoritmo para um estágio 2 é a seguinte. Seja V(r) o último termo da sequência
        computado no estágio 1 do algoritmo e C o menor múltiplo de 6 inferior ao último index M usado para computar o
        último termo da sequência de Lucas. Sendo N o número a ser fatorado computa-se V(Cr) e V(6r) módulo N. A fórmula
        de adição V(m+n)=V(m)V(n)-V(m-n), permite computar os termos de index (C+6k)r de forma recursiva por meio da
        cadeia de relações recursivas: V(Cr+12r)=V(Cr+6r)V(6r)-V(Cr), V(Cr+18r)=V(Cr+12r)V(6r)-V(Cr+6r),
        V(Cr+24r)=V(Cr+18r)V(6r)-V(Cr+12r) e assim sucessivamente.
        Cada passo requer um multiplicação e uma subtração módulo N. Coletando os produtos [V(C6kr)-V(r)] (mod N)
        espera-se que o fator primo p seja revelado. Versões mais modernas do estágio 2 fazem uso de complexas técnicas
        de multiplicação polinomial para computar V(m) cobrindo todos os primos no intervalo [B1,B2] similar as usadas
        na multiplicação de inteiros via FFT.

*/


//**************************************************************************************************************************
//FIM DO HEADER
#endif
