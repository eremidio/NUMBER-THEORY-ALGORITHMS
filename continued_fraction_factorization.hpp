//VAMOS CRIAR PROGRAMA QUE IMPLEMENTA O ALGORITMO DE FRAÇÕES CONTÍNUAS PARA FATORAR NÚMEROS INTEIROS.


/*
O ALGORITMO DE EXPANSÃO EM FRAÇÕES CONTÍNUAS ESTÁ ENTRE OS MAIS ANTIGOS E MAIS EFICIENTES MÉTODOS COMPUTACIONAIS PARA FATORAR
NÚMEROS INTEIROS (RESULTADOS RAZOÁVEIS COM UM PROGRAMA OTIMIZADO SÃO OBTIDOS PRA NÚMEROS ATÉ 50 DIGITOS).

O PRINCIPAL OBJETIVO DESTE ALGORITMO É PRODUZIR  RELAÇÕES DE CONGRUÊNCIA DA FORMA a²=b² (mod n) DONDE FATORES PRIMOS NÃO
TRIVIAIS SÃO OBTIDOS VIA mdc(a+b, n) E mdc(a-b, n).

PARA PRODUZIR TAIS RELAÇÕES DE CONGRUÊNCIA O ALGORITMO USA A EXPANSÃO DE n^(1/2) EM FRAÇÕES PARCIAIS. O TEOREMA DE LEGENDRE
AFIRMA QUE PARA UM NÚMERO IRRACIONAL SUA EXPANSÃO EM FRAÇÕES PARCIAIS É PERIÓDICA. O ALGORITMO USA ESTE TEOREMA E TAMBÉM UM PEQUENA BASE DE NÚMEROS PRIMOS PARA GERAR RELAÇÕES CONSTITUTIVAS SATISFEITAS PELOS NÚMEROS SELECIONADOS.

ESTE ALGORITMO TAMBÉM PODE SER USADOS PARA SE RESOLVER A EQUAÇÃO DE PELL QUE DEFINE A IRRACIONALIDADE DE n^(1/2).

PARA MAIORES INFORMAÇÕES: https://trizenx.blogspot.com/2018/10/continued-fraction-factorization-method.html

*/ 

//**************************************************************************************************************************
//CABEÇALHO
#ifndef CONTINUED_FRACTION_FACTORIZATION_H
#define CONTINUED_FRACTION_FACTORIZATION_H
#include<vector>
#include<cmath>
#include<iostream>
#include"mod_bin_exponentiation.h"

//**************************************************************************************************************************
//FUNÇÕES AUXILIARES
//Função que executa o algoritmo de Euclides
int64_t euclides_algorithm(int64_t a, int64_t b){
if(b==0)
return a;
else return euclides_algorithm(b, a%b);
                                                };

//Função que determina se um  número é quadrado perfeito
bool perfect_square_check(int64_t n){
//Variáveis locais
int64_t odd=1;
//Procedimentos
while(n>0){
n-=odd;
odd+=2;
if(n<0)
return false;
          };

return true;
                                    };

//Função que checa se um número é primo
bool is_prime(int64_t n){
//Casos triviais
if(n<=1)
return false;
if(n==2 || n==3)
return true;
if(n%2==0 || n%3==0)
return false;

//Loop com otimização 6k+1
for(int64_t i=5; i<std::sqrt(n); i+=6){
if((n%i)==0 || (n%(i+2))==0)
return false;
                                      };
return true;
                        };

//Função que calcula o símbolo de Kronecker (a|p) para um número a e um primo p, neste caso é o símbolo de legendre
int64_t kronecker_symbol(int64_t a, int64_t p){
return mod_bin_pow(a, (p-1)/2, p);
                                              };

//Função que printa um vetor de inteiros na tela (usada também como função de teste)
void print_vector(std::vector<int64_t> vector_int){
std::cout<<"{";
for(auto y:vector_int){
std::cout<<y<<" ";
                      };
std::cout<<"}\n";
                                                  };

//**************************************************************************************************************************
//CLASSE DO ALGORITMO
/*

OBSERVAÇÃO: Neste algotitmo usamos uma busca envolvendo no máximo duas equações para encontrar equações consitutivas do tipo
a²=b²(mod n). Alguns números compostos não podem ser fatorados usando este algoritmo puramente, pois a fração contínua de
n^(1/2) possui um período muito curto. E talvez não seja possível obter relações constitutivas rk=(Ak)² (mod n) suficiente.
Neste caso podemos multiplicar n por um inteiro k e checa se o símbolo de Kronecker (nk|p)=1, no momento de construir a base de
números primos.

*/

class continued_fraction_factorization{
public:
//Membros da classe
int64_t number;//Número a ser fatorado
int64_t smoothness;//Limite para a base de primos
int64_t e0, e1, f0, f1, a, x, y, z;//Variáveis usadas na busca por convergentes
int64_t Ak, Bk;//Numerador e denominador dos convergentes da expansão em frações contínuas
int64_t rk;//Candidatos para as relações constitutivas
int64_t selection1, selection2;//Candidatos satisfazendo as relações constitutivas
int64_t factor1, factor2;//Fatores do número em questão
std::vector<int64_t> Ak_vector, Bk_vector, Ak_squared_vector, rk_vector;//Coeficientes da expansão em frações contínuas
std::vector<int64_t> base_vector;//Base de primos usadas no cálculo
 
//Métodos da classe
void run();//Função principal
void setup();//Função que ajusta variáveis para o cálculo de números primos
void fill_prime_buffer();//Função que seleciona vetores para a base de números primos
bool check_smoothness(int64_t);//Função que checa se um dado número é expansível na base de primos selecionada
void convergents_calculation();//Função que calcula convergentes para a expansão em frações contínuas
void fast_constitutive_relation();//Função que checa por possíveis quadrados modulo o número a ser fatorado
void slow_constitutive_relation();////Função que calcula por possíveis quadrados modulo o número a ser fatorado
                                      };

//**************************************************************************************************************************
//MÉTODOS DA CLASSE
//Função principal
void continued_fraction_factorization::run(){
//Ajuste de variáveis
selection1=0;
selection2=0;
factor1=0;
factor2=0;
setup();
fill_prime_buffer();

//Cálculo dos convergentes da expansão em frações contínuas
convergents_calculation();

//Checagem de eventuais candidatos satisfazendo as relações constitutivas
fast_constitutive_relation();
if(factor1!=0 && factor1<number){
std::cout<<"Fatores primos encontrados: "<<factor1 <<" e "<< factor2<< "\n";
return;
                                };


//Cálculo de relações constitutivas usando duas equações
slow_constitutive_relation();
if(factor1!=0 && factor1<number)
std::cout<<"Fatores primos encontrados: "<<factor1 <<" e "<< factor2<< "\n";

if(factor1==0)
std::cout<<"Não foram encontrados fatores deste número\n";

                                            };

//Função que recebe input do usuário e calcula um limite de profundidade em que o algoritmo é executado
void continued_fraction_factorization::setup(){
std::cout<<"Usuário digite um número que será fatorado: ";
std::cin>>number;

//Cálculo da profundidade de busca
smoothness=std::floor(std::exp(std::sqrt(std::log(number)*std::log(std::log(number))))/2.0);
                                              };

//Função que seleciona uma base de números primos
void continued_fraction_factorization::fill_prime_buffer(){
//Ajuste de variáveis
base_vector.resize(0);
base_vector.push_back(2);
//Preenchendo o buffer com primos ímpares
for(int64_t i=3; i<smoothness; i+=2){
if(is_prime(i)==true)
base_vector.push_back(i);
                                    };

//TESTE 1, USE UM // APÓS O MESMO
//print_vector(base_vector);
                                                          };

//Função que checa se um dado número é expansível na base de primos selecionada
bool continued_fraction_factorization::check_smoothness(int64_t n){
for (auto y:base_vector){
while((n%y)==0)
n/=y;
                        };
if(n==1)
return true;
else
return false;
                                                                  };

//Função que calcula os convergentes da expansão em frações contínuas
void continued_fraction_factorization::convergents_calculation(){
//Variáveis locais
int64_t x=std::round(std::sqrt(number));

//Ajuste de variáveis
Ak_vector.resize(0);
Bk_vector.resize(0);
Ak_squared_vector.resize(0);
rk_vector.resize(0);
e0=1;
e1=0;
f0=0;
f1=1;
y=x;
a=2*y;
z=1;

//Loop principal
while(true){
y=a*z-y;
z=std::round((number-(y*y))/z);
a=std::round((x+y)/z);

Ak=e1+x*f1;
Bk= f1;

//Ajuste de variáveis
Ak%=number;
Bk%=number;

Ak_vector.push_back(Ak);
Bk_vector.push_back(Bk);

//Preenchendo o buffer de relações constitutivas
rk= (Ak*Ak)%number;
if(check_smoothness(rk)==true){
Ak_squared_vector.push_back(Ak*Ak);
rk_vector.push_back(rk);
                              };

//Calculando os coeficientes para a próxima iteração 
e0=e1;
f0=f1;
e1=a*e1+e0;
f1=a*f1+f0;

//Ajuste de variáveis
e0%=number;
e1%=number;
f0%=number;
f1%=number;

if(z==1)
break;

           };

//TESTE USE UM // APÓS O MESMO
//std::cout<<"TESTE 2\n";
//print_vector(Ak_vector);
//print_vector(Bk_vector);
//print_vector(Ak_squared_vector);
//print_vector(rk_vector);
                                                                };

//Função que checa por possíveis quadrados modulo o número a ser fatorado
void continued_fraction_factorization::fast_constitutive_relation(){
//Variáveis locais
int64_t temp1, temp2;

//Checando o vetor de resíduos rk's por fatores quadráticos
for(int64_t i=0; i<rk_vector.size(); ++i){
if(perfect_square_check(rk_vector[i])==true && rk_vector[i]>1){
selection1=std::sqrt(rk_vector[i]);
selection2=std::sqrt(Ak_squared_vector[i]);

//Cálculo dos fatores primos
temp1=selection1+selection2;
factor1=euclides_algorithm(temp1, number);
if(factor1>1 && factor1!=number){
factor2=number/factor1;
return;
                                };

if(selection1>selection2)
temp2=selection1-selection2;
if(selection1<selection2)
temp2=selection2-selection1;

factor1=euclides_algorithm(temp2, number);
if(factor1>1 && factor1!=number){
factor2=number/factor1;
return;
                                };


if(factor1==1 || factor2==1){
factor1=0;
factor2=0;
continue;
                            }

                                                              };
                                         };
                                                                   };

//Função que calcula por possíveis quadrados modulo o número a ser fatorado
void continued_fraction_factorization::slow_constitutive_relation(){
//Variáveis locais
int64_t temp1, temp2;

//Checando o vetor de resíduos rk's por fatores quadráticos
for(int64_t i=0; i<rk_vector.size(); ++i){
for(int64_t j=0; j<rk_vector.size(); ++j){
//Restrição
if(i==j)
continue;

if(perfect_square_check(rk_vector[i]*rk_vector[j])==true && (rk_vector[i]*rk_vector[j])>1){
selection1=std::sqrt(rk_vector[i]*rk_vector[j]);
selection2=std::sqrt(Ak_squared_vector[i]*Ak_squared_vector[j]);

//Cálculo dos fatores primos
temp1=selection1+selection2;
factor1=euclides_algorithm(temp1, number);
if(factor1>1 && factor1!=number){
factor2=number/factor1;
return;
                                };

if(selection1>selection2)
temp2=selection1-selection2;
if(selection1<selection2)
temp2=selection2-selection1;

factor1=euclides_algorithm(temp2, number);
if(factor1>1 && factor1!=number){
factor2=number/factor1;
return;
                                };


if(factor1==1 || factor2==1){
factor1=0;
factor2=0;
continue;
                            }

                                                              };


                                         };
                                         };
                                                                   };

//**************************************************************************************************************************
//FIM DO HEADER
#endif
