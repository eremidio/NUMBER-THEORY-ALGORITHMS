//VAMOS CRIAR UM PROGRAMA PARA A APROXIMAR A FUNÇÃO GAMMA USANDO UMA FÓRMULA DE RAMANUJAN

/*

A FUNÇÃO Γ(x) PODE SER APROXIMADA PARA ARGUMENTOS REAIS x≳0 POR MEIO DA SEGUINTE FÓRMULA:
Γ(x+1)={√π}{(x/e)^e}+{8x³+4x²+x+(1/30)}^(1/6). TAL FÓRMULA PRODUZ UM ERRO DA ORDEM DE 
0,00005% DO VALOR CORRETO PODENDO SER ÚTIL EM MUITOS CONTEXTOS


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Stirling%27s_approximation#Versions_suitable_for_calculators
                          https://archive.org/details/lost-notebook/page/n337/mode/2up
 
*/


//***************************************************************************************
//CABEÇALHO
#ifndef RAMANUJAN_GAMMA_FUNCTION_APPROXIMATION_H
#define RAMANUJAN_GAMMA_FUNCTION_APPROXIMATION_H
#include<stdint.h>
#include<math.h>


//***************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
long double factorial_function_ramanujan_approximation(int);
long double gamma_function_ramanujan_approximation(double);


//***************************************************************************************
//FUNÇÕES
//Função que aproxima a função n! usando a fórmula de Ramanujan
long double factorial_function_ramanujan_approximation(int n){
  
  //Variáveis locais
  const long double pi_log=0.5*log(4.0*atan(1.0));
  long double log_part=(n*log(n))-n+pi_log;
  long double six_root_part=log((8*n*n*n)+(4*n*n)+n+(1.0/30))/6;
  long double result=exp(log_part+six_root_part);

  //Resultado
  return result;

};

//Função que aproxima a função Γ(x) usando a fórmula de Ramanujan
long double gamma_function_ramanujan_approximation(double n){

  //Variáveis locais
  const double pi_root=sqrt(4.0*atan(1.0));
  const double e=exp(1.0);
  double power_part=pow((n/e), n);
  double six_root_part=pow(((8*n*n*n)+(4*n*n)+n+(1.0/30)), (1.0/6));

  
  //Resultado
  return (pi_root*power_part*six_root_part);

};


//***************************************************************************************
//FIM DO HEADER
#endif
