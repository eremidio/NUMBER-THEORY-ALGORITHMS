// VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS DEFINIDAS NO ARQUIVO
// elliptic_curve_factorization.hpp COMPILAR ESTE PROGRAMA COM: g++ -o
// elliptic_curve_factorization elliptic_curve_factorization.cpp

// CABEÇALHO
#include "elliptic_curve_factorization.hpp"
using namespace std;

// FUNÇÃO PRINCIPAL
int
main ()
{
  // Instanciando um objeto da classe e executando um algoritmo
  elliptic_curve_method factorizer;
  factorizer.run ();

  // TESTES USE UM // APÓS OS TESTES
  // cout<<modular_inverse(73, 75)<<"\n";

  // Finalizando a aplicação
  return 0;
}
