// UM PROGRAMA SIMPLES QUE CONVERTE UM INTEIRO EM NOTAÇÃO BINÁRIA
// POTÊNCIA DE 2 SÃO TRIVIAIS: 2=2¹ --> 10, 4=2² --> 100, 8=2³ --> 1000 E NO
// ALGORITMO SÃO INVERTIDAS CABEÇALHO
#include <stdint.h>
#include <stdio.h>

int
main ()
{
  // Variáveis-input do usuário
  unsigned long long number;
  printf ("Usuário digite um número que será convertido em binário:\n->");
  scanf ("%llu", &number);

  // Calculando se o número é par ou não
  int last = (number & 1);

  // Convertendo o número em binário
  while (number > 0)
    {
      if (number & 1)
        printf ("1");
      else
        printf ("0");

      number >>= 1;
    };

  // Ajustando o último digito
  if (last == 0)
    printf ("0\n");
  else
    printf ("\n");

// Finalizando a aplicação
end:
  return 0;
}
