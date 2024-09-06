// VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO eisenstein_integer_number_theoretical_algorithms.hpp
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o eisenstein_integer_number_theoretical_algorithms eisenstein_integer_number_theoretical_algorithms.cpp -O2

// Cabeçalho
#include "eisenstein_integer_number_theoretical_algorithms.hpp"
using namespace std;

// Função principal
int main() {
  // Variáveis locais
  eisenstein_integer<int> z1, z2, gcd_z;

  // Procedimentos
  // Inicializando objetos da classe
  z1.set();
  z2.set();

  cout << "z1: " << z1.algebraic() << '\n';
  cout << "z2: " << z2.algebraic() << '\n';

  // Teste de primalidade
  if (is_eisenstein_prime<int>(z1) == true)
    cout << "z1 é um primo de Eisenstein\n";
  else
    cout << "z1 não é um primo de Eisenstein\n";

  if (is_eisenstein_prime<int>(z2) == true)
    cout << "z2 é um primo de Eisenstein\n";
  else
    cout << "z2 não é um primo de Eisenstein\n";

  // Algoritmo de Euclides
  gcd_z = gcd<int>(z1, z2);
  cout << "mdc(z1,z2): " << gcd_z.algebraic() << '\n';

  // Fatoração
  factorization<int>(z2);

  // Finalizando a aplicação
  return 0;
}
