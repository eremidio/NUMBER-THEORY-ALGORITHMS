// VAMOS CRIAR UM PROGRAMA TESTAR AS ROTINAS CRIADAS NO ARQUIVO
// baby_step_giant_step.hpp COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o
// baby_step_giant_step baby_step_giant_step.cpp

// Cabeçalho
#include "baby_step_giant_step.hpp"
#include <iostream>
using namespace std;

// Função principal
int
main ()
{
  // Variáveis locais
  int64_t a, c, m, k;
  // Procedimento
  // Recebendo input do usuário
  cout << "Digite um inteiro: ";
  cin >> a;
  cout << "Digite um inteiro: ";
  cin >> c;
  cout << "Digite um inteiro: ";
  cin >> m;

  // Calculando o logaritmo discreto
  k = discrete_logarithm (a, c, m);
  if (k == (-1))
    cout << "Não existe logaritmo natural de " << c << " na base " << a
         << " módulo " << m << ".\n";
  else
    cout << "Logaritmo natural de " << c << " na base " << a << " módulo " << m
         << " é " << k << ".\n";
  // Encerrando a aplicação
  return 0;
}
