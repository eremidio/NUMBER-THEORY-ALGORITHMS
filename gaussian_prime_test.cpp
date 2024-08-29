// VAMOS CRIAR UMA ROTINA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO gaussian_prime_test.hpp
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o gaussian_prime_test gaussian_prime_test.cpp

// Cabeçalho
#include "gaussian_prime_test.hpp"

#include <iostream>
using namespace std;

// Função principal
int main() {
  // Variáveis locais
  complex<int64_t> z;
  bool test;

  // Procedimentos
  // Recebendo input do usuário
  z.set();

  // Testando a primalidade do inteiro gaussiano
  test = gaussian_prime_test(z);
  if (test == true) cout << z.algebraic() << " é primo.\n";
  if (test == false) cout << z.algebraic() << " não é primo.\n";

  // Finalizando a aplicação
  return 0;
}
