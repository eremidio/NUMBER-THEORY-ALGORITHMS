// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE CÁLCULO DE DIVISORES DE UM INTEIRO A MENOS DE UMA CONGRUÊNCIA

/*

SEJAM r, s, n INTEIROS TAIS QUE r<s<n, O ALGORITMO DE LENSTRA PARA DIVISORES EM CLASSES RESIDUAIS RETORNA OS DIVISORES d QUE SATISFAZEM A
RELAÇÃO DE CONGRUÊNCIA d= r (mod s). ESTE ALGORITMO É PARTICULARMENTE ÚTIL COMO SUBROTINA EM OUTROS ALGORITMOS MAIS SOFISTICADOS COMO O
TESTE DE PRIMALIDADE APR-CL E O TESTE DE PRIMALIDADES (n+1) E (n²-1) GENERALIZADO. EMBORA POSSA SER EMPREGADO PARA FATORAR DIRETAMENTE 
UM INTEIRO n QUE NÃO POSSUA FATORES PRIMOS INFERIORES A n^(1/3) EM O(n^(1/3)log²(n)). 


O ALGORITMO FUNDAMENTA-SE NO ALGORITMO DE EUCLIDES EXTENDIDO. CADEIAS EUCLIDIANAS a(i), b(i), c(i) COM CONDIÇÕES INICIAIS DETERMINADAS A
MENOS DE ALGUMAS RELAÇÕES DE CONGRUÊNCIA SÃO CÁLCULADAS E OS POSSÍVEIS VALORES DESTA SEQUÊNCIA DEVEM SATISFAZER UM SISTEMA DE EQUAÇÕES
LINEARES ENVOLVENDO OS VALORES DE r, s, n, a(i), b(i), c(i). OS VALORES DE x, y INTEIROS POSITIVOS OBTIDOS NA SOLUÇÃO DESTE SISTEMA SÃO
DIVISORES DE n SATISFAZENDO A RELAÇÃO d = r (mod s).


PARA MAIORES REFERÊNCIAS: Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance
                          A Course In Computational Algebraic Number Theory by Henri Cohen
                          Number Theoretical Algorithms in Criptography by O. N. Vasilenko


*/

//***************************************************************************************************************************************
// CABEÇALHO
#ifndef DIVISOR_RESIDUE_CLASS_ALGORITHM_H
#define DIVISOR_RESIDUE_CLASS_ALGORITHM_H
#include"miller_rabin_128bits.h"
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


//***************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
int64_t gcd_s64(int64_t, int64_t);
int64_t modular_inverse(int64_t, int64_t);
uint64_t integer_sqrt_u128(__uint128_t);
int64_t centered_mod_s64(int64_t, int64_t);

void quadratic_system_equation_solver(int64_t, int64_t, int64_t, int64_t, int64_t, int64_t, int64_t);
void lenstra_divisors_residue_class_algorithm(int64_t, int);


//***************************************************************************************************************************************
// FUNÇÕES
// Função que implementa o algoritmo de Euclides para o cálculo do mdc de dois inteiros de 64 bits
int64_t gcd_s64(int64_t a, int64_t b) {

  if (b == 0) return a;
  else return gcd_s64(b, (a % b));

};


// Função que calcula o inverso modular de um número inteiro a (mod n) usando o algoritmo extendido de Euclides
int64_t modular_inverse(int64_t a, int64_t n) {

  //Restrição: a, n devem ser coprimos    
    if (a == 0 || gcd_s64(a, n) != 1)
      return 0;


  // Variáveis locais
  __int128_t r0, r1, t0, t1, r2, t2;

  // Procedimentos
    // Ajuste de variáveis
    a %= n;
    if (a < 0)  a += n;
    r0 = a;
    r1 = n;
    t0 = 1;
    t1 = 0;

    // Calculando os valores finais dos coeficientes recursivamente
    while (r1 != 0) {

      __int128_t quotient = r0 / r1;

      r2 = r0 - quotient * r1;
      t2 = t0 - quotient * t1;

      // Atualizando variáveis para a próxima iteração
      r0 = r1;
      r1 = r2;

      t0 = t1;
      t1 = t2;

    };


    //Cálculo do resultado
    t0 %= n;
    if (t0 < 0)
      t0 += n;

  return (int64_t)t0;

};


// Função que calcula a raiz quadrada inteira de um inteiro de 128 bits
uint64_t integer_sqrt_u128(__uint128_t n) {

  // Variáveis locais
  __uint128_t low = 0;
  __uint128_t high = ((__uint128_t)1 << 64);

  // Procedimentos: loop principal
  while (low < high) {

    __uint128_t mid = (low + high + 1) / 2;
    if (mid <= n / mid)
      low = mid;
    else
      high = mid - 1;

  };


  //Resultado
  return (uint64_t)low;

};


// Função que calcula o representante de c módulo s pertencente ao intervalo simétrico |c| < s
int64_t centered_mod_s64(int64_t c, int64_t s) {

  // Procedimentos: loop principal
  c %= s;
  if (c >= s / 2)
    c -= s;
  if (c < -(s / 2))
    c += s;

  //Resultado
  return c;

};


// Função que resolve um sistema de equações do primeiro grau ax+by=c, (xs+r)(ys+r')=n usando uma equação do 2º grau
   //  T² -(c.s+ai.r+bi.r')T+ai.bi.n=0
void quadratic_system_equation_solver(int64_t ai, int64_t bi, int64_t c, int64_t s, int64_t r, int64_t r_prime, int64_t n) {

  //Variáveis da equação do 2º grau
  __int128_t B;
  __int128_t C;
  __int128_t delta;
  __int128_t P;

  uint64_t sqrt_delta;

  __int128_t root1;
  __int128_t root2;

  int64_t divisor1;
  int64_t divisor2;


  // Procedimentos
    //Restrição
    if (ai == 0 || bi == 0) return;

    // O polinômio é T² - (c.s + ai.r + bi.r')T + ai.bi.n = 0
    P = (__int128_t)c * s + (__int128_t)ai * r  + (__int128_t)bi * r_prime;
    B = -P;
    C = (__int128_t)ai * bi * n;

    // Calculando o discriminante da equação
    delta = B * B - 4 * C;
    if (delta < 0) return; //Não há raízes reais

    // Calculando a raiz quadrada inteira do discriminante
    sqrt_delta = integer_sqrt_u128((__uint128_t)delta);

    // O discriminante precisa ser um quadrado perfeito
    if ((__uint128_t)sqrt_delta * sqrt_delta != (__uint128_t)delta)
      return;

    // As raízes são: T = (P + sqrt(delta))/2 e T = (P - sqrt(delta))/2
    if (((P + sqrt_delta) & 1) != 0) return;
    if (((P - sqrt_delta) & 1) != 0) return;

    root1 = (P + sqrt_delta) / 2;
    root2 = (P - sqrt_delta) / 2;

    // Checando se as raízes são positivas
    if (root1 <= 0 && root2 <= 0) return;

    // A primeira raiz corresponde a: u = ai(xs+r), portanto, u deve ser divisível por ai.
    if (root1 > 0 && root1 % ai == 0) {
      __int128_t divisor128 = root1 / ai;

      if (divisor128 > 0 && divisor128 <= INT64_MAX) {

        divisor1 = (int64_t)divisor128;

        // Verificando a relação de congruência
        if (divisor1 % s == r && n % divisor1 == 0) {
          printf("Divisor de %li congruente à %li módulo %li encontrado: %li\n",  n, r, s, divisor1);
        };

      };

    };


    // A segunda raiz corresponde a:v = bi(ys+r'), portanto, v deve ser divisível por bi.

    if (root2 > 0 && root2 % bi == 0) {
      __int128_t divisor128 = root2 / bi;
      if (divisor128 > 0 && divisor128 <= INT64_MAX) {

        divisor2 = (int64_t)divisor128;

        // A segunda raiz corresponde a um divisor da classe r' módulo s.
        if (divisor2 % s == r_prime && n % divisor2 == 0) {
          if (divisor2 % s == r) {

            printf("Divisor de %li congruente à %li módulo %li encontrado: %li\n", n, r, s, divisor2);

          };

        };

      };


    };

};


//Algoritmo que calcula divisores d de um inteiro n satisfazendo a relação de congruência d = r (mod s), com r<s<n
void lenstra_divisors_residue_class_algorithm(int64_t n, int counter){

  //Restrição
  if(miller_rabin128(n)){
    printf("%li é primo!\n", n);
    return;
  }

  //Variáveis locais
  __int128_t t0, t1, t2;
  int64_t s=cbrt((double)n)+1, r=1;
  int64_t r_inv=0, r_prime=0;
  int64_t a0, a1, a2, b0, b1, b2, c0, c1, c2, c, qi;


  //Procedimentos
    //Ajuste de variáveis
    rerun:

    //Loop principal: sobre valores de r coprimos com s
    for(r=1; r<s; ++r){

      //Restrição
      if(gcd_s64(r, s)>1) continue;

      //Ajuste de variáveis usadas no cálculo
      r_inv=modular_inverse(r, s);

      if(r_inv == 0)
        continue;

      r_prime=(int64_t)(((__int128_t)r_inv*n)%s);
      if(r_prime == 0) continue;

      a0=s;
      b0=0;
      c0=0;

      //AJuste de variáveis
      a1=(int64_t)(((__int128_t)r_prime*r_inv)%s);
      b1=1;
      t0=(__int128_t)n*r_inv-(__int128_t)r*a1;
      c1=(int64_t)((t0/s)%s);
      if(c1 < 0) c1 += s;


      //Caso base: 1ªiteração no loop euclidiano
      c=c1; {
        __int128_t min = (__int128_t)2*a1*b1;
        __int128_t max = (__int128_t)a1*b1 + (__int128_t)n/((__int128_t)s*s);

        //Encontrando os representantes de c1 módulo s no intervalo  2.a1.b1 < c < a1*b1 + n/s²
        while ((__int128_t)c <= min) c += s;
        while ((__int128_t)c >= max) c -= s;

        if ((__int128_t)c > min && (__int128_t)c < max) {
          quadratic_system_equation_solver( a1, b1, c, s, r, r_prime, n);

        };

      };


      //Loop euclidiano:
      for(uint64_t i=2; ; ++i){

        //Cálculo de parâmetros usados no cálculo
        if((i&1) && (a0%a1)==0)  qi=(a0/a1)-1;
        else qi=a0/a1;

        a2=a0-qi*a1;
        b2=b0-qi*b1;
        c2=c0-qi*c1;

        //Condição que determina o fim do loop
        if(!(i&1) && a2==0)
          break;


        c=c2;

        //Caso 1: i é par --> |c| < s
        if(!(i&1)){
          c=centered_mod_s64(c, s);
          quadratic_system_equation_solver(a2, b2, c, s, r, r_prime, n);

        };

        //Caso 2: i é ímpar --> 2.a_i.b_i < c < a_i.b_i + n/s²
        if((i&1)){
          __int128_t min = (__int128_t)2*a2*b2;
          __int128_t max = (__int128_t)a2*b2 + (__int128_t)n/((__int128_t)s*s);


          while ((__int128_t)c <= min) c += s;
          while ((__int128_t)c >= max) c -= s;


          if ((__int128_t)c > min && (__int128_t)c < max) {
            quadratic_system_equation_solver(a2, b2, c, s, r, r_prime, n);
          };

        }


        //Ajuste de variaveis
        t1=a2;
        t0=a1;
        a0=t0;
        a1=t1;

        t1=b2;
        t0=b1;
        b0=t0;
        b1=t1;

        t1=c2;
        t0=c1;
        c0=t0;
        c1=t1;

      };//Fim do loop euclidiano


    }; //Fim do loop principal sobre os valores de r


    //Ajuste de variávels
    if(counter>0){
      s++; counter--;
      goto rerun;

    };


};


//***************************************************************************************************************************************
// FIM DO HEADER
#endif

