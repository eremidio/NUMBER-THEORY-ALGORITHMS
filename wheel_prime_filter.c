// VAMOS IMPLEMENTAR O ALGORITMO DE RODA PARA DETERMINAR SE UM NÚMERO É PRIMO
// OU NÃO. COMPILAR ESTE PROGRAMA COM O COMANDO:: gcc -o wheel_prime_filter
// wheel_prime_filter.c -lm
/*
O MÉTODO DE FATORAÇÃO DE RODA É USADO PARA GERAR UMA LISTA DE NÚMEROS PRIMOS A
PARTIR DE UMA LISTA DE NÚMEROS PRIMOS MENOR. O ALGORITMO É EXECUTADO NOS
SEGUINTES PASSOS:
1. ESCOLHEMOS A CIRCUNFERÊNCIA DA RODA, UM NÚMERO INTEIRO r.
2. COMPUTA-SE A EXPANSÃO DE r EM FATORES PRIMOS.
3. PRIMOS SERÃO DA FORMA p+kr, ONDE p SÃO NÚMEROS COPRIMOS DE r NO INTERVALO
[0, r) E k INTEIRO. ESPECIFICAMENTE NÚMEROS PRIMOS SÃO DA FORMA n≠0 mod(p) PARA
TODO p EM [0,r).

EXMEPLOS:
PARA N=6, OS FATORES PRIMOS DE 6 SÃO 2, 3. NO INTERVALO [1,6] APENAS 1 E 5 SÃO
COPRIMOS COM 2 E 3, PORTANTO TEMOS DE TESTAR VALORES DADO UM NÚMERO INTEIRO n
QUE SATIZFAZ: i=[1,2,3,5]+6k, k INTEIRO E i ≠ 0 mod (j) COM j=2,3,5 (1 é o caso
trivial).

PARA N=30, CUJOS FATORES PRIMOS SÃO 2, 3, 5. OS NÚMEROS COPRIMOS COM 30 NO
INTERVALO [0, 30] SÃO 7,11, 13, 17,23, 29. PORTANTO TEMOS DE TESTAR VALORES
DADO UM NÚMERO INTEIRO n QUE SATIZFAZEM: i=[1,2,3,5, 7,11,13, 17,23, 29]+30k, k
INTEIRO E i ≠ 0 mod (j) COM j=2,3,5,7,11, 13, 17, 23, 29 (1 é o caso trivial).

CADA UPGRADE POR UM FATOR (k+1) DA RODA CORRESPONDE A UM GIRO DA MESMA NA BUSCA
POR NÚMEROS PRIMOS. RODAS DE CIRCUNFERÊNCIA MAIOR QUE 30 SÃO COMPUTACIONALMENTE
DISPENDIOSAS. NOTE-SE QUE NO ALGORITMO ACIMA OS NÚMEROS COMPOSTOS FORMADOS PELA
MULTIPLICAÇÃO DE FATORES PRIMOS ACIMA DO FATOR PRIMO MÁXIMO NÃO SÃO EXCLUÍDOS
DA LISTA. AINDA SIM A LISTA FUNCIONA COMO UM FILTRO PARA DESCATAR NÚMEROS NÃO
PRIMOS MULTIPLOS DE PRIMOS MENORES.
*/

// CABEÇALHO
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// FUNÇÕES
// Algoritmo da roda para n=6
void
six_wheel_algorithm (uint64_t number)
{
  // Variáveis locais
  uint64_t turns, i; // Variáveis de iteração
  uint64_t tester1 = 1;
  uint64_t tester2 = 2;
  uint64_t tester3 = 3;
  uint64_t tester5 = 5;

  // Procedimentos
  // Calculando o número de voltas a ser dados
  turns = floor (number / 6);

  // Iniciando a lista de números primos até um dado valor
  printf ("Eis a sua lista de possíveis números primos até %li:\n", number);
  printf ("2, 3, 5, ");

  // Calculando outros termos da lista
  while (i < turns)
    {
      ++i;
      tester1 += 6;
      if (tester1 > number)
        break;
      if (tester1 % 2 != 0 && tester1 % 3 != 0 && tester1 % 5 != 0)
        printf ("%li, ", tester1);

      tester2 += 6;
      if (tester2 > number)
        break;
      if (tester2 % 2 != 0 && tester2 % 3 != 0 && tester2 % 5 != 0)
        printf ("%li, ", tester2);

      tester3 += 6;
      if (tester3 > number)
        break;
      if (tester3 % 2 != 0 && tester3 % 3 != 0 && tester3 % 5 != 0)
        printf ("%li, ", tester3);

      tester5 += 6;
      if (tester5 > number)
        break;
      if (tester5 % 2 != 0 && tester5 % 3 != 0 && tester5 % 5 != 0)
        printf ("%li, ", tester5);
    };

  // Finalizando a lista de números primos
  printf ("...\n");
};

// FUNÇÃO PRINCIPAL
int
main ()
{
  // Variáveis locais
  uint64_t number;

  // Procedimento
  // Recebendo input do usuário
  printf ("Digite um número inteiro:");
  scanf ("%li", &number);

  // Aplicando o algoritmo de roda para n=6
  six_wheel_algorithm (number);

  // Encerrando a aplicação
  return 0;
}
