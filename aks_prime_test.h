// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE PRIMALIDADE AKS

/*
O TESTE DE PRIMALIDADE AKS É O TESTE DE PRIMALIDADE MAIS EFICIENTE PARA SE
TESTAR A PRIMALIDADE DE NÚMEROS GRANDES. É O ÚNICO TESTE QUE TEM TEMPO DE
EXECUÇÃO POLINOMIAL INDEPENDENTEMENTE DO NÚMERO A SER TESTADO, ALÉM DISSO A
PROVA DO TESTE EM QUESTÃO INDEPENDE DE FATOS AINDA NÃO PROVADOS MATEMATICAMENTE
COMO A HIPÓTESE DE RIEMANN.

O TESTE BASEIA-SE NA SEGUINTE IDENTIDADE (x+a)^n (mod n)=(x^n)+a PARA n PRIMOS.
ENQUANTO ESTA RELAÇÃO CONSITITUI UM TESTE DE PRIMALIDADE EM SI.
COMPUTANCIONALMENTE ELA NÃO É VIÁVEL, POIS O NÚMERO DE TERMOS CRESCE
EXPONENCIALMENTE COMO VALOR DE n. ESCOLHENDO UM VALOR DE r ADEQUADO ESCREVEMOS
(x+a)^n = f(x)q(x)+r(x), ONDE f(x), q(x), r(x) SÃO POLINÔMIOS E r(x) TEM GRAU
(r-1). O TESTE SE REDUZ ENTÃO A TESTES SOBRE OS COEFICIENTES DE r(x). ALGUNS
TESTES ADICIONAIS SÃO PERFORMADOS ENVOLVENDO A ORDEM MULTIPLICATIVA DE n PARA
DETECTAR A PRIMALIDADE DO NÚMERO EM QUESTÃO.

ESTE TESTE NÃO É MUITO PRÁTICO PARA NÚMEROS USADOS EM CONTEXTOS PRÁTICOS COMO
EM CRIPTOGRAFIA, EMBORA SEJA O MAIS EFICIENTE ASSINTOTICAMENTE. TESTES COMO O
TESTE DE CURVAS ELÍPTICAS PRODUZEM CERTIFICADOS DE PRIMALIDADE MAIS RAPIDAMENTE
PARA NÚMEROS ATÉ ESTA ORDEM DE MAGNITUDE. PARA NÚMEROS DE ATÉ 64 BITS O TESTE
DE BAILLIE-PSW E O TESTE DE MILLER RABIN FORNECEM RESULTADOS PRECISOS VÁRIAS
ORDENS DE MAGNITUDE MAIS RÁPIDO.

O ARTIGO ORIGINAL ESTÁ DISPONÍVEL EM:
https://doi.org/10.4007/annals.2004.160.781

PARA MAIORES INFORMAÇÕES:https://en.wikipedia.org/wiki/AKS_primality_test
                         https://medium.com/@sibu.it13/aks-primality-test-f184cf6365a1
                         https://cs.stackexchange.com/questions/23260/when-is-the-aks-primality-test-actually-faster-than-other-tests/23360#23360
                         https://tabidots.github.io/2019/04/number-theory-in-clojure-aks-primality-test#the-crazy-polynomial-part

*/

//**********************************************************************************************************************************************************************
// CABEÇALHO
#ifndef AKS_PRIME_TEST
#define AKS_PRIME_TEST
#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <gmp.h>

//**********************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
uint64_t mul_mod(uint64_t, uint64_t, uint64_t);
uint64_t pow_mod(uint64_t, uint64_t, uint64_t);
uint64_t multiplicative_order(uint64_t, uint64_t);
uint64_t gcd_u64(uint64_t, uint64_t);
uint64_t binomial_coefficient(uint64_t, uint64_t, uint64_t);

bool power_prime_test(uint64_t);
uint64_t lowest_multiplicative_order(uint64_t);
bool trial_division(uint64_t, uint64_t);
bool polinomial_test(uint64_t, uint64_t);
bool aks_primality_test(uint64_t);

//**********************************************************************************************************************************************************************
// FUNÇÕES AUXILIARES
/*
Para maiores informações:
https://en.wikipedia.org/wiki/Modular_arithmetic#Example_implementations
*/

// Função que calcula uma relação do tipo a*b (mod m)
uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t m) {
  // Variáveis locais
  long double x;
  uint64_t c;
  int64_t r;

  // Procedimentos
  if (a >= m) a %= m;
  if (b >= m) b %= m;
  x = a;
  c = x * b / m;
  r = (int64_t)(a * b - c * m) % (int64_t)m;
  return r < 0 ? r + m : r;
};

// Função que calcula uma relação do tipo a^b (mod m)
uint64_t pow_mod(uint64_t a, uint64_t b, uint64_t m) {
  // Variáveis  locais
  uint64_t r = m == 1 ? 0 : 1;

  // Procedimentos
  while (b > 0) {
    if (b & 1) r = mul_mod(r, a, m);
    b = b >> 1;
    a = mul_mod(a, a, m);
  };

  // Resultado
  return r;
};

// Função que calcula a ordem multiplicativa de um inteiro
uint64_t multiplicative_order(uint64_t a, uint64_t n) {
  // Variáveis locais
  uint64_t power, i;
  uint64_t limit = (log2(n) * log2(n));
  uint64_t limit2 = (log2(n) * log2(n) *log2(n) * log2(n) * log2(n))+1;

  // Procedimentos
  for (i = (limit+1); i <limit2; ++i) {
    power = pow_mod(a, i, n);
    if (power == 1) return i;
  };

  // Caso o teste acima falhe
  if(pow_mod(a, (n-1), n))
    return (n-1);
  else return 0;

};


//Função que implementa o algoritmo de Euclides
uint64_t gcd_u64(uint64_t a, uint64_t b){

  if(b==0) return a;
  else return gcd_u64(b, (a%b));

};


// Função que calcula um coeficiente binomial a menos de uma congruência
/* 
NOTA: usaremos a biblioteca gmp, normalmente disponíveis em sistemas Unix
      para evitar integer overflow e testar números de maior magnitude.
      A biblioteca GMP deve estar instalada para se usar este programa.
      Consultar tutoriais online se necessário. 
      
*/
uint64_t binomial_coefficient(uint64_t n, uint64_t k, uint64_t m) {

  //Restrições
  if (k > n) return 0; // C(n, k) is 0 se k > n
  if (k > n / 2) k = n - k; //Explorando a propriedade de simetria dos coefficientes

  //Inicializando variáveis locais
  mpz_t result;
  mpz_init(result);
  mpz_set_ui(result, 1); 


  //Procedimentos
    //Loop principal: Cálculando C(n, k), usaremos que C(n, k+1)= C(n,k)[(n-k)/(k+1)]
    for (unsigned long i = 0; i < k; i++) {
        mpz_mul_ui(result, result, n - i);
        mpz_divexact_ui(result, result, i + 1);
        mpz_mod_ui(result, result, m);
    }


  //Limpando o cachê de memória e retornando o resultado final
  uint64_t final_result = mpz_get_ui(result); 
  mpz_clear(result); 
  return final_result;
}

//**********************************************************************************************************************************************************************
// FUNÇÕES
// Função que testa se n é da forma a^b
bool power_prime_test(uint64_t n) {
  // Variáveis locais
  uint64_t max_power = log2(n);
  uint64_t sqrt_n = sqrt(n);
  uint64_t tester;

  // Procedimentos
  // Loop principal
  for (uint64_t i = 3; i <= sqrt_n; i += 2) {
    tester = i;
    for (uint64_t j = 1; j < max_power; j++) {
      tester *= i;

      if (tester == n) return false;  // O número em questão não é primo

      if (tester > n) break;
    };
  };

  // Resultado caso o número passe no teste acima
  return true;
};

// Função que calcula o menor r tal que a ordem multiplicativa de Ord(n) (mod r)>4log2(n²)
uint64_t lowest_multiplicative_order(uint64_t n) {
 
  // Váriáveis
  uint64_t ord = multiplicative_order(2, n), tester;
  uint64_t limit = (4*log2(n) * log2(n) * log2(n));
  uint64_t limit2 = sqrt(n);
  uint64_t i;

  // Procedimentos
  // Loop principal
  for (i = 3; i < limit2; i++) {
    if (gcd_u64(n, i) == 1) tester = multiplicative_order(i, n);
    if (tester < ord) ord = tester;
  };
  // Resultado
  return ord;
};

// Função que determina se n é divisível por algum fator no intervalo (2, min{Ord(n), (n-1)})
bool trial_division(uint64_t n, uint64_t ord) {

  // Variáveis locais
  uint64_t upper_bound=((n-1)>ord)?ord:(n-1);

  //Procedimentos
    // Teste da divisão
    for (uint64_t i = 2; i <= upper_bound; i++) {
      if ((n%i)==0) return false;
    };

  // Caso o número a ser testado passe no teste acima
  return true;
};

// Função que testa a relação de congruência (x+a)^n = x^n+a (mod [x^r-1], n)
/*
NOTA: Estritamente o algoritmo requer que sejam testados valores no intervalo 2≲ a ≲ (√φ(r))log₂(n).
Porém,certas conjecturas ainda não comprovadas postulam que o teste com a=1 é suficiente para
produzir resultados corretos.
*/

bool polinomial_test(uint64_t n, uint64_t r) {

  // Variáveis locais
  uint64_t i, j, counter = 0, polynomial_coefficient;

  // Procedimentos
  // Loop principal (i conta o número de termos no polinômio resto [1, ...,  r], j são os indexes usados no cálculo dos coefficientes)
  for (i = 0; i < n; ++i) {
    // Ajuste de variáveis
    polynomial_coefficient = 0;

    // Computando o termo do resto da divisão por  x^r-1, reduzindo módulo via adição os coeficientes binomiais de (x+a)^n
    for (j = i; j < n; j += r){
      polynomial_coefficient = polynomial_coefficient + binomial_coefficient(n, j, n);
      if(polynomial_coefficient>n) polynomial_coefficient%=n;
    }

    // Condição que verifica se um número é composto
    if (polynomial_coefficient > 0 && i > 0) return false;
    if (polynomial_coefficient != 1 && i == 0) return false;

    // Fim do teste
    counter++;
    if (counter == r) break;
  };

  // Caso o número testado passe no teste acima
  return true;
};


// Função que implementa o teste de primalidade AKS (Agrawal-Kayal-Saxena)
bool aks_primality_test(uint64_t n) {
  // Caso trivial: primos inferiores a 100
  if (n < 2) return false;

  uint64_t prime_seed[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
  for(int i=0; i<25; ++i){
    if(n==prime_seed[i]) return true;
    if((n%prime_seed[i])==0) return false;
  }

  // Teste 1: checando se o número é da forma a^b
  if (power_prime_test(n) == false) return false;

  // Etapa 2: calculando a menor ordem multiplicativa para o número em questão
  uint64_t ord = lowest_multiplicative_order(n);

  // Testes 2 e 3: testes envolvendo a ordem multiplicativa do número em questão
  if (ord ==0 || ord>=n) return true;
  if (trial_division(n, ord) == false) return false; 

  //if(ord>=sqrt(n)) return true;   /*CONDIÇÃO DE SUFICIÊNCIA PARA TESTAR A PRIMALIDADE DE n*/

  // Teste 4: Checando a relação de congruência (x+a)^n = x^n+a (mod [x^r-1], n) para a=1
  if (polinomial_test(n, ord) == false) return false;

  // Caso o número passe nos testes acima sua primalidade está provada
  return true;
};

//**********************************************************************************************************************************************************************
// FIM DO HEADER
#endif
