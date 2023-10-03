//ESTE ARQUIVO CONTERÁ A FUNÇÃO PRINCIPAL QUE COORDENA A EXECUÇÃO DO ALGORITMO DA PENEIRA QUADRÁTICA VERSÃO MULTIPOLINOMIAL
//ESTE ARQUIVO DEVERÁ SER INCLUÍDO EM QUALQUER PROGRAMA QUE VÁ EXECUTAR O ALGORITMO
//AS FUNÇÕES AQUI PRESENTES SÃO AS ÚNICAS FUNÇÕES QUE UM USUÁRIO NECESSITA ACESSAR PARA EXECUTAR O ALGORITMO
//ANTES DE USAR UMA PENEIRA QUADRÁTICA É RAZOÁVEL TENTAR FATORA O NÚMERO EM QUESTÃO USANDO CURVAS ELÍTPICAS OU O MÉTODO DE POLLARD RHO PARA ELIMINAR FATORES PEQUENOS

//**********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef QUADRATIC_SIEVE_MAIN_H
#define QUADRATIC_SIEVE_MAIN_H
#include"quadratic_sieve_class.h"
#include"quadratic_sieve_data_colection.h"
#include"quadratic_sieve_data_processing.h"


//**********************************************************************************************************************************************************************
//FUNÇÃO PRINCIPAL
//Função principal
void quadratic_sieve::run(){
//Parte 1: recebendo input do usuário
char number_string[42];

printf("Usuário digite um número a ser fatorado: ");
scanf("%s", number_string);
number=scanf128(number_string);

//Parte 2: ajustando a base de primos
printf("Digite um limitante superior para a busca da base de fatores primos a serem usados no algoritmo: ");
scanf("%li", &smoothness_bound);

set_prime_base();

//Parte 3: checando se o número em questão é um quadrado perfeito neste caso uma fatoração é facilmente obtida
perfect_square=square_root_checker(number_square_root, number);

if((number_square_root*number_square_root)==number){
factor1=number_square_root;
factor2=number_square_root;
return;
                                                   };

//Parte 4: peneirando números suaves em relação a base de números primos
printf("Digite um número que determina o intervalo de seleção de candidato para as possíveis relações constitutivas: ");
scanf("%li", &sieve_interval);

sieving_algorithm();
build_matrices();

//Parte 5: busca por relações constitutivas do tipo
congruence_finder_algorithm();

//Parte 6: calculando fatores primos de um número
factors_calculation();
                           };


//Função que printa o resultado do algoritmo
void quadratic_sieve::print_result(){
printf("Resultado da execução do algoritmo:\n");
printf128(number);
printf128(factor1);
printf128(factor2);

                                    };


//**********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
