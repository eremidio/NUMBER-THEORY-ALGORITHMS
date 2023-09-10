// Vamos criar um programa básico em C++ para verificar a conjectura 3n+1,
// também conhecida como conjectura de Collatz Para maiores informações:
// https://en.wikipedia.org/wiki/Collatz_conjecture#Cycles

// Cabeçalho
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

int
main ()
{
  cout << "Programa para verificar a conjectura 3n+1.";
  cout << "Esta conjectura postula que uma sequência de números inteiros "
          "definidos pela regras x(n+1)=x(n)/2 se x(n) for par e x(n)=3x(n)+1 "
          "se x(n) for ímpar, sempre converge para o loop composto pelos "
          "elementos 4,2,1 (1*3+1=4 -> 4/2=2 -> 2/2=1 -> 1*3+1=4 -> ...)\n\n";

  // Abrindo um arquivo para estocar os dados altere o nome do arquiv caso
  // queira executar mais de uma simulação
  fstream arquivo;
  arquivo.open ("3to1.txt", ios::out | ios::app);
  if (arquivo.is_open ())
    cout << "OK!\n\n";
  // Variáveis usadas no programa
  long long int valor, contador;
  long long int *ponteiro = (long long int *)malloc (sizeof (long long int));
  // Entrada de dados do usuário
  cout << "Digite um número inteiro maior que 1 para que possamos testar a "
          "conjectura 3n+1:\n";
  cin >> valor;
  contador = 0;
  arquivo << "Valor inicial: " << valor << ".\n";
  // Loop principal
  do
    {
      contador = contador + 1;

      switch (valor % 2)
        {
        case 0:
          {
            *ponteiro = valor / 2;
            break;
          };
        case 1:
          {
            *ponteiro = 3 * valor + 1;
            break;
          };
        };
      // Exibindo a sequência de resultados na tela e salvando o conteúdo no
      // arquivo
      cout << *ponteiro << "\n";
      arquivo << *ponteiro << "\n";
      // Atualizando a variável principal
      valor = *ponteiro;
    }
  while (valor != 1);
  cout << contador << " iterações até cair no loop principal\n";
  arquivo << "Número de iterações para alcançar o loop principal: " << contador
          << "\n";

  // Fechando o arquivo, limpando o cachê de memória e enecerrando o programa
  arquivo.close ();
  free (ponteiro);
  return 0;
}
