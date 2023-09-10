// VAMOS CRIAR UM PROGRAMA PARA CALCULAR SOLUÇÕES DA EQUAÇÃO DE PELL
// COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o pell_equation pell_equation.c
// -lm

/*
A EQUAÇÃO DE PELL TEM A FORMA x²-ny²=1.
SE n FOR UM INTEIRO, ENTÃO A EQUAÇÃO PROVÊ UM TESTE QUE DETERMINA SE A RAÍZ
QUADRADA DE n É IRRACIONAL OU NÃO. SE SOLUÇÕES NÃO TRIVIAIS (x, y) (OU SEJA
x=1, y=0) FOREM ENCONTRADAS ENTÃO n^(1/2) É IRRACIONAL.

UM MÉTODO GERAL DE SOLUÇÃO EXISTE SE A FRAÇÃO CONTÍNUA DE n^(1/2) FOR
CONHECIDA.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Pell%27s_equation


*/

//**********************************************************************************************************************
// CABEÇALHO
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

//**********************************************************************************************************************
// FUNÇÕES
// Função que determina se um número é inteiro ou não
bool
non_integer_check (long double x)
{
  return (floor (x) - x < 0);
};

// Função que busca soluções para a equação de Pell iterativamente
void
pell_equation_solver (uint64_t n, uint64_t max_n)
{
  // Variáveis locais
  long double x_;
  uint64_t x, y;
  // Procedimentos
  for (y = 1; y < max_n; ++y)
    {
      x_ = sqrt (1 + n * (y * y));
      if (non_integer_check (x_) == false)
        {
          x = x_;
          printf ("Soluções para a equação de Pell foram encontradas!\nx=%lu, "
                  "y=%lu\n√%lu é irracional.\n",
                  x, y, n);
          return;
        };
    };

  printf ("Soluções para a equação de Pell  não foram encontradas no limite "
          "especificado!\n");
};

//**********************************************************************************************************************
// FUNÇÃO PRINCIPAL
int
main ()
{
  // Variáveis locais
  uint64_t n, limit;
  // Procedimentos
  // Recebendo input do usuário
  printf ("Digite um número inteiro: ");
  scanf ("%lu", &n);
  printf (
      "Digite um um valor limite para buscar soluções da equação de Pell: ");
  scanf ("%lu", &limit);

  // Aplicando o teste da equação de Pell
  pell_equation_solver (n, limit);
  // Finalizando a aplicação
  return 0;
}
