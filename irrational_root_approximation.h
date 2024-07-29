//VAMOS CRIAR UM PROGRAMA QUE APROXIMA RAÍZES IRACIONAIS USANDO A EQUAÇÃO DE PELL

/*
SE UM NÚMERO n NÃO É UM QUADRADO PERFEITO, ENTÃO A EQUAÇÃO x²-ny², NÃO SE IGUALA A
ZERO A NÃO SER QUE (x,y)=(0,0). DESTA FORMA OS VALORES DE √n USANDO SOLUÇÕES DA 
EQUAÇÃO a+b√n=(1+√n)^i, PARA i=1,2,3,... ESPECIFICAMENTE OBTEMOS APROXIMAÇÕES 
RACIONAIS a/b.

PARA MAIORES INFORMAÇÕES: 

*/ 

//*************************************************************************************************************
//CABEÇALHO
#ifndef IRRATIONAL_ROOT_APPROXIMATION_H
#define IRRATIONAL_ROOT_APPROXIMATION_H
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

//*************************************************************************************************************
//ESTRUTURAS USADAS NO ALGORITMO

/* 
NOTA: um número algébrico Q(√n)será representado como a+b√n, com a, b racionais, com as usuais regras de 
multiplicação de números reais √n.√n=n, as expressões são simplificadas usando as regras usuais.

*/

struct algebraic_number{
  int64_t a;
  int64_t b;
  int64_t root;

};

//*************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
struct algebraic_number algebraic_multiplication(struct algebraic_number, struct algebraic_number);
void irrational_root_approximation(int64_t, int);

//*************************************************************************************************************
//FUNÇÕES
//Função que implementa a multiplicação algébrica de dois inteiros
struct algebraic_number algebraic_multiplication(struct algebraic_number z1, struct algebraic_number z2){

  //Restrição
  assert(z1.root==z2.root);

  //Variáveis locais
  struct algebraic_number result;


  //Procedimentos
    //Cálculo do resultado
    result.root=z1.root;
    result.a=(z1.a*z2.a)+(z1.b*z2.b*result.root);
    result.b=(z1.b*z2.a)+(z1.a*z2.b);


  //Resultado
  return result;

};




//Função que cálcula aproximações racionais de ráizes quadradas não inteiras
void irrational_root_approximation(int64_t n, int ord){

  //Variáveis locais
  struct algebraic_number z={1, 1, n};
  double ratio;
  int64_t x=1, y=1;


  //Procedimentos
    //------------------------
    printf("Aproximações racionais de √%li: \n",n );
    printf("------------------------------------------------------------------------------------------\n");
    printf("n                       x                              y                               x\\y\n");
    printf("1                       1                              1                               1.0\n");
    
    //Loop principal
    for(int i=2; i<=ord; ++i){

      z=algebraic_multiplication(z, z);
      x=z.a;
      y=z.b;
      ratio=(x*1.0)/y;

      printf("%d                      %li                            %li                              %lf \n",
              i, x, y, ratio);

    }  


};


//*************************************************************************************************************
//FIM DO HEADER
#endif
