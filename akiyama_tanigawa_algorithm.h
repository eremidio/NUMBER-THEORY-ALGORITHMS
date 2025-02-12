//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE AKIYAMA-TANIGAWA PARA COMPUTAR DE FORMA SIMPLES OS NÚMEROS DE BERNOULLI 

/*

O ALGORITMO DE AKIYAMA-TANIGAWA É UM ALGORITMO EFICIENTE SIMILAR AO TRIÂNGULO DE PASCAL PARA COMPUTAR
A SEQUÊNCIA DE NÚMEROS DE BERNOULLI. O ALGORITMO POSSUI A VANTAGEM DETRABALHAR COM FRAÇÕES COM
NUMERADORES E DENOMINADORES RELATIVAMENTE PEQUENOS.

PARA MAIORES INFORMAÇÕES: https://cs.uwaterloo.ca/journals/JIS/VOL3/KANEKO/AT-kaneko.pdf

*/


//*********************************************************************************************************************
//CABEÇALHO
#ifndef AKIYAMA_TANIGAWA_ALGORITHM_H
#define AKIYAMA_TANIGAWA_ALGORITHM_H
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>

//*********************************************************************************************************************
//ESTRUTURAS E FUNÇÕES AUXILIARES USADAS NO ALGORITMO

  //Função que calcula o gcd de dois inteiros de 128 bits
  __int128_t aki_tan_gcd(__int128_t a, __int128_t b){
 
    if(b==0) return a;
    else return aki_tan_gcd(b, (a%b));

  };


  //----------------------------------------------
//Estrutura que representa o n-ésimo  número de Bernoulli como uma fração
/*NOTA: nos restringiremos a inteiros de 128 bits, para grandes valores é necessário
        usar bibliotecas como GMP para operar com números inteiros de precisão
        múltipla.
*/
struct bernoulli_fraction{

  __int128_t num;
  __int128_t den;

};


//Função que inicializa um número de Bernoulli
struct bernoulli_fraction set_bernoulli_fraction(int64_t a, int64_t b){

  struct bernoulli_fraction bn={a, b};
  return bn;

};


//Função que computa recursivamente os números de Bernoulli
struct bernoulli_fraction compute_bernoulli_fraction(struct bernoulli_fraction b1, struct bernoulli_fraction b2, int64_t index){

  //Variáveis locais
  struct bernoulli_fraction b3;
  int64_t ratio;

  //Procedimentos
    //Cálculo do numerador e denominador
    b3.num=((b1.num*b2.den)-(b2.num*b1.den));
    b3.den=(b1.den*b2.den);

    ratio= aki_tan_gcd(index, b3.den);
    index=index/ratio; b3.den=b3.den/ratio;
    b3.num=b3.num*index;


    //Racionalizando o resultado
    ratio= aki_tan_gcd(b3.num, b3.den);
    if(ratio>1){
      b3.num=b3.num/ratio; b3.den=b3.den/ratio;
    }
    if(b3.num==0) b3.den=1;//Ajuste fino do resultado


  //Resultado
  return b3;

};



//*********************************************************************************************************************
//VARIÁVEIS  GLOBAIS
struct bernoulli_fraction bernoulli_fractions_array[100];//Array global de números de Bernoulli


//*********************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void akiyama_tanigawa_algorithm(int);

//*********************************************************************************************************************
//FUNÇÕES
//Função que computa os n-ésimos primeiros números de Bernoulli usando o algoritmo de Akiyama-Tanigawa
void akiyama_tanigawa_algorithm(int n){

  //Variáveis locais
  struct bernoulli_fraction* old_bf=NULL;
  struct bernoulli_fraction* new_bf=NULL;
  int index=0;

  //Procedimentos
    //Inicializando o array de números de Bernoulli (linha 0 no triângulo de Bernoulli)
    old_bf =(struct bernoulli_fraction*) malloc(n*sizeof(struct bernoulli_fraction));
    if(old_bf==NULL){
      printf("Erro de memória.\n");
      return;
    }

    for(int i=0; i<n; ++i){
      old_bf[i].num=1;
      old_bf[i].den=(i+1);
    };
    
    bernoulli_fractions_array[index].num=old_bf[0].num;//Adicionando o 1º elemento a lista
    bernoulli_fractions_array[index].den=old_bf[0].den;

    //Atualizando variáveis para a próxima iteração
    index++;
    n--;

    
    //Cálculo recursivo dos números de Bernoulli
    while(n>0){

      //Alocando espaço para elementos da linha seguinte no triângulo de Bernoulli  
      new_bf=(struct bernoulli_fraction*) realloc(new_bf, n*sizeof(struct bernoulli_fraction));

      //Computando elementos da nova linha
      for(int i=0; i<n; ++i){
        struct bernoulli_fraction bn = compute_bernoulli_fraction(old_bf[i], old_bf[i+1], (i+1));
        new_bf[i].num= bn.num; new_bf[i].den= bn.den;
    
      }

      //Adicionando um elemento a lista
      bernoulli_fractions_array[index].num=new_bf[0].num;
      bernoulli_fractions_array[index].den=new_bf[0].den;

      //Atualizando variáveis para a próxima iteração
      old_bf =(struct bernoulli_fraction*) realloc(old_bf, 0);
      old_bf=new_bf;
      new_bf=NULL;
      index++;
      n--;
    

    };//Fim do loop principal


    //Limpando o cachê de memória
    if(old_bf!=NULL) free(old_bf); old_bf=NULL;
    if(new_bf!=NULL) free(new_bf); new_bf=NULL;

};


//*********************************************************************************************************************
//FIM DO HEADER
#endif
