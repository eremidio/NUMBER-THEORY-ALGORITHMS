//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA ROTINA QUE REDUZ FORMAS QUADRṔATICAS A UMA FORMA REDUZIDA

/*
FORMAS QUADRÁTICAS BINÁRIAS f(x,y)=ax²+bxy+cy² SÃO EXTREMAMENTE IMPORTANTES EM TEORIA DE NÚMEROS. UMA FORMA QUADRÁTICA PODE SER REPRESENTADO POR UMA TRIPLA ORDENADA (a, b, c), O DISCRIMINANTE DEUMA FORMA QUADRÁTICA É DADO POR Δ=b²-4ac. UMA FORMA QUADRÁTICA É DITA SER REDUTÍVEL SE A SEGUINTE RELAÇÃO FOR SATISFEITA: |b|≲ a ≲ c. SE UMA
DESTA RELAÇÕES FOR UMA IGUALDADE ENTÃO b ≳ 0.

FORMAS QUADRÁTICAS PODEM SER TRANSFORMADAS EM OUTRAS QUADRÁTICAS VIA UMA TRANSFORMAÇÃO LINEAR. TAL FATO ESTABELECE UMA RELAÇÃO DE EQUIVALÊNCIA ENTRE FORMAS QUADRÁTICAS.
DUAS FORMAS QUADRÁTICAS PERTENCEMA MESMA CLASSE DE EQUIVALÊNCIA SE ELAS ESTÃO RELACIONADAS A MENOS DE UMA TRANSFORMAÇÃO LINEAR.

UM TEOREMA DE GAUSS AFIRMA QUE TODA FORMA QUADRÁTICA DE DISCRIMINANTE NEGATIVO É EQUIVALENTE A UMA FORMA QUADRÁTICA REDUZIDA. ESTE TEOREMA PERMITE DETERMINAR UM
CONJUNTO DE CLASSES DE EQUIVALÊNCIAS DE FORMAS QUADRÁTICAS.

FORMAS QUADRÁTICAS BINÁRIAS ESTÃO DIRETAMENTE RELACIONADAS COM A TEORIA DE CORPOS ALGÉBRICOS QUADRÁTICOS (REAIS E IMAGINÁRIOS) E SÃO DE GRANDE INTERESSE EM TEORIA
DE NÚMEROS ALGÉBRICA.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Binary_quadratic_form
*/


//******************************************************************************************************************************************************************
//CABEÇALHO
#if !defined QUADRATIC_FORMS_REDUCTION_H
#define QUADRATIC_FORMS_REDUCTION_H
#include<stdint.h>
#include<inttypes.h>
#include<stdbool.h>
#include<assert.h>
#include<stdio.h>

//******************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool negative_discriminat_checker(int64_t[]);
void reduce_quadratic_form(int64_t[]);

//******************************************************************************************************************************************************************
//FUNÇÕES
//Função que checa se uma forma quadrática possui discriminante negativo
bool negative_discriminat_checker(int64_t quadratic_form[]){
//Variáveis locais
int64_t a=quadratic_form[0], b=quadratic_form[1], c=quadratic_form[2];
int64_t discriminant=((b*b)-(4*a*c));
//Resultado
if(discriminant<0)
return true;
else
return false;

                                                           };

//Função que tranasforma uma forma quadrática em forma reduzida equivalente
void reduce_quadratic_form(int64_t quadratic_form[]){
//Restrição
assert(negative_discriminat_checker(quadratic_form)==true && quadratic_form[0]>0);

//Variáveis locais
int64_t a=quadratic_form[0], b=quadratic_form[1], c=quadratic_form[2];
int64_t discriminant=((b*b)-(4*a*c));
int64_t b_, c_, temp;

//Procedimento
//TESTE USE UM // APÓS O MESMO
//printf("Δ=%li\n", discriminant);

//Loop principal
while(a>c || b>a || (-1)*a>=b){
//Caso 1: a>c
if(a>c){
b=(-1)*b;
temp=a;
a=c;
c=temp;
break;
       };

//Caso 2: a≲c e |b|>a
if(a<=c){

if(b>a || (-1)*a>=b){
//Deteminação dos parâmetros b, c  da forma quadrática reduzida
for(b_=((-1)*a+1); b_<=a; b_++){
temp=b_;

while(temp<0)
temp+=(2*a);

c_=((b_*b_)-discriminant)/(4*a);
if(temp==(b%(2*a))){
c=c_;
b=b_;
break;
                   };
                               };

                    };

        };

                              };//Fim do loop principal


//Ajuste final dos parâmetros
end:
if(a==c){
if((-1)*a<b && b<0)
b=(-1)*b;
        };

//Resultado
quadratic_form[0]=a;
quadratic_form[1]=b;
quadratic_form[2]=c;
                                                    };

//******************************************************************************************************************************************************************
//FIM DO HEADER
#endif
