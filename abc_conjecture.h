//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ROTINAS PARA TESTAR A CONJECTURA ABC

/*
 
SEJA n UM NÚMERO INTEIRO, O RADICAL DE n DENOTADO POR rad(n) CORRESPONDE AO PRODUTO DE TODOS OS FATORES PRIMOS DE n IGNORANDO-SE SUAS 
MULTIPLICIDADES. SEJA μ(n) A FUNÇÃO DE MÖBIUS, SE μ(n) ≠ 0, ISTO É, SE n NÃO TIVER FATORES PRIMOS REPETIDOS ENTÃO rad(n)=n. POR
EXEMPLO: 6=2x3, ENTÃO rad(6)=6; 1000=2³x5³, ENTÃO rad(1000)=2x5=10.

A CONJECTURA ABC (SURGIDA COMO UMA CONSEQUÊNCIA DA CONJECTURA DE SZPIRO SOBRE CONDUTORES DE CURVAS ELÍPTICAS) AFIRMA QUE DADO
INTEIROS a, b, c COPRIMOS ENTRE SI COM a+b=c, EXISTE APENAS UM NÚMERO FINITO DE TRIPLAS (a, b, c) SATISFAZENDO A DESIGUALDADE
rad(abc)^{1+ε} < c COM ε>0 UM REAL POSITIVO. DEFININDO A QUALIDADE DE UM TRIPLA ORDENADA COMO q(a, b, c)= ln(c)/ln(rad(abc)), A
DESIGUALDADE ANTERIOR PODE SER EXPRESSA COMO q(a, b, c)>{1+ε}, PARA UM TRIPLA DE INTEIROS E UM NÚMERO REAL SATISFAZENDO AS
CONDIÇÕES ACIMA. EMBORA HAJA INFINITAS TRIPLAS ORDERNADAS COM q(a, b, c)>1, PARA UM DADO ε A CONJECTURA PREVÊ QUE APENAS UM NÚMERO
FINITO DE TRIPLAS ORDENADAS SATIFAÇA AS DESIGUALDADES PRÉVIAS, EM PARTICULAR, SE a E b FOREM DIVISÍVEIS POR GRANDES POTÊNCIAS DE
NÚMEROS PRIMOS PEQUENOS. SE A CONJECTURA FOR VERDADEIRA DEVE EXISTIR UMA TRIPLA (a, b, c) QUE TENHA A QUALIDADE MÁXIMA.

A CONJECTURA ABC É UMA DAS CONJECTURAS MAIS IMPORTANTES EM TEORIA ADITIVA DOS NÚMEROS, POIS INÚMEROS RESULTADOS JÁ DEMONSTRADOS E
CONJECTURAS EM ABERTO EMERGEM COMO UMA CONSEQUÊNCIA NATURAL DESSA CONJECTURA.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Abc_conjecture
                          https://en.wikipedia.org/wiki/Szpiro%27s_conjecture
                          https://en.wikipedia.org/wiki/Mason%E2%80%93Stothers_theorem
                          Elementary Methods in Number Theory, by Melvin B. B. Nathanson

*/


//****************************************************************************************************************************************
//CABEÇALHO
#ifndef ABC_CONJECTURE_H
#define ABC_CONJECTURE_H
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>

//VARIÁVEIS GLOBAIS
int32_t ABC_SIZE=0;//Raiz quadrada do limitante superior
size_t ABC_COUNTER=0;//Contador de triplas ordenadas
const int32_t ABC_RAD_MAX=5000000;//Contador de triplas ordenadas
int32_t ABC_RADICALS[5000001];//Rádicais de inteiros inferiores a 5x10^6

//****************************************************************************************************************************************
//ESTRUTURAS AUXILIARES USADAS NO ALGORITMO
//Estrutura que aloca uma tripla ordenada de inteiros de 64 bits e o fator de qualidade associado a esta tripla
struct abc_set{

  int64_t a;
  int64_t b;
  int64_t c;
  double q;//Fator de qualidade

};


//****************************************************************************************************************************************
//FUNÇÕES AUXILIARES
//Função que preenche um buffer de inteiros contendo os menores fatores primos de inteiros até 10⁸
int32_t* fill_prime_factor_array(){

  //Variáveis locais
  int32_t* ABC_PRIME_ARRAY = (int32_t*)calloc(ABC_SIZE+1, sizeof(int32_t));


  //Procedimentos
    //Inicializando elementos do array
    for(int32_t i=0; i<=ABC_SIZE; ++i)
      ABC_PRIME_ARRAY[i]=i;

    //Loop principal
    for(int32_t n=2; n<ABC_SIZE; n++){

      if((ABC_PRIME_ARRAY[n]-n)<0) continue;//Checando se n contém um fator primo não trivial menor que n

      for(int32_t m=(n<<1); m<=ABC_SIZE; m+=n){
        if(ABC_PRIME_ARRAY[m]==m)
          ABC_PRIME_ARRAY[m]=n;
      }

    }


  //Resultado
  return ABC_PRIME_ARRAY;

};

//Função que calcula o gcd de dois números inteiros de 64 bits
int64_t gcd_s64(int64_t a, int64_t b){

  //Variáveis locais
  int64_t temp=0;

  //Procedimentos
    //Loop principal
    while(b>0){

      temp=(a%b);
      a=b;
      b=temp;

    };


  //Resultado
  return a;

};



//****************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t compute_integer_radical(int64_t, int32_t[]);
bool check_number_triple(int64_t, int64_t, int64_t, int32_t[], double*);
struct abc_set* test_abc_conjecture(int32_t[]);


//****************************************************************************************************************************************
//FUNÇÕES
//Função que computa o radical de um inteiro de 64 bits
int64_t compute_integer_radical(int64_t n, int32_t ABC_PRIME_ARRAY[]){
  
  //Caso base:
  if(n==1) return 1;
  if(n<=ABC_RAD_MAX && ABC_RADICALS[n]>0) return ABC_RADICALS[n];

  //Variáveis locais
  double rad=1.0;
  int32_t factor=0;

  
  //Procedimentos
    //Loop principal
    while(1){

      //Caso 1:  n ≲ ABC_SIZE
      mainloop1:
      if(n<=ABC_SIZE){
        while(n>1){
          if(n<=ABC_RAD_MAX && ABC_RADICALS[n]>0) return rad*ABC_RADICALS[n];
          factor=ABC_PRIME_ARRAY[n];
          rad=rad*factor;
          while(n%factor==0) n=n/factor;
          
        
        }

      };//Fim do loop 1
      if(n<2) break;


      //Caso 2: n>ABC_SIZE
      mainloop2:
      for(int32_t i=2; i<=ABC_SIZE; ++i){

        if(n<=ABC_RAD_MAX && ABC_RADICALS[n]>0) return rad*ABC_RADICALS[n];
        if(ABC_PRIME_ARRAY[i]<i || n%ABC_PRIME_ARRAY[i]>0) continue;

        n=n/ABC_PRIME_ARRAY[i];
        rad=rad*ABC_PRIME_ARRAY[i];
        while(n%ABC_PRIME_ARRAY[i]==0)
          n=n/ABC_PRIME_ARRAY[i];

        if(n<2) break;

      };//Fim do loop 2
      if(n<2) break;

      if(n>2){ //caso n contenha algum fator primo superior a ABC_SIZE
        rad=rad*n; break;
      }//Fim do loop 2


    };//Fim do loop principal

  
  //Resultado
  if(n<=ABC_RAD_MAX) ABC_RADICALS[n]=rad;
  return rad;

};

//Função que checa se uma tripla de inteiros (com a, b coprimos entre si) satisfaz as desigualdades que caracterizam a conjectura abc
bool check_number_triple(int64_t a, int64_t b, int64_t c, int32_t ABC_PRIME_ARRAY[], double* rad_abc){
   
  //Variáveis locais
  double rad_t=1.0;

  
  //Procedimentos
    //Computando o radical do inteiros
    rad_t=rad_t*compute_integer_radical(a, ABC_PRIME_ARRAY);
    rad_t=rad_t*compute_integer_radical(b, ABC_PRIME_ARRAY);
    if(rad_t>c) return false;
    rad_t=rad_t*compute_integer_radical(c, ABC_PRIME_ARRAY);
    if(rad_t>c) return false;

  //Resultado
  (*rad_abc)=rad_t;
  return true;


};

//Função que computa triplas ordenadas que satisfazem a desigualdades que caracterizam a conjectura abc
struct abc_set* test_abc_conjecture(int32_t ABC_PRIME_ARRAY[]){

  //Variáveis locais
  struct abc_set* abc_array=NULL;
  size_t abc_index=0;
  int64_t ABC_MAX=ABC_SIZE*ABC_SIZE;
  register int64_t a, b, c;
  double radical;


  //Procedimentos
    //Loop principal
    for(a=1; a<ABC_MAX; ++a){
      for(b=(a+1); b<ABC_MAX; ++b){

        //Restrição: a, b, c devem ser coprimos entre si
        if( ( !(a&1) && !(b&1) ) || gcd_s64(a, b)>1) continue;
        else c=a+b;
        
        //Calculando a qualidade da tripla ordenada
        if(check_number_triple(a, b, c, ABC_PRIME_ARRAY, &radical)==true){

          abc_index++;
          abc_array=(struct abc_set*)realloc(abc_array, abc_index*sizeof(struct abc_set));
          abc_array[abc_index-1].a=a; abc_array[abc_index-1].b=b; abc_array[abc_index-1].c=c;
          abc_array[abc_index-1].q=log(c)/log(radical);

        }


      };
    };//Fim do loop principal


  //Resultado
  ABC_COUNTER=abc_index;
  return abc_array;

};

//****************************************************************************************************************************************
//FIM DO HEADER
#endif
