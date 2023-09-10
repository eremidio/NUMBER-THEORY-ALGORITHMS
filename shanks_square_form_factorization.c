// VAMOS CRIAR UM PROGRAMA QUE EMPREGA O ALGORITMO DE FORMAS QUADRÁTICAS DE
// SHANK PARA FATORAR NÚMEROS INTEIROS COMPILAR ESTE PROGRAMA COM O COMANDO:
// gcc -o shanks_square_form_factorization shanks_square_form_factorization.c
// -lm

/*
O ALGORITMO DE SHANKS É UM APRIMORAMENTO DO TESTE DE FERMAT PARA FATORAR
NÚMEROS INTEIROS E USA O FATOR DE SE FOREM ENCONTRADOS a E b SATISFAZENDO a²=b²
(mod n), COM n SENDO O NÚMERO A SER FATORADO ENTÃO POSSÍVEIS FATORES NÃO
TRIVIAIS TEM A SEGUINTE FORMA mdc(a+b, n) OU mdc(|a-b|, n).

ESTE ALGORITMO NÃO FUNCIONA PARA NÚMEROS DA FORMA n=p^k, COM p PRIMO E k
INTEIRO POSITIVO.

PARA MAIORES INFORMAÇÕES:
https://en.wikipedia.org/wiki/Shanks%27s_square_forms_factorization

*/

//***************************************************************************************************************************
// CABEÇALHO
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// VARIÁVEIS GLOBAIS
const int64_t multiplicatives[]
    = { 1, 3, 5, 7, 11, 15, 21, 35, 55, 77, 105, 165, 231, 385, 1155 };
int multiplicatives_size
    = sizeof (multiplicatives) / sizeof (multiplicatives[0]);

//***************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
bool perfect_square_checker (int64_t);
int64_t euclides_algorithm (int64_t, int64_t);
void shanks_algorithm (int64_t);

//***************************************************************************************************************************
// FUNÇÕES
// Função que determina se um número é quadrado perfeito
bool
perfect_square_checker (int64_t n)
{
  // Variáveis locais
  int64_t odd = 1;
  // Procedimentos
  while (n > 0)
    {
      n -= odd;
      odd += 2;
      if (n == 0)
        return true;
      if (n < 0)
        return false;
    };
};

// Função que implementa o algoritmo de Euclides
int64_t
euclides_algorithm (int64_t a, int64_t b)
{
  if (b == 0)
    return a;
  else
    return euclides_algorithm (b, a % b);
};

// Função que implementa o algoritmo de formas quadráticas de Shanks
void
shanks_algorithm (int64_t n)
{
// Definindo um fator multiplicativo
rerun:
  int k_index = 0;
  if (k_index == multiplicatives_size)
    {
      printf ("O algoritmo não foi capaz de fatorar o número em questão!\n");
    };

  int64_t k = multiplicatives[k_index];

  // Variáveis locais
  int64_t factor1 = 0, factor2 = 0;
  int64_t i;                             // Variável de iteração
  int64_t b0, b, p0, p1, p2, q0, q1, q2; // Variáveis usadas nos loops

  // Ajustando variáveis para o loop
  i = 0;
  p0 = floor (sqrt (k * n));
  p1 = p0;
  q0 = 1;
  q1 = (k * n - (p0 * p0));

  // TESTE, USE UM // APÓS O MESMO
  // printf("TESTE 1\n %li, %li, %li, %li\n", i, p0, q0, b);

  // Loop1
  while (perfect_square_checker (q1) == false)
    {
      ++i;
      if (n > 1000000 && i > sqrt (n))
        break;

      // Cálculo das variáveis
      b = floor ((p0 + p1) / q1);
      p2 = (b * q1) - p1;
      q2 = q0 + (b * (p1 - p2));

      // TESTE, USE UM // APÓS O MESMO
      // printf("TESTE 2\n %li, %li, %li, %li\n", i, p2, q1, b);

      // Atualizando variáveis para a proxima iteração
      q0 = q1;
      q1 = q2;
      p1 = p2;
    };

  // TESTE, USE UM // APÓS O MESMO
  // printf("TESTE 3\n %li\n", q2);

  // Reajuste de variáveis para o loop retrógado
  b0 = floor ((p0 - p1) / sqrt (q2));
  p0 = b0 * sqrt (q2) + p2;
  p1 = p0;
  q0 = sqrt (q2);
  q1 = ((k * n) - (p0 * p0)) / q0;
  i = 0;

  // TESTE, USE UM // APÓS O MESMO
  // printf("TESTE 4\n %li, %li, %li, %li\n", i, p0, q0, b);

  // Loop retógrado
  do
    {
      ++i;
      if (n > 1000000 && i > sqrt (n))
        break;

      b = floor ((p0 + p1) / q1);
      p2 = b * q1 - p1;
      q2 = q0 + (b * (p1 - p2));

      // TESTE, USE UM // APÓS O MESMO
      // printf("TESTE 5\n %li, %li, %li, %li\n", i, p2, q1, b);
      // printf("%li\n", p1);

      // Fim do loop retrogrado
      if (p1 == p2)
        break;

      // Atualizando variáveis para a proxima iteração
      q0 = q1;
      q1 = q2;
      p1 = p2;
    }
  while (true);

  // Calculando os fatores primos
  factor1 = euclides_algorithm (p1, n);
  if (factor1 > 1 && factor1 < n)
    {
      factor2 = n / factor1;
      printf ("Fatores encontrados: %li e %li\n", factor1, factor2);
    }
  else
    {
      factor1 = 0;
      k_index++;
      goto rerun;
    };
};

//***************************************************************************************************************************
// FUNÇÃO PRINCIPAL
int
main ()
{
  // Variáveis locais
  int64_t number;

  // Procedimentos
  // Recebendo input do usuário
  printf ("Digite um número inteiro a ser fatorado: ");
  scanf ("%li", &number);

  // Fatorando o número em questão
  shanks_algorithm (number);

  // Finalizando a aplicação
  return 0;
}
