//VAMOS CRIAR UM PROGRAMA COM ALGUNS ALGORITMOS ENVOLVENDO INTEIROS DE EISENSTEIN

/*
NOTA: O PRESENTE PROGRAMA PROVÊ O ALGORITMO DE EUCLIDES E O TESTE DE PRIMALIDADE DE INTEIROS DE EISENSTEIN.  A FATORAÇÃO DE INTEIROS DE EISENSTEIN É UM ALGORITMO MAIS
SOFISTICADO SE COMPARADO AO DOS INTEIROS E NÃO SERÁ IMPLEMENTADO.
*/

//**********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef EISENSTEIN_INTEGERS_NUMBER_THEORETICAL_ALGORITHMS_H
#define EISENSTEIN_INTEGERS_NUMBER_THEORETICAL_ALGORITHMS_H
#include"eisenstein_integers.hpp"

//**********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool trial_division(int64_t);
void factoring(std::vector<int64_t>&, int64_t);
void find_eisentein_coefficients(int64_t , int64_t&, int64_t&);

template<typename T>
bool is_eisenstein_prime(eisenstein_integer<T>);

template<typename T>
eisenstein_integer<T> gcd(eisenstein_integer<T>, eisenstein_integer<T>);

template<typename T>
void factorization(eisenstein_integer<T>);


//**********************************************************************************************************************************************************************
//FUNÇÕES

//---------------------------
//Função que testa a primalidade de um número usaremos uma otimização 30k+1
bool trial_division(int64_t n){
//Casos triviais primos menos que 100
if(n<2)
return false;

if(n==2 || n==3 || n==5 || n==7 || n==11 || n==13 || n==17 || n==23 || n==29)
return true;
if(n==31 || n==37 || n==41 || n==43 || n==47 || n==53 || n==59 || n==61 || n==67)
return true;
if(n==73 || n==73 || n==79 || n==83 || n==89 || n==97)
return true;


//Variáveis locais
int64_t i;
int64_t limit = std::sqrt(n);
int64_t divisors[8]={1, 7, 11, 13, 17, 19, 23, 29};//Números coprimos com 30 no intervalo 1,...,30

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


//---------------------------
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
if(n%x==0){
prime_vector.push_back(x);
while(n%x==0)
n/=x;
          };

if(n==1)
return;
                      };

//Busca por fatores maiores que 1000
for(auto i=1001; i<limit; i+=2){
if(n%i==0){
prime_vector.push_back(i);
while(n%i==0)
n/=i;
          };

if(n==1)
return;
                               };
                                                             };


//---------------------------
//Função que dada uma norma em Z[ω]={a+bω} determina valores adequados de a, b
void find_eisentein_coefficients(int64_t N, int64_t& x, int64_t& y){
//Variáveis locais
int64_t tester, i, j;
int64_t limit=10*std::sqrt(N);

//Ajuste inicial do coeficientes
x=std::sqrt(N);
y=std::sqrt(N);

//Loop principal
for(i=0; i<limit; i++){
for(j=0; j<limit; j++){
tester=(i*i)+(j*j)-(i*j);

if(tester==N)
break;
                      };
                      };

x=i;
y=j;
                                                                   };

//---------------------------
//Função que determina se um inteiro de Eisenstein é primo ou não
template<typename T>
bool is_eisenstein_prime(eisenstein_integer<T> z){
//Caso trivial: primos racionais da forma p=2 (mod 3)
//Variáveis locais
int64_t z_a=static_cast<int64_t> (z.a);

//Teste
if(z.b==0){
if(trial_division(z_a)==true && (z_a%3)==2)
return true;
          };

//Caso geral: inteiros cuja norma é primo satisfazendo p= (1 mod 3)
//Variáveis locais
int64_t z_norm=static_cast<int64_t> (z.norm());

//Teste
if(trial_division(z_norm)==true && (z_norm%3)==1)
return true;

//Não primos
return false;
                                                 };


//---------------------------
//Função que implementa o algoritmo de Euclides
template<typename T>
eisenstein_integer<T> gcd(eisenstein_integer<T> z1, eisenstein_integer<T> z2){
//Restrição
if(z2.norm()>z1.norm())
return gcd(z2, z1);

//Variáveis locais
eisenstein_integer<T> quotient, remainder;

//Cálculo do resto da divisão
quotient=z1/z2;
remainder=z1-(quotient*z2);

//Resultado
if(remainder.a==0 && remainder.b==0)
return z2;
else 
return gcd(z2, remainder);

                                                                             };


//---------------------------
template<typename T>
void factorization(eisenstein_integer<T> z){

//Variáveis locais
std::vector<int64_t> factor_vector;
int64_t z_norm=static_cast<int64_t> (z.norm());
int64_t real_part, imag_part;

//Procedimentos
//Fatorando a norma de z[ω]
factoring(factor_vector, z_norm);

//Loop principal: calculando fatores primos de  Z[ω]=a+bω
std::cout<<"Eis os fatores primos de "<<z.algebraic()<<":\n";
for(auto factor:factor_vector){
if((factor%3)==2)
std::cout<<factor<<", ";

if(factor==3)
std::cout<<"−(1 + 2ω)², ";

if((factor%3)==1){

find_eisentein_coefficients(factor, real_part, imag_part);

if(real_part==0 && imag_part==0)
std::cout<<"O algoritmo não foi capaz de calcular fatores primos no intervalo de busca selecionado.\n";

else{
eisenstein_integer<T> prime1(real_part, imag_part);
eisenstein_integer<T> prime2((real_part-imag_part), (-1)*imag_part);

std::cout<<prime1.algebraic()<<"/"<<prime2.algebraic()<<", ";

    };

                };


                              };

std::cout<<"...\n";

                                           };

//**********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
