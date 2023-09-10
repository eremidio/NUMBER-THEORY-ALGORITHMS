// VAMOS ESCREVER UM ARQUIVO QUE IMPLEMENTA AS QUATRO OPERAÇÕES FIUNDAMENTAIS
// DA ARITMETICA USANDO OPERADORES DE BIT

/*
OS SEGUINTES OPERADORES ESTÃO DISPONÍVEIS EM C E C++:

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
MULTIPLICAÇÃO POR POTÊNCIAS DE DOIS E >> A DIVISÃOPOR POTÊNCIAS DE 2.

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

*/

//****************************************************************************************************************************
// CABEÇALHO
#include <stdint.h>
//****************************************************************************************************************************
// OPERAÇÕES ARITMÉTICAS

// Soma
int64_t
bit_add (int64_t a, int64_t b)
{
  if (b == 0)
    return a;
  else
    return bit_add (a ^ b, (a & b) << 1);
};

// Subtração
int64_t
bit_sub (int64_t a, int64_t b)
{
  if (b == 0)
    return a;
  else
    return bit_sub (a ^ b, ((~a) & b) << 1);
};

// Multiplição
int64_t
bit_mul (int64_t a, int64_t b)
{
  // Variáveis locais
  int sign;
  int64_t parcel = a;
  // Procedimentos
  // Conferindo os sinais de a e b, para operandos negativos
  if (a > 0 && b < 0)
    {
      sign = 0;
      b = (~b) + 1;
    };
  if (a < 0 && b > 0)
    {
      sign = 0;
      a = (~a) + 1;
    };
  if (a < 0 && b < 0)
    {
      sign = 1;
      b = (~b) + 1;
      a = (~a) + 1;
    };
  if (a > 0 && b > 0)
    {
      sign = 1;
    };

  // Dois algoritmos são possíveis:
  /* 1.Executar a multiplicação usando as relações: para b para a.b =
     (2a).(b/2), se b for ímpar a.b =(2a).(b/2)+a. A paridade é checada usando
     b&1 de forma que todos exceto talvezz o último bit são zerados. Usa-se os
     operadores << e >> para multiplicação por dois. Deve-se definir uma
     variável inicializada em 0 para alocar os resultados de cada etapa.
  */

  /* 2. Recursão usando a adição de a+a e reduzindo b em uma unidade até zerar
   * o valor de b. */

  while (b != 1)
    {
      a = bit_add (a, parcel);
      b = bit_sub (b, 1);
    };

  // Calculando o sinal do resultado
  if (sign == 1)
    return a;
  if (sign == 0)
    return (~a) + 1;
};

// Divisão
int64_t
bit_div (int64_t a, int64_t b)
{
  // Caso trivial
  if (b > a)
    return 0;
  // Variáveis locais
  int sign;
  int64_t result = 0;
  // Procedimentos
  // Conferindo os sinais de a e b, para operandos negativos
  if (a > 0 && b < 0)
    {
      sign = 0;
      b = (~b) + 1;
    };
  if (a < 0 && b > 0)
    {
      sign = 0;
      a = (~a) + 1;
    };
  if (a < 0 && b < 0)
    {
      sign = 1;
      b = (~b) + 1;
      a = (~a) + 1;
    };
  if (a > 0 && b > 0)
    {
      sign = 1;
    };

  // Usaremos recursão e a operação de subtração

  while (a > 0)
    {
      a = bit_sub (a, b);
      result = bit_add (result, 1);
    };

  // Calculando o sinal do resultado
  if (sign == 1)
    return result;
  if (sign == 0)
    return (~result) + 1;
};
