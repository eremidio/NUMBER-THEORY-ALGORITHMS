// VAMOS CRIAR UMA CLASSE DE MATRIZES PARA OPERAÇÕES BÁSICAS COMO COMO SOMA,
// SUBTRAÇÃO, MULTIPLICAÇÃO E TRANSPOSIÇÃO. CLASSE ÚTIL PARA PROBLEMAS DE
// ÁLGEBRA LINEAR BÁSICA E PARA ALGORITMOS COMPLEXOS QUE REQUER MANIPULAÇÃO
// BÁSICA DE MATRIZES

/*
OPERAÇÕES MAIS COMPLEXAS COMO CÁLCULO DE MATRIZES INVERSAS E CÁLCULO DO
DETERMINANTE PODEM SER DEFINIDOS SOBRE ELEMENTOS DESTA CLASSE USANDO ALGORITMOS
COMO A ELIMINAÇÃO DE GAUSS-JORDAN, ENTRE OUTROS.

USAMOS AQUI INDEXAGEM DE [0 ...  (linhas-1)]  [0 ...  (colunas-1)] PARA
REFERENCIAR ELEMENTOS DA MATRIZ. O PRIMEIRO ELEMENTO (1,1) DA MATRIZ, POR
EXEMPLO, É REFERENCIADO PELOS INDEXES (0,0).

*/

//**********************************************************************************************************************************************************************
// CABEÇALHO
#ifndef SIMPLE_MATRIX_CLASS_H
#define SIMPLE_MATRIX_CLASS_H
#include <inttypes.h>
#include <stdint.h>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

// CONSTANTES GLOBAIS
enum matrix_types { Zero, Identity };

//**********************************************************************************************************************************************************************
// CLASSE DE MATRIZES
template <typename T>
class Matrix {
 public:
  // Membros da classe
  int64_t rows, columns;  // Parâmetros que definem o tamanho da matriz
  std::vector<std::vector<T>>
      matrix;  // Vamos implementar matrizes como arrays dinâmicos (vetores) de
               // arrays dinâmicos

  // Construtores e destruídores
  Matrix(int64_t, enum matrix_types);  // Matríz nula e matriz identidade
  Matrix(int64_t, int64_t);  // Matriz especificados o número de linhas e
                             // colunas
  Matrix(int64_t);  // Matrizes quadradas mesmo número de linhas e colunas
  Matrix(const Matrix<T>&);  // Construtor que cópia elementos de uma matrix
  Matrix(){};                // Construtor
  virtual ~Matrix(){};       // Destruidor

  // Métodos da classe
  // Redimensionamento de matrizes
  void set_size();    // Função que dimensiona uma matriz
  void add_row();     // Função que adiciona uma linha a matriz abaixo
  void add_column();  // Função que adiciona coluna a matriz a direita
  void remove_row();  // Função que remove uma linha a matriz a matriz abaixo
  void remove_column();  // Função que remove uma coluna da matriz a direita
  void reshape(int64_t,
               int64_t);  // Função que redimensiona uma matriz adicionado
                          // linhas abaixo e colunas a direita da matriz

  // Operações de acesso aos elementos da matrizes
  Matrix<T> get_row(int64_t);     // Função que retorna uma linha da matriz
  Matrix<T> get_column(int64_t);  // Função que retorna uma coluna da matriz
  Matrix<T> slice(int64_t, int64_t, int64_t,
                  int64_t);  // Função que retorna uma submatriz da matriz
  Matrix<T> comatrix(
      int64_t, int64_t);  // Função que gera uma matriz quadrada removendo a
                          // linha e a coluna que um elemento se encontra
  T get_element(int64_t, int64_t);  // Função que retorna um elemento da matriz

  // Operações de entrada e saída de elementos
  void set_element(int64_t, int64_t,
                   T);  // Função que define o valor de um elemento na matriz
  void manual_setup();  // Função para definir manualmente as entradas da matriz
  void print_matrix();  // Função que printa uma matriz na tela

  // Operações básicas
  Matrix<T> operator+(Matrix<T>&);        // Adição de matrizes
  Matrix<T> operator-(Matrix<T>&);        // Subtração de matrizes
  Matrix<T> operator*(Matrix<T>&);        // Multiplicação de matrizes
  Matrix<T> operator=(const Matrix<T>&);  // Cópia de Matrizes
  Matrix<T> scalar_multiplication(T);  // Multiplicação de matrizes por escalares
  Matrix<T> transpose();  // Função que retorna a matriz transposta
  void permute_rows(int64_t, int64_t);     // Permutação de linhas da matriz
  void permute_columns(int64_t, int64_t);  // Permutação de colunas da matriz
};

//**********************************************************************************************************************************************************************
// MÉTODOS DA CLASSE

//************************************
// Construtores da classe

// Matriz especificados o número de linhas e colunas
template <typename T>
Matrix<T>::Matrix(int64_t a, int64_t b) {
  // Definindo o tamanho da matriz
  rows = a;
  columns = b;

  // Variáveis locais
  std::vector<T> matrix_row;
  int64_t i;

  // Redimensionando a matriz
  matrix_row.resize(b);

  for (i = 0; i < a; ++i) matrix.push_back(matrix_row);
};

// Matrizes quadradas mesmo número de linhas e colunas
template <typename T>
Matrix<T>::Matrix(int64_t n) {
  // Definindo o tamanho da matriz
  rows = n;
  columns = n;

  // Variáveis locais
  std::vector<T> matrix_row;
  int64_t i;

  // Redimensionando a matriz
  matrix_row.resize(n);

  for (i = 0; i < n; ++i) matrix.push_back(matrix_row);
};

// Matríz nula e matriz identidade
template <typename T>
Matrix<T>::Matrix(int64_t n, enum matrix_types x) {
  // Definindo o tamanho da matriz
  rows = n;
  columns = n;

  // Variáveis locais
  std::vector<T> matrix_row;
  int64_t i, j;

  // Redimensionando a matriz
  matrix_row.resize(n);

  for (i = 0; i < n; ++i) matrix.push_back(matrix_row);

  // Ajustando os elementos da matriz
  if (x == Zero) {
    for (i = 0; i < n; ++i) {
      for (j = 0; j < n; ++j) {
        matrix[i][j] = 0;
      };
    };
  };

  if (x == Identity) {
    for (i = 0; i < n; ++i) {
      for (j = 0; j < n; ++j) {
        if (i == j)
          matrix[i][j] = 1;
        else
          matrix[i][j] = 0;
      };
    };
  };
};

// Construtor que  cópia elementos de uma matrix
template <typename T>
Matrix<T>::Matrix(const Matrix<T>& m2) {
  // Variáveis locais
  int64_t i, j;

  // Procedimentos
  // Copiando o número de elementos da matriz
  rows = m2.rows;
  columns = m2.columns;

  // Ajustando o  tamanho da matriz
  reshape(m2.rows, m2.columns);

  // Copiando os elementos da matriz
  for (i = 0; i < rows; ++i) {
    for (j = 0; j < columns; ++j) matrix[i][j] = m2.matrix[i][j];
  };
};

// Cópia de matrizes
template <typename T>
Matrix<T> Matrix<T>::operator=(const Matrix<T>& m2) {
  // Condição que checa se duas matrizes não são iguais
  if (this != &m2) {
    this->rows = m2.rows;
    this->rows = m2.columns;
    this->reshape(m2.rows, m2.columns);
    this->matrix = m2.matrix;
  };

  return *this;
};

//************************************
// Redimensionamento de matrizes
// Função que dimensiona uma matriz
template <typename T>
void Matrix<T>::set_size() {
  // Recebendo input do usuário
  std::cout << "Número de linhas: ";
  std::cin >> rows;
  std::cout << "Número de colunas: ";
  std::cin >> columns;

  // Variáveis locais
  int64_t i;
  std::vector<T> matrix_row;

  // Redimensionando a matriz
  matrix_row.resize(columns);

  for (i = 0; i < rows; ++i) matrix.push_back(matrix_row);
};

// Função que adiciona uma linha a matriz abaixo
template <typename T>
void Matrix<T>::add_row() {
  // Variáveis locais
  std::vector<T> matrix_row;

  // Procedimentos
  matrix_row.resize(columns);
  matrix.push_back(matrix_row);

  // Atualizando o número de linhas
  rows++;
};

// Função que adiciona uma coluna a matriz a direita
template <typename T>
void Matrix<T>::add_column() {
  // Variáveis locais
  int64_t i;

  // Procedimentos
  for (i = 0; i < rows; ++i) matrix[i].resize(matrix[i].size() + 1);

  // Atualizando o número de colunas
  columns++;
};

// Função que remove uma linha da matriz abaixo
template <typename T>
void Matrix<T>::remove_row() {
  // Procedimentos
  matrix.pop_back();

  // Atualizando o número de linhas
  rows--;
};

// Função que remove uma coluna da matriz a direita
template <typename T>
void Matrix<T>::remove_column() {
  // Variáveis
  int64_t i;

  // Procedimentos
  for (i = 0; i < rows; ++i) matrix[i].pop_back();

  // Atualizando o número de colunas
  columns--;
};

// Função que redimensiona uma matriz adicionado linhas abaixo e colunas a
// direita da matriz
template <typename T>
void Matrix<T>::reshape(int64_t k, int64_t l) {
  // Variáveis locais
  std::vector<T> matrix_row;
  int i;

  // Procedimentos
  // Ajuste de variáveis
  rows = k;
  columns = l;

  // Adicionando linhas
  matrix_row.resize(columns);

  while (k > matrix.size()) matrix.push_back(matrix_row);

  // Adicionando colunas
  for (i = 0; i < rows; ++i) matrix[i].resize(columns);
};

//************************************
// Operações de acesso aos elementos da matrizes

// Função que retorna uma linha da matriz
template <typename T>
Matrix<T> Matrix<T>::get_row(int64_t k) {
  // Restrição
  assert(k < rows);

  // Variáveis locais
  Matrix<T> row_matrix(1, columns);
  int64_t i;

  // Procedimentos
  for (i = 0; i < columns; i++) row_matrix.set_element(0, i, matrix[k][i]);

  // Resultado
  return row_matrix;
};

// Função que retorna uma coluna da matriz
template <typename T>
Matrix<T> Matrix<T>::get_column(int64_t k) {
  // Restrição
  assert(k < columns);

  // Variáveis locais
  Matrix<T> column_matrix(rows, 1);
  int64_t i;

  // Procedimentos
  for (i = 0; i < rows; i++) column_matrix.set_element(i, 0, matrix[i][k]);

  // Resultado
  return column_matrix;
};

// Função que retorna uma submatriz da matriz
template <typename T>
Matrix<T> Matrix<T>::slice(int64_t start_row, int64_t end_row,
                           int64_t start_column, int64_t end_column) {
  // Variáveis locais
  int64_t i, j;
  int64_t new_rows = end_row - start_row + 1;
  int64_t new_columns = end_column - start_column + 1;
  Matrix<T> slice_matrix(new_rows, new_columns);

  // Procedimentos
  // Definindo elementos da matriz
  for (i = 0; i < new_rows; ++i) {
    for (j = 0; j < new_columns; ++j)
      slice_matrix.set_element(i, j, matrix[i + start_row][j + start_column]);
  };

  // Resultados
  return slice_matrix;
};

// Função que gera uma matriz quadrada removendo a linha e a coluna que um
// elemento se encontra
template <typename T>
Matrix<T> Matrix<T>::comatrix(int64_t k1, int64_t k2) {
  // Restrição
  assert(k1 < rows && k2 < columns);

  // Variáveis locais
  Matrix<T> reduced_matrix((rows), (columns));
  int64_t new_rows = rows - 1;
  int64_t new_columns = columns - 1;
  int64_t i, j;

  // Definindo elementos da matriz
  for (i = 0; i < new_rows; ++i) {
    for (j = 0; j < new_columns; ++j) {
      if (i < k1 && j < k2) reduced_matrix.set_element(i, j, matrix[i][j]);
      if (i >= k1 && j < k2) reduced_matrix.set_element(i, j, matrix[i + 1][j]);
      if (i < k1 && j >= k2) reduced_matrix.set_element(i, j, matrix[i][j + 1]);
      if (i >= k1 && j >= k2)
        reduced_matrix.set_element(i, j, matrix[i + 1][j + 1]);
    };
  };

  // Resultados
  reduced_matrix.remove_row();
  reduced_matrix.remove_column();
  return reduced_matrix;
};

// Função que retorna um elemento da matriz
template <typename T>
T Matrix<T>::get_element(int64_t i, int64_t j) {
  return matrix[i][j];
};

//************************************
// Operações de entrada e saída de elementos

// Função que define o valor de um elemento na matriz
template <typename T>
void Matrix<T>::set_element(int64_t row, int64_t column, T value) {
  matrix[row][column] = value;
};

// Função para definir manualmente as entradas da matriz
template <typename T>
void Matrix<T>::manual_setup() {
  // Variáveis locais
  int64_t i, j;
  T element;

  // Procedimentos
  for (i = 0; i < rows; ++i) {
    for (j = 0; j < columns; ++j) {
      std::cout << "Digite o valor do elemento (" << i << "," << j
                << ") da matriz: ";
      std::cin >> element;
      set_element(i, j, element);
    };
  };
};

// Função que printa uma matriz na tela
template <typename T>
void Matrix<T>::print_matrix() {
  // Variáveis locais
  int64_t i, j;

  // Procedimentos
  for (i = 0; i < rows; ++i) {
    for (j = 0; j < columns; ++j) std::cout << matrix[i][j] << " ";
    std::cout << '\n';
  };
  std::cout << '\n';
};

//************************************
// Operações básicas em matrizes

// Adição de matrizes
template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T>& m2) {
  // Restrição
  assert(rows == m2.rows && columns == m2.columns);

  // Variáveis locais
  Matrix<T> result;
  int64_t i, j;

  // Procedimentos
  // Redimensionando a matriz
  result.reshape(rows, columns);

  // Somando elemento a elemento na matriz
  for (i = 0; i < rows; ++i) {
    for (j = 0; j < columns; ++j)
      result.set_element(i, j, matrix[i][j] + m2.matrix[i][j]);
  };
  // Resultado
  return result;
};

// Subtração de matrizes
template <typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T>& m2) {
  // Restrição
  assert(rows == m2.rows && columns == m2.columns);

  // Variáveis locais
  Matrix<T> result;
  int64_t i, j;

  // Procedimentos
  // Redimensionando a matriz
  result.reshape(rows, columns);

  // Somando elemento a elemento na matriz
  for (i = 0; i < rows; ++i) {
    for (j = 0; j < columns; ++j)
      result.set_element(i, j, matrix[i][j] - m2.matrix[i][j]);
  };
  // Resultado
  return result;
};

// Multiplicação de matrizes
template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& m2) {
  // Restrição
  assert(columns == m2.rows);

  // Variáveis locais
  Matrix<T> result(rows, m2.columns);
  int64_t i, j, k;

  // Procedimentos
  // Loop principal
  for (i = 0; i < rows; ++i) {
    for (j = 0; j < m2.columns; ++j) {
      // Ajuste de variáveis
      result.matrix[i][j] = 0;

      // Somando o produto da i-ésima linha de uma matriz pela j-ésima coluna da
      // outra matriz
      for (k = 0; k < m2.rows; ++k)
        result.matrix[i][j] =
            result.matrix[i][j] + (matrix[i][k] * m2.matrix[k][j]);
    };
  };
  // Resultado
  return result;
};

// Multiplicação de matrizes por escalares
template <typename T>
Matrix<T> Matrix<T>::scalar_multiplication(T k) {
  // Variáveis locais
  Matrix<T> result(rows, columns);
  int64_t i, j;

  // Procedimentos
  // Loop principal
  for (i = 0; i < rows; ++i) {
    for (j = 0; j < columns; ++j) result.matrix[i][j] = (matrix[i][j]) * k;
  };
  // Resultado
  return result;
};

// Função que retorna a matriz transposta
template <typename T>
Matrix<T> Matrix<T>::transpose() {
  // Variáveis locais
  int64_t i, j;
  T temp;
  Matrix<T> result(columns, rows);

  // Procedimentos
  // Loop principal
  for (i = 0; i < columns; ++i) {
    for (j = 0; j < rows; ++j) result.matrix[i][j] = matrix[j][i];
  };
  // Resultado
  return result;
};

// Permutação de linhas da matriz
template <typename T>
void Matrix<T>::permute_rows(int64_t k1, int64_t k2) {
  // Restrição
  assert(k1 < rows && k2 < rows);

  // Variáveis locais
  int64_t i;
  T temp;

  // Procedimentos
  // Loop principal
  for (i = 0; i < columns; ++i) {
    temp = matrix[k2][i];
    matrix[k2][i] = matrix[k1][i];
    matrix[k1][i] = temp;
  };
};

// Permutação de colunas da matriz
template <typename T>
void Matrix<T>::permute_columns(int64_t k1, int64_t k2) {
  // Restrição
  assert(k1 < columns && k2 < columns);

  // Variáveis locais
  int64_t i;
  T temp;

  // Procedimentos
  // Loop principal
  for (i = 0; i < rows; ++i) {
    temp = matrix[i][k2];
    matrix[i][k2] = matrix[i][k1];
    matrix[i][k1] = temp;
  };
};

//**********************************************************************************************************************************************************************
// FIM DO HEADER
#endif
