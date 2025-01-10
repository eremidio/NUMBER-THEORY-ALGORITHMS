// VAMOS CRIAR UM PROGRAMA QUE IMPLEMNTA O CÁLCULO DE RAÍZES QUADRADAS PARA
// INTEIROS DE 128 BITS

//***********************************************************************************************************************************************************
// CABEÇALHO
#ifndef SQRT128_H
#define SQRT128_H
#include "int128.h"

//***********************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
__int128_t sqrt128(__int128_t);

//***********************************************************************************************************************************************************
// FUNÇÕES
// Função que calcula raízxes quadradas ou um limitante inferior do valor exato
// para inteiros de 128bits
__int128_t sqrt128(__int128_t number) {
  // Variáveis locais
  __int128_t sqrt_n = 1;
  __int128_t helper;

  // Procedimentos
  // Estimando a ordem de grandezada raíz quadrada
  while ((sqrt_n * sqrt_n) < number) sqrt_n *= 10;

  while ((sqrt_n * sqrt_n) > number) sqrt_n /= 10;

  helper = sqrt_n;

  // Ajuste fino  do resultado
  while (helper > 0) {
    while ((sqrt_n * sqrt_n) < number) sqrt_n += helper;

    if ((sqrt_n * sqrt_n) == number) break;

    if ((sqrt_n * sqrt_n) > number) {
      sqrt_n -= helper;
      helper /= 10;
    };
  };

  while (sqrt_n * sqrt_n < number) sqrt_n++;

  // Resultado
  return sqrt_n;
};

//***********************************************************************************************************************************************************
// FIM DO HEADER
#endif
