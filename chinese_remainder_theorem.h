//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TEOREMA DE RESÍDUO CHINÊS

/*
O TEOREMA DE RESÍDUO CHINÊS AFIRMA QUE DADO AS RELAÇÕES DE CONGRUÊNCIA:
x = a(1) mod(n(1))
x = a(2) mod(n(2))
....
x = a(k) mod(n(k))

PROVIDO QUE O TERMOS DA SEQUÊNCIA n(1), n(2), ... ; SEJAM RELATIVAMENTE PRIMOS E PARA TODO i=1,2,...; 0≲ a(i) ≲ n(i).
EXISTE UM ÚNICO x QUE SATISFAZ ESTAS RELAÇÕES A MENOS DE UMA RELAÇÃO DE CONGRUÊNCIA COM N = n(1)n(2)(...)n(k).

VÁRIAS TÉCNICAS EXISTEM PARA CALCULAR O VALOR DE x QUE SATIFAZ ESTAS RELAÇÕES.
O TEOREMA PODE SER EXTENDIDO PARA CASOS EM QUE n(1), n(2), ... ; NÃO SÃO RELATIVAMENTE PRIMOS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Chinese_remainder_theorem

*/ 

//**************************************************************************************************************************
//CABEÇALHO
#ifndef CHINESE_REMAINDER_THEOREM_H
#define CHINESE_REMAINDER_THEOREM_H
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>

//**************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t chinese_remainder_theorem(int64_t[], int64_t[], int64_t);

//**************************************************************************************************************************
//FUNÇÕES
int64_t chinese_remainder_theorem(int64_t a[], int64_t n[], int64_t k){
//Variáves locais
int64_t x, status;
int64_t i;//Variáveis de iteração

//Procedimentos
//Calculando o valor x
x=a[0];//Valor inicial

while(true){
status=0;//Variável de controle
//Checando se as relações de congruência são satisfeitas
for(i=1; i<k; ++i){
if(x%n[i]!=a[i]){
status++;
break;
                };
                  };

//Condição para que todas as relações de congruências sejam satisfeitas
if(status==0)
break;
else
x+=n[0];

           };

return x;
                                                                      };

//**************************************************************************************************************************
//FIM DO HEADER
#endif
