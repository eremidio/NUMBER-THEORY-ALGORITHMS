// VAMOS CRIAR UM ARQUIVO PARA CALCULAR PARTIÇÕES DE UM NÚMERO INTEIRO

/*

UMA PARTIÇÃO DE UM NÚMERO INTEIRO NÃO NEGATIVO É UMA DECOMPOSIÇÃO DESTE NÚMERO
COMO UMA SOMA DE NÚMEROS INTEIROS NÃO NEGATIVOS. POR EXEMPLO AS PARTIÇÕES DE n=4
SÃO: 1+1+1+1, 2+2, 2+1+1, 3+1, 4.

PARTIÇÕES PODEM SER REPRESENTATADAS DIAGRAMATICAMENTE USANDO CHAMADOS  DIAGRAMAS
DE YOUNG (DIAGRAMAS DE FERRER). PARA n=4 TEMOS OS SEGUINTES DIAGRAMAS DE YOUNG:

+---+  +---+---+  +---+---+  +---+---+---+   +---+---+---+---+
|   |  |   |   |  |   |   |  |   |   |   |   |   |   |   |   |
+---+  +---+---+  +---+---+  +---+---+---+   +---+---+---+---+
|   |  |   |   |  |   |      |   |           4
+---+  +---+---+  +---+      +---+
|   |  2+2        |   |      3+1
+---+             +---+
|   |             2+1+1
+---+
1+1+1+1

DIAGRAMAS DE YOUNG SÃO PARTICULARMENTE ÚTEIS PARA REPRESENTAR FUNÇÕES SIMÉTRICAS
E SÃO MUITO IMPORTANTES EM TEORIA DE REPRESENTAÇÃO DE CONJUNTOS, TENDO
APLICAÇÕES IMPORTANTES EM FÍSICA TEÓRICA (MECÂNICA QUÂNTICA E TEORIA QUÂNTICA DE
CAMPOS).

A CHAMADA FUNÇÃO PARTIÇÃO p(n) CONTABILIZA O NÚMERO DE PARTIÇÕES DE UM NÚMERO
INTEIRO n. NÃO EXISTE UMA FÓRMULA EXPLÍCITA PARA O CÁLCULO DE p(n), PORÉM SEU
VALOR PODE SER EXPLICITAMENTE CALCULADO USANDO RELAÇÕES RECURSIVAS OU APROXIMADO
PARA GRANDES VALORES USANDO EXPRESSÕES QUE CONVERGEM PARA O VALOR CORRETO COM
GRANDE PRECISÃO. UMA FUNÇÃO GERADORA USANDO SÉRIES GEOMÉTRICAS PODE SER USADA
PARA CALCULAR OS VALORES DE p(n) PARA UMA DADO VALOR DE n.


PARA MAIORES INFORMAÇÕES:
https://en.wikipedia.org/wiki/Partition_(number_theory)
                          https://en.wikipedia.org/wiki/Partition_function_(number_theory)
                          https://en.wikipedia.org/wiki/Young_tableau#Diagrams

*/

//****************************************************************************************************************************
// CABEÇALHO
#ifndef INTEGER_PARTITON_H
#define INTEGER_PARTITON_H
#include"int128.h"
#include <math.h>
#include <stdint.h>


//CONSTANTES GLOBAIS
__int128_t partition_array[2000];
int summation_array[2000];


//****************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int sum_of_divisors(int); 
__int128_t partition_function(int);

//****************************************************************************************************************************
// FUNÇÕES
// Função que calcula a soma dos divisores de uma dado número
 int sum_of_divisors( int n) {

  // Casos triviais
  if (n == 0) return 0;
  if (n == 1) return 1;

  // Variáveis locais
  int sum = 0;
  int i;  // Variável de iteração
  int limit = sqrt(n);

  // Procedimento: loop principal
  for (i = 1; i <= limit; ++i) {
  
    // Caso particular de quadrados perfeitos
    if ((i * i) == n) {
      sum += i;
      continue;
    };

    if ((n % i) == 0) sum += (i + (n / i));

  };

  //Resultado
  return sum;

};

// Função que calcula o número de partições para um dado número inteiro
__int128_t partition_function(int n) {

  // Casos triviais
  if (n == 0 || n == 1) return 1;

  // Caso geral:
  // Variáveis
  __int128_t sum = 0, s0;
  int s1;


  //Procedimentos
  //Definindo a função recursivamente
  for (int i = 0; i < n; ++i){
    s1=summation_array[n-i];
    s0=partition_array[i];
  
    if(s0>0 && s1>0){
      sum += s0*s1;
    }
    else if(s0>0){
      int temp=sum_of_divisors(n - i);
      sum += s0*temp;
      summation_array[n-i]=temp;
    }
    else if(s1>0){
      __int128_t temp=partition_function(i);
      sum += s1* temp;
      partition_array[i]=temp;
    }
    else{
      int temp0=sum_of_divisors(n - i);
      __int128_t temp1=partition_function(i);

      sum += temp0 * temp1;
      partition_array[i]=temp1;
      summation_array[n-i]=temp0;
    }
  }

  // Resultado
  return sum / n;

};

//****************************************************************************************************************************
// FIM DO HEADER
#endif
