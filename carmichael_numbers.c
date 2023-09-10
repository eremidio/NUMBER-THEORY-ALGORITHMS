// VAMOS CRIAR UM PROGRAMA EM C QUE DETERMINA SE UM NÚMERO PERTENCE A CLASSE
// DOS ALGORITMOS DE CHARMICAEL NUMBERS COMPILAR ESTE PROGRAMA COM O COMANDO:
// gcc -o carmichael_numbers carmichael_numbers.c

/*
OS NÚMEROS DE CARMICHAEL SATISFAZEM A SEGUINTE PROPOSIÇÃO: SENDO n UM NÚMERO
COMPOSTO PARA b RELATIVAMENTE PRIMO COM n TÊM-SE b^(n-1) = 1 (mod n) OU b^n = b
(mod n).

ESTA DEFINIÇÃO FAZ COM QUE NÚMEROS DE CARMICHAEL PASSEM PELO TESTE DE
PRIMALIDADE DE FERMAT (SÃO OS CHAMADOS PSEUDOPRIMOS DE FERMAT). POR ESTA RAZÃO
OS TESTE PRIMALIDADE DE FERMAT NÃO É UM TESTE 100% DETERMINÍSTICO DE
PRIMALIDADE.

PARA DETECTAR SE UM NÚMERO É UM NÚMERO DE CARMICHAEL PODE-SE TESTAR PARA
VALORES DE ATÉ n SE AS IDENTIDADES ACIMAS NA DEFINIÇÃO SÃO SATISFEITAS. OUTRA
POSSIBILIDADE É USAR O TEOREMA DE KORSELTS QUE AFIRMA QUE: UM NÚMERO n É UM
NÚMERO DE CARMICHAEL SE E SOMENTE SE ELE NÃO TIVER FATORES PRIMOS QUADRÁTICOS E
PARA TODO FATOR PRIMO p (n-1) DIVIDE (p-1).

NÚMEROS DE CARMICHAEL SÃO UM SUBCONJUNTO (SUBONJUNTO K1) DOS CHAMADOS NÚMERO DE
KNÖDEL.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Carmichael_number
                          https://en.wikipedia.org/wiki/Knödel_number

*/

//***************************************************************************************************************************
// CABEÇALHO
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//***************************************************************************************************************************
// FUNÇÕES
// Função que determina se um número em questão é um número de Carmichael
bool
carmichael_checker (uint64_t n)
{
  // Caso trivial
  if (n % 2 == 0)
    return false;
  // Caso geral
  // Variáveis locais
  uint64_t *prime_factors = NULL;
  bool result;
  uint64_t i, prime_size = 0, n1 = n;
  // Procedimentos
  // Loop principal: busca por fatores primos ímpares
  for (i = 3; i < n; i += 2)
    {
      if (n1 % i == 0)
        {
          n1 /= i;
          prime_size++;
          prime_factors = (uint64_t *)realloc (prime_factors,
                                               prime_size * sizeof (uint64_t));
          prime_factors[prime_size - 1] = i;

          // Checando por fatores quadráticos
          if (n1 % i == 0)
            {
              result = false;
              goto last_step;
            };
        };
      if (n1 == 1)
        break;
    };

  // TESTE, USE UM // APÓS OS TESTES
  // for(int j=0; j<prime_size; ++j)
  // printf("%lu ", prime_factors[j]);
  // printf("\n");

  // Teste de divisibilidade
  for (i = 0; i < prime_size; ++i)
    {
      if (((n - 1) % (prime_factors[i] - 1)) != 0)
        {
          result = false;
          goto last_step;
        };
    };

  // Caso o número passe nos testes acima um número de Carmichael foi
  // encontrado
  result = true;

// Limpando o cachê de memória e retornando os resultados
last_step:
  free (prime_factors);
  return result;
}

//***************************************************************************************************************************
// FUNÇÃO PRINCIPAL
int
main ()
{
  // Variáveis locais
  uint64_t number;

  // Procedimentos
  // Recebendo input do usuário
  printf ("Digite um número inteiro: ");
  scanf ("%lu", &number);
  // Testando se o número em questão é um número de Carmichael
  bool test = carmichael_checker (number);

  if (test == true)
    printf ("O número %lu é um número de Carmichael.\n", number);
  else
    printf ("O número %lu não é um número de Carmichael.\n", number);

  // Finalizando a aplicação
  return 0;
}
