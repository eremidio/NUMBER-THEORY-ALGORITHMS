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


    for (int i = s - 2; i >= 0; --i) w[i] = (w[i] + w[i + s]) % n;

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

    //Ajuste dos coeficientes de polinômios
    y[0] = 1;
    z[0] = b;
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
      __int128_t* temp = poly_mul_aks(z, z, n, s);
      if(temp == NULL) {
        free(y);
        free(z);
        return NULL;
      }
     
      free(z);
      z = temp;
      e>>= 1;
    };

  //Limpando o cachê de memória e retornando o resultado
  free(z);
  return y;

};



// Função que testa a relação de congruência (x+b)^n = x^n+b (mod [x^s-1], n)
/*
  NOTA: Estritamente o algoritmo requer que sejam testados valores no intervalo 1≲ b ≲ (√φ(r))log₂(n).
  (φ é a função totiente de Euler). Porém,certas conjecturas ainda não comprovadas postulam que
  o teste com a=1 é suficiente para produzir resultados corretos. A função a seguir pode ser
  modificada de modo a testar os valores no intervalo 1≲ b ≲ (√r)log₂(n) por exemplo. 
*/

bool polinomial_test(uint64_t n, uint64_t s){

    // Variáveis locais
    __int128_t* polynomial_coefficients = NULL;
    size_t i;

    // Procedimentos
    // Calculando (x+b)^n = x^n+b (mod [x^s-1], n)
    polynomial_coefficients = poly_pow_aks(n, s, 1);
    if (polynomial_coefficients == NULL) {
        return false;
    }

    // Teste 1: Verificando os coeficientes
    if (polynomial_coefficients[0] != 1) return false;
    if (polynomial_coefficients[1] != 1) return false;

    // Teste 2: Checando se os outros coeficientes são nulos
    for (i = 2; i < s; ++i) {
        if (polynomial_coefficients[i] != 0) return false;
    }

    // Caso passe nos testes acima o número testado é primo
    free(polynomial_coefficients);
    return true;
}

//***********************************************************************************
//FIM DO HEADER
#endif

