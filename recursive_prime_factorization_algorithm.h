//VAMOS CRIAR UM ARQUIVO QUE USA RELAÇÕES RECURSIVAS GERADORAS DE NÚMEROS PRIMOS PARA FATORAR NÚMEROS INTEIROS

/*
O SEGUINTE ALGORITMO FOI BASEADO NO PAPER: https://cs.uwaterloo.ca/journals/JIS/VOL11/Rowland/rowland21.pdf
APARENTEMENTE UMA CONTRIBUIÇÃO ORIGINAL A TEORIA DE NÚMEROS COMPUTACIONAL, NÃO VI REFERÊNCIAS SOBRE O ALGORITMO EM QUESTÃO NA LITERATURA.
QUALQUER ENGANO GENTILEZA ME COMUNICAR NO EMAIL: e.r.emidio@yandex.com

A IDEIA PRINCIPAL DO ALGORITMO É USAR A RELAÇÃO RECURSIVA: a(n)=a(n-1)+mdc(n, a(n-1)) QUE PRODUZ UMA SEQUÊNCIA DE NÚMEROS PRIMOS
OU FATORES 1's. O ALGORITMO É COMO SE SEGUE:
1. SEJA N O NÚMERO A SER FATORADO. SE N FOR PAR DIVIDA N POR 2 ATÉ QUE N SEJA ÍMPAR.
2. AJUSTE a(0)=N.
3. OS TERMOS DA SEQUÊNCIA a(n)=a(n-1)+mmc(n, a(n-1)) SÃO COMPUTADOS RECURSIVAMENTE ATÉ QUE UM FATOR PRIMO NÃO TRIVIAL p>2 SEJA OBTIDO.
4. SE n>N^(1/2)+1, ENTÃO É GARANTIDO QUE N É PRIMO.

O PRESENTE ALGORITMO BASEIA-SE NA SEGUINTE PROPOSIÇÃO NÃO PROVADA AINDA:

PROPOSIÇÃO: SEJA N, UM NUMÉRO NATURAL ÍMPAR QUALQUER TAL QUE N>2 E SEJA A SEQUÊNCIA a(n)=a(n-1)+mdc(n, a(n-1)). SE PARA n<N^(1/2)+1,
mdc(n, a(n-1))>2. ENTÃO mdc(n, a(n-1)) É UM FATOR NÃO TRIVIAL DE N.

DESTA PROPOSIÇÃO O COROLÁRIO SEGUINTE É TRIVIAL:
COROLÁRIO: DADO N E A SEQUÊNCIA DE VALORES a(n)'s ACIMA. SE PARA n<N^(1/2)+1, NÃO HOUVER mdc(n, a(n-1))>2, ENTÃO N É PRIMO.


O PRESENTE ALGORITMO PODE SER EXECUTADO UMA ÚNICA VEZ PROVENDO ASSIM UM FATOR NÃO TRIVIAL DE N OU CONFIRMANDO QUE N É PRIMO.
RECURSIVIDADE GARANTE QUE UMA FATORAÇÃO COMPLETA DE N SEJA OBTIDA. 

TESTES INDICAM QUE APÓS p ITERAÇÕES UMA FATOR PRIMO É REVELADO, A COMPLEXIDADE DESTE ALGORITMO SERIA ENTÃO O(pln(p)), ONDE p É O 
MENOR FATOR PRIMO DE N OU NO PIOR CASO O(N^(1/2)ln(N)) QUANDO N FOR PRIMO. NÃO É, PORTANTO, ADEQUADO A FATORAÇÃO DE NÚMEROS INTEIROS
GRANDES, PORÉM NAS MÁQUINAS MODERNAS É RAZOÁVEL PARA NÚMEROS DA ORDEM DE 10^18.

*/ 

//*****************************************************************************************************************************************************************
//CABEÇALHO
#ifndef RECURSIVE_PRIME_FACTORIZATION
#define RECURSIVE_PRIME_FACTORIZATION
#include"gcd_euclides_fast.h"
#include<stdio.h>
#include<math.h>

//*****************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t gcd(uint64_t, uint64_t);
void elias_rowland_prime_factorization_algorithm(uint64_t);

//*****************************************************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides para calcular o mdc de dois inteiros
uint64_t gcd(uint64_t a, uint64_t b){

  if(b==0)
    return a;
  else
    return gcd(b, a%b);

};

//Função que fatora um número inteiro ou declara que o mesmo é primo usando relações recursivas
void elias_rowland_factorization_algorithm(uint64_t n){

  //Caso base n é par
  if(!(n&1)){
    printf("Fator primo de %lu encontrado: 2\nCofator: %lu\n", n, (n>>1));
    elias_rowland_factorization_algorithm((n>>1));//Chamada recursiva do algoritmo
    return;
  }

  //Variáveis locais
  uint64_t counter=1;
  uint64_t root=sqrt(n), cofactor;
  uint64_t r0=n, tester=0;


  //Procedimentos 
    //Loop principal
    while(counter<(root+2)){

    //Condição que detecta se um fator primo de n foi encontrado
    if(tester>2){
      cofactor=(n/tester);
      printf("Fator primo de %lu encontrado: %lu\nCofator: %lu\n", n, tester, cofactor);
      elias_rowland_factorization_algorithm(cofactor);//Chamada recursiva do algoritmo
      return;
    };

    //Atualizando variáveis para a próxima iteração
    tester=gcd(counter, r0);
    r0+=tester;
    counter+=1;
                       };

  //Caso um fator não trivial seja encontrado na etapa anterior o número em questão é primo
  printf("%lu é primo\n", n);

};


//*****************************************************************************************************************************************************************
//FIM DO HEADER
#endif
