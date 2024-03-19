//VAMOS IMPLEMENTAR ROTINAS AUXILIARES USADAS NO ALGORITMO DE FATORAÇÃO VIA CURVAS ELÍPTICAS
/*
NOTA: Usaremos inteiros de 64 bits nas pré-computação de primos usados no algoritmo, a aritmética em curvas elípticas será feita usando-se inteiros de 512 bits para
evitar overflow.

*/

//********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef MONTGOMERY_ELLPITIC_CURVE_FACTORIZATION_AUXILIARY_FUNCTIONS_H
#define MONTGOMERY_ELLPITIC_CURVE_FACTORIZATION_AUXILIARY_FUNCTIONS_H
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/cstdint.hpp>
#include<vector>
#include<stdint.h>
#include<cmath>
#include<random>
using namespace boost::multiprecision;


//********************************************************************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
bool fast_prime_checking(uint64_t);
void fill_prime_buffer(std::vector<uint64_t>&, uint64_t);
void fill_prime_buffer(std::vector<uint64_t>&, uint64_t, uint64_t);
int512_t euclides_algorithm(int512_t, int512_t);
uint64_t euclides_algorithm(uint64_t, uint64_t);
int64_t generate_random_number();
void extract_bits(std::vector<int8_t>&, int512_t);

//Funções que definem a aritmética de em curvas elípticas na parametrização de Montgomery usando coordenadas projetivas
void pointwise_doubling(int512_t&, int512_t&, int512_t, int512_t);
void pointwise_addition(int512_t&, int512_t&, int512_t, int512_t, int512_t, int512_t, int512_t, int512_t);
void pointwise_scalar_multiplication(int512_t&, int512_t&, int512_t, int512_t, int512_t);

//********************************************************************************************************************************************************************
//FUNÇÕES
//Função que determina se um inteiro de 64 bits é primo ou não usando uma otimização 30k+1
bool fast_prime_checking(uint64_t n){
//Casos triviais: primos menores que 30
if(n==2 || n==3 || n==5 || n==7 || n==11 || n==13 || n==17 || n==19 ||n==23 || n==29)
return true;

//Variáveis locais
uint64_t i;
uint64_t limit = std::sqrt(n);
uint64_t divisors[8]={1, 7, 11, 13, 17, 19, 23, 29};//Números coprimos com 30 no intervalo 1,...,30

//Procedimentos
//Teste de divisão por 2, 3, 5
if((n%5)==0 || (n%3)==0 || (n%2)==0)
return false;

//Loop principal
//1º iteração
for(i=1; i<8; ++i){
if((n%divisors[i])==0)
return false;
                  };

//Demais interações
while(divisors[7]<limit){
//Atualizando variáveis
for(i=0; i<8; ++i)
divisors[i]=divisors[i]+30;

//Testando possíveis divisores
for(i=0; i<8; ++i){
if((n%divisors[i])==0)
return false;
                  };

                       };

//Caso o número passe nos testes acima
return true;
                                    };

//Função que preenche um buffer de primos até um determinado valor
void fill_prime_buffer(std::vector<uint64_t>& prime_vector, uint64_t upper_bound, uint64_t lower_bound){
//Variáveis locais
uint64_t i;

//Procedimentos
//Ajuste de variáveis
prime_vector.resize(0);

//Prrenchendo o buffer de primos
for(i=lower_bound; i<=upper_bound; ++i){
if(fast_prime_checking(i)==true)
prime_vector.push_back(i);
                                       };
                                                                                                       };

void fill_prime_buffer(std::vector<uint64_t>& prime_vector, uint64_t upper_bound){
//Variáveis locais
uint64_t i;

//Procedimentos
//Ajuste de variáveis
prime_vector.resize(0);

//Prrenchendo o buffer de primos
for(i=2; i<=upper_bound; ++i){
if(fast_prime_checking(i)==true)
prime_vector.push_back(i);
                             };
                                                                                 };
//Função que implementa o algoritmo de euclides para inteiro de 512 bits
int512_t euclides_algorithm(int512_t a, int512_t  b){
if(b==0)
return a;
else
return euclides_algorithm(b, a%b);
                                                    };

uint64_t euclides_algorithm(uint64_t a, uint64_t b){
if(b==0)
return a;
else
return euclides_algorithm(b, a%b);
                                                  };

//Função usada para se gerar um número inteiro aleatório da ordem 64 bits 
int64_t generate_random_number(){
//Variáveis locais
int64_t result;
const int64_t limit=100000000000000000;

//Procedimentos
//Ajuste da distribuição de números aleatórios
std::random_device generator_x;
std::mt19937 gen(generator_x());
std::uniform_int_distribution<int64_t> elliptic_distribution(1, limit);

//Resultado
result=elliptic_distribution(generator_x);
return result;
                                };

//Função extrai os bits de um inteiro de 512 bits e o aloca em um vetor
void extract_bits(std::vector<short>& bit_vector, int512_t n){
//Procedimentos
//Ajuste de variáveis
bit_vector.resize(0);

//Extraindo os bits 
while(n>0){
if(n&1)
bit_vector.push_back(1);
else
bit_vector.push_back(0);
n>>=1;
          };
                                                             };

//****************************************************************************************************************************************************************
//ARITMÉTICA DE CURVAS ELÍPITICAS: 'a' é o parâmetro que define a curva e 'n' é o número a ser fatorado
//Função que a partir de um ponto P=(x:y:z) computa [2]P=P+P
void pointwise_doubling(int512_t& x_point, int512_t& z_point, int512_t a, int512_t n){
//Variáveis locais
int512_t x_temp=x_point;
int512_t z_temp=z_point;

//Procedimentos
x_point = ((x_temp*x_temp)-(z_temp*z_temp))*((x_temp*x_temp)-(z_temp*z_temp));
z_point = (4*z_temp)*((x_temp*x_temp*x_temp)+(a*x_temp*x_temp*z_temp)+(x_temp*z_temp*z_temp));

x_point=(x_point%n);
z_point=(z_point%n);
                                                                                     };


//Função que adiciona dois pontos na curva P=(xp:yp:zp) e Q=(xq:yq:zq) --> R=(xr:yr:zr)
void pointwise_addition(int512_t& x_result, int512_t& z_result, int512_t x1, int512_t z1, int512_t x2, int512_t z2, int512_t x3, int512_t z3, int512_t n){
//Procedimentos
x_result = z3*((x1*x2)-(z1*z2))*((x1*x2)-(z1*z2));
z_result = x3*((x1*z2)-(x2*z1))*((x1*z2)-(x2*z1));
x_result=(x_result%n);
z_result=(z_result%n);
                                                                                                                                                         };


//Função que multiplica dois pontos na curva por um escalar[k]P=P+...+P (k vezes)
void pointwise_scalar_multiplication(int512_t& x_result, int512_t& z_result, int512_t x_point, int512_t z_point, int512_t scalar_factor, int512_t a, int512_t n){
//Variáveis locais
std::vector<short> bit_vector;
int512_t u, v, u1, v1, t, w, t1, w1;

//Procedimentos
if(scalar_factor==1){
z_result=z_point;
x_result=x_point;
return;
                    }
else if(scalar_factor==2){
z_result=z_point;
x_result=x_point;
pointwise_doubling(x_result, z_result, a, n);
return;
                         }
else if(scalar_factor>2){
//Ajuste de variáveis
extract_bits(bit_vector, scalar_factor);
u=x_point;
v=z_point;
t=x_point;
w=z_point;
pointwise_doubling(t, w, a, n);

//Loop principal
for(int i=(bit_vector.size()-2); i>=0; --i){
if(bit_vector[i]==1){
u1=u;
v1=v;
pointwise_addition(u, v, t, w, u1, v1, x_point, z_point, n);
pointwise_doubling(t, w, a, n);
                    };

if(bit_vector[i]==0){
t1=t;
w1=w;
pointwise_addition(t, w, u, v, t1, w1, x_point, z_point, n);
pointwise_doubling(u, v, a, n);
                    };

                                           };
x_result=(u%n);
z_result=(v%n);
                        };
                                                                                                                                                                };


//********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
