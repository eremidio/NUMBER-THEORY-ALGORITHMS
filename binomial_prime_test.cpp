// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE BINOMIAL PARA TESTAR SE UM
// NÚMERO É PRIMO OU NÃO COMPILAR ESTE PROGRAMA COM O COMANDO:g++ -o
// binomial_prime_test binomial_prime_test.cpp

/*

O TESTE DE PRIMALIDADE BINOMIAL É BASEADO NA SEGUINTE PROPOSIÇÃO:
PARA TODO NÚMERO PRIMO p, TÊM-SE: (x+a)^p= (x^p)+(a^p) mod(n).

COMO EXEMPLO:
(x+a)² = x²+2ax+a² = x²+ a² mod(2), [ 2 É PRIMO]
(x+a)³ = x³+3ax² +3a²x+a³ = x³ + a³ mod(3) [3 É PRIMO]
(x+a)⁴ = x⁴+4ax³+6a²x²+4ax³+a⁴= x⁴+2a²x²+a⁴ mod(4) [4 NÃO É PRIMO]

NESTA IMPLEMENTAÇÃO USAREMOS CONVOLUÇÃO PARA CALCULAR OS TERMOS DA EXPANSÃO EM
POTÊNCIAS DE n {1,1}x{1,1}={1x1, 1x1+1x1, 1x1}={1,2,1} {1,2,1}x{1,1}={1x1,
1x1+2x1, 2x1+1x1, 1x1}={1, 3, 3, 1} {1, 3, 3, 1}x{1,1}={1x1, 1x1+3x1, 3x1+3x1,
3x1+1x1, 1x1}={1, 4, 6, 4, 1}

ALGUNS TESTE PRELIMINARES PODEM SER USADOS PARA TESTAR A PRIMALIDADE DOS
NÚMEROS DE ANTEMÃO. E OUTRAS OUTRAS OTIMIZAÇÕES COMO NÃO CALCULAR TODOS OS
TERMOS DA EXPANSÃO PODEM SER FEITOS. (POR SIMETRIA APENAS METADE DOS
COEFICIENTES+2 NECESSITAM SER CALCULADOS, POIS A CADA ITERAÇÃO 1 ELEMENTO A
MAIS NECESSITA SER CALCULADO.)


ESTE ALGORITMO NÃO FOI TESTADO PARA EFICIÊNCIA.
ESTIMA-SE PORÉM UM COMPLEXIDADE PARA UM DADO INPUT n DA ORDEM O(n²) E REQUER UM
ESPAÇO AUXILIAR O(n). É INSPIRADO NO TESTE DE PRIMALIDADE AKS.

*/

//***************************************************************************************************************************
// CABEÇALHO
#include <assert.h>
#include <cmath>
#include <iostream>
#include <stdint.h>
#include <vector>
using namespace std;

//***************************************************************************************************************************
// FUNÇÕES
// Calculando a n-ésima linha do trângulo de Pascal, usando recursão a n-ésima
// linh será obtida a partirda (n-1)-ésima linha
vector<uint64_t>
get_nth_line (uint64_t n)
{
  // Variáveis locais
  vector<uint64_t> current_line;
  // Adicionandoo primeiro elemento da linha atual
  current_line.push_back (1);

  // Caso base
  if (n == 0)
    return current_line;

  // Definindo os demais elementos recursivamente
  vector<uint64_t> previous_line = get_nth_line (n - 1);

  for (uint64_t i = 1; i < previous_line.size (); ++i)
    current_line.push_back (previous_line[i] + previous_line[i - 1]);

  // Adicionando o último elemento da linha atual
  current_line.push_back (1);

  // Resultado
  return current_line;
};

// Teste de primalidade
bool
binomial_test (uint64_t n)
{
  // Variáveis locais
  vector<uint64_t> coefficient_vector = get_nth_line (n);
  uint64_t i;

  // TESTE
  // for(i=0; i<coefficient_vector.size(); ++i)
  // cout<<coefficient_vector[i]<<" ";
  // cout<<"\n";

  // Teste de primalidade
  for (i = 1; i < (coefficient_vector.size () / 2) + 1; ++i)
    {
      if (coefficient_vector[i] % n > 0)
        return false;
    };
  return true;
};

//***************************************************************************************************************************
// FUNÇÃO PRINCIPAL
int
main ()
{
  // Variáveis locais
  uint64_t n;
  // Procedimento
  cout << "Digite um número inteiro positivo: ";
  cin >> n;
  // Testando a primalidade do número em questão
  if (binomial_test (n) == true)
    cout << "O número " << n << " é primo.\n";
  else
    cout << "O número " << n << " não é primo.\n";

  // Finalizando a aplicação
  return 0;
}
