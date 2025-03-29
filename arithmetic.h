//VAMOS ESCREVER UM ARQUIVO QUE IMPLEMENTA AS QUATRO OPERAÇÕES FUNDAMENTAIS DA ARITMETICA USANDO OPERADORES DE MANIPULAÇÕES DE BIT

/*
OS SEGUINTES OPERADORES ESTÃO DISPONÍVEIS MUITAS LINGUAGENS DE PROGRAMAÇÃO PARA MANIPULAÇÃO FORMAL DE BITS:

1. & AND

0 & 0 = 0
1 & 0 = 0
0 & 1 = 0
1 & 1 = 1

2. | OR
0 | 0 = 0
1 | 0 = 1
0 | 1 = 1
1 | 1 = 1

3. ~ NOT
  ~ 0 = 1
  ~ 1 = 0

4. ^ EXCLUSIVE OR

0 ^ 0 = 0
1 ^ 0 = 1
0 ^ 1 = 1
1 ^ 1 = 0

5. OS OPERADORES << (SHIFT LEFT) E >> (SHIFT RIGHT) TRANSLADAM A SEQUÊNCIA DE
BITS PARA A ESQUERDA OU DIREITA PREENCHENDO AS LACUNAS COM 0'S. << PERFORMA UMA
MULTIPLICAÇÃO POR POTÊNCIAS DE DOIS E >> A DIVISÃO POR POTÊNCIAS DE 2.

OPERAÇÕES ARITMÉTICAS SÃO INDEPENDENTES DO SISTEMA DE NUMERAÇÃO USADO.
SEJA POR EXEMPLO A AOPERAÇÃO DE ADIÇÃO:
5 + 7 = 12
EM BINÁRIO

CARRY:  111  (UM BIT É EMPRESTADO CASO A SOMA DÊ DOIS OU TRÊS)
        ----
        0101
     +  0111
        ----
        1100

5 - 3 = 2
EM BINÁRIO:
CARRY:  0010  (TOMAMOS UM BIT EMPRESTADO CASO O BIT SER SUBTRAÍDO SEJA MENOR)
         ^
         ||
          v
        0101
     -  0011
        ----
        0010

PARA REFERÊNCIAS: https://people.eecs.berkeley.edu/~vazirani/sp04/notes/lecture2.pdf


*/



//****************************************************************************************************************************
//CABEÇALHO
#include <stdint.h>
#include <stdbool.h>


//****************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t bit_add(int64_t, int64_t);
int64_t bit_sub(int64_t, int64_t);
int64_t bit_mul(int64_t, int64_t);
int64_t bit_div(int64_t, int64_t);


//****************************************************************************************************************************
//OPERAÇÕES ARITMÉTICAS

// Soma
int64_t bit_add(int64_t a, int64_t b){
  if (b == 0)
    return a;
  else
    return bit_add(a ^ b, (a & b) << 1);
};

// Subtração
int64_t bit_sub(int64_t a, int64_t b) {
  if (b == 0)
    return a;
  else
    return bit_sub(a ^ b, ((~a) & b) << 1);
};


// Multiplição
  // Dois algoritmos são possíveis:
  /* 1.Executar a multiplicação usando as relações: para b para a.b =
     (2a).(b/2), se b for ímpar a.b =(2a).(b/2)+a. A paridade é checada usando
     b&1 de forma que todos exceto talvez o último bit são zerados. Usa-se os
     operadores << e >> para multiplicação por dois. Deve-se definir uma
     variável inicializada em 0 para alocar os resultados de cada etapa.
  */

  /* 2. Recursão usando a adição de a+a e reduzindo b em uma unidade até zerar o
   * valor de b. */

int64_t bit_mul(int64_t a, int64_t b) {
 
  //Variáveis locais
  int64_t result=0;
  bool is_negative=false;

  
  //Procedimentos
    //Ajuste de sinais
    if((a>0 && b<0) || (a<0 && b>0)) is_negative=true;
    if(a<0) a=(-a); if(b<0) b=(-b); 


    //Loop principal:iterando sobre os bits da segunda parcela
    while(b>0){
      
      //Checando a paridade do bit da segunda parcela
      if(b&1)result=bit_add(result, a);
 
      //Atualizando variáveis para a próxima iteração
      b>>=1;
      a<<=1;

    }; //Fim do loop principal


  //Resultado
  if(is_negative) return (-result);
  else return result;

};


//Divisão
int64_t bit_div(int64_t a, int64_t b) {

  //Restrição
  if (b == 0) return (-1);


  //Caso base: divisor maior que o dividendo
  if(b>a) return 0;



  //Variáveis locais
  int64_t result = 0;
  int64_t shift = 0;
  bool is_negative=false;



  //Procedimentos
    //Ajuste de sinais
    if((a>0 && b<0) || (a<0 && b>0)) is_negative=true;
    a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;

    //Ajuste da diferença de magnitude entre os dois números
    while (a >= b) {
      b <<= 1;
      shift++;
    }

    //Ajuste do divisor
    b >>= 1;
    shift--;

    // Loop principal: iterando sobre os bits
    while (shift >= 0) {

      //Se o dividendo for maior ou igual ao divisor, subtrai e coloca o bit correspondente no resultado
      if (a >= b) {
        a=bit_sub(a, b);
        result |= (1 << shift);
      }


      // Desloca o divisor b para a direita
      b >>= 1;
      shift--;
    };


  //Resultado
  if(is_negative) return (-result);
  else return result;

};
