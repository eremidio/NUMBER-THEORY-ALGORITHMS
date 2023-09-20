//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UM ALGORITMO PARA FATORAR INTEIROS GAUSSIANOS

/*
NOTA: NO PRESENTE ALGORITMO O RESULTADO FICA DEFINIDO A MENOS DE UMA CONSTANTE MULTIPLICATIVA (-1), i, (-i).

PARA EXEMPLOS, CONSULTAR: https://en.wikipedia.org/wiki/Table_of_Gaussian_integer_factorizations# 

*/

//**********************************************************************************************************************************
//CABEÇALHO
#ifndef GAUSSIAN_FACTORIZATION_H
#define GAUSSIAN_FACTORIZATION_H
#include"complexification.hpp"
#include"gaussian_prime_test.hpp"
#include"gaussian_euclidean_division.hpp"
#include"complex_numbers.hpp"
#include<stdint.h>
#include<cmath>
#include<vector>

//**********************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool perfect_square_checker(int64_t);
void sum_of_squares(int64_t, int64_t&, int64_t&);
void factoring(std::vector<int64_t>&, int64_t);
void gaussian_factorization(complex<int64_t>);

//**********************************************************************************************************************************
//FUNÇÕES
//Função que verifca se um inteiro é um quadrado perfeito
bool perfect_square_checker(int64_t n){
//Variáveis locais
int64_t odd=1;

//Procedimentos
//Loop principal
while(n>0){
n-=odd;
odd+=2;
if(n<0)
return false;
          };

return true;

                                      };

//Função que expressa um fator primo como a soma de quadrados
void sum_of_squares(int64_t n, int64_t& a, int64_t& b){
//Variáveis locais
int64_t limit=std::sqrt(n), b_squared;
//Procedimentos
for(a=1; a<limit; ++a){
b_squared= n-(a*a);
if(perfect_square_checker(b_squared)==true){
b=std::round(std::sqrt(b_squared));
return;
                                           };
                      };

                                                      };


//Função que calcula fatores de um inteiro e aloca os resultados em um vetor
void factoring(std::vector<int64_t>& prime_vector, int64_t n){
//Ajuste de variáveis
prime_vector.resize(0);

//Variáveis locais
int64_t i, limit=std::sqrt(n);
int64_t prime_seed[]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};

//Procedimentos
//Busca por fatores primos menores que 1000
for(auto x:prime_seed){
while(n%x==0){
prime_vector.push_back(x);
n/=x;
             };
if(n==1)
return;
                      };

//Busca por fatores maiores que 1000
for(auto i=1001; i<limit; i+=2){
while(n%i==0){
prime_vector.push_back(i);
n/=i;
             };
if(n==1)
return;

                               };
                                                             };

//Função que cálcula os fatores primos de um inteiro gaussiano a menos de uma constante multiplicativa -1, i, -i
void gaussian_factorization(complex<int64_t> z){
//Caso base z é primo
if(gaussian_prime_test(z)==true){
std::cout<<z.algebraic()<<'\n';
return;
                                };

//Variáveis  locais
int64_t gaussian_norm=(z.real*z.real)+(z.imag*z.imag);
std::vector<int64_t>prime_vector;
int64_t real_part, imag_part;
complex<int64_t> gaussian_gcd, gaussian_factor, prime_factor;
int64_t i, j;

//Procedimentos
//Calculando os fatores primos do número a ser fatorado
factoring(prime_vector, gaussian_norm);

//TESTE
//for(auto x:prime_vector)
//std::cout<<x<<" ";
//std::cout<<'\n';

//Calculando os fatores do número em questão
std::cout<<"Eis a sua lista de fatores primos a menos de uma constante multiplicativa (i, (-i) ou (-1)):\n";

for(auto x:prime_vector){
//Fatores 2
if(x==2)
std::cout<<"1+1i/(-i)(1-1i), ";

//Fator do tipo p = 3 (mod 4)
if((x%4)==3)
std::cout<<x<<", ";

//Fator do tipo p = 1 (mod 4)
if((x%4)==1){
//Expressando o fator em questão como a soma de quadrados
sum_of_squares(x, imag_part, real_part);

//Testando possíveis fatores
gaussian_factor.real=real_part;
gaussian_factor.imag=imag_part;

gaussian_gcd=gaussian_euclides_algorithm(z, gaussian_factor);

if(gaussian_gcd.real==0 || gaussian_gcd.imag==0)
gaussian_gcd=gaussian_euclides_algorithm(z, gaussian_factor.conj());

std::cout<<gaussian_gcd.algebraic()<<", ";

            };
                        };

//Finalizando a função
std::cout<<"...\n";
                                               };

//**********************************************************************************************************************************
//FIM DO HEADER
#endif

