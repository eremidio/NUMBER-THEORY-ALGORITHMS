//VAMOS CRIAR UM PROGRAMA QUE TESTA A VALIDADE DA CONJECTURA DE GOLDBACH

/*

  A CONJECTURA DE GOLDBACH É UMA IMPORTANTE CONJECTURA EM TEORIA ADITIVA DOS NÚMEROS QUE AFIRMA QUE QUALQUER INTEIRO n PAR SUPERIOR A 2 PODE
  SER EXPRESSO COMO A SOMA DE 2 NÚMEROS PRIMOS. VARIAÇÕES DESTA PROPOSIÇÃO EXISTEM NA LITERATURA MATEMÁTICA. A CONJECTURA FOI VERIFICADA
  NUMERICAMENTE PARA VALORES DA ORDEM DE 10^18, MAS A PROVA DO RESULTADO PARA TODOS OS INTEIROS PARES PERMANECE UM PROBLEMA EM ABERTO. O
  CHAMADO TEOREMA DE CHEN QUE AFIRMA QUE TODO INTEIRO PAR SUFICIENTEMENTE GRANDE É A SOMA DE DOIS PRIMOS OU DE UM UM PRIMO E UM SEMIPRIMO
  É UMA VERSÃO SIMPLIFICADA DA CONJECTURA ORIGINAL (NORMALMENTE DENOMINADA VERSÃO FORTE DA CONJECTURA DE GOLDBACH).

  A FUNÇÃO DE PARTIÇÃO DE GOLDBACH g(n) É UMA FUNÇÃO ARTIMÉTICA QUE ENUMERA O NÚMERO DE REPRESENTAÇÕES DE UM INTEIRO n COMO A SOMA DE DOIS
  PRIMOS. UMA FORMA ANALÍTICA PERMITE EXPRESSAR ESTA FUNÇÃO EM TERMOS DA CONSTANTE DE NÚMEROS PRIMOS GÊMEOS, DE UM PRODUTÓRIO ENVOLVENDO
  NÚMEROS PRIMOS DIVIDINDO n E DA INTEGRAL DEFINIDA NO INTERVALO [2, n] DA FUNÇÃO f(x)=ln(x)^2.

  VERSÕES MENOS RESTRITIVAS DA CONJECTURA DE GOLDBACH, COMO A PROPOSIÇÃO FRACA DE GOLDBACH SEGUNDO A QUAL TODO INTEIRO ÍMPAR SUPERIOR A 7
  PODE SER EXPRESSO COMO A SOMA DE TRÊS PRIMOS ÍMPARES JÁ FORAM DEMONSTRADAS.


  PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Goldbach%27s_weak_conjecture
                            https://en.wikipedia.org/wiki/Goldbach%27s_conjecture
                            https://mathworld.wolfram.com/GoldbachConjecture.html
                            https://en.wikipedia.org/wiki/Chen's_theorem  
                            https://en.wikipedia.org/wiki/Goldbach's_comet
                            https://mathworld.wolfram.com/GoldbachPartition.html

*/


//***************************************************************************************************************************************************
//CABEÇALHO
#ifndef GOLDBACH_CONJECTURE_H
#define GOLDBACH_CONJECTURE_H 
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>


//CONSTANTES GLOBAIS
enum show_golbach_partition{ Yes, No};
int32_t GOLDBACH_BOUND=0;


//***************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool* fill_prime_buffer(int32_t);
int32_t compute_golbach_partition(int32_t, bool[], enum show_golbach_partition);


//***************************************************************************************************************************************************
//FUNÇÕES
//Função que preenche um buffer de números primos (0/false-> primo, 1/true-> não primo)
bool* fill_prime_buffer(int32_t n){

  //Variáveis locais
  bool* prime_array=(bool*)calloc(n+1, sizeof(bool));
  
  
  //Procedimentos
    //Ajuste dos elementos do array
    for(int32_t i=2; i<=n; ++i) prime_array[i]=true;

    //Loop principal: removendo números compostos
    for(int32_t k=2; (k*k)<=n; ++k){

      if(!prime_array[k]) continue;
      for(int32_t l=(k*2); l<=n; l+=k){
        prime_array[l]=false;
      }

    }

  
  //Resultado
  GOLDBACH_BOUND=n;
  return prime_array;

};


//Função que computa a função de partição de Goldbach
int32_t compute_golbach_partition(int32_t n, bool prime_array[], enum show_golbach_partition x){

  //Restrição
  if(n>GOLDBACH_BOUND)
    return -1;


  //Exibindo as partições 
  if(x==Yes) printf("%i = ", n);


  //Variáveis locais
  register int32_t result=0, diff=0;


  //Procedimentos: loop principal
  for(int32_t i=2; i<=n; ++i){

    if(!prime_array[i]) continue;
    diff=n-i;
    if(prime_array[diff]){
      result++;
      if(x==Yes) printf("%i + %i = ", i, diff);  
    }

  }; //Fim do loop principal

    
  //Resultado
  if(x==Yes) printf("...\n");
  return result;

};


//***************************************************************************************************************************************************
//FIM DO HEADER
#endif
