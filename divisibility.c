// VAMOS ESCREVER UM PROGRAM QUE CONTÉM VÁRIAS ROTINAS PARA DETERMINAR SE UM
// INTEIRO É DIVISÍVEL POR DETERMINADOS NÚMEROS PRIMOS COMPILAR ESTE PROGRAMA
// COM O COMANDO: gcc -o divisibility divisibility.c -lm

/*
UM NÚMERO INTEIRO a É DITO SER DIVISÍVEL POR OUTRO INTEIRO b SE a = 0 mod(b).
ISTO É O RESTO DA DIVISÃO DE UM NÚMERO POR OUTRO FOR ZERO.A NOTAÇÃO a|b É USADA
TAMBÉM NESTE CASO. VÁRIOS CRITÉRIOS DE DIVISIBILIDADE SÃO EMPREGADOSPARA
NÚMEROS ESPECÍFICOS, SEJA n UM NÚMERO COMPOSTO E p(1), ..., p(N) SEUS FATORES
PRIMOS UM NÚMERO SERÁ DIVISÍVEL POR n SE E SOMENTE FOR DIVISÍVEL POR CADA UM DE
SEUS FATORES PRIMOS. BASTA ENTÃO DEFINIR ROTINAS ESPECIFÍCAS PARA TESTAR A
DIVISIBILIDADE POR NÚMEROS PRIMOS

*/

//**************************************************************************************************************************
// CABEÇALHO
#include "divisibility.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

//**************************************************************************************************************************
// FUNÇÃO PRINCIPAL

int
main ()
{
  // Variáveis
  uint64_t number;
  // Recebendo input do usuário
  printf ("Usuário digite um número: ");
  scanf ("%li", &number);

  // Testando a divisibilidade de um número pelos números primos até 30
  printf ("Divisibilidade por 2: %s\n",
          divisible_by_2 (number) ? "Verdadeiro" : "Falso");
  printf ("Divisibilidade por 3: %s\n",
          divisible_by_3 (number) ? "Verdadeiro" : "Falso");
  printf ("Divisibilidade por 5: %s\n",
          divisible_by_5 (number) ? "Verdadeiro" : "Falso");
  printf ("Divisibilidade por 7: %s\n",
          divisible_by_7 (number) ? "Verdadeiro" : "Falso");
  printf ("Divisibilidade por 11: %s\n",
          divisible_by_11 (number) ? "Verdadeiro" : "Falso");
  printf ("Divisibilidade por 13: %s\n",
          divisible_by_13 (number) ? "Verdadeiro" : "Falso");
  printf ("Divisibilidade por 17: %s\n",
          divisible_by_17 (number) ? "Verdadeiro" : "Falso");
  printf ("Divisibilidade por 19: %s\n",
          divisible_by_19 (number) ? "Verdadeiro" : "Falso");
  printf ("Divisibilidade por 23: %s\n",
          divisible_by_23 (number) ? "Verdadeiro" : "Falso");
  printf ("Divisibilidade por 29: %s\n",
          divisible_by_29 (number) ? "Verdadeiro" : "Falso");

  // Finalizando a aplicação
  return 0;
};
