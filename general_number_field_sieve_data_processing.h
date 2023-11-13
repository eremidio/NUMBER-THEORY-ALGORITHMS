//ESTE ARQUIVO CONTÉM AS ROTINAS DO ALGORITMO USADAS NA FASE DE PROCESSAMENTO DE DADOS USADOS NO ALGORITMO

//*********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef GENERAL_NUMBER_FIELD_SIEVE_DATA_PROCESSING_H
#define GENERAL_NUMBER_FIELD_SIEVE_DATA_PROCESSING_H 
#include"general_number_field_sieve_class.h"//Dependências necessárias estão inclusas aqui
#include<time.h>
#include<stdlib.h>


//*********************************************************************************************************************************************************************
//MÉTODOS
//Função de ajuste de parâmetros usados no cálculo de matrizes
void general_number_field_sieve::congruence_finder_algorithm_setup(){
//Cálculo da matriz reduzida do sistema
reduced_matrix=parity_matrix*transpose_parity_matrix;

//Ajuste de vetores usados no cálculo de congruências
check_vector.reshape(a_vector.size(), 1);
congruence_vector.reshape(a_vector.size(), 1);
                                                                    };

//Função que gera combinações lineares das matrizes reduzidas do sistema
void general_number_field_sieve::generate_check_vector(int64_t k){
//Gerador de sementes aleatórias
srand(time(NULL));

//Número de pares (a, b)
if(k>126){
//Variáveis locais
int64_t j, random_int;

//Procedimentos
for(j=0; j<a_vector.size(); ++j){
random_int=rand()%101;

if(random_int&1)
check_vector.matrix[j][0]=1;
else
check_vector.matrix[j][0]=0;
                                };
         }
else{
//Variáveis locais
int64_t i;

//Procedimentos
for(i=0; i<a_vector.size(); ++i){
if(k&1)
check_vector.matrix[i][0]=1;
else
check_vector.matrix[i][0]=0;

//Atualizando o valor da chave usada
k>>=1;
                                };
    };
                                                                 };

//Algoritmo usado para selecionar números (a,b) usados para determinação de uma relação do tipo x²=y² (mod n)
void general_number_field_sieve::congruence_finder_algorithm(){

//Variáveis locais
int64_t i, j,odd_count;
int64_t max_depth=1000000;

//Procedimentos
//Loop principal
for(i=1; i<max_depth; ++i){
generate_check_vector(i);
congruence_vector=reduced_matrix*check_vector;

odd_count=0;
for(j=0; j<a_vector.size(); ++j){
if(((congruence_vector.matrix[j][0])%2)==1){
odd_count++;
break;
                                           };

//Caso uma dependência linear seja encontrada essa parte do algoritmo se encerra
if(odd_count==0)
return;
                               };

                          };

                                                              };

//Função que calcula quadrados perfeitos sobre a base de fatores primos racional
void general_number_field_sieve::rational_square_finder_algorithm(){
//Variáveis locais
int64_t i;

//Procedimentos
//Ajuste de variáveis
rational_selection=1;

/*
NOTA: Está se assumindo que Q(α) é um domínio de fatorização única o que não necessariamente é verdade. O algoritmo mais geral para o cálculo de raízes é mais 
complicado e envolve fatores f'(x).
*/

for(i=0; i<a_vector.size(); ++i){

if(check_vector.matrix[i][0]==0)
continue;
if(check_vector.matrix[i][0]==1)
rational_selection*=(a_vector[i]+(b_vector[i]*m));

                                };

//Computando a raíz quadrada 
rational_selection*=f_derivative.evaluate_polynomial(m);
rational_selection*=f_derivative.evaluate_polynomial(m);
square_root_128(rational_square_root, rational_selection);

                                                                  };

//Função que calcula quadrados perfeitos sobre a base de fatores primos algébrica
/*
NOTA: Usaremos aqui o método de força bruta que envolve o cálculo de produtos do (a+bα) e redução do polinômio em α congruente mod f(x). 
Então usaremos redução módulo n via o homeomorfismo φ(a+b)=φ(a)+φ(b); φ(ab)=φ(a)φ(b); φ(1)= 1(mod n); φ(α)=m (mod n).
Este é o metodo mais simples e o menos propenso a erros, porém não o mais eficiente para números excessivamente grandes de fatores (a, b) na base fatores primos
algébricos na prática fatoração envolve cerca de 10^7 ~ 10^8 pares (a,b) de modo que o procedimento aqui descrito rapidamente se torna inviável.
Técnicas mais sofisticadas usam decomposição de polinômios sobre corpos númericos finitos sobre os quais P(α)=Π(a+bα)é irredutível o resultado é então obtido
combinando-se usando o resultados via teorema do resíduo chinês.
O métodos de Newton-Raphson pode ser usado para aproximar a solução real usando-se neste caso polinômio em duas variáveis, porém, este método usa primos maiores do que o
número a ser fatorado e para este caso a computação pode ser excessivamente complicada em problemas reais. 
Para referências consultar a literatura.
*/
void general_number_field_sieve::algebraic_square_finder_algorithm(){
//Variáveis locais
polynomial<__int128_t> algebraic_polynomial, factor_polynomial, reduced_polynomial;
int64_t i;

//Procedimentos
//Ajuste de variáveis
algebraic_polynomial.degree=1;
algebraic_polynomial.polynomial_coefficients={b_vector[0], a_vector[0]};
algebraic_polynomial.polynomial_powers={1, 0};
factor_polynomial.degree=1;
factor_polynomial.polynomial_powers={1, 0};

//Cálculo do produto polinomial em α Π(a+bα) modulo f(x)
for(i=1; i<a_vector.size(); ++i){
factor_polynomial.polynomial_coefficients[0]=b_vector[i];
factor_polynomial.polynomial_coefficients[1]=a_vector[i];
algebraic_polynomial=algebraic_polynomial*factor_polynomial;
                                };

//Cálculo do polinômio reduzido em Q(α)
reduced_polynomial=remainder(algebraic_polynomial, f_polynomial);

//Cálculo da raíz algébrica
algebraic_square_root=((reduced_polynomial.evaluate_polynomial(m)%m)*(f_derivative.evaluate_polynomial(m)%m))%m;

                                                                    };

//Função que calcula fatores primos
void general_number_field_sieve::factor_calculation(){
//Calculando fatores primos usando o algoritmo de Euclides
if(rational_square_root>algebraic_square_root){
factor1= euclides_algorithm((rational_square_root-algebraic_square_root),number);
if(factor1>1){
factor2=number/factor1;
return;
             };
                                              };

if(rational_square_root<algebraic_square_root){
factor1= euclides_algorithm((algebraic_square_root-rational_square_root),number);
if(factor1>1){
factor2=number/factor1;
return;
             };
                                              };

factor1= euclides_algorithm((algebraic_square_root+rational_square_root),number);
factor2=number/factor1;
                                                     };


//*********************************************************************************************************************************************************************
//FIM DO HEADER
#endif  
