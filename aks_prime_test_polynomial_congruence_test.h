//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE CONGRUÊNCIAS POLINOMIAIS DO TESTE DE PRIMALIDADE AKS (AGRAWAL-KAYENA-SAXENA)

/*

  AS PRESENTES ROTINAS CHECAM A CONGRUÊNCIA  (x+b)^n = x^n+b (mod [x^s-1], n)
  PARA MAIORES INFORMAÇÕES: The Joy Of Factoring by Samuel Wagstaff Jr

*/

//***********************************************************************************
//CABEÇALHO
#ifndef AKS_POLYNOMIAL_CONGRUENCE_TEST_H 
#define AKS_POLYNOMIAL_CONGRUENCE_TEST_H 
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


//***********************************************************************************
//DECLARAÇÃO DE FUNÇÕES
__int128_t* poly_mul_aks(__int128_t*, __int128_t*, int64_t, int64_t);
__int128_t* poly_pow_aks(uint64_t, uint64_t, uint64_t);
bool polinomial_test(uint64_t, uint64_t);


//***********************************************************************************
//FUNÇÕES
//Função que implementa a multiplicação de polinômios em Zn[x]/(x^s-1)
__int128_t* poly_mul_aks(__int128_t* y, __int128_t* z, int64_t n, int64_t s){

  //Variáveis locais
  __int128_t* w = (__int128_t*)calloc((2*s), sizeof(__int128_t));
  uint64_t i, j;


  //Procedimentos
    //Checando a alocação de memória 
    if (w == NULL) {
      fprintf(stderr, "Erro de alocação de memória\n");
      free(y);
      free(z);
      return NULL;
    }


    //Ajuste dos coeficientes do polinômio
    for(int i = 0; i < s; ++i) {
      for(int j = 0; j < s; ++j) {
        w[i + j] = (w[i + j] + (y[i] * z[j]) ) % n;
      }
    }


    //Reduzindo o polinômio módulo (x^s-1)
    //Como x^s = 1, temos x^(i+s) = x^i
    for (int i = s - 2; i >= 0; --i) {
      w[i] = (w[i] + w[i + s]) % n;
    }


  //Resultado
  return w;

};


// Função que implementa a exponenciação de polinômios em Zn[x]/(x^s-1)
__int128_t* poly_pow_aks(uint64_t n, uint64_t s, uint64_t b){

  //Variáveis locais
  __int128_t* y = (__int128_t*)calloc((2*s), sizeof(__int128_t));
  __int128_t* z = (__int128_t*)calloc((2*s), sizeof(__int128_t));
  uint64_t e=n;


  //Procedimentos
    //Checando a alocação de memória 
    if (y == NULL || z == NULL) {
      fprintf(stderr, "Erro de alocação de memória\n");
      free(y);
      free(z);
      return NULL;
    }

    //Checando se o grau do polinômio é válido
    if (s < 2) {
      fprintf(stderr, "Erro: o valor de s deve ser maior que 1\n");
      free(y);
      free(z);
      return NULL;
    }

    //Ajuste dos coeficientes de polinômios
    y[0] = 1;
    z[0] = b % n;
    z[1] = 1;

    //Loop principal
    while(e > 0) {

      if(e&1) {

        __int128_t* temp = poly_mul_aks(y, z, n, s);

        if(temp == NULL) {
          free(y);
          free(z);
          return NULL;
        }
        
        free(y);
        y = temp;
      }

      //Atualizando variáveis para a próxima iteração 
      e>>= 1;
      if(e == 0) {
        break;
      }

      __int128_t* temp = poly_mul_aks(z, z, n, s);

      if(temp == NULL) {
        free(y);
        free(z);
        return NULL;
      }
     
      free(z);
      z = temp;

    };

  //Limpando o cachê de memória e retornando o resultado
  free(z);
  return y;

};



// Função que testa a relação de congruência (x+b)^n = x^n+b (mod [x^s-1], n)
/*
  NOTA: Estritamente o algoritmo requer que sejam testados valores no intervalo 1 <= b <= (√φ(r))log₂(n) (φ(r) é a função totiente de Euler). Porém, certas
        conjecturas postulam que o teste com a=1 é suficiente para produzir resultados corretos. A função a seguir pode ser modificada de modo a testar os
        valores no intervalo 1 <= b <= (√φ(r))log₂(n), por exemplo, sendo assim condizente com a formulação original do algoritmo.
*/

bool polinomial_test(uint64_t n, uint64_t s){

    // Variáveis locais
    __int128_t* polynomial_coefficients = NULL;
    uint64_t grau_x_n;
    size_t i;

    // Checando parâmetros inválidos
    if (n < 2 || s < 2) {
        return false;
    }

    // Procedimentos
      // Calculando (x+b)^n = x^n+b (mod [x^s-1], n)
      polynomial_coefficients = poly_pow_aks(n, s, 1);
      if (polynomial_coefficients == NULL) {
        return false;
      }

    /*
      Como estamos trabalhando módulo (x^s-1), temos x^s = 1. Portanto: x^n = x^(n mod s).
      O polinômio esperado é x^(n mod s) + 1
    */
    grau_x_n = n % s;


    // Teste 1: Verificando o coeficiente constante
    if (polynomial_coefficients[0] != ((grau_x_n == 0) ? 2 : 1)) {
        free(polynomial_coefficients);
        return false;
    }


    // Teste 2: Verificando o coeficiente de x^(n mod s)
    if (grau_x_n != 0) {

        if (polynomial_coefficients[grau_x_n] != 1) {
            free(polynomial_coefficients);
            return false;
        }
    }


    // Teste 3: Checando se os outros coeficientes são nulos
    for (i = 1; i < s; ++i) {

        if (i == grau_x_n) {
            continue;
        }

        if (polynomial_coefficients[i] != 0) {
            free(polynomial_coefficients);
            return false;
        }
    }


  // Caso passe nos testes acima o número testado satisfaz
  free(polynomial_coefficients);
  return true;

};


//***********************************************************************************
//FIM DO HEADER
#endif
