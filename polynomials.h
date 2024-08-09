// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA CLASSE DE POLINÔMIOS DE UMA ÚNICA
// VARIÁVEL EM C++ (ÚTIL IMPLEMENTAR ALGORITMOS QUE USAM POLINÔMIOS)

/*
ESTA CLASSE SERÁ PARA USO DE POLINÔMIOS QUE ASSUMEM VALORES NO CORPO DOS NÚMEROS
REAIS.

*/

//*******************************************************************************************************************************************************************
// CABEÇALHO
#ifndef POLYNOMIALS_H
#define POLYNOMIALS_H
#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include<float.h>
#include <iostream>
#include <string>
#include <vector>

//*******************************************************************************************************************************************************************
// CLASSE
template <typename T>
class polynomial {
 public:
  // Membros da classe
  int64_t degree;
  std::vector<T> polynomial_coefficients;
  std::vector<int64_t> polynomial_powers;

  // Construtores e destruidores
  polynomial(){};
  virtual ~polynomial(){};

  // Métodos da classe
  // Funções básicas
  void set_degree();        // Função que define o grau de um polinômio
  void set_coefficients();  // Função que define os coeficientes de um
                            // polinômios
  void set();                // Função que define um polinômio
  std::string algebraic();   // Função que printa um polinômio na tela
  T evaluate_polynomial(T);  // Função que define o valor da raíz de um polinômio
  void adjust_degree();//Função que reduz o grau de um polinômio contendo coeficientes nulos

  // Operações aritméticas básicas em aneis de polinômios
  polynomial<T> operator+(polynomial<T>&);
  polynomial<T> operator-(polynomial<T>&);
  polynomial<T> operator*(polynomial<T>&);
  polynomial<T> operator/(polynomial<T>&);
  polynomial<T> operator=(const polynomial<T>&);
};

//*******************************************************************************************************************************************************************
// MÉTODOS DA CLASSE

//**********************
// Funções básicas
// Função que define o grau de um polinômio
template <typename T>
void polynomial<T>::set_degree() {
  // Variáveis locais
  int64_t k;

  // Procedimentos
  // Recebendo input do usuário
  std::cout << "Grau do polinômio: ";
  std::cin >> k;
  degree = k;

  // Ajustando o array de potências
  for (int64_t i = degree; i >= 0; --i) polynomial_powers.push_back(i);
};

// Função que define os coeficientes de um polinômios
template <typename T>
void polynomial<T>::set_coefficients() {
  // Variáveis locais
  T element;

  // Procedimentos
  // Ajuste do array de coeficientes
  polynomial_coefficients.resize(0);

  // Definindo os coeficientes do polinômio
  for (int64_t i = degree; i >= 0; --i) {
    std::cout << "Coeficiente de x^" << i << ": ";
    std::cin >> element;
    polynomial_coefficients.push_back(element);
  };
};
// Função que define um polinômio
template <typename T>
void polynomial<T>::set() {
  set_degree();
  set_coefficients();
};

// Função que define o valor de um polinômio dado um argumento
template <typename T>
T polynomial<T>::evaluate_polynomial(T value) {
  // Variáveis locais
  int64_t i, j;
  T result = 0, parcel;

  // Procedimentos
  for (i = 0; i <= degree; ++i) {
    parcel = polynomial_coefficients[i];

    for (j = 0; j < polynomial_powers[i]; ++j) parcel *= value;

    result += parcel;
  };

  // Resultado
  return result;
};

//Função que corrige o grau de um polinômio contendo coeficientes nulos nos termos de maior potência
template <typename T>
void polynomial<T>::adjust_degree(){
  
  //Variáveis locais
  std::vector<T> new_coefficients;


  //Procedimentos
    //Loop principal: eleminando os termos 0 dos monômios de maior potência
    new_coefficients.resize(0);
    for(auto c:polynomial_coefficients){
      if(c==0 && new_coefficients.size()==0) continue;
      else if(c>0 && c<DBL_EPSILON) new_coefficients.push_back(0);
      else if(c<0 && ((-1)*c)<DBL_EPSILON) new_coefficients.push_back(0);
      else new_coefficients.push_back(c);

    }

    //Ajuste do grau do polinômio
    polynomial_coefficients=new_coefficients;
    degree = polynomial_coefficients.size()-1;
    polynomial_powers.resize(0);
    for (int64_t i = degree; i >= 0; --i) polynomial_powers.push_back(i);
    if(degree==0 && polynomial_coefficients.size()==0) polynomial_coefficients.push_back(0);

}



// Função que printa um polinômio na tela
template <typename T>
std::string polynomial<T>::algebraic() {
  // Variável
  std::string polynomial_string = "";
  int64_t i;

  // Procedimentos
   //Caso base: zero
   if((polynomial_coefficients[0]==0 && degree==0) || polynomial_coefficients.size()==0){
     polynomial_string = " ";
     return polynomial_string;    
   }
    
    
  // 1º coeficiente
  if (polynomial_coefficients[0] != 0) {
    polynomial_string += std::to_string(polynomial_coefficients[0]);
    polynomial_string += "x^";
    polynomial_string += std::to_string(polynomial_powers[0]);
  };

  // Demais coeficientes
  if (degree >= 0) {
    for (i = 1; i <= degree; ++i) {
      if (polynomial_coefficients[i] > 0) polynomial_string += "+";
      if (polynomial_coefficients[i] == 0) continue;
      polynomial_string += std::to_string(polynomial_coefficients[i]);

      if (polynomial_powers[i] > 0) {
        polynomial_string += "x^";
        polynomial_string += std::to_string(polynomial_powers[i]);
      } else
        continue;
    };
  };

  // Resultado
  return polynomial_string;
};

//**********************
// Operações aritméticas básicas em aneis de polinômios

//**********************
// Adição
template <typename T>
polynomial<T> polynomial<T>::operator+(polynomial<T>& p2) {
  // Variáveis locais
  polynomial<T> result;
  int64_t difference, temp, i = 0;

  // Procedimento
  // Definindo o grau do polinômio a ser obtido como resultado
  if (degree > p2.degree) {
    result.degree = degree;
    difference = degree - p2.degree;
  } else {
    result.degree = p2.degree;
    difference = p2.degree - degree;
  };

  // Definindo os coeficientes do polinômio resultante
  result.polynomial_coefficients.resize(0);  // Ajuste de variáveis
  temp = difference;                         // Ajuste de variáveis

  if (result.degree == degree) {
    while (result.polynomial_coefficients.size() < (result.degree + 1)) {
      if (difference > 0) {
        difference--;
        result.polynomial_coefficients.push_back(polynomial_coefficients[i]);
        ++i;
      };

      if (difference <= 0) {
        result.polynomial_coefficients.push_back(
            polynomial_coefficients[i] + p2.polynomial_coefficients[i - temp]);
        ++i;
      };
    };
  };

  if (result.degree == p2.degree) {
    while (result.polynomial_coefficients.size() < (result.degree + 1)) {
      if (difference > 0) {
        difference--;
        result.polynomial_coefficients.push_back(p2.polynomial_coefficients[i]);
        ++i;
      };

      if (difference <= 0) {
        result.polynomial_coefficients.push_back(
            p2.polynomial_coefficients[i] + polynomial_coefficients[i - temp]);
        ++i;
      };
    };
  };

  // Ajustando o array de potências do polinômio resultado
  result.polynomial_powers.resize(0);
  if (result.degree == degree) {
    for (auto x : polynomial_powers) result.polynomial_powers.push_back(x);
  };
  if (result.degree == p2.degree) {
    for (auto y : p2.polynomial_powers) result.polynomial_powers.push_back(y);
  };

  //Ajuste final
  if(result.polynomial_coefficients[0]==0 && result.degree>0)
    result.adjust_degree();

  // Resultado
  return result;
};

//**********************
// Subtração
template <typename T>
polynomial<T> polynomial<T>::operator-(polynomial<T>& p2) {
  // Variáveis locais
  polynomial<T> result;
  int64_t difference, temp, i = 0;

  // Procedimento
  // Definindo o grau do polinômio a ser obtido como resultado
  if (degree > p2.degree) {
    result.degree = degree;
    difference = degree - p2.degree;
  } else {
    result.degree = p2.degree;
    difference = p2.degree - degree;
  };

  // Definindo os coeficientes do polinômio resultante
  result.polynomial_coefficients.resize(0);  // Ajuste de variáveis
  temp = difference;                         // Ajuste de variáveis

  if (result.degree == degree) {
    while (result.polynomial_coefficients.size() < (result.degree + 1)) {
      if (difference > 0) {
        difference--;
        result.polynomial_coefficients.push_back(polynomial_coefficients[i]);
        ++i;
      };

      if (difference <= 0) {
        result.polynomial_coefficients.push_back(
            polynomial_coefficients[i] - p2.polynomial_coefficients[i - temp]);
        ++i;
      };
    };
  };

  if (result.degree == p2.degree) {
    while (result.polynomial_coefficients.size() < (result.degree + 1)) {
      if (difference > 0) {
        difference--;
        result.polynomial_coefficients.push_back((-1) *
                                                 p2.polynomial_coefficients[i]);
        ++i;
      };

      if (difference <= 0) {
        result.polynomial_coefficients.push_back(
            (-1) * p2.polynomial_coefficients[i] +
            polynomial_coefficients[i - temp]);
        ++i;
      };
    };
  };

  // Ajustando o array de potências do polinômio resultado
  result.polynomial_powers.resize(0);
  if (result.degree == degree) {
    for (auto x : polynomial_powers) result.polynomial_powers.push_back(x);
  };
  if (result.degree == p2.degree) {
    for (auto y : p2.polynomial_powers) result.polynomial_powers.push_back(y);
  };

  //Ajuste final
  if(result.polynomial_coefficients[0]==0 && result.degree>0)
    result.adjust_degree();

  // Resultado
  return result;
};

//**********************
// Multiplicação
template <typename T>
polynomial<T> polynomial<T>::operator*(polynomial<T>& p2) {
  // Variáveis locais
  polynomial<T> result;
  T calculated_coefficient;
  int64_t i, j, k;

  // Procedimentos
  // Ajuste do grau do polinômio resultante
  result.degree = degree + p2.degree;

  // Ajuste do array de potências
  result.polynomial_powers.resize(0);
  for (i = result.degree; i >= 0; --i) result.polynomial_powers.push_back(i);

  // Ajuste do array de coeficientes
  result.polynomial_coefficients.resize(0);

  // Adicionando o primeiro coeficiente
  result.polynomial_coefficients.push_back(polynomial_coefficients[0] *
                                           p2.polynomial_coefficients[0]);
  k = 1;  // Ajuste de variáveis

  // Ajustando os demais coeficientes
  while (k < result.degree) {
    calculated_coefficient = 0;
    for (i = 0; i < polynomial_coefficients.size(); ++i) {
      for (j = 0; j < p2.polynomial_coefficients.size(); ++j) {
        if ((i + j) == k)
          calculated_coefficient =
              calculated_coefficient +
              (polynomial_coefficients[i] * p2.polynomial_coefficients[j]);
      };
    };

    result.polynomial_coefficients.push_back(calculated_coefficient);
    k++;
  };

  // Adicionando o último coeficiente
  result.polynomial_coefficients.push_back(
      polynomial_coefficients[(polynomial_coefficients.size() - 1)] *
      p2.polynomial_coefficients[(p2.polynomial_coefficients.size() - 1)]);

  // Resultado
  return result;
};

//**********************
// Divisão
template <typename T>
polynomial<T> polynomial<T>::operator/(polynomial<T>& p2) {
  // Restrição
  assert(degree >= p2.degree);

  // Variáveis locais
  std::vector<T> operand_vector = polynomial_coefficients;
  T ratio;
  polynomial<T> result;
  int64_t i, k = 0;

  // Procedimentos
  // Caso base: polinômios de mesmo grau
  if (degree == p2.degree) {
    result.degree = 0;
    result.polynomial_powers = {0};
    result.polynomial_coefficients.push_back(polynomial_coefficients[0] /
                                             p2.polynomial_coefficients[0]);
    return result;
  };

  // Ajuste do grau do polinômio resultante
  result.degree = degree - p2.degree;

  // Ajuste do array de potências
  result.polynomial_powers.resize(0);
  for (i = result.degree; i >= 0; --i) result.polynomial_powers.push_back(i);

  // Ajuste do array de coeficientes
  result.polynomial_coefficients.resize(0);

  while (result.polynomial_coefficients.size() < (result.degree + 1)) {
    ratio = operand_vector[k] / p2.polynomial_coefficients[0];
    result.polynomial_coefficients.push_back(ratio);

    for (i = k; i < (k + p2.polynomial_coefficients.size()); ++i)
      operand_vector[i] = operand_vector[i] - (ratio * p2.polynomial_coefficients[i - k]);
      if(i==k) operand_vector[i]=0;

    // Atualizando variável para a próxima iteração
    ++k;
  };

  // Resultado
  return result;
};

//**********************
// Cópia
template <typename T>
polynomial<T> polynomial<T>::operator=(const polynomial<T>& p2) {
  // Condição que checa a não igualdade dos polinômios
  if (this != &p2) {
    // Ajuste do grau do polinômio
    this->degree = p2.degree;

    // Ajuste do array de coeficientes
    this->polynomial_coefficients = p2.polynomial_coefficients;

    // Ajuste do array de potências
    this->polynomial_powers = p2.polynomial_powers;
  };

  // Resultado
  return *this;
};

//**********************
// Resto da divisão
template <typename T>
polynomial<T> remainder(polynomial<T>& p1, polynomial<T>& p2) {
  // Restrição
  assert(p1.degree >= p2.degree);

  // Variáveis locais
  polynomial<T> quotient, temp, result;
  polynomial<T> zero_polynomial;
  zero_polynomial.degree = 0;
  zero_polynomial.polynomial_powers = {0};
  zero_polynomial.polynomial_coefficients = {0};

  // Procedimentos
  // Computando o a sequência intermediária
  quotient = p1 / p2;
  temp = quotient * p2;
 

  // Caso base: p2 divide p1
  if (temp.degree == p1.degree &&
      temp.polynomial_coefficients == p1.polynomial_coefficients)
    return zero_polynomial;

  // Computando o resultado
  result = p1 - temp;

  // Resultado
  return result;
};

//*******************************************************************************************************************************************************************
// FIM DO HEADER
#endif
