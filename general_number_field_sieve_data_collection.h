//ESTE ARQUIVO CONTÉM AS ROTINAS DO ALGORITMO USADAS NA FASE DE COLETA DE DADOS USADOS NO ALGORITMO

//*********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef GENERAL_NUMBER_FIELD_SIEVE_DATA_COLLECTION_H
#define GENERAL_NUMBER_FIELD_SIEVE_DATA_COLLECTION_H 
#include"general_number_field_sieve_class.h"//Dependências necessárias estão inclusas aqui

//*********************************************************************************************************************************************************************
//MÉTODOS
//Função de ajuste de parâmetros do algoritmo de seleção de números suaves
void general_number_field_sieve::sieving_algorithm_setup(){
//Ajuste de parâmetros
std::cout<<"Digite um número N que determina o intervalo de busca por números suaves em relação as bases de fatores selecionadas: ";
std::cin>>N;

b=1;
a_vector.resize(0);
b_vector.resize(0);
a_test_vector.resize(0);
b_test_vector.resize(0);
sieving_size=(rational_factor_base.size()+algebraic_factor_base_r.size()+quadratic_factor_base_r.size()+1);
sieving_counter=0;
sieving_failure=false;
                                                           };

//Função que seleciona possíveis candidatos em relação a base racional de fatores primos
void general_number_field_sieve::rational_sieving_algorithm(){
//Variáveis locais
int64_t limit;

//Procedimentos
//Ajuste de variáveis
if(N<1000)
limit=N/10;
else if(N<1000000)
limit=std::sqrt(N);
else
limit=std::sqrt(std::sqrt(N));

//Loop principal
mainloop:
while(b<limit){

for(a=(-1)*N; a<=N; ++a){
sieving_tester=(a+(b*m));//Ajuste de variáveis

//Loop sobre a base racional de fatores 
for(auto x:rational_factor_base){
while((sieving_tester%x)==0)
sieving_tester/=x;
                                };

//Seleção de possíveis candidatos (a,b)
if(sieving_tester==1){
a_test_vector.push_back(a);
b_test_vector.push_back(b);
                     };
                        };

//Atualizando variável para a próxima iteração
b++;
              };
                                                               };

//Função que determina se um número (a, b) é completamente fatorado pela base algébrica de fatores primos
bool general_number_field_sieve::is_algebraic_factorable(__int128_t x, __int128_t y){
//Variáveis locais
__int128_t prime_product=1, monomial_sum=0;
int64_t power_x=f_polynomial.degree;
int64_t power_y=0;

//Procedimentos
//Seleção de base reduzida de primos
for(int64_t i=0; i<algebraic_factor_base_p.size(); ++i){
if( ((x+(y*algebraic_factor_base_r[i]))%algebraic_factor_base_p[i])==0 )
prime_product*=algebraic_factor_base_p[i];
                                                       };

//Teste polinomial para detecção de uma fatoração completa sobre uma base de números algébricas (b^d)f(a/b) = Πp(i), onde p(i) são os primos selecionados anteriormente
for(auto x3:f_polynomial.polynomial_coefficients){
monomial_sum+=(x3*pow128(x, power_x)*pow128(y, power_y));
power_x--;
power_y++;
                                                  };
if((monomial_sum%prime_product)==0)
return true;
else
return false;
                                                                                    };

//Função de seleção de números suaves em relação às bases de números algébricas e racionais
void general_number_field_sieve::sieving_algorithm(){
//Variáveis locais
int64_t i;

//Procedimento
//Loop principal sobre os possíveis candidadtos selecionados na etapa de seleção sobre a base de primos racional
for(i=0; i<a_test_vector.size(); ++i){
__int128_t a_tester=a_test_vector[i];
__int128_t b_tester=b_test_vector[i];

if(is_algebraic_factorable(a_tester, b_tester)==true){
a_vector.push_back(a_tester);
b_vector.push_back(b_tester);
sieving_counter++;
                                                     };
                                     };

//Checando se a etapa de seleção de números suaves foi bem sucedida
if(sieving_counter<=sieving_size)
sieving_failure=true;
                                                   };

//Função que constrói a matriz de fatores primos módulo 2
void general_number_field_sieve::build_matrix(){
//Variáveis de uso geral
int64_t row_number=0, column_number=0;
int64_t index=0;//Index de par (a,b)
__int128_t monomial_sum, quadratic_character;

//Parte 2: ajuste de variáveis e cálculo dos elementos da primeira coluna da matriz
parity_matrix.reshape(a_vector.size(), sieving_size);//Ajustando o tamanho da matriz

matrix_calculation:
column_number=0;

if((a_vector[index]+(b_vector[index]*m))<0)
parity_matrix.matrix[row_number][column_number]=1;
else
parity_matrix.matrix[row_number][column_number]=0;

column_number++;//Atualização de variáveis

//Parte 3: fatoração sobre a base racional de primos
//Ajuste de variáveis
factoring_tester=(a_vector[index]+(b_vector[index]*m));

for(auto x:rational_factor_base){
prime_power_counter=0;
while((factoring_tester%x)==0){
prime_power_counter++;
factoring_tester/=x;
                              };

parity_matrix.matrix[row_number][column_number]=(prime_power_counter%2);
column_number++;//Atualização de variáveis

                                };


//Parte 4:cálculo de fatores primos congruente módulo 2 sobre a base algébrica de fatores primos
//Variáveis locais
int64_t power_x=f_polynomial.degree;
int64_t power_y=0;

//Procedimento
//Ajuste de variáveis
monomial_sum=0;

//Cálculo de (b^d)f(a/b)
for(auto y:f_polynomial.polynomial_coefficients){
monomial_sum+=(y*pow128(a_vector[index], power_x)*pow128(b_vector[index], power_y));
power_x--;
power_y++;
                                                };

//Fatorando sobre a base algébrica
for(auto z:algebraic_factor_base_p){
prime_power_counter=0;
while((factoring_tester%z)==0){
prime_power_counter++;
factoring_tester/=z;
                              };

parity_matrix.matrix[row_number][column_number]=(prime_power_counter%2);
column_number++;//Atualização de variáveis

                                  };

//Parte 5: cálculo de fatores primos congruente módulo 2 sobre a base quadrática de fatores primos
//Variável local
int64_t k;

//Procedimento
for(k=0; k<quadratic_factor_base_r.size(); k++){
quadratic_character=legendre_symbol((a_vector[index]+(b_vector[index]*quadratic_factor_base_p[k])), quadratic_factor_base_r[k]);

if(quadratic_character==1)
parity_matrix.matrix[row_number][column_number]=0;
else
parity_matrix.matrix[row_number][column_number]=1;

column_number++;//Atualização de variáveis
                                               };

//Etapa 6: atualizando variáveis para a próxima iteração
if(index<(b_vector.size()-1)){
index++;
row_number++;

goto matrix_calculation; 
                             };
                                               };

//Função que constrói a transposta da matriz de fatores primos módulo 2
void general_number_field_sieve::build_transpose_matrix(){
transpose_parity_matrix=parity_matrix.transpose();
                                                         };


//*********************************************************************************************************************************************************************
//FIM DO HEADER
#endif 
