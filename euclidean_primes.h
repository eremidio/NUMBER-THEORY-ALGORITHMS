//VAMOS CRIAR PROGRAMAS QUE COMPUTAM CONJUNTOS DE PRIMOS EUCLIDIANOS

/*

DADO UM CONJUNTO DE NÚMEROS PRIMOS {p(1), ..., P(k)}, UM SEGUNDO CONJUNTO DE PRIMOS
{q(1),..., q(s)} TAIS QUE [q(j)-1] = Πp(i)^e(i) PODEM SER GERADOS TAIS PRIMOS SÃO
DENOMINADOS PRIMOS EUCLIDIANOS. TAL DEFINIÇÃO É PROVENIENTE DA DEMONSTRAÇÃO MAIS
SIMPLES DA INFINITUDE DOS NÚMEROS PRIMOS. AS VEZES É REQUERIDO QUE OS PRIMOS
EUCLIDIANOS SEJAM TAIS QUE (q-1) NÃO CONTENHA FATORES PRIMOS REPETIDOS.

TAIS CONJUNTOS DE NÚMEROS PRIMOS SÃO ÚTEIS EM ALGORITMOS COMO OS TESTES DE
PRIMALIDADE APR-CL E O TESTE DE PRIMALIDADE EM CORPOS FINITOS, NOS QUAIS ESCOLHAS
ADEQUADAS DESTES CONJUNTOS DE NÚMEROS PRIMOS DETERMINA O TEMPO DE EXECUÇÃO DESTES
ALGORITMOS.

PARA MAIORES INFORMAÇÕES: https://math.dartmouth.edu/~carlp/nothingtalk2.pdf

*/


//*******************************************************************************************
//CABEÇALHO
#ifndef EUCLIDIAN_PRIMES
#define EUCLIDEAN_PRIMES
#include"baillie_psw_prime_test.h"
#include<stdlib.h>
#include<stdio.h>


//*******************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void setup_euclidean_prime_set(int64_t, int64_t, int64_t);


//*******************************************************************************************
//FUNÇÕES
//Função que define um conjunto de primos euclidiano (não contendo fatores repetidos)
void setup_euclidean_prime_set(int64_t initial_bound, int64_t euclidean_lower_bound, int64_t euclidean_upper_bound){

  //Variáveis locais
  int64_t * initial_prime_set=NULL;
  int64_t * euclidean_prime_set=NULL;
  int32_t initial_set_size=0, euclidean_set_size=0, tester;


  //Procedimentos
    //Definindo o conjunto de primos iniciais
    initial_set_size++;
    initial_prime_set=(int64_t*)realloc(initial_prime_set, initial_set_size*sizeof(int64_t));
    initial_prime_set[initial_set_size-1]=2;
    initial_set_size++;
    initial_prime_set=(int64_t*)realloc(initial_prime_set, initial_set_size*sizeof(int64_t));
    initial_prime_set[initial_set_size-1]=3;

    for(int64_t i=5; i<initial_bound; i+=2){
    
      if((i%6==5 || i%6==1) && baillie_psw_test(i)==true){
        initial_set_size++;
        initial_prime_set=(int64_t*)realloc(initial_prime_set, initial_set_size*sizeof(int64_t));
        initial_prime_set[initial_set_size-1]=i;
      }

    }
    
  
    //Definindo conjunto de primos euclidianos
    for(int64_t j=euclidean_lower_bound; j<euclidean_upper_bound; j++){

      if((j==3 ||(j%6==5 || j%6==1)) && baillie_psw_test(j)==true){

        //Checando se (q-1) é completamente fatorado em relação ao conjunto de primos iniciais 
        tester=(j-1);
        for(int32_t k=0; k<initial_set_size; ++k){
          if(tester%initial_prime_set[k]==0) tester/=initial_prime_set[k];

          if(tester==1){
            euclidean_set_size++;
            euclidean_prime_set=(int64_t*)realloc(euclidean_prime_set, initial_set_size*sizeof(int64_t));
            euclidean_prime_set[euclidean_set_size-1]=j;    
            break;
          }

                
        };


      }

    }


    //Exibindo oresultado da execuçãodo algoritmo
    printf("Conjunto dos primos iniciais: ");
    for(int32_t l=0; l<initial_set_size; ++l) printf("%li, ", initial_prime_set[l]);
    printf("...\n");

    printf("Conjunto dos primos euclidianos: ");
    for(int32_t m=0; m<euclidean_set_size; ++m) printf("%li, ", euclidean_prime_set[m]);
    printf("...\n");

    //Limpando o cachê de mémoria
    if(initial_prime_set) free(initial_prime_set);
    if(euclidean_prime_set) free(euclidean_prime_set);


};

//*******************************************************************************************
//FIM DO HEADER
#endif

