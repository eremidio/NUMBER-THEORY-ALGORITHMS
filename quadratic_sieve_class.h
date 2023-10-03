//ESTE ARQUIVO CONTERÁ A CLASSE COM MEMBROS E MÉTODOS USADOS PARA IMPLEMENTAR O ALGORITMO DA PENEIRA QUADRÁTICA

/*
O ALGORITMO DA PENEIRA QUADRÁTICA É ASSINTOTICAMENTE O SEGUNDO MÉTODO MAIS EFICIENTE PARA FATORAR NÚMEROS INTEIROS E O MAIS RÁPIDO PARA NÚMEROS COM MENOS DE 100 DIGITOS
DECIMAIS (POSSUI A MESMA COMPLEXIDADE DO QUE O MÉTODO DE CURVAS ELÍPTICAS, PORÉM USA APENAS OPERAÇÕES ELEMENTARES DE PRECISÃO SIMPLES EM SUA EXECUÇÃO).

O ALGORITMO USA UM CONJUNTO DE POLINÔMIOS DO SEGUNDO GRAU PARA PRODUZIR NÚMEROS QUE SATISFAZEM A RELAÇÃO: b(N) = a²(N) (mod n), N=1,2,... onde n É O NÚMERO A SER FATORADO. OS NÚMEROS b(N) SÃO REQUERIDOS SEREM SUAVES (COMPLETAMENTE FATORADOS) EM RELAÇÃO A UMA BASE DE NÚMEROS PRIMOS p(i), i=0,1,...; PREVIAMENTE SELECIONADA USANDO O
CRITÉRIO DE EULER n^((p-1)/2) = 1 (mod n), O QUE IMPLICA QUE O SÍMBOLO DE LEGENDRE SATISFAZ (n|p)=1.

UMA MATRIZ AUXILIAR (mod 2) É PRODUZIDA COM A EXPANSÃO DOS NÚMEROS b(N) É GERADA E USADA PARA DETERMINAR UM PRODUTO DE b(N) QUE É UM QUADRADO PERFEITO Q=q², DESTA FORMA
AO FINAL DO ALGORITMO UMA RELAÇÃO DO TIPO: q²=a² (mod n) É PRODUZIDA, ONDE a PODE SER IGUAL A UM OU IGUAL AO PRODUTO DE VÁRIOS a(N)'s. AS RELAÇÕES mmc(|q-a|, n) E
mmc(q+a, n) POSSUEM GRANDE CHANCEDE PRODUZIR FATORES NÃO TRIVIAIS DOS NÚMEROS A SEREM FATORADOS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Quadratic_sieve#cite_note-1


*/


//**********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef QUADRATIC_SIEVE_H
#define QUADRATIC_SIEVE_H
#include"int128.h"
#include"mod_bin_exponentiation128.h"
#include"quadratic_sieve_auxiliary_functions.h"
#include"matrix.h"
#include<stdint.h>
#include<stdio.h>
#include<inttypes.h>
#include<vector>
#include<cmath>

//**********************************************************************************************************************************************************************
//CLASSE DO ALGORITMO
class quadratic_sieve{
public:
//*****************************
//Membros da classe
//Input e output do algoritmo
__int128_t number;
__int128_t factor1, factor2;

//Base de primos 
int64_t smoothness_bound;
std::vector<int64_t> prime_base;

//Variável usadas para checar se umnúmero é quadrado perfeito
__int128_t number_square_root;
bool perfect_square;

//Matrizes e vetores usados no processo de peneira
int64_t sieve_interval;
std::vector<int64_t> prime_expansion_vector;
std::vector<__int128_t> a_squared_vector, b_vector;
int64_t dimension;
Matrix<int> parity_matrix, transpose_parity_matrix, reduced_matrix, linear_dependence_vector;
int linear_vector1[13] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
int linear_vector2[13] = {0, 1, 2, 4, 6, 10, 12, 16, 18, 22, 28, 30, 36};
bool sieve_complete;

//Matrizes e vetores usados no processo de seleção de candidatos as relações constitutivas
Matrix<int> check_vector, congruence_vector;
int64_t selection_tester;

//Variáveis usadas no cálculo de fatores primos
bool selection_square;
__int128_t a, b, a_squared, b_squared;


//*****************************
//Métodos da classe

//Funções de uso geral
void run();//Função principal (esta função também cuidará das entradas de dados pelo usuário)
void print_result();//Função que printa o resultado do algoritmo

//Funções relacionadas a base de primos usadas no algoritmo
void set_prime_base();//Função que calcula uma base números primos a serem usados no algoritmo

//Funções relacionadas ao processo de peneira
void sieving_algorithm();//Função que realiza a peneira de números suaves em relação a base de primos
void build_matrices();//Função que calcula as matrizes usadas na parte do algoritmo que envolve álgebra linear

//Funções usadas para encontrar relações de congruências do tipo b²=a² (mod n)
void generate_check_vector(int64_t);
void congruence_finder_algorithm();

//Função que calcula fatores primos do número em questão
void factors_calculation();
                     };


//**********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
