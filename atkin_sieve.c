// ESTE ARQUIVO CONTERÁ UMA IMPLEMENTAÇÃO DA PENEIRA DE ATKINS, UM DOS
// ALGORITMOS MAIS EFICIENTES PARA SE CALCULAR NÚMEROS PRIMOS COMPILAR ESTE
// PROGRAMA COM O COMANDO: gcc -o atkin_sieve atkin_sieve.c -lm

/*
O ALGORITMO DE ATKIN USA FORMAS QUADRÁTICAS PARA CALCULAR NÚMEROS PRIMOS.
OS SEGUINTES TEOREMAS PROVADOS NO ARTIGO ORIGINAL DE 2003 SÃO USADOS:
TEOREMA 1: SEJA n UM NATURAL , TAL QUE n≡ 1, 13, 17, 29, 37, 41, 49, 53
mod(60); ISTO É, n≡1 mod(4). ENTÃO n É PRIMO SE E SOMENTE SE O NÚMERO SOLUÇÕES
DE 4x²+y²=n FOR ÍMPAR E NÃO FOR UM QUADRADO PERFEITO.

TEOREMA 2: SEJA n UM NATURAL , TAL QUE n≡ 7, 19, 31, 43 mod(60); ISTO É, n≡1
mod(6). ENTÃO n É PRIMO SE E SOMENTE SE O NÚMERO SOLUÇÕES DE 3x²+y²=n FOR ÍMPAR
E NÃO FOR UM QUADRADO PERFEITO.

TEOREMA 3: SEJA n UM NATURAL , TAL QUE n≡ 11, 23, 47, 59 mod(60); ISTO É, n≡11
mod(12). ENTÃO n É PRIMO SE E SOMENTE SE O NÚMERO SOLUÇÕES DE 3x²-y²=n FOR
ÍMPAR E NÃO FOR UM QUADRADO PERFEITO.

O ALGORITMO É EXECUTADO NAS SEGUINTES ETAPAS:
1. UM ARRAY DE BOOLEANOS É INDEXADO POR UM LIMITE ESPECIFICADO PELO USUÁRIO.
2. INICIALMENTE TODOS OS ELEMENTOS DESTE ARRAY SÃO INSTANCIADOS COMO FALSO.
3. PARA TODOS OS INDEXES SUPERIORES A 60 A CONGRUÊNCIA POR 60 É COMPUTADA.
4. CASO O RESULTADO DA ETAPA SEJA 2, 3, 5 (FATORES PRIMOS DE 60), O NÚMERO É
MARCADO COMO NÃO PRIMO.
5. CASO O RESULTADO DA ETAPA 3 SEJA: 1, 7, 11, 13, 17, 23, 29, 31, 37, 43, 47,
49, 53, 59. É CHECADO SE O INDEX EM QUESTÃO SATIFAZ AS CONSDIÇÕES DOS TEOREMAS
CITADOS ACIMA.
6. INDEXES SATISFAZENDO A CONDIÇÃO DOS TEOREMAS ACIMA SÃO MARCADOS COMO PRIMOS.

*/

// Cabeçalho
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//***************************************************************************************************************************
// FUNÇÕES
// Função que determina se um número é um não-quadrado perfeito e ímpar
bool
square_free_odd_checker (uint64_t number)
{
  // Variável local
  uint64_t i, limit; // Variáveis de iteração
  // Ajuste de variáveis
  limit = floor (sqrt (number));

  // Condição 1: o número deve ser ímpar
  if (number % 2 == 0)
    return false;

  // Condição 2: o número não deve ter fatores primos quadráticos (2²=4 já está
  // automaticamente descartado)
  for (i = 3; i <= limit; i += 2)
    {
      if (number % (i * i) == 0)
        return false;
    };
  // Caso as condições acima sejam satisfeitas
  return true;
};

// Função que calcula soluções inteiras para a forma quadrática 4x²+y²=n, com n
// e y ímpares
uint64_t
theorem1 (uint64_t number)
{
  // Variáveis locais
  uint64_t x, y, limit; // Variáveis de iteração
  uint64_t temp, result;

  // Ajuste de variáveis
  limit = floor (sqrt (number));
  result = 0;
  // Contando soluções inteiras para a forma quadrática do teorema 1
  for (x = 1; x < limit; ++x)
    {
      for (y = 1; y < limit; y += 2)
        {
          temp = (4 * x * x) + (y * y);

          // Condição que a equação tenha solução
          if (temp == number)
            result++;

          // TESTE USE UM // APÓS O TESTE
          // printf("%li, %li, %li\n", x, y, temp);
        };
    };

  return result;
};

// Função que calcula soluções inteiras para a forma quadrática 3x²+y²=n, com n
// e x ímpares; e y par
uint64_t
theorem2 (uint64_t number)
{
  // Variáveis locais
  uint64_t x, y, limit; // Variáveis de iteração
  uint64_t temp, result;

  // Ajuste de variáveis
  limit = floor (sqrt (number));
  result = 0;
  // Contando soluções inteiras para a forma quadrática do teorema 2
  for (x = 1; x < limit; x += 2)
    {
      for (y = 2; y < limit; y += 2)
        {
          temp = (3 * x * x) + (y * y);

          // Condição que a equação tenha solução
          if (temp == number)
            result++;

          // TESTE USE UM // APÓS O TESTE
          // printf("%li, %li, %li\n", x, y, temp);
        };
    };

  return result;
};

// Função que calcula soluções inteiras para a forma quadrática 3x²-y²=n, com x
// e y alternadamente par/ímpar ou vice-versa
uint64_t
theorem3 (uint64_t number)
{
  // Variáveis locais
  uint64_t x, y, limit; // Variáveis de iteração
  uint64_t temp, result;

  // Ajuste de variáveis
  limit = number;
  result = 0;
  // Contando soluções inteiras para a forma quadrática do teorema 2
  for (x = 2; x <= limit; ++x)
    {
      // Caso 1: x é par
      if (x % 2 == 0 && x > 2)
        {
          for (y = 1; y < x; y += 2)
            {
              temp = (3 * x * x) - (y * y);

              // Condição que a equação tenha solução
              if (temp == number)
                result++;

              // TESTE USE UM // APÓS O TESTE
              // printf("%li, %li, %li\n", x, y, temp);
            };
        };

      // Caso 2: x é ímpar
      if (x % 2 == 1)
        {
          for (y = 2; y < x; y += 2)
            {
              temp = (3 * x * x) - (y * y);

              // Condição que a equação tenha solução
              if (temp == number)
                result++;

              // TESTE USE UM // APÓS O TESTE
              // printf("%li, %li, %li\n", x, y, temp);
            };
        };
    };

  return result;
};

// Função que implementa o algoritmo de Atkin
void
atkin_algorithm (uint64_t atkin_int)
{

  // Variáveis locais
  bool atkin_array[atkin_int]; // Array de booleanos
  bool atkin_test; // Variável que determina se um número é primo ou não
  uint64_t atkin_residue, atkin_value; // Módulo 60 e número de soluções as
                                       // formas quadrátricas dos teoremas
  uint64_t i;                          // Variável de iteração

  // Procedimentos
  // Inicializando o array de booleanos com o valor falso
  for (i = 0; i < atkin_int; ++i)
    {
      atkin_array[i] = false;
      // 2, 3, 5 são primos
      if (i == 2 || i == 3 || i == 5)
        atkin_array[i] = true;
    };

  // Calculando o resíduo dos números e aplicando os teoremas 1, 2, 3 para
  // determinar se um número  é primo ou não
  for (i = 0; i < atkin_int; ++i)
    {
      // Ignorando os casos triviais
      if (atkin_array[i] == true)
        continue;
      if (i % 2 == 0 || i % 3 == 0 || i % 5 == 0)
        continue;

      // Casos não triviais encontrados o algoritmo prossegue com o cálculo do
      // resíduo módulo 60
      atkin_residue = i % 60;

      // Caso 1: teorema 1; n≡ 1, 13, 17, 29, 37, 41, 49, 53 mod(60)
      if (atkin_residue == 1 || atkin_residue == 13 || atkin_residue == 17
          || atkin_residue == 23 || atkin_residue == 37 || atkin_residue == 41
          || atkin_residue == 49 || atkin_residue == 53)
        {
          atkin_value = theorem1 (i);
          atkin_test = square_free_odd_checker (atkin_value);
          if (atkin_test == true)
            atkin_array[i] = true;
        };
      // Caso 2: teorema 2; n≡ 7, 19, 31, 43 mod(60);
      if (atkin_residue == 7 || atkin_residue == 19 || atkin_residue == 31
          || atkin_residue == 43)
        {
          atkin_value = theorem2 (i);
          atkin_test = square_free_odd_checker (atkin_value);
          if (atkin_test == true)
            atkin_array[i] = true;
        };

      // Caso 3: teorema 3; n≡ 11, 23, 47, 59 mod(60)
      if (atkin_residue == 11 || atkin_residue == 23 || atkin_residue == 47
          || atkin_residue == 59)
        {
          atkin_value = theorem3 (i);
          atkin_test = square_free_odd_checker (atkin_value);
          if (atkin_test == true)
            atkin_array[i] = true;
        };
    };

  // Exibindo o resultado
  printf ("Eis a lista de números primos até %li:\n", atkin_int);
  for (i = 0; i < atkin_int; ++i)
    {
      if (atkin_array[i] == true)
        printf ("%li, ", i);
    };

  printf ("...\n");
};
//***************************************************************************************************************************
// FUNÇÃO PRINCIPAL
int
main ()
{
  // Variáveis locais
  uint64_t number;

  // Procedimentos
  // Recebendo o input do usuário
  printf ("Usuário digite um limitante superior para sua sequência de números "
          "primos:\n->");
  scanf ("%li", &number);

  // TESTES USE UM // APÓS OS MESMOS
  // bool test1=square_free_odd_checker(551);
  // printf("%s\n", test1?"true":"false");
  // printf("teorema1: %li\n", theorem1(89));
  // printf("teorema2: %li\n", theorem2(91));
  // printf("teorema3: %li\n", theorem3(39));

  // Aplicando o algoritmo de Atkin
  atkin_algorithm (number);

  // Finalizando a aplicação
  return 0;
}
