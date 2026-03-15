//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA A PENEIRA DE ATKIN UM DOS ALGORITMOS MAIS EFICIENTES PARA GERAR NÚMEROS PRIMOS

/*

O ALGORITMO DE ATKIN (OU ATKIN-BERNSTEIN) USA REPRESENTAÇÕES DE INTEIROS POR FORMAS QUADRÁTICAS BINÁRIAS PARA DETECTAR NÚMEROS
PRIMOS. OS SEGUINTES TEOREMAS (PROVADOS NO ARTIGO ORIGINAL DE 2003) CONSTITUEM A BASE DO ALGORITMO:

TEOREMA 1: SEJA n UM NATURAL , TAL QUE n≡ 1, 13, 17, 29, 37, 41, 49, 53 mod(60), ISTO É, n≡1 mod(4). ENTÃO n É PRIMO SE E
SOMENTE SE O NÚMERO SOLUÇÕES DE 4x²+y²=n FOR ÍMPAR E n NÃO FOR UM QUADRADO PERFEITO.

TEOREMA 2: SEJA n UM NATURAL, TAL QUE n≡ 7, 19, 31, 43 mod(60); ISTO É, n≡1 mod(6). ENTÃO n É PRIMO SE E SOMENTE SE O NÚMERO
SOLUÇÕES DE 3x²+y²=n FOR ÍMPAR E n NÃO FOR UM QUADRADO PERFEITO.

TEOREMA 3: SEJA n UM NATURAL, TAL QUE n≡ 11, 23, 47, 59 mod(60); ISTO É, n≡11 mod(12). ENTÃO n É PRIMO SE E SOMENTE SE O
NÚMERO SOLUÇÕES DE 3x²-y²=n FOR ÍMPAR E n NÃO FOR UM QUADRADO PERFEITO.

O ALGORITMO USA DOIS LOOPS INTERNOS COM x,y ≲ √n PARA CHECAR AS CONGRUÊNCIAS DOS TEOREMAS ACIMA. MÚLTIPLOS DE QUADRADOS
PERFEITOS SÃO REMOVIDOS EM UMA ETAPA SUBSEQUENTE DE MODO QUE RESTE APENAS NÚMEROS PRIMOS (COMO 60=2⁴x3x5, OS NÚMEROS 2,3,5
DEVEM SER INCLUSOS AO FINAL).

O ALGORITMO TEM UMA COMPLEXIDADE ASSINTÓTICA DE O(n), SENDO TEORICAMENTE O ALGORITMO MAIS EFICIENTE PARA GERAÇÃO DE NÚMEROS
PRIMOS, EMBORA ALGUMAS VARIANTES DO CRIVO DE ERATÓSTENES TENHAM MELHOR PERFORMANCE QUANDO IMPLEMENTADAS (MENORES CONSTANTES
MULTIPLICATIVAS).


PARA MAIORES INFORMAÇÕES: https://www.ams.org/journals/mcom/2004-73-246/S0025-5718-03-01501-1/S0025-5718-03-01501-1.pdf
                          https://en.wikipedia.org/wiki/Sieve_of_Atkin#Computational_complexity

*/

//*************************************************************************************************************************
//CABEÇALHO
#ifndef ATKIN_SIEVE_H
#define ATKIN_SIEVE_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include<math.h>


//*************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool* fill_prime_array_sieve(int64_t);
void atkin_sieve(int64_t);


//*************************************************************************************************************************
//FUNÇÕES
//Função que computa uma lista de números primos usando representações de inteiros por formas quadráticas binárias módulo 60
bool* fill_prime_array_sieve(int64_t n){

  //Variáveis locais
  bool* prime_array=(bool*)calloc((n+1), sizeof(bool));
  int64_t value=0, mod=0, k2=0, x2=0, y2=0;
  int64_t root_n=sqrt(n)+1;


  //Procedimentos
    //Pré computando quadrados perfeitos
    int64_t* num_array=(int64_t*)malloc((root_n+1)*sizeof(int64_t));
    num_array[0]=0; num_array[1]=1;

    for(int64_t i=1; i<root_n; ++i)
      num_array[i+1]=num_array[i]+(i<<1)+1; // (n+1)²=n²+2n+1 --> (n+1)²-n² = 2n+1
    
    
    //Loop principal: checando congruências usando fórmas quadráticas binárias
    for(int64_t x=1; x<=root_n; ++x){
      for(int64_t y=1; y<=root_n; ++y){
  
        x2=num_array[x]; y2=num_array[y]; 

        //Caso 1: f(x, y) = 4x²+y²
        value=(x2<<2)+y2;
        mod=(value%12);

        if(value<=n && (mod==1 || mod==5))
          prime_array[value]=((prime_array[value]+1)&1);// Toggling usando operadores bitwise: false <---> true

        //Caso 2: f(x, y) = 3x²+y²
        value=value-x2;
        mod=(value%12);

        if(value<=n &&  mod==7)
          prime_array[value]=((prime_array[value]+1)&1);

        //Caso 3: f(x, y) = 3x²-y²
        if(y>=x) continue;

        value=value-(y2<<1);
        mod=(value%12);

        if(value<=n &&  mod==11)
          prime_array[value]=((prime_array[value]+1)&1);

      }
    }

    //Removendo múltiplos de quadrados perfeitos
    for(int64_t k=5; (k2=(k*k))<=n; ++k){

      if(prime_array[k2]==false)
        continue;

      for(int64_t l=k2; l<=n; l+=k2)
        prime_array[l]=false;
    }

    //Ajuste dos elementos iniciais
    prime_array[2]=true; prime_array[3]=true; prime_array[5]=true;

    //Limpando o cachê de memória
    if(num_array){
      free(num_array); num_array=NULL;
    }


  //Resultado
  return prime_array;

};

//Função que implementa o crivo de Atkin
void atkin_sieve(int64_t n){

  //Variáveis locais
  bool* prime_array=fill_prime_array_sieve(n);// 1--> indexa números primos, 0 -->indexa números compostos


  //Procedimentos
    //Exibindo o resultado do algoritmo
    printf("Lista de números primos encontrados até %li: ", n);

    for(int64_t i=1; i<=n; ++i){
    
      if(prime_array[i]==true){
        printf("%li, ", i);
      }

    }

    printf("...\n");


    //Limpando o cachê de memória
    if(prime_array){
      free(prime_array); prime_array=NULL;
    }

};

//FIM DO HEADER
#endif
