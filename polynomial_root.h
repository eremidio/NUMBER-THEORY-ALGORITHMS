//VAMOS CRIAR UM PROGRAMA QUE CALCULA RAÍZES DE POLINÔMIOS

/*
USAREMOS EXPRESSÕES MATEMÁTICAS PARA OS CASOS DE GRAU 1 E PARA GRAUS MAIORES OU IGUAIS A 2 USAREMOS O MÉTODO DE NEWTON-RAPHSON.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Newton%27s_method

*/

//**********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef POLYNOMIAL_ROOT_H
#define POLYNOMIAL_ROOT_H
#include"polynomials.h"//Arquivo já inclui as dependências necessárias


//**********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
polynomial<T> polynomial_derivative(polynomial<T>&);
template<typename T>
T find_root(polynomial<T>&);

//**********************************************************************************************************************************************************************
//FUNÇÕES 
//Função que calcula a derivada de um polinômio
template<typename T>
polynomial<T> polynomial_derivative(polynomial<T>& p2){
//Restrição
assert(p2.degree>=1);

//Variáveis locais
int64_t i,j;
polynomial<T> result;

//Procedimentos
//Ajuste do grau do polinômio resultante e do array de potências
result.degree=(p2.degree-1);

for(i=result.degree; i>=0; --i)
result.polynomial_powers.push_back(i);

//Ajuste dos arrays de coeficientes
result.polynomial_coefficients.resize(0);

for(j=0; j<p2.polynomial_coefficients.size(); ++j)
result.polynomial_coefficients.push_back(p2.polynomial_coefficients[j]*p2.polynomial_powers[j]);

//Resultado
return result;
                                                      };

//Função que cálcula a raíz de um polinômio
template<typename T>
T find_root(polynomial<T>& p2){
//Casos base
//Grau 1:
if(p2.degree==1){
return (p2.polynomial_coefficients[0]/p2.polynomial_coefficients[1]);
                };

//Caso geral: Usando o algoritmo de Newton-Raphson
//Variáveis locais
polynomial<T> derivative=polynomial_derivative(p2);
int64_t trials=100;
T next, previous;
T value1, value2;
T temp1, temp2;

//Procedimentos
//Ajuste do número de iterações
for(int64_t i=1; i<=p2.degree; ++i)
trials*=10;

//Recebendo palpite inicial do usuário
std::cout<<"Valor inicial: ";
std::cin>>previous;

//Loop principal
for(int64_t j=0; j<trials; ++j){
temp1=p2.evaluate_polynomial(previous);
temp2=derivative.evaluate_polynomial(previous);
next=previous-(temp1/temp2);

//Atualizando variáveis para a proxima iteração
previous=next;

                               };

//Resultado
return previous;
                              };



//**********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
