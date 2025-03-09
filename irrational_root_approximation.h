//VAMOS CRIAR UM PROGRAMA QUE APROXIMA RAÍZES IRACIONAIS USANDO SOLUÇÕES DA EQUAÇÃO DE PELL

/*
SE UM NÚMERO n NÃO É UM QUADRADO PERFEITO, ENTÃO A EXPRESSÃO x²-ny², NÃO SE IGUALA A ZERO A NÃO SER QUE
(x,y)=(0,0). DESTA FORMA OS VALORES DE √n USANDO SOLUÇÕES DA EQUAÇÃO a+b√n=(1+√n)^i, PARA i=1,2,3,...
ESPECIFICAMENTE OBTEMOS APROXIMAÇÕES RACIONAIS a/b PARA √n.

PARA MAIORES INFORMAÇÕES: Introduction to Modern Number Theory, by Yuri I. Manin and Alexei A. Panchishkin

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
#include<gmp.h>


//*************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void irrational_root_approximation(unsigned long, int);

//*************************************************************************************************************
//FUNÇÕES
//Função que cálcula aproximações racionais de ráizes quadradas não inteiras
/* 
NOTA: um número algébrico Q(√n)será representado como a+b√n, com a, b racionais, com as usuais regras de 
multiplicação de números reais (√n)²=n.

*/

void irrational_root_approximation(unsigned long n, int ord){


  //Variáveis locais
  mpz_t a, b, root;//Coeficientes do número algébrico z=a+b√n
  mpz_t a1, b1, a2, b2;
  mpz_t v1, v2, v3, v4;
  mpf_t q, num, den;


  //Procedimentos
    //------------------------
    printf("Aproximações racionais de √%lu: \n", n);
    printf("------------------------------------------------------------------------------------------\n");
    printf("n                                  x                                     y                               x\\y\n");
    printf("1                                  1                                     1                               1.0\n");


    //Inicializando variáveis 
    mpz_init(a); mpz_init(b); mpz_init(root);
    mpz_init(a1); mpz_init(b1);
    mpz_init(a2); mpz_init(b2);
    mpz_init(v1); mpz_init(v2); mpz_init(v3); mpz_init(v4);
    mpf_init2(q, 2048); mpf_init2(num, 2048); mpf_init2(den, 2048);

    mpz_set_ui(a, 1);  mpz_set_ui(b, 1); mpz_set_ui(root, n); 
    mpz_set_ui(a1, 1);  mpz_set_ui(b1, 1);

    for(int i=2; i<=ord; ++i){

      //Calculando o produto de números algébricos: z1=a1+b1√n, z2=a2+b2√n --> z1*z2=(a1.a2+b1.b2.n)+(b1.a2+b1.a2)√n

        //Coeficiente a 
        mpz_mul(v1, a1, a); mpz_mul(v2, b1, b); mpz_mul(v3, v2, root); mpz_add(v4, v1, v3); mpz_set(a2, v4);

        //Coeficiente b 
        mpz_mul(v1, a1, b);  mpz_mul(v2, b1, a); mpz_add(v3, v1, v2); mpz_set(b2, v3);

        //Calculando a razão entre os coeficientes
        mpf_set_z(num, a2); mpf_set_z(den, b2); mpf_div(q, num, den);

        //Exibindo o resultado do cálculo
        gmp_printf("%i                                  %Zd                                     %Zd                               %.15Ff\n", i, a2, b2, q);


      //Atualizando variáveis para a próxima iteração
      mpz_set(a1, a2); mpz_set(b1, b2); 


    };


  

    //Limpando o cachê de memória
    mpz_clear(a); mpz_clear(b); mpz_clear(root);
    mpz_clear(a1); mpz_clear(b1);
    mpz_clear(a2); mpz_clear(b2);
    mpz_clear(v1); mpz_clear(v2); mpz_clear(v3); mpz_clear(v4);
    mpf_clear(q); mpf_clear(num); mpf_clear(den);



};


//*************************************************************************************************************
//FIM DO HEADER
#endif
