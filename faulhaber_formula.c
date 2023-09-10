// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA A FÓRMULA DE FAULHABER
// COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o faulhaber_formula
// faulhaber_formula.c -lm

/*
A FÓRMULA DE FAULHABER NOS DÁ A SOMA DE UMA POTÊNCIA p DOS n-ÉSIMOS PRIMEIROS
NÚMEROS INTEIROS. ESTA É UMA IMPORTANTE APLICAÇÃO DOS NÚMEROS DE BERNOULLI,
ÚTIL POR EXEMPLO NO CÁLCULO DE SOMATÓRIOS. PARA MAIORES INFORMAÇÕES:
https://en.wikipedia.org/wiki/Faulhaber%27s_formula

*/

// Cabeçalho
#include "bernoulli_numbers.h"
#include <stdio.h>

// Fórmula de Faulhaber
uint64_t
faulhaber_formula (uint64_t n, uint64_t power)
{
  // Variáveis locais
  uint64_t result = 0;
  uint64_t k;
  // Procedimentos
  for (k = 0; k <= power; ++k)
    {
      result += (combination (power + 1, k)
                 * bernoulli_number_generator_positive_sign (k)
                 * pow (n, power - k + 1));
    };
  // Resultado
  return result / (power + 1);
};

// Função principal
int
main ()
{
  // Variáveis locais
  uint64_t number, power;
  // Procedimento
  // Recebendo input do usuário
  printf ("Digite um número inteiro (nº de termos incluidos na soma): ");
  scanf ("%lu", &number);
  printf ("Digite um número inteiro (expoente): ");
  scanf ("%lu", &power);
  // Exibindo o resultado da soma
  printf ("1^%lu+2^%lu+...+%lu^%lu = %lu\n", power, power, number, power,
          faulhaber_formula (number, power));

  // Finalizando a aplicação
  return 0;
}
