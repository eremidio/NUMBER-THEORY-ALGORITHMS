//ESTE ARQUIVO CONTÉM A FUNÇÃO PRINCIPAL DO ALGORITMO
//ESTE ARQUIVO DEVERÁ SER INCLUSO AO ARQUIVO CONTENDO A FUNÇÃO PRINCIPAL DO PROGRAMA A SER EXECUTADO

//*********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef GENERAL_NUMBER_FIELD_SIEVE_MAIN_H
#define GENERAL_NUMBER_FIELD_SIEVE_MAIN_H
#include"general_number_field_sieve_class.h"//Depências necessárias estão inclusas aqui
#include"general_number_field_sieve_precomputations.h"
#include"general_number_field_sieve_data_collection.h"
#include"general_number_field_sieve_data_processing.h"


//*********************************************************************************************************************************************************************
//FUNÇÃO PRINCIPAL DO ALGORITMO
void general_number_field_sieve::run(){
restart:
//Etapa 1: recebendo input do usuário
char number_string[45];
std::cout<<"Digite o número a ser fatorado: ";
if(scanf("%s", number_string)!=1)
return;
number=scanf128(number_string);
std::cout<<"Etapa 1 concluída com sucesso!\n";

//Etapa 2: seleção de polinômios e e da raízes do polinômio módulo o número a ser fatorado
polynomial_root_selection();
std::cout<<"Etapa 2 concluída com sucesso!\n";

//Etapa 3: definição de bases racionais e algébricas de primos usadas no algoritmo
set_rational_factor_base();
set_algebraic_factor_base();
set_quadratic_factor_base();
std::cout<<"Etapa 3 concluída com sucesso!\n";

//Etapa 4: seleção de números suaves em relação a base de primos selecionadas e construção das matrizes de fatores primos congruentes módulo 2
sieving_algorithm_setup();
rational_sieving_algorithm();
sieving_algorithm();

//O algoritmo se encerra caso a peneira de números suaves não seja bem sucedida na escolha de números suaves em relação a base primos selecionado
if(sieving_failure==true){
std::cout<<"Etapa 4 não foi concluída com sucesso!\n";
return;
                         };

std::cout<<"Etapa 4 concluída com sucesso!\n";

//Etapa 5:construção da matriz de fatores primos
build_matrix();
build_transpose_matrix();

std::cout<<"Etapa 5 concluída com sucesso!\n";

//Etapa 6: determinação de congruência do tipo x²=y² (mod n)
congruence_finder_algorithm_setup();
congruence_finder_algorithm();
std::cout<<"Etapa 6 concluída com sucesso!\n";

//Etapa 7: cálculo de quadrados perfeitos e fatores primos
rational_square_finder_algorithm();
algebraic_square_finder_algorithm();
factor_calculation();
                                     };


//Função que printa o resultado do algoritmo
void general_number_field_sieve::print_result(){
printf("Resultado da execução do algoritmo:\n");
printf128(number);
printf128(factor1);
printf128(factor2);
                                              };



//*********************************************************************************************************************************************************************
//FIM DO HEADER
#endif   
