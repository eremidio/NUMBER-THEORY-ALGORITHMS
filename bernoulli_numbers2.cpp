// VAMOS CRIAR UM PROGRAMA QUE COMPUTA OS NÚMEROS DE BERNOULLI A PARTIR DFA
// FUNÇÃO ZETA DE RIEMANN COMPILAR ESTE PROGRAMA COM: g++ -o bernoulli_numbers2
// bernoulli_numbers2.cpp

// Cabeçalho
#include "bernoulli_numbers2.hpp"
#include <iostream>
using namespace std;

// Função principal
int
main ()
{
  // Variáveis locais
  int n;
  /// Procedimento
  // Recebendo input do usuário
  cout << "Digite um número inteiro: ";
  cin >> n;

  // Exibindo o resultado
  cout << "B(" << n << ")= " << bernoulli_number_generator0 (n) << "\n";
  // Finalizando a aplicação
  return 0;
}
