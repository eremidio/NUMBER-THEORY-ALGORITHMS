//VAMOS CRIAR UM PROGRAMA EM C QUE IMPLEMENTA O ALGORITMO DE SHOR PARA FATORIZAR NÚMEROS INTEIROS

//ESTE PROGRAMA NEM SEMPRE PRODUZ UM RESULTADO DESEJADO, DE FATO O ALGORITMO USA NÚMEROS ALEÁTÓRIOS EM SUA IMPLEMENTAÇÃO.
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o shor_factorization shor_factorization.c -lm

/*
O ALGORITMO DE SHOR É EXECUTADO NAS SEGUINTES ETAPAS:
1. DADO UM NÚMERO n A SER FATORADO, TESTA-SE PRIMEIRO SE n É PAR. NESTE CASO UMA DECOMPOSIÇÃO É DADA POR: (n, n/2) E O
ALGORITMO SE ENCERRA.
2. SELECIONA-SE UM NÚMERO ALEATÓRIO x ENTRE 2 E n.
3. É TESTADO SE x É UM DIVISOR DE n. CASO POSITIVO FATORES DE n FORAM ENCONTRADOS E O ALGORITMO SE ENCERRA.
4. ENCONTRA-SE UM EXPOENTE r (A ORDEM MULTIPLICATIVA DE x MÓDULO n DENOTADA POR ord(x) mod n) TAL QUE (x^r)≡1 mod(n);
4. SE (x^(r/2)+1) NÃO FOR ZERO, OS FATORES PRIMOS SÃO DADOS POR mdc((x^(r/2)+1), n) E mdc((x^(r/2)-1), n), ONDE mdc DENOTA O
MÁXIMO DIVISOR COMUM QUE É ENCONTRADO VIA ALGORITMO DE EUCLIDES.

ESTE ALGORITMO SÓ É COMPUTACIONALMENTE VANTAJOSO PARA FATORAR NÚMEROS MUITO GRANDES.
COM O ADVENTO DA COMPUTAÇÃO QUÂNTICA SE ESPERA QUE NOVAS IMPLEMENTAÇÕES DESTE ALGORITMO FUNCIONEM DE FORMA EFICAZ.
DE FATO OS PASSOS DESCRITOS ACIMA REPRESENTAM A PARTE CLÁSSICA DO ALGORITMO. O ASPECTO MAIS COMPUTACIONALMENTE DISPENDIOSO É
CALCULAR r NO PASSO 4. NA COMPUTAÇÃO QUÂNTICA A IDEIA É USAR TRANSFORMADA DE FOURIER E SUPERPOSIÇÃO DE ESTADOS QUÂNTICOS EM 
ESPAÇOS DE HILBERT PARA DETERMINAR ord(x) mod n DE FORMA EFICAZ.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Shor%27s_algorithm

*/

//CABEÇALHO
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>
#include<time.h>

//FUNÇÕES
//Função que usa um gerador de números para gerar um número usado no teste do algoritmo de Shor
uint64_t generate_key(uint64_t value) {
  //Semente para geração de números aleatórios
  srand(time(NULL));

  //Variáveis locais
  uint64_t key;
  key = 2 + rand() % value - 2;
  return key;
};

//Algoritmo de Euclides
uint64_t euclides_check(uint64_t a, uint64_t b) {
  //Procedimentos
  if (b == 0)
    return a;
  else
    return euclides_check(b, (a%b));
};

//Função que calcula um expoente do algoritmo de Shor
uint64_t get_exponent(uint64_t number1 /*semente aleatória*/ , uint64_t number2 /*número a ser fatorado*/ ) {
  //Variáveis locais
  uint64_t residue;
  uint64_t exponent;
  uint64_t temp;

  //Caso geral
  for (int i = 1; i < 10000000; ++i) {
    temp = pow(number1, i);
    residue = temp % number2;

    if (residue == 1 && (i % 2) == 0) {
      exponent = i;
      break;
    };

  };

  return exponent;
};

//Algoritmo de Shor
void shor_algorithm(uint64_t shor_int) {
  //Variáveis locais
  int counter = 0;
  uint64_t shor_factor1, shor_factor2, shor_exponent, shor_random, shor_test;

  //Testando se o número a ser fatorado é par
  if ((shor_int % 2) == 0) {
    shor_factor1 = 2;
    shor_factor2 = shor_int / 2;
    printf("Fator1:%li.\nFator2:%li.\n", shor_factor1, shor_factor2);
    return;
  };

  //Testando se um fator primo já foi encontrado
  step1:
    counter++;
  if (counter > 15000000) {
    printf("Algoritmo falhou.\n");
    return;
  };
  //O número gerado aleatoriamente deve ser coprimo com o número a ser fatorado
  shor_random = generate_key(shor_int);
  if (euclides_check(shor_random, shor_int) != 1)
    goto step1;

  if ((shor_int % shor_random) == 0) {
    shor_factor1 = shor_random;
    shor_factor2 = shor_int / shor_random;
    printf("Fator1:%li.\nFator2:%li.\n", shor_factor1, shor_factor2);
    return;
  };

  //Prosseguindo com o teste
  //Calculando o expoente 
  shor_exponent = get_exponent(shor_random, shor_int);
  if (shor_exponent == 0)
    goto step1;

  //Testando a fatorização do número de interesse
  step2:
    shor_test = pow(shor_random, (shor_exponent) / 2) + 1;
  if (shor_test == 0)
    goto step1;

  shor_factor1 = euclides_check(shor_test, shor_int);
  shor_test = pow(shor_random, (shor_exponent) / 2) - 1;
  shor_factor2 = euclides_check(shor_test, shor_int);

  //Exibindo o resultado
  printf("Fator1:%li.\nFator2:%li.\n", shor_factor1, shor_factor2);

};

//FUNÇÃO PRINCIPAL
int main() {
  //Variáveis
  uint64_t number;

 
 //Procedimentos
  //Recebendo input do usuário
  printf("Digite un número inteiro para que fatores deste número seja calculado.\n->");
  scanf("%li", & number);

  //Calculando os fatores do número a ser decomposto
  shor_algorithm(number);

  //Finalizando a aplicação
  return 0;
}
