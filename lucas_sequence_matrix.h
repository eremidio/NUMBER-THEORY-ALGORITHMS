//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O CÁLCULO DE SEQUÊNCIAS DE LUCAS USANDO MATRIZES

/*
PARA SEQUÊNCIAS DE LUCAS DO PRIMEIRO E SEGUNDO TIPO AS SEGUINTES FÓRMULAS DE DUPLICAÇÃO
DE INDEXES SÃO VÁLIDAS:
U(2n)=U(n)V(n)
V(2n)=V(n)²-2Q^n
U(2n+1)=U(n+1)V(n)-(Q^n)
V(2n+1)=V(n)V(n+1)-P(Q^n)

TAIS RELAÇÕES PODEM SER ESCRITAS EM NOTAÇÃO MATRICIAL SIMPLIFICADA:

  |U(m+1) V(m+1)|   |P  -Q|^m |U(1) V(1)|
  |             | = |     |   |         |
  | U(m)   V(m) |   |1   0|   |U(0) V(0)|



PARA MAIORES INFORMAÇÕES: Prime Numbers And Computer Methods For Factorization, by Hans Riesel

*/ 


//*************************************************************************************************************
//CABEÇALHO
#ifndef LUCAS_SEQUENCE_MATRIX_H
#define LUCAS_SEQUENCE_MATRIX_H
#include"matrix_exponentiation.h"
#include"matrix_modular_reduction.h"


//*************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T, typename U>
Matrix<T> lucas_sequence_matrix(T, T, U);
template<typename T, typename U>
Matrix<T> lucas_sequence_modular_matrix(T, T, U, U);


//*************************************************************************************************************
//FUNÇÕES

//Função que calcula a matríz correspodente aos n-ésimos e (n+1)-ésimos termos da sequência de Lucas
template<typename T, typename U>
Matrix<T> lucas_sequence_matrix(T P, T Q, U k){

  //Variáveis locais
  Matrix<T> result(2,2);
  Matrix<T> coefficients_matrix(2,2);
  Matrix<T> initial_matrix(2,2);


  //Procedimentos
    //Ajuste das matrizes
    coefficients_matrix.matrix[0][0]=P;
    coefficients_matrix.matrix[0][1]=(Q*(-1));
    coefficients_matrix.matrix[1][0]=1;
    coefficients_matrix.matrix[1][1]=0;    
    initial_matrix.matrix[0][0]=1;
    initial_matrix.matrix[0][1]=P;
    initial_matrix.matrix[1][0]=0;
    initial_matrix.matrix[1][1]=2;

    //Cálculo do resultado
    Matrix<T> powering_matrix=matrix_pow<T, U>(coefficients_matrix, k);
    result=powering_matrix*initial_matrix;

  //Resultado
  return result;    

};

//Função que calcula a matríz correspodente aos n-ésimos e (n+1)-ésimos termos da sequência de Lucas a menos de uma relação de congruência
template<typename T, typename U>
Matrix<T> lucas_sequence_modular_matrix(T P, T Q, U k, U modulus){

  //Variáveis locais
  Matrix<T> temp(2,2), result(2,2);
  Matrix<T> coefficients_matrix(2,2);
  Matrix<T> initial_matrix(2,2);


  //Procedimentos
    //Ajuste das matrizes
    coefficients_matrix.matrix[0][0]=P;
    coefficients_matrix.matrix[0][1]=(Q*(-1));
    coefficients_matrix.matrix[1][0]=1;
    coefficients_matrix.matrix[1][1]=0;    
    initial_matrix.matrix[0][0]=1;
    initial_matrix.matrix[0][1]=P;
    initial_matrix.matrix[1][0]=0;
    initial_matrix.matrix[1][1]=2;


    //Cálculo do resultado
    Matrix<T> powering_matrix=matrix_powmod<T, U>(coefficients_matrix, k, modulus);
    temp=powering_matrix*initial_matrix;
    result=matrix_mod<T, U>(temp, modulus);

  //Resultado
  return result;  


};


//*************************************************************************************************************
//FIM DO HEADER
#endif
