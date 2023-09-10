// ESTE ARQUIVO PROVÊ UMA CLASSE DE NÚMEROS COMPLEXOS EM C++

// Cabeçalho
#pragma once
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

// Classe dos números complexos

template <typename T> class complex
{
public:
  // Membros da classe
  T real;
  T imag;

  // Construtores e destruídores
  complex (T, T);
  complex (){};
  void set ();
  ~complex ();

  // Métodos da classe
  // Função que exepressa um número complexo em notação algébrica
  std::string algebraic ();
  // Operações aritmética básica de números complexos
  complex<T> operator+ (complex<T>);
  complex<T> operator- (complex<T>);
  complex<T> operator* (complex<T>);
  complex<T> operator/ (complex<T>);

  // Norma
  T norm ();
  T polar ();

  // Conjugação e cálculo do inverso múltiplicativo
  complex<T> conj ();
  complex<T> inv ();

  // Fórmula de Euler e potenciação com expoente real
  complex<T> exp ();
  complex<T> pow (double);
};

// Construtores e destruidores
template <typename T> complex<T>::complex (T a, T b)
{
  real = a;
  imag = b;
};

template <typename T> complex<T>::~complex (){};

// Função que inicializa um número complexo a partir de sua expressão algébrica
template <typename T>
void
complex<T>::set ()
{
  // Variáveis locais
  char complex_string[102];
  std::string real_part, imag_part;
  int i;

  // Inicializando variáveis
  real_part = "";
  imag_part = "";

  // Recebendo o input do usuário
  std::cout << "Usuário digite o valor do número complexo em questão usando a "
               "notação algébrica (a+bi) ou (a-bi):"
            << '\n';
  std::cin >> complex_string;

  // Determinando as partes reais e imaginária do número complexo
  for (i = 0; i < 102; ++i)
    {
      if (complex_string[i] != '+' && complex_string[i] != '-')
        real_part.push_back (complex_string[i]);
      if (complex_string[i] == '+')
        break;
      if (complex_string[i] == '-')
        {
          break;
        };
    };

  for (; i < 102; ++i)
    {
      if (complex_string[i] == 'i')
        continue;
      imag_part.push_back (complex_string[i]);
    };

  // Obtendo as partes reais e complexas
  std::stringstream (real_part) >> real;
  std::stringstream (imag_part) >> imag;
};

// Função que escreve um npumero complexo em sua notação algébrica
template <typename T>
std::string
complex<T>::algebraic ()
{
  std::string result; // Variável temporária

  if (imag >= 0)
    result = std::to_string (real) + "+" + std::to_string (imag) + "i";
  if (imag < 0)
    result = std::to_string (real) + std::to_string (imag) + "i";
  return result;
};

// Operações aritméticas com números complexos
// Soma
template <typename T>
complex<T>
complex<T>::operator+ (complex<T> z1)
{
  // Resultado
  complex<T> z2;

  // Definição
  z2.real = real + z1.real;
  z2.imag = imag + z1.imag;
  return z2;
};

// Subtração
template <typename T>
complex<T>
complex<T>::operator- (complex<T> z1)
{
  // Resultado
  complex<T> z2;

  // Definição
  z2.real = real - z1.real;
  z2.imag = imag - z1.imag;
  return z2;
};

// Multiplicação
template <typename T>
complex<T>
complex<T>::operator* (complex<T> z1)
{
  // Resultado
  complex<T> z2;

  // Definição
  z2.real = (real * z1.real) - (imag * z1.imag);
  z2.imag = (real * z1.imag) + (imag * z1.real);
  return z2;
};

// Divisão
template <typename T>
complex<T>
complex<T>::operator/ (complex<T> z1)
{
  // Resultado
  complex<T> z2;
  T norm;

  // Definição
  norm = std::sqrt (std::pow (z1.real, 2) + std::pow (z1.imag, 2));
  z2.real = (real * z1.real) + (imag * z1.imag);
  z2.imag = (imag * z1.real) - (real * z1.imag);
  z2.imag /= norm;
  z2.real /= norm;
  return z2;
};

// Norma de um número complexo
template <typename T>
T
complex<T>::norm ()
{
  return std::sqrt (std::pow (real, 2) + std::pow (imag, 2));
};

// Ângulo associado a um número polar
template <typename T>
T
complex<T>::polar ()
{
  T result = std::atan (imag / real);
  return result;
};

// Conjungado de um número complexo
template <typename T>
complex<T>
complex<T>::conj ()
{
  // Resultado
  complex<T> z1;
  // Procedimento
  z1.real = real;
  z1.imag = (-1) * imag;
  return z1;
};

template <typename T>
complex<T>
complex<T>::inv ()
{
  // Variáveis locais
  complex<T> z1;

  // Procedimento
  z1.real = real;
  z1.imag = (-1) * imag;
  z1.imag /= norm ();
  z1.real /= norm ();
  return z1;
};

// Fórmula de Euler
template <typename T>
complex<T>
complex<T>::exp ()
{
  // Variáveis locais
  T z_angle;
  T z_norm;
  complex<T> z1;

  // Procedimentos
  z_angle = polar ();
  z_norm = norm ();
  z1.real = std::exp (z_norm) * std::cos (z_angle);
  z1.imag = std::exp (z_norm) * std::sin (z_angle);
  return z1;
};

// Potenciação com expoente inteiro
template <typename T>
complex<T>
complex<T>::pow (double n)
{
  // Variáveis locais
  T z_angle;
  T z_norm;
  complex<T> z1;

  // Procedimentos
  z_angle = polar ();
  z_norm = norm ();
  z1.real = std::pow (z_norm, n) * std::cos (z_angle * n);
  z1.imag = std::pow (z_norm, n) * std::sin (z_angle * n);
  return z1;
};
