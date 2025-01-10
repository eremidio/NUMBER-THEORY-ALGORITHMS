// VAMOS CRIAR UM ARQUIVO PARA OPERAÇÕES BÁSICAS DE INPUT E OUTPUT DE FUNÇÕES
// ENVOLVENDO INTEIROS DE 128 BITS EM C/C++

//*******************************************************************************************************************************
// CABEÇALHO
#ifndef INT128_INPUT_OUTPUT_H
#define INT128_INPUT_OUTPUT_H
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//*******************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
int char_to_int(char);
char int_to_char(int);

__int128_t scanf128(char[]);
void printf128(__int128_t);

//*******************************************************************************************************************************
// FUNÇÕES
// Função que converte um caractére em um inteiro
int char_to_int(char c) {
  if (c >= '0' && c <= '9')
    return c - '0';
  else
    return (-1);
};

// Função que converte um inteiro de 0 a 9 em um caractére
char int_to_char(int d) {
  if (d >= 0 && d <= 9)
    return d + '0';
  else
    return '\0';
};

// Função que recebe um inteiro de 128bits em uma c-string (array de caractéres)
__int128_t scanf128(char number_string[]) {

    // Variáveis
    __int128_t power10 = 1, result = 0;
    size_t digit_number = strlen(number_string);

    // Procedimentos
    // Calculando o resultado final
    for (int i = (digit_number - 1); i >= 0; --i) {
      result += (power10 * char_to_int(number_string[i]));

      // Ajuste de variáveis
      power10 *= 10;
    };

  // Resultado
  return result;
};

// Função que escreve um inteiro como uma string
void printf128(__int128_t number) {

  // Variáveis locais
  int number_digits = 0;
  __int128_t power10 = 1;
  char number_string[100];
  int i;

  // Procedimentos
    // Calculando o número de dígitos
    while (power10 <= number) {
      power10 *= 10;
      number_digits++;
    };

    // Certifique-se de que number_digits não seja maior que o tamanho do buffer
    if (number_digits > 99) {
      printf("Número muito grande para ser impresso.\n");
      return;
    };

    // Escrevendo a string numérica
    for (i = 0; i < number_digits; ++i) {
      number_string[i] = int_to_char(number % 10);
      number /= 10;
    };

    number_string[i] = '\0';

    // Invertendo a string antes de imprimir
    for (int start = 0, end = (i - 1); start < end; ++start, --end) {
      char temp = number_string[start];
      number_string[start] = number_string[end];
      number_string[end] = temp;
    };

    // Printando a string
    printf("%s\n", number_string);
};

//*******************************************************************************************************************************
// FIM DO HEADER
#endif
