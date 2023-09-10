// VAMOS CRIAR UMA ROTINA PARA TESTAR O ALGORITMO DA PENEIRA RACIONAL DEFINIDA
// NO ARQUIVO rational_sieve.hpp COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o
// rational_sieve rational_sieve.cpp

// CABEÇALHO
#include "rational_sieve.hpp"
#include <iostream>

// FUNÇÃO PRINCIPAL
int
main ()
{
  // Instanciando um objeto da classe e executando o algoritmo
  rational_sieve factorizer;
  factorizer.run ();
  // Finalizando a aplicação
  return 0;
}
