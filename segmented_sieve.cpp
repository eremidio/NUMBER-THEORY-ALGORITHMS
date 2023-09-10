// VAMOS CRIAR UM PROGRAMA QUE USA UMA PENEIRA SEGMENTADA PARA CALCULAR NÚMEROS
// PRIMOS COMPILAR ESTE PROGRAMA COM: g++ -o segmented_sieve
// segmented_sieve.cpp

//****************************************************************************************************************************
// CABEÇALHO
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// VARIÁVEIS GLOBAIS
vector<uint64_t> prime_buffer;

//****************************************************************************************************************************
// FUNÇÕES
// Função que calcula se um número é primo ou não
bool
is_prime (uint64_t n)
{
  // Casos triviais
  // 0,1
  if (n <= 1)
    return false;

  // Primos menores que 100
  if (n == 2 || n == 3 || n == 5 || n == 7 || n == 11 || n == 13 || n == 17
      || n == 19 || n == 23 || n == 29 || n == 31 || n == 37 || n == 41)
    return true;
  if (n == 43 || n == 47 || n == 53 || n == 59 || n == 61 || n == 67 || n == 71
      || n == 73 || n == 79 || n == 83 || n == 89 || n == 97)
    return true;

  // Testando divisibilidade por primos menores do que 100
  if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0 || n % 11 == 0
      || n % 13 == 0 || n % 17 == 0 || n % 19 == 0 || n % 23 == 0
      || n % 29 == 0 || n % 31 == 0 || n % 37 == 0 || n % 41 == 0)
    return false;
  else if (n % 43 == 0 || n % 47 == 0 || n % 53 == 0 || n % 59 == 0
           || n % 61 == 0 || n % 67 == 0 || n % 71 == 0 || n % 73 == 0
           || n % 79 == 0 || n % 83 == 0 || n % 89 == 0)
    return false;
  else if (n % 97 == 0)
    return false;

  // Variáveis locais
  uint64_t sqrt_n = std::sqrt (n);

  // Procedimento usando uma otimização 30k+1
  for (uint64_t i = 31; i < sqrt_n + 1; i += 30)
    {
      if ((n % i) == 0 || (n % (i + 6)) == 0 || (n % (i + 10)) == 0
          || (n % (i + 12)) == 0 || (n % (i + 16)) == 0 || (n % (i + 22)) == 0
          || (n % (i + 28)) == 0)
        return false;
    };
  return true;
};

// Função que preenche um buffer de númeror primos até n^1/2
void
fill_prime_buffer (uint64_t n)
{
  // Variáveis locais
  uint64_t sqrt_n = floor (sqrt (n));
  // Procedimentos
  for (uint64_t i = 0; i <= sqrt_n; ++i)
    {
      if (is_prime (i))
        prime_buffer.emplace_back (i);
    };
};

// Função que printa os valores de primos até um dado valor
void
segmented_sieve (uint64_t n, uint64_t max_size)
{
  // Variáveis locais
  uint64_t turns, upper, lower, mark_index /*index no array*/,
      real_value /*valor real*/, counter /*contador*/, prime;
  uint64_t i, j; // Variáveis de ieteração
  bool *bool_array = new bool[max_size];
  // Procedimentos
  // Ajuste de variáveis para a primeira iteração
  turns = 1;
  lower = 0;
  upper = (max_size * turns) - 1;

  for (i = 0; i < max_size - 1; ++i)
    bool_array[i] = true;

  // Printando os primos alocados no buffer
  for (auto p : prime_buffer)
    cout << p << " ";

  // Loop principal
  while (lower < n)
    {
      // Iterando pelo vetores de números
      for (i = 0; i < prime_buffer.size (); ++i)
        {
          // Ajuste do contador
          prime = prime_buffer[i];
          counter = lower / prime;
          // Iterando pelo array de booleanos
          for (; counter * prime < upper; counter++)
            {
              mark_index = (counter * prime) % max_size;
              bool_array[mark_index] = false;
            };
        };

      // Printando os primos no segmento em questão
      for (i = 0; i < max_size - 1; ++i)
        {
          if (bool_array[i] == true)
            {
              real_value = i + max_size * (turns - 1);
              if (real_value > prime_buffer[prime_buffer.size () - 1])
                cout << real_value << " ";
            };
        };

      // Atualizando variáveis para a próxima iteração
      turns++;
      lower += max_size;
      upper += max_size;
      for (i = 0; i < max_size - 1; ++i)
        bool_array[i] = true;
    };
  cout << "\n";
  // Limpando o cachê de memória
  delete[] bool_array;
};

//****************************************************************************************************************************
// FUNÇÃO PRINCIPAL
int
main ()
{
  // Recebendo input do usuário
  uint64_t n, max_size;
  // Procedimentos
  // Recebendo input do usuário
  cout << "Digite um limitante para sua sequência de números primos: ";
  cin >> n;
  cout << "Digite o tamanho do intervalo de segmentação: ";
  cin >> max_size;
  // Preenchendo o buffer de números primos
  fill_prime_buffer (n);

  // TESTE USE UM // APÓS O MESMO
  // for(uint64_t i=0; i<prime_buffer.size(); ++i)
  // cout<<prime_buffer.at(i)<< " ";
  // cout<<"\n";

  // Printando os números primos até um dado valor
  segmented_sieve (n, max_size);

  // Finalizando a aplicação
  return 0;
};
