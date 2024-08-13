//VAMOS CRIAR UM PROGRAMA QUE COMPUTA OS NÚMEROS DE PERRIN

/*
OS NÚMEROS DE PERRIN CONSISTEM NA SEQUÊNCIA DE INTEIROS P(n) DEFINIDA PELAS RELAÇÕES
P(0)=3, P(1)=0, P(2)=2, P(n)=P(n-2)+P(n-3) SE n≳0 E P(n)=P(n+3)-P(n+1) SE n<0.

OS NÚMEROS DE PERRIN PODEM SER EXPRESSOS CALCULADOS DE DIVERSAS FORMAS: USANDO-SE OS 
COEFICIENTES BINOMIAIS (INDICANDO SEU PAPEL EM PROBLEMAS DE ANÁLISE COMBINATÓRIA),
EM TERMOS DE SOLUÇÕES DA EQUAÇÃO x³-x-1=0 (1 REAL E DUAS COMPLEXAS CONJUGADAS) VIA A
FÓRMULA DE BINET, EM TERMOS DE SOMAS PARCIAIS DOS TERMOS ANTERIORES DA SEQUÊNCIA,
USANDO-SE MULTIPLICAÇÃO E EXPONECIAÇÃO DE MATRIZES, ENTRE OUTROS.

OS NÚMEROS DE PERRIN POSSUEM LIGAÇÃO COM A TEORIA DOS GRAFOS: P(n) É O NÚMERO DE 
CONJUNTOS INDEPENDENTE MÁXIMO EM UM GRAFO CÍCLICO DE n VÉRICES.

OS NÚMEROS DE PERRIN POSSUEM UMA RELAÇÃO COM OS TERMOS DA SEQUÊNCIA DE PADOVAN
SIMILAR A RELAÇÃO ENTRE NÚMEROS DE FIBONACCI E OS NÚMEROS DE LUCAS.


NÚMEROS DE PERRIN SÃO DE GRANDE UTILIDADE EM TEORIA DOS NÚMEROS DEVIDO A SEGUINTE
PROPOSIÇÃO: SE n FOR PRIMO, ENTÃO P(n)=0 (mod n). NÚMEROS COMPOSTOS SATISFAZENDO ESTA
IDENTIDADE SÃO DENOMINADOS PSEUDOPRIMOS DE PERRIN. COMBINADO COM UM TESTE DE LUCAS E
UM TESTE DE FERMAT NA BASE 2, OBTÉM-SE UM EFICIENTE E POSSIVELMENTE DETERMINÍSTICO
TESTE DE PRIMALIDADE COM EFICIÊNCIA SIMILAR AO TESTE DE BAILLIE-PSW.

CALCULAREMOS NÚMEROS DE PERRIN USANDO A NOTAÇÃO MATRICIAL.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Perrin_number#Binet_formula
                          https://en.wikipedia.org/wiki/Padovan_sequence
                          https://oeis.org/A001608
                          https://oeis.org/A078712
                          https://oeis.org/A000931

*/

//*************************************************************************************
//CABEÇALHO
#ifndef PERRIN_NUMBER_H
#define PERRIN_NUMBER_H
#include"matrix_exponentiation.h"
#include"matrix_modular_reduction.h"


//*************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
template<typename T>
Matrix<T> perrin_matrix_positive_n(T);
template<typename T>
Matrix<T> perrin_matrix_negative_n(T);
template<typename T>
Matrix<T> modular_perrin_matrix(T, T);



//*************************************************************************************
//FUNÇÕES 
//Função que calcula os termos P(n), P(n+1), P(n+2) da sequência dos números de Perrin
template<typename T>
Matrix<T> perrin_matrix_positive_n(T n){

  //Variáveis locais
  Matrix<T> coefficients_matrix, initial_matrix;


  //Procedimentos
    //Inicializando a matriz de coeficientes
    coefficients_matrix.reshape(3,3);
    coefficients_matrix.matrix[0][0]=0; coefficients_matrix.matrix[0][1]=1; coefficients_matrix.matrix[0][2]=0; 
    coefficients_matrix.matrix[1][0]=0; coefficients_matrix.matrix[1][1]=0; coefficients_matrix.matrix[1][2]=1; 
    coefficients_matrix.matrix[2][0]=1; coefficients_matrix.matrix[2][1]=1; coefficients_matrix.matrix[2][2]=0; 

    //Inicializando a matriz de valores P(0), P(1), P(2)
    initial_matrix.reshape(3,1);
    initial_matrix.matrix[0][0]=3; initial_matrix.matrix[1][0]=0; initial_matrix.matrix[2][0]=2; 


    //Calculando o resultado 
    Matrix<T> power_matrix=matrix_pow<T, T>(coefficients_matrix, n);
    Matrix<T> result=power_matrix*initial_matrix;


  //Resultado
  return result;

};

//Função que calcula os termos P(-n), P(1-n), P(2-n) da sequência dos números de Perrin
template<typename T>
Matrix<T> perrin_matrix_negative_n(T n){

  //Variáveis locais
  Matrix<T> coefficients_matrix, initial_matrix;


  //Procedimentos
    //Inicializando a matriz de coeficientes
    coefficients_matrix.reshape(3,3);
    coefficients_matrix.matrix[0][0]=(-1); coefficients_matrix.matrix[0][1]=0; coefficients_matrix.matrix[0][2]=1; 
    coefficients_matrix.matrix[1][0]=1; coefficients_matrix.matrix[1][1]=0; coefficients_matrix.matrix[1][2]=0; 
    coefficients_matrix.matrix[2][0]=0; coefficients_matrix.matrix[2][1]=1; coefficients_matrix.matrix[2][2]=0; 

    //Inicializando a matriz de valores P(0), P(1), P(2)
    initial_matrix.reshape(3,1);
    initial_matrix.matrix[0][0]=3; initial_matrix.matrix[1][0]=0; initial_matrix.matrix[2][0]=2; 


    //Calculando o resultado 
    Matrix<T> power_matrix=matrix_pow<T, T>(coefficients_matrix, n);
    Matrix<T> result=power_matrix*initial_matrix;


  //Resultado
  return result;

};

//Função que calcula os termos P(n), P(n+1), P(n+2) da sequência dos números de Perrin a menos de uma relação de conngruência
template<typename T>
Matrix<T> modular_perrin_matrix(T n, T modulus){

  //Variáveis locais
  Matrix<T> coefficients_matrix, initial_matrix;


  //Procedimentos
    //Inicializando a matriz de coeficientes
    coefficients_matrix.reshape(3,3);
    coefficients_matrix.matrix[0][0]=0; coefficients_matrix.matrix[0][1]=1; coefficients_matrix.matrix[0][2]=0; 
    coefficients_matrix.matrix[1][0]=0; coefficients_matrix.matrix[1][1]=0; coefficients_matrix.matrix[1][2]=1; 
    coefficients_matrix.matrix[2][0]=1; coefficients_matrix.matrix[2][1]=1; coefficients_matrix.matrix[2][2]=0; 

    //Inicializando a matriz de valores P(0), P(1), P(2)
    initial_matrix.reshape(3,1);
    initial_matrix.matrix[0][0]=3; initial_matrix.matrix[1][0]=0; initial_matrix.matrix[2][0]=2; 


    //Calculando o resultado 
    Matrix<T> power_matrix=matrix_powmod<T, T>(coefficients_matrix, n, modulus);
    Matrix<T> temp=power_matrix*initial_matrix;
    Matrix<T> result=matrix_mod<T, T>(temp, modulus);

  //Resultado
  return result;

};



//*************************************************************************************
//FIM DO HEADER
#endif
