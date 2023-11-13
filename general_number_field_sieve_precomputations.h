//ESTE ARQUIVO CONTÉM AS ROTINAS QUE PRECOMPUTAM QUANTIDADES USADAS NA EXECUÇÃO DO ALGORITMO

//*********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef GENERAL_NUMBER_FIELD_SIEVE_PRECOMPUTATION_H
#define GENERAL_NUMBER_FIELD_SIEVE_PRECOMPUTATION_H
#include"general_number_field_sieve_class.h"//Depências necessárias estão inclusas aqui


//*********************************************************************************************************************************************************************
//MÉTODOS
//Função de seleção de polinômio e escolha da raíz m tal que f(m)=0 (mod n)
void general_number_field_sieve::polynomial_root_selection(){
//Variáveis locais
__int128_t n=number;
std::vector<__int128_t> f_polynomial_coefficients;
char number_string2[45];
__int128_t m_power=1;
int64_t i, j;

//Procedimentos
//Ajuste de variáveis
f_polynomial_coefficients.resize(0);
std::cout<<"Digite o valor da raiz do polinômio: ";
if(scanf("%s", number_string2)!=1)
return;
m=scanf128(number_string2);

//Calculando a expansão do número a ser fatorado na base m
while(m_power<number)
m_power*=m;
m_power/=m;

while(true){
f_polynomial_coefficients.push_back(n/m_power);
n%=m_power;
m_power/=m;

if(m_power<=0)
break;

if(m_power==m && n<m){
f_polynomial_coefficients.push_back(n);
break;
                     };

if(m_power==m && n==m){
f_polynomial_coefficients.push_back(1);
f_polynomial_coefficients.push_back(0);
break;
                      };

           };

//Ajuste do array de coeficientes do polinômio usado no algoritmo
f_polynomial.polynomial_coefficients=f_polynomial_coefficients;

//Ajuste do array de potências dom polinômio usado no algoritmo
f_polynomial.degree=f_polynomial.polynomial_coefficients.size()-1;
//Ajuste do array de potências
f_polynomial.polynomial_powers.resize(0);

//Definindo o array de potências do polinômio
for(i=f_polynomial.degree; i>=0; --i)
f_polynomial.polynomial_powers.push_back(i);


//Vamos computar também a derivada de f(x),f'(x)
f_derivative=polynomial_derivative(f_polynomial);


//TESTES USE UM // APÓS OS TESTES
//for(auto x:f_polynomial.polynomial_coefficients)
//printf128(x);
//for(auto y:f_polynomial.polynomial_powers)
//std::cout<<y<<" ";
//std::cout<<'\n';

//printf128(f_polynomial.evaluate_polynomial(m));
//printf128(f_polynomial.evaluate_polynomial(m)%number);
                        
                                                            };
//Função que define uma base racional de fatores primos
void general_number_field_sieve::set_rational_factor_base(){
//Recebendo input do usuário
std::cout<<"Digite um limitante para sua base racional de primos:";
std::cin>>factor_base_upper_bound1;

//Selecionando melementos para a base racional de primos
for(int64_t i=2; i<factor_base_upper_bound1; ++i){
if(is_int64_prime(i)==true)
rational_factor_base.push_back(i);
                                                 };

//TESTE USE UM // APÓS O MESMO
//for(auto x:rational_factor_base)
//printf128(x);
                                                           };

//Função que define uma base algébrica de fatores primos
void general_number_field_sieve::set_algebraic_factor_base(){
//Recebendo input do usuário
std::cout<<"Digite um limitante para sua base algébrica de primos:";
std::cin>>factor_base_upper_bound2;

//Variáveis locais
int64_t r;
int64_t i, j, k;

//Procedimento seleção de primos para a base algébrica
//Fatores primos
for(i=2; i<factor_base_upper_bound2; ++i){
if(is_int64_prime(i)==true)
algebraic_factor_base_p.push_back(i);
                                         };

//Inteiros congruentes via função polinomial
algebraic_factor_base_r.resize(0);

for(auto x:algebraic_factor_base_p){
for(j=2; j<factor_base_upper_bound2; ++j){
if((f_polynomial.evaluate_polynomial(j)%x)==0){
algebraic_factor_base_r.push_back(j);
break;
                                              };
                                         };
                                   };

//TESTE USE UM // APÓS O MESMO
//for(auto x1:algebraic_factor_base_p)
//printf128(x1);
//for(auto x2:algebraic_factor_base_r)
//printf128(x2);
                                                            };
//Função que define uma base quadrática de fatores primos
void general_number_field_sieve::set_quadratic_factor_base(){
//Variáveis locais
int64_t number_of_elements;
int64_t i, j;

//Procedimentos
//Ajuste de variáveis
std::cout<<"Digite quantos elementos serão usados em sua base quadrática de primos:";
std::cin>>number_of_elements;
quadratic_factor_base_p.resize(0);
quadratic_factor_base_r.resize(0);

//Coleta de números primos
for(i=factor_base_upper_bound2; ; ++i){
if(is_int64_prime(i)==true){
quadratic_factor_base_p.push_back(i);
number_of_elements--;
                           };

if(number_of_elements<1)
break;
                                      };

//Coleta de inteiros congruents
for(auto x:quadratic_factor_base_p){
for(j=2; ; ++j){
if((f_polynomial.evaluate_polynomial(j)%x)==0){
quadratic_factor_base_r.push_back(j);
break;
                                              };
               };
                                   };

//TESTE USE UM // APÓS O MESMO
//for(auto x1:quadratic_factor_base_p)
//printf128(x1);
//for(auto x2:quadratic_factor_base_r)
//printf128(x2);
                                                            };

//*********************************************************************************************************************************************************************
//FIM DO HEADER
#endif   
