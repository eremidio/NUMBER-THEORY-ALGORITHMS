//VAMOS CRIAR UMA ROTINA PARA CALCULAR OS NÚMEROS DE BERNOULLI USANDO AFUNÇÃOZETA DE RIEMANN

/*
OS NÚMEROS D BERNOULLI PODE SER CALCULADOS USANDO-SE A FUNÇÃO ZETA DE RIEMANN POR MEIO DA RELAÇÃO:

B(n)= -nζ(1-n) PARA n>1 OU n=1.

*/

//****************************************************************************************************************************
//CABEÇALHO
#ifndef BERNOULLI2_H
#define BERNOULLI2_H
#include"riemann_zeta.hpp"
//****************************************************************************************************************************
//PROTOTIPOS DE FUNÇÕES
double bernoulli_number_generator0(int n);

//****************************************************************************************************************************
//FUNÇÕES
//Gerando os números de Bernoulli usando uma fórmula explicita B
double bernoulli_number_generator0(int n){
//Casos triviais
if(n==0)
return 1.0;
if(n==1)
return 0.5;
//Variáveis locais
double x=(1.0-n);
//Procedimento
return (-1)*n*riemann_zeta_function_analytical_continuation(x);
                                         };
//****************************************************************************************************************************
//FIM DO HEADER
#endif
