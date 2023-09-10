// VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO
// farey_sequence.h COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o farey_sequence
// farey_sequence.cpp

// Cabeçalho
#include "farey_sequence.hpp"
#include <iostream>
using namespace std;

// Função principal
int
main ()
{
  // Variáveis locais
  int n;
  // Procedimento
  // Recebendo input do usuário
  cout << "Digite um número inteiro: ";
  cin >> n;

  // Gerando as sequências de Farey
  cout << "Ordem crescente:\n";
  for (int i = 1; i <= n; ++i)
    generate_farey_sequence (i, Up);
  cout << "Ordem decrescente:\n";
  for (int i = 1; i <= n; ++i)
    generate_farey_sequence (i, Down);

  // Finalizando a aplicação
  return 0;
}
