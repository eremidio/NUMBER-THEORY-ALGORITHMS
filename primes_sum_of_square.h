// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UM ALGORITMO PARA EXPRESSAR NÚMEROS PRIMOS EM TERMOS DE FORMAS QUADRÁTICAS REDUZIDAS

/*
USANDO A TEORIA DAS FORMAS QUADRÁTICAS BINÁRIAS É POSSÍVEL DEMONSTRAR UMA SÉRIE
DE TEOREMAS QUE ESTABELECEM RELAÇÕES DE CONGRUÊNCIAS DO TIPO p= a (mod m), COM p
PRIMO E a, m INTEIROS E NÃO NECESSARIAMENTE PRIMOS QUE DEFINEM CONDIÇÕES PARA
QUE p SEJA EXPRESSO POR MEIO DE RELAÇÕES DO TIPO p=x²+ny², COM x, y, n INTEIROS
PARA VALORES FIXOS DE n. OS VALORES DE x, y PODEM SER OBTIDOS POR MEIO DO
ALGORITMO DE CORNARCHIA.

PARA MAIORES INFORMAÇÕES: Primes of the Form x² + ny² : Fermat, Class Field
Theory, and Complex Multiplication by D. A. Cox
                          http://math.uchicago.edu/~may/REU2014/REUPapers/Kaplan.pdf

*/

//************************************************************************************************************************************************************
// CABEÇALHO
#ifndef PRIME_SUM_OF_SQUARE_H
#define PRIME_SUM_OF_SQUARE_H
#include <stdio.h>
#include "cornarcchia_algorithm_composite_modulus.h"  //Dependências necessárias estão inclusas


//************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
bool fast_prime_checking(int64_t);
bool test1(int64_t);
bool test2(int64_t);
bool test3(int64_t);
bool test4(int64_t);
bool test5(int64_t);
bool test6(int64_t);
bool test7(int64_t);
bool test10(int64_t);
bool test13(int64_t);
bool test14(int64_t);
bool test15(int64_t);
bool test21(int64_t);
bool test22(int64_t);
bool test30(int64_t);
void prime_sum_of_square(int64_t);

//************************************************************************************************************************************************************
// FUNÇÕES
// Função que determina se um número é primo com otimização 30k+1
bool fast_prime_checking(int64_t n) {
  // Casos triviais primos menos que 30
  if (n < 2) return false;

  if (n == 2 || n == 3 || n == 5 || n == 7 || n == 11 || n == 13 || n == 17 ||
      n == 23 || n == 29)
    return true;

  // Variáveis locais
  int64_t i;
  int64_t limit = sqrt(n);
  int64_t divisors[8] = {
      1,  7,  11, 13,
      17, 19, 23, 29};  // Números coprimos com 30 no intervalo 1,...,30

  // Procedimentos
  // Teste de divisão por 2, 3, 5
  if ((n % 5) == 0 || (n % 3) == 0 || (n % 2) == 0) return false;

  // Loop principal
  // 1º iteração
  for (i = 1; i < 8; ++i) {
    if ((n % divisors[i]) == 0) return false;
  };

  // Demais interações
  while (divisors[7] < limit) {
    // Atualizando variáveis
    for (i = 0; i < 8; ++i) divisors[i] = divisors[i] + 30;

    // Testando possíveis divisores
    for (i = 0; i < 8; ++i) {
      if ((n % divisors[i]) == 0) return false;
    };
  };

  // Caso o número passe nos testes acima
  return true;
};

// Função que testa se um primo pode ser escrito na forma p=x²+y²
bool test1(int64_t p) {
  // Caso trivial
  if (p == 2) return true;

  // Resultado
  if ((p % 4) == 1)
    return true;
  else
    return false;
};

// Função que testa se um primo pode ser escrito na forma p=x²+2y²
bool test2(int64_t p) {
  // Caso trivial
  if (p == 2) return true;

  // Variáveis locais
  int64_t residue = (p % 8);

  // Resultado
  if (residue == 1 || residue == 3)
    return true;
  else
    return false;
};

// Função que testa se um primo pode ser escrito na forma p=x²+3y²
bool test3(int64_t p) {
  // Caso trivial
  if (p == 3) return true;

  // Variáveis locais
  int64_t residue = (p % 3);

  // Resultado
  if (residue == 1)
    return true;
  else
    return false;
};

// Função que testa se um primo pode ser escrito na forma p=x²+4y²
bool test4(int64_t p) {
  // Variáveis locais
  int64_t residue = (p % 4);

  // Resultado
  if (residue == 1)
    return true;
  else
    return false;
};

// Função que testa se um primo pode ser escrito na forma p=x²+5y²
bool test5(int64_t p) {
  // Caso trivial
  if (p == 5) return true;

  // Variáveis locais
  int64_t residue = (p % 20);

  // Resultado
  if (residue == 1 || residue == 9)
    return true;
  else
    return false;
};

// Função que testa se um primo pode ser escrito na forma p=x²+6y²
bool test6(int64_t p) {
  // Variáveis locais
  int64_t residue = (p % 24);

  // Resultado
  if (residue == 1 || residue == 7)
    return true;
  else
    return false;
};

// Função que testa se um primo pode ser escrito na forma p=x²+7y²
bool test7(int64_t p) {
  // Caso trivial
  if (p == 7) return true;

  // Variáveis locais
  int64_t residue = (p % 7);

  // Resultado
  if (residue == 1 || residue == 2 || residue == 4)
    return true;
  else
    return false;
};

// Função que testa se um primo pode ser escrito na forma p=x²+10y²
bool test10(int64_t p) {
  // Variáveis locais
  int64_t residue = (p % 40);

  // Resultado
  if (residue == 1 || residue == 9 || residue == 11 || residue == 19)
    return true;
  else
    return false;
};

// Função que testa se um primo pode ser escrito na forma p=x²+13y²
bool test13(int64_t p) {
  // Caso trivial
  if (p == 13) return true;

  // Variáveis locais
  int64_t residue = (p % 52);

  // Resultado
  if (residue == 1 || residue == 9 || residue == 17 || residue == 19 ||
      residue == 25 || residue == 29 || residue == 49)
    return true;
  else
    return false;
};

// Função que testa se um primo pode ser escrito na forma p=x²+14y² (ou
// 2p=x²+14y²)
bool test14(int64_t p) {
  // Variáveis locais
  int64_t residue = (p % 56);

  // Resultado
  if (residue == 1 || residue == 9 || residue == 15 || residue == 23 ||
      residue == 25 || residue == 39)
    return true;
  else
    return false;
};

// Função que testa se um primo pode ser escrito na forma p=x²+15y²
bool test15(int64_t p) {
  // Variáveis locais
  int64_t residue = (p % 60);

  // Resultado
  if (residue == 1 || residue == 9 || residue == 31 || residue == 49)
    return true;
  else
    return false;
};

// Função que testa se um primo pode ser escrito na forma p=x²+21y²
bool test21(int64_t p) {
  // Variáveis locais
  int64_t residue = (p % 84);

  // Resultado
  if (residue == 1 || residue == 25 || residue == 37)
    return true;
  else
    return false;
};

// Função que testa se um primo pode ser escrito na forma p=x²+22y²
bool test22(int64_t p) {
  // Variáveis locais
  int64_t residue = (p % 88);

  // Resultado
  if (residue == 1 || residue == 9 || residue == 15 || residue == 23 ||
      residue == 25 || residue == 31 || residue == 47 || residue == 49 ||
      residue == 71 || residue == 81)
    return true;
  else
    return false;
};

// Função que testa se um primo pode ser escrito na forma p=x²+30y²
bool test30(int64_t p) {
  // Variáveis locais
  int64_t residue = (p % 20);

  // Resultado
  if (residue == 1 || residue == 31 || residue == 49 || residue == 79)
    return true;
  else
    return false;
};

// Função que expressa números em termos de formas quadráticas reduzidas
void prime_sum_of_square(int64_t p) {

  // Restrição a números primos
  if (fast_prime_checking(p) == false) {
    printf("%li não é primo.\n", p);
    return;
  };

  // Variáveis locais procedimentos
  int64_t x, y;

  // Procedimentos
  // Teste se um primo pode ser escrito na forma p=x²+y²
  if (test1(p) == true) {
    cornarcchia_algorithm_composite_modulus(1, p, &x, &y);
    printf("Solução de %li=x²+y²\n x=%li, y=%li\n", p, x, y);
  };

  // Teste se um primo pode ser escrito na forma p=x²+2y²
  if (test2(p) == true) {
    cornarcchia_algorithm_composite_modulus(2, p, &x, &y);
    printf("Solução de %li=x²+2y²\n x=%li, y=%li\n", p, x, y);
  };

  // Teste se um primo pode ser escrito na forma p=x²+3y²
  if (test3(p) == true) {
    cornarcchia_algorithm_composite_modulus(3, p, &x, &y);
    printf("Solução de %li=x²+3y²\n x=%li, y=%li\n", p, x, y);
  };

  // Teste se um primo pode ser escrito na forma p=x²+4y²
  if (test4(p) == true) {
    cornarcchia_algorithm_composite_modulus(4, p, &x, &y);
    printf("Solução de %li=x²+4y²\n x=%li, y=%li\n", p, x, y);
  };

  // Teste se um primo pode ser escrito na forma p=x²+5y²
  if (test5(p) == true) {
    cornarcchia_algorithm_composite_modulus(5, p, &x, &y);
    printf("Solução de %li=x²+5y²\n x=%li, y=%li\n", p, x, y);
  };

  // Teste se um primo pode ser escrito na forma p=x²+6y²
  if (test6(p) == true) {
    cornarcchia_algorithm_composite_modulus(6, p, &x, &y);
    printf("Solução de %li=x²+6y²\n x=%li, y=%li\n", p, x, y);
  };

  // Teste se um primo pode ser escrito na forma p=x²+7y²
  if (test7(p) == true) {
    cornarcchia_algorithm_composite_modulus(7, p, &x, &y);
    printf("Solução de %li=x²+7y²\n x=%li, y=%li\n", p, x, y);
  };

  // Teste se um primo pode ser escrito na forma p=x²+10y²
  if (test10(p) == true) {
    cornarcchia_algorithm_composite_modulus(10, p, &x, &y);
    printf("Solução de %li=x²+10y²\n x=%li, y=%li\n", p, x, y);
  };

  // Teste se um primo pode ser escrito na forma p=x²+13y²
  if (test13(p) == true) {
    cornarcchia_algorithm_composite_modulus(13, p, &x, &y);
    printf("Solução de %li=x²+13y²\n x=%li, y=%li\n", p, x, y);
  };

  // Teste se um primo pode ser escrito na forma p=x²+14y²
  if (test14(p) == true) {
    cornarcchia_algorithm_composite_modulus(14, p, &x, &y);
    if (x > 0 || y > 0)
      printf("Solução de %li=x²+14y²\n x=%li, y=%li\n", p, x, y);
  };

  // Teste se um primo pode ser escrito na forma p=x²+15y²
  if (test15(p) == true) {
    cornarcchia_algorithm_composite_modulus(15, p, &x, &y);
    printf("Solução de %li=x²+15y²\n x=%li, y=%li\n", p, x, y);
  };

  // Teste se um primo pode ser escrito na forma p=x²+21y²
  if (test21(p) == true) {
    cornarcchia_algorithm_composite_modulus(21, p, &x, &y);
    printf("Solução de %li=x²+21y²\n x=%li, y=%li\n", p, x, y);
  };

  // Teste se um primo pode ser escrito na forma p=x²+22y²
  if (test22(p) == true) {
    cornarcchia_algorithm_composite_modulus(22, p, &x, &y);
    printf("Solução de %li=x²+22y²\n x=%li, y=%li\n", p, x, y);
  };

  // Teste se um primo pode ser escrito na forma p=x²+30y²
  if (test30(p) == true) {
    cornarcchia_algorithm_composite_modulus(30, p, &x, &y);
    printf("Solução de %li=x²+30y²\n x=%li, y=%li\n", p, x, y);
  };
};

//************************************************************************************************************************************************************
// FIM DO HEADER
#endif
