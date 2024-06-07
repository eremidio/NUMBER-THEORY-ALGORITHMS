//VAMOS CRIAR UM PROGRAMA TESTAR AS ROTINAS CRIADAS NO ARQUIVO baby_step_giant_step.hpp
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o  baby_step_giant_step baby_step_giant_step.cpp -O2

// Cabeçalho
#include "baby_step_giant_step.hpp"
#include <iostream>
using namespace std;

// Função principal
int main(){

  // Variáveis locais
  int64_t a, c, m, k;


  // Procedimento
    // Recebendo input do usuário
    cout << "Digite um inteiro (base): ";
    cin >> a;
    cout << "Digite um inteiro (logaritmando): ";
    cin >> c;
    cout << "Digite um inteiro(congruente): ";
    cin >> m;

    // Calculando o logaritmo discreto
    k = baby_step_giant_step(a, c, m);
    if (k == (-1))
      cout<< "Não existe logaritmo natural de " << c << " na base " << a << " módulo " << m << ".\n";
     else
      cout<< "Logaritmo natural de " << c << " na base " << a << " módulo " << m << " é " << k << ".\n";


  // Encerrando a aplicação
  return 0;

          }
