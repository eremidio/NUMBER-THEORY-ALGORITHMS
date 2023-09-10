// VAMOS ESCREVER UM PROGRAMA EM C++ QUE CALCULA A EXPANSÃO P-ÁDICA DE NÚMEROS
// INTEIROS E RACIONAIS
/*
PARA MAIORES INFORMAÇÕES SOBRE NÚMEROS P-ÁDICOS:
https://en.wikipedia.org/wiki/P-adic_number
*/
// COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o p_adic p_adic.cpp

//***************************************************************************************************************************
/*CABEÇALHO*/
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

//***************************************************************************************************************************
// FUNÇÃO QUE CALCULA A EXPANSÃO P-ÁDICA DE UM INTEIRO POSITIVO
void
p_adic_positive_integer (long long int number, long long int prime)
{
  // VÁRIÁVEIS LOCAIS
  string result = "";
  long long int power_prime, value, digit;
  int i; // VARIÁVEL DE ITERAÇÃO
  // PROCEDIMENTOS
  // CASOS BASE
  if (number == prime)
    {
      cout << "Coeficientes da expansão p-ádica de " << number << " na base "
           << prime << ": 1, 0, \n";
      return;
    };

  if (number < prime)
    {
      cout << "Coeficientes da expansão p-ádica de " << number << " na base "
           << prime << ": " << number << ", \n";
      return;
    };

  // CALCULANDO A MAIOR POTÊNCIA DO NÚMERO PRIMO MENOR QUE O VALOR QUE SERÁ
  // EXPRESSO NESSA BASE
  value = number;  // AJUSTE VARIÁVEIS
  power_prime = 1; // AJUSTE VARIÁVEIS
  i = 0;           // AJUSTE DE VARIÁVEIS

  while (power_prime < value)
    {
      power_prime *= prime;
      ++i;
    };

  power_prime /= prime; // AJUSTANDO A POTÊNCIA DO NÚMERO PRIMO.
  // CALCULANDO O RESULTADO
  do
    {
      digit = value / power_prime;
      result += to_string (digit); // ADICIONANDO UM DIGITO AO RESULTADO
      result += ", ";
      // REDEFININDO OS VALORES
      value = value % power_prime;
      power_prime = power_prime / prime;

      if (value < prime)
        {
          result
              += to_string (value); // ADICIONANDO O ÚLTIMO DIGITO AO RESULTADO
          result += ", ";
        };
    }
  while (power_prime != 1);
  result += " ";

  cout << "Coeficientes da expansão p-ádica de " << number << " na base "
       << prime << ": " << result << "\n";
};
//***************************************************************************************************************************
// FUNÇÃO QUE CALCULA A EXPANSÃO P-ÁDICA DE UM INTEIRO NEGATIVO
void
p_adic_negative_integer (long long int number, long long int prime)
{
  // VARIÁVEIS LOCAIS
  long long int *positive_digits_array = NULL;
  long long int *negative_digits_array = NULL;
  int digits_array_size;
  int i; // VARIÁVEL DE ITERAÇÃO
  long long int power_prime, value;
  string result = "..., ";
  result += to_string (prime - 1);
  result += ", ";

  // CÁLCULO DOS DIGITOS DA EXPANSÃO P-ÁDICA DO MÓDULO DE UM NÚMERO NEGATIVO
  value = number * (-1); // AJUSTE DE VARIÁVEL

  // CASO BASE
  if (value == prime)
    {
      digits_array_size = 2;
      positive_digits_array = (long long int *)realloc (
          positive_digits_array, 2 * sizeof (long long int));
      positive_digits_array[0] = 1;
      positive_digits_array[1] = 0;
      goto negative_step;
    };

  if (value < prime)
    {
      digits_array_size = 1;
      positive_digits_array = (long long int *)realloc (
          positive_digits_array, sizeof (long long int));
      positive_digits_array[0] = value;
      goto negative_step;
    };
  // CASO GERAL
  if (value > prime)
    {
      power_prime = 1;       // AJUSTE VARIÁVEIS
      digits_array_size = 0; // AJUSTE DE VARIÁVEIS

      // CALCULANDO A MAIOR POTÊNCIA DO NÚMERO PRIMO MENOR QUE O VALOR QUE SERÁ
      // EXPRESSO NESSA BASE
      while (power_prime < value)
        {
          power_prime *= prime;
        };
      power_prime /= prime; // AJUSTANDO A POTÊNCIA DO NÚMERO PRIMO.

      // CALCULANDO OS DÍGITOS DA EXPANSÃO P-ÁDICA DO MÓDULO DE UM NÚMERO
      // NEGATIVO
      do
        {
          digits_array_size++;
          positive_digits_array = (long long int *)realloc (
              positive_digits_array,
              digits_array_size * sizeof (long long int));
          positive_digits_array[digits_array_size - 1] = value / power_prime;

          /*TESTE 1.1, USE UM // APÓS OS TESTES*/
          // cout<<"Digito positivo:
          // "<<positive_digits_array[digits_array_size-1]<<"\n";

          // REDEFININDO OS VALORES
          value = value % power_prime;
          power_prime = power_prime / prime;

          if (value < prime)
            {
              digits_array_size++;
              positive_digits_array = (long long int *)realloc (
                  positive_digits_array,
                  digits_array_size * sizeof (long long int));
              positive_digits_array[digits_array_size - 1] = value;
              /*TESTE 1.2, USE UM // APÓS OS TESTES*/
              // cout<<"Digito positivo:
              // "<<positive_digits_array[digits_array_size-1]<<"\n";
              break;
            };
        }
      while (power_prime != 1);
    };

// CÁLCULO DOS DIGITOS DA EXPANSÃO P-ÁDICA DE UM NÚMERO NEGATIVO
negative_step:
  // AJUSTANDO O ARRAY DE INDEXES
  negative_digits_array = (long long int *)realloc (
      negative_digits_array, digits_array_size * sizeof (long long int));
  // CALCULANDO OS ELEMENTOS DESTE ARRAY
  for (i = 0; i < digits_array_size; ++i)
    {
      if (i != digits_array_size - 1)
        {
          negative_digits_array[i] = prime - positive_digits_array[i] - 1;
          /*TESTE 2.1, USE UM //APÓS OS TESTES*/
          // cout<<"Digito negativo: "<<negative_digits_array[i]<<"\n";

          result += to_string (negative_digits_array[i]);
          result += ", ";
        };

      if (i == digits_array_size - 1)
        {
          negative_digits_array[i] = prime - positive_digits_array[i];
          /*TESTE 2.2, USE UM //APÓS OS TESTES*/
          // cout<<"Digito negativo: "<<negative_digits_array[i]<<"\n";

          result += to_string (negative_digits_array[i]);
          result += ", ";
        };
    };

  // EXPRESSANDO O RESULTADO FINAL
  cout << "Coeficientes da expansão p-ádica de " << number << " na base "
       << prime << ": " << result << "\n";

  // LIMPANDO O CACHÊ DE MEMÓRIA
  free (negative_digits_array);
  free (positive_digits_array);
};

//***************************************************************************************************************************
// FUNÇÃO QUE CALCULA A EXPANSÃO P-ÁDICA DE UM NÚMERO RACIONAL COM AS SEGUINTES
// CONDIÇÕES:
// 1. NUMERADOR<DENOMINADOR
// 2. BASE/DENOMINADOR RELATIVAMENTE PRIMOS
void
p_adic_rational (long long int numerator, long long int denominator,
                 long long int prime)
{
  // VARIÁVEIS LOCAIS
  long long int periodic_length;
  long long int constant1, constant2;
  long long int power_prime, value, residue1;
  long long int *digits_array = NULL;
  long long int header_integer = 1;
  int i; // VARIÁVEIS PARA ITERAÇÃO EM LOOPS
  string result = "..., ";

  // PROCEDIMENTOS
  // CALCULANDO A EXTENSÃO PARTE PERIÓDICA DA EXPANSÃO
  power_prime = prime;
  periodic_length = 1;

  do
    {
      periodic_length++;
      residue1 = power_prime % denominator;
      // CONDIÇÃO PARA ENCERRAR O LOOP
      if (residue1 == 1)
        break;
      // BUSCANDO AS PRÓXIMAS POTÊNCIAS DA BASE
      power_prime = power_prime * prime;
    }
  while (true);

  // CALCULANDO O FATOR MULTIPLICATIVO DA FRAÇÃO 1/(1-prime^periodic_length)
  constant1 = denominator - numerator;
  /*TESTE USE UM // APÓS O TESTE*/
  // cout<<"Constant1: "<<constant1 <<"\n";
  constant2 = constant1 * (power_prime - 1);
  constant2 = constant2 / denominator;
  /*TESTE USE UM // APÓS O TESTE*/
  // cout<<"Constant2: "<<constant2 <<"\n";
  /*TESTE USE UM // APÓS O TESTE*/
  // cout<<"power_prime: "<<power_prime <<"\n";

  // CALCULANDO OS DIGITOS DA EXPANSÃO P-ÁDICA
  digits_array = (long long int *)realloc (
      digits_array, periodic_length * sizeof (long long int));
  power_prime = power_prime / prime;
  value = constant2;
  /*TESTE USE UM // APÓS O TESTE*/
  // cout<<"value: "<<value <<"\n";
  // cout<<"power_prime: "<<power_prime <<"\n";

  for (i = 0; i < periodic_length; ++i)
    {
      digits_array[i] = static_cast<long long int> (value / power_prime);
      /*TESTE USE UM // APÓS O TESTE*/
      // cout<<"digit: "<<digits_array[i] <<"\n";
      // REAJUSTANDO VARIÁVEIS
      value = value % power_prime;
      power_prime = power_prime / prime;
      if (power_prime == 0)
        break;
      /*TESTE USE UM // APÓS O TESTE*/
      // cout<<"value: "<<value <<"\n";
      // cout<<"power_prime: "<<power_prime <<"\n";
    };

  // EXIBINDO O RESULTADO
  for (i = 0; i < periodic_length - 1; ++i)
    {
      result += to_string (digits_array[i]);
      result += ", ";
    };

  for (i = 0; i < periodic_length - 1; ++i)
    {
      result += to_string (digits_array[i]);
      result += ", ";
    };

  // AJUSTANDO O ÚLTIMO DÍGITO
  for (i = 0; i < periodic_length - 1; ++i)
    {
      if (i == (periodic_length - 2))
        digits_array[i] = (digits_array[i] + header_integer) % prime;
      result += to_string (digits_array[i]);
      result += ", ";
    };

  cout << "Coeficientes da expansão p-ádica de " << numerator << "/"
       << denominator << " na base " << prime << ": " << result << "\n";
  // LIBERANDO O CACHÊ DE MEMÓRIA
  free (digits_array);
};

//***************************************************************************************************************************
// FUNÇÃO PRINCIPAL
int
main ()
{
  // VARIÁVEIS
  long long int number1, number2, denominator, numerator, prime;

  number1 = 233;
  number2 = -9;
  numerator = 1;
  denominator = 3;
  prime = 5;

  // TESTE 1: CALCULANDO A EXPANSÃO P-ÁDICA PARA UM NÚMERO INTEIRO POSITIVO
  p_adic_positive_integer (number1, prime);

  // TESTE 2: CALCULANDO A EXPANSÃO P-ÁDICA PARA UM NÚMERO INTEIRO POSITIVO
  p_adic_negative_integer (number2, prime);

  // TESTE 3: CALCULANDO A EXPANSÃO P-ÁDICA PARA UM NÚMERO RACIONAL
  // CASO1: NUMERADOR<DENOMINADOR
  p_adic_rational (numerator, denominator, prime);
  p_adic_rational (1, 5, 3);
  p_adic_rational (1, 8, 7);
  p_adic_rational (3, 8, 5);
  p_adic_rational (2, 9, 7);

  // FINALIZANDO O PROGRAMA
  return 0;
};
