//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA VERSÃO ALTERNATIVA DA FÓRMULA DE LEGENDRE PARA CONTAGEM DE NÚMEROS PRIMOS

/*

SEJA n UM NÚMERO INTEIRO E α O MAIOR INTEIRO TAL QUE α²<n. A FUNÇÃO DE CONTAGEM DE NÚMEROS π(n) PODE SER CALCULADA POR MEIO 
DA SEGUINTE FORMULAÇÃO ALTERNATIVA: SEJA P={p1, ..., pk} O CONJUNTO DE TODOS OS PRIMOS NO INTERVALO 1,.., α E Q O PRODUTO
DOS ELEMENTOS NO CONJUNTO P. SENDO d OS DIVISORES DE Q, O VALOR DE π(n) PODE SER CALCULADO POR MEIO DA SEGUINTE FÓRMULA:
π(n)=π(√n)+ Σμ(d)|_n/d_|, ONDE A SOMA É EFETUADA SOBRE TODOS OS DIVISORES d DE Q E μ(d) DENOTA A FUNÇÃO DE MÖBIUS. TAL
ALGORITMO É UMA REFORMULAÇÃO DO ALGORITMO ORIGINAL PROPOSTO POR LEGENDRE QUE CONSISTE EM UMA APLICAÇÃO DIRETA DO PRINCÍPIO
DE INCLUSÃO/EXCLUSÃO DE TEORIA DOS CONJUNTOS EM ANÁLISE COMBINATÓRIA, SENDO EQUIVALENTE A PENEIRA DE ERATÓSTENES.

NA CHAMADA PENEIRA DE BRUN A FUNÇÃO DE MÖBIUS É SUBSTITUÍDA POR UMA FUNÇÃO QUE POSSUI UM NÚMERO MENOR OU MAIOR DE RAÍZES E
QUE POSSA SER FACILMENTE COMPUTÁVEL, DE FORMA TAL QUE LIMITES SUPERIORES OU INFERIORES PARA CONTAGEM DE NÚMEROS PRIMOS OU
COMPOSTOS EM UM DETERMINADO INTEVALO POSSA SER ESTIMADO DENTRO DE UMA MARGEM DE ERRO BEM DEFINIDA. TAIS OBSERVAÇÕES
PERMITEM APLICAR CRIVOS PARA ESTIMAR O TAMANHO INTERVALOS FILTRADOS COM GRANDE PRECISÃO. O CHAMADO CRIVO DE SELBERG É UMA
VARIANTE DESTE ALGORITMO PARTICULAMENTE ADAPTADA PARA FORNECER LIMITES SUPERIORES DO TAMANHO DESTES INTERVALOS.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Brun_sieve
                          https://en.wikipedia.org/wiki/Selberg_sieve
                          https://en.wikipedia.org/wiki/Legendre_sieve
                          https://www.kskedlaya.org/18.785/brun.pdf
                          https://travorlzh.github.io/2024/02/25/bruns-sieve.html
                          https://github.com/FLDutchmann/selberg-sieve4


*/


//**************************************************************************************************************************
//CABEÇALHO
#include"mobius_function_lambert_series.h"
#include<stdbool.h>
#include<math.h>


//**************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int32_t* prime_root_sieving_counting(int32_t, int32_t*);
bool is_prime_root_smooth(int32_t, int32_t[], int32_t);
int32_t legendre_sieve_prime_counting(int32_t);


//**************************************************************************************************************************
//FUNÇÕES
// Função que preenche um buffer de números primos
int32_t* prime_root_sieving_counting(int32_t n, int32_t* root_counter) {

  // Variáveis locais
  int32_t* prime_array = NULL;
  int32_t prime_index = 0;
  int32_t counter = 0;
  int32_t root = sqrt(n);
  bool sieve_array[root + 100];
  int32_t i, j;

  // Procedimentos

  // Inicializando o array de booleanos
  for (i = 2; i < (root + 100); ++i) sieve_array[i] = true;

  // Peneirando os números primos no intervalo 0, 1, 2,..., n^(1/2)+100
  for (i = 0; (i * i) < (root + 100); i++) {
    if (sieve_array[i] == true) {
      for (j = (i * i); j < (root + 100); j += i) sieve_array[j] = false;
    };
  };

  // Computando o número de primos no intervalo até n^1/2
  for (i = 0; i < (root + 100); ++i) {
    if (sieve_array[i] == true) {
      if (i <= root) counter++;
      prime_index++;
      prime_array =(int32_t*)realloc(prime_array, prime_index * sizeof(int32_t));
      prime_array[prime_index - 1] = i;
    };
  };

  // Resultado
  (*root_counter) = counter;
  return prime_array;

};


//Função que checa se um inteiro é um número suave em relação a uma base fixa de números primos
bool is_prime_root_smooth(int32_t n, int32_t prime_array[], int32_t root_counter){

  //Procedimentos
    //Testando a divisibilidade de n por um dado conjunto de primos
    for(int32_t i=0; i<root_counter; ++i){
      //if(n<prime_array[i]) break; 
      if(n%prime_array[i]==0) n/=prime_array[i];
      if(n==1) return true;

    }

  //Resultado
  return false;

};


//Função de contagem de primos
int32_t legendre_sieve_prime_counting(int32_t n){

  //Variáveis locais
  int32_t root_counter;
  int32_t* prime_array=prime_root_sieving_counting(n, &root_counter);
  int8_t * mobius_array=compute_mobius_function(n);
  int64_t legendre_weighted_sum=n;
  int64_t result=(root_counter-1);
  

  //Procedimentos
    //Computando o somatório de Legendre
    for(int32_t i=2; i<=n; ++i){
      if(mobius_array[i]==0) continue;
      else if(is_prime_root_smooth(i, prime_array, root_counter)==true) legendre_weighted_sum+=(mobius_array[i]*floor(n/i));
    }

    //Limpando o cachê de memória
    if(prime_array) free(prime_array); prime_array=NULL;
    if(mobius_array) free(mobius_array); mobius_array=NULL;


  //Resultado
  return (result+legendre_weighted_sum);

};

//**************************************************************************************************************************
//FIM DO HEADER
