//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE PRIMALIDADE USANDO (CURVAS) CÚBICAS DE PELL PARA INTEIROS DE 64 BITS

/*

SEJA O CORPO FINITO Rp=F(p)[t]/(t³-r), ONDE p(t)=(t³-r) É IRREDUTÍVEL PARA UM DADO VALOR r. ELEMENTOS DE Rp SÃO POLINÔMIOS
DO SEGUNDO GRAU f(t)=x+yt+zt² COM A REGRA DE MULTIPLICAÇÃO USUAL (USANDO A SUBSTITUIÇÃO t³≡r E REDUÇÃO DOS COEFICIENTES 
MÓDULO p). SEJA ω UMA RAÍZ CÚBICA PRIMITVA DA UNIDADE. PODEMOS DEFINIR A NORMA DE UM ELEMENTO EM Rp PELA EXPRESSÃO
Nr([x+yt+zt²])=x³-3xyzr+y³r+z²r³ (OBTIDA MULTIPLICANDO-SE OS ELEMENTOS x+yωt+zω²t² E x+yω²t+zωt²). SEJA Up O GRUPO DE
ELEMENTOS EM Rp DE NORMA 1. A CÚBICA DE PELL COM ELEMENTOS EM F(p) (INTEIROS A MENOS DE UMA RELAÇÃO DE CONGRUÊNCIA MÓDULO p)
É DEFINIDA PELA EQUAÇÃO x³-3xyzr+y³r+z²r³=1. TAIS OBSERVAÇÕES ESTABELECEM UM ISOMORFISMO ENTRE CÚBICAS DE PELL E ELEMENTOS
EM Rp QUE POSSUI A ESTRUTURA DE UM GRUPO.

SEJA I(Rp) O CONJUNTO DE ELEMENTOS EM Rp DE NORMA NÃO NULA. A PROJETIVIZAÇÃO DE I(Rp), Pp=I(Rp)/F(p), DEFINE CLASSES DE
EQUIVALÊNCIA EM Rp. PODEMOS USAR O ISOMORFISMO ACIMA PARA COMPUTAR UM CONJUNTO DE SEQUÊNCIAS NÚMERICAS QUE (xk, yk, zk)
QUE ASSOCIA UMA TRIPLA DE ELEMENTOS EM F(p) A PONTOS EM UMA PROJETIVIZAÇÃO DA CÚBICA DE PELL. TEOREMAS GARANTEM QUE SE
CERTAS RELAÇÕES DE CONGRUÊNCIA FOREM SATISFEITAS PELAS COORDENADAS DE UM PONTO (xk, yk, zk) =[1:1:0]^k DA PROJETIVIZAÇÃO
DA CÚBICA, ENTÃO p É UM NÚMERO PRIMO.


PARA MAIORES INFORMAÇÕES: https://link.springer.com/content/pdf/10.1007/s00009-025-02839-w.pdf


*/



//*******************************************************************************************************************************************
//CABEÇALHO
#ifndef PELL_CUBIC_PRIMALITY_TEST_H
#define PELL_CUBIC_PRIMALITY_TEST_H
#include"mod_bin_exponentiation.h"
#include"matrix_exponentiation.h"
#include"matrix_modular_reduction.h"


//*******************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t set_r_value(int64_t);
Matrix<__int128_t> setup_pell_matrix(int64_t);
bool pell_cubic_primality_test(int64_t);


//*******************************************************************************************************************************************
//FUNÇÕES
//Função que define um parâmetro r usado no algoritmo
int64_t set_r_value(int64_t p){

  //Caso base: p = 2 mod 3
  if(p%3==2) return 2;


  //Caso geral: p=1 mod 3
  //Variáveis locais
  int64_t r=2, p1=(p-1)/3;

  //Procedimentos: loop principal
  while(r<p){
    if(pow_mod(r, p1, p)==1) break;
    r++;
  }

  //Resultado
  return r;

};

//Função que define uma matriz usada para se calcular coordenadas de um ponto na projetivização da cúbica de Pell
Matrix<__int128_t> setup_pell_matrix(int64_t r){

  //Variáveis locais
  Matrix<__int128_t> pell_matrix(3);


  //Procedimentos: definindo entradas das matrizes
  pell_matrix.matrix[0][0]=1; pell_matrix.matrix[0][1]=0; pell_matrix.matrix[0][2]=r;
  pell_matrix.matrix[1][0]=1; pell_matrix.matrix[1][1]=1; pell_matrix.matrix[1][2]=0;
  pell_matrix.matrix[2][0]=0; pell_matrix.matrix[2][1]=1; pell_matrix.matrix[2][2]=1;


  //Resultado
  return pell_matrix;

};


//Função que testa se um número é primo usando cúbicas de Pell
bool pell_cubic_primality_test(int64_t p){

  //Casos bases: 
  if(p<2) return false;
  if(p==2 || p==3) return true;
  if(!(p&1) || p%3==0) return false;
  if(pow_mod(2, (p-1), p)!=1) return false;//Teste de Fermat na base 2



  //Variáveis locais
  __int128_t xp, yp, zp;
  int64_t k=p/3;
  int64_t r=set_r_value(p);
  Matrix<__int128_t> pell_matrix = setup_pell_matrix(r);
  Matrix<__int128_t> power_matrix = matrix_powmod<__int128_t, int64_t>(pell_matrix, p, p);


  //Procedimentos
    //Ajuste de variáveis
    power_matrix=matrix_mod<__int128_t, int64_t>(power_matrix, p);
    xp=power_matrix.matrix[0][0]; if(xp<0) xp+=p;
    yp=power_matrix.matrix[1][0]; if(yp<0) yp+=p;
    zp=power_matrix.matrix[2][0]; if(zp<0) zp+=p;

    //Testes:
    if(p%3==2){
      if(xp==1 && yp==0 && zp== pow_mod(2, k, p)) return true;
    }

    /*
      NOTA: Para o caso p = 1 mod 3, o artigo sugere o teste adicional yp+yp²=(-1) (mod p). Alguns
            pseudoprimos podem burlar o teste sem essa condição adicional.  
    */
    if(p%3==1){
      if(r==p) return false;
      if(xp==1 && yp==pow_mod(r, k, p) && zp==0) return true;
    }


  //Resultado
  return false;

};


//*******************************************************************************************************************************************
//FIM DO HEADER
#endif
