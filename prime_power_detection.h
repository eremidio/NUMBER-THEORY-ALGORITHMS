//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ROTINAS EFICIENTES PARA DETECTAR POTÊNCIAS DE NÚMEROS PRIMOS

/*

EM MUITOS ALGORITMOS É NECESSÁRIO DETERMINAR SE UM NÚMERO INTEIRO É UM QUADRADO PERFEITO, OU POTÊNCIA DE UM NÚMERO PRIMO.QUANDO
FOR REQUERIDO QUE ESTE PROCEDIMENTO SEJA REPETIDO INÚMERAS VEZES, PODEMOS USAR ALGORITMOS MAIS EFICIENTES DO QUE A FORÇA BRUTA.
TAIS ALGORITMOS ENVOLVEM TEOREMAS RELACIONADOS A CLASSES RESIDUAIS QUADRÁTICAS (SOLUÇÕES DA EQUAÇÃO x² = a (mod p)) E ALGUMAS 
PROPRIEDADES DE DIVISIBILIDADE DE NÚMEROS INTEIROS. POR EXEMPLO, UM NÚMERO É UM QUADRADO PERFEITO SE E SOMENTE SE O SÍMBOLO DE 
LEGENDRE (n|p) FOR IGUAL 1 PARA TODO PRIMO NÃO DIVIDINDO n. NO PRESENTE ALGORITMO USAREMOS UMA ESQUEMA EFICIENTE DE BUSCA EM 
TABELAS NO LUGAR DE COMPUTAR OS SÍMBOLOS DE LEGENDRE DIRETAMENTE PARA A DETECÇÃO DE NÃO QUADRADOS PERFEITOS.


O SEGUINTE TEOREMA PERMITE A DETECÇÃO DE POTÊNCIAS DE NÚMEROS PRIMOS: SEJA a, UMA TESTEMUNHA DA COMPOSIÇÃO DE n NO TESTE DE
PRIMALIDADE DE MILLER-RABIN TAL QUE mdc(a,n)=1, ISTO É SUPONHA QUE (n-1)=(2^t)q, TAL QUE (a^q)≠1 (mod n) E para s=0,1,...,t-1
(a^q(2^s))≠ (-1) (mod n), ENTÃO SE n FOR DA FORMA n=(p^k) COM p PRIMO E k INTEIRO mdc((a^n-a), n) É UM FATOR NÃO TRIVIAL DE n.


PARA MAIORES INFORMAÇÕES: A Course In Computational Algebraic Number Theory by Henri Cohen

*/ 


//**************************************************************************************************************************************
//CABEÇALHO
#ifndef PRIME_POWER_DETECTION_H
#define PRIME_POWER_DETECTION_H
#include"baillie_psw_prime_test.h"
#include<stdbool.h>
#include<stdint.h>
#include<math.h>

//CONSTANTES GLOBAIS
const int q11[11]={1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0};
const int q63[63]={1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
const int q64[64]={1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
const int q65[65]={1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1};




//**************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool fast_square_detection(int64_t, int64_t*);
bool fast_prime_power_detection(int64_t, int64_t*);

//**************************************************************************************************************************************
//FUNÇÕES
//Função que determina se um número é um quadrado perfeito
bool fast_square_detection(int64_t number, int64_t* root){

  //Variáveis locais
  int64_t t=(number%64), r;

  //Procedimentos
    //Testes rápidos para detecção de não quadrados perfeitos
      //Teste 1:
      if(q64[t]==0) return false;

      //Ajuste de variáveis
      r=(number%45045);  
      //Teste 2:
      if(q63[r%63]==0) return false;
      //Teste 3:
      if(q65[r%65]==0) return false;
      //Teste 4:
      if(q11[r%11]==0) return false;

      //Teste 5:
      r=floor(sqrt(number));
      if((r*r)==number){
        (*root)=r;
        return true;      
      }
      else return false;

};


//Função que detecta potências de números primos por divisão e erro usando uma roda 210k+r
bool fast_prime_power_detection(int64_t number, int64_t* prime){

  //Caso base: n=2 ou n primo
  if(!(number&1)){

    case2:
    if(number==2){
      (*prime)=2;
      return true;
            }

    while(number>2) number>>=1;
    if(number==2) goto case2;
    else return false;
  

  }

  if(baillie_psw_test(number)==true){
    (*prime)=number;
    return true;
  }


  //Variáveis locais
  int prime105[3] = {3, 5, 7};
  int remainder_seed[48] = {1,   11,  13,  17,  19,  23,  29,  31,  37,  41, 43,  47,  53,  59,  61,  67,  71,  73,  79,  83,
                            89,  97,  101, 103, 107, 109, 113, 121, 127, 131,137, 139, 143, 149, 151, 157, 163, 167, 169, 173,
                            179, 181, 187, 191, 193, 197, 199, 209};


  int64_t prime_divisor;
  int64_t root=sqrt(number);


  //Procedimentos
    //Teste com fatores 3,5,7
    for(int k=0; k<3; ++k){
 
      prime_divisor=prime105[k];
 
      if((number%prime_divisor)==0){
        while((number%prime_divisor)==0) number/=prime_divisor;
        if(number==1){
          (*prime)=prime_divisor;
          return true;
        }
        else return false;
                                   };
    }


    //Loop principal
    for(int64_t i=0; ; ++i){

      for(int j=0; j<48; ++j){

          prime_divisor=(210*i)+remainder_seed[j];
          if(prime_divisor>root) return false;

          if((number%prime_divisor)==0 && prime_divisor>7){

             while((number%prime_divisor)==0) number/=prime_divisor;
             if(number==1){
               (*prime)=prime_divisor;
               return true;
                          }
             else return false;
             
          }

                             };//Fim do loop sobre classes residuais módulo 210 para números primos
    }  //Fim do loop principal 


    return false;
};



//**************************************************************************************************************************************
//FIM DO HEADER
#endif
