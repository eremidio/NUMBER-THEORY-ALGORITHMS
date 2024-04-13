//VAMOS CRIAR UM PROGRAMA PARA IMPLEMENTAR O ALGORITMO DE LEGENDRE PARA FATORAR NÚMEROS DA FORMA n=(a^k)+(b^k) OU n=(a^k)-(b^k)

/*
O SEGUINTE TEOREMA DEVIDO A LEGENDRE É ÚTIL PARA FAORAR NÚMEROS INTEIROS DAS FORMAS n=(a^k)+(b^k) OU n=(a^k)-(b^k), COM a,b,k INTEIROS E mdc(a,b)=1.
TEOREMA: SEJA n=(a^k)+(b^k) OU n=(a^k)-(b^k), COM a,b,k INTEIROS E mdc(a,b)=1, A MENOS DE FATORES ALGÉBRICOS, TODOS OS FATORES PRIMOS DE n TEM A 
FORMA p=lk+1 PARA l INTEIRO. SE DECONSIDERAMOS OS CASOS a,b=2 E  n=(a^k)-(b^k) COM k PAR TÊM-SE QUE p=2lk+1.

TAL TEOREMA É PARTICULARMENTE ÚTIL NA BUSCA DE FATORES PRIMOS DE NÚMEROS DE FORMA ESPECIAL DADA ACIMA. USAREMOS O TESTE AQUI PARA INTEIROS DE 64 BITS.

PARA REFERÊNCIAS:


*/  

//****************************************************************************************************************************************************
//CABEÇALHO
#ifndef LEGENDRE_SPECIAL_PURPOSE_FACTORIZATION_ALGORITHM_H
#define LEGENDRE_SPECIAL_PURPOSE_FACTORIZATION_ALGORITHM_H
#include"mod_bin_exponentiation.h"
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<math.h>


//****************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void legendre_special_purpose_factorization_algorithm(uint64_t, uint64_t, uint64_t, signed);

//****************************************************************************************************************************************************
//FUNÇÕES

//Função
void legendre_special_purpose_factorization_algorithm(uint64_t a, uint64_t b, uint64_t k, signed signal){

 //Variáveis locais
 uint64_t N, root;
 uint64_t divisor, i, step;

 //Procedimentos
 //Cálculo do número a ser fatorado
 if(signal==1){
  N=bin_pow(a, k)+bin_pow(b, k);
  step=2;
              }

 else if(signal*(-1)==1){
  N=bin_pow(a, k)-bin_pow(b, k);
  step=1;
                        }

 else{
  printf("O último argumento passado a função deve ser 1 ou -1.\n");
  return;
     };

 printf("Número a ser fatorado: %lu\n", N);
 root=sqrt(N);


 //Loop principal: busca por fatores até N^(1/2)
 for(i=1; ;i++){

  divisor=(k*step*i)+1;

  if((N%divisor)==0){

   printf("Fator de %lu encontrado: %lu.\n", N, divisor);
   printf("Cofator: %lu.\n", (N/divisor));
   N/=divisor;

                    };

  if(divisor>root)
   break;

               };

 //Caso nenhum fator tenha sido encontrado na etapa anterior
 printf("Não foram encotrado fatores primos de %lu.\n", N);
 
                                                                                                        };

//****************************************************************************************************************************************************
//FIM DO HEADER
#endif
