//VAMOS CRIAR UM PROGRAMA QUE COMPUTA O NÚMERO DE CLASSE DE UM CORPO QUADRÁTICO DE DISCRIMINANTE POSITIVO USANDO FORMAS QUADRÁTICAS REDUZIDAS

/*
PARA CORPOS ALGÉBRICOS Q(√d) COM d>0 E SUFICIENTEMENTE PEQUENO É POSSÍVEL COMPUTAR O NÚMERO DE CLASSE REALIZANDO-SE A CONTAGEM DE FORMAS QUADRÁTICAS REDUZIDAS DE
DISCRIMINANTE POSITIVO. UMA FORMA QUADRÁTICA ax²+bxy+cy², CUJO DISCRIMINANTE Δ=b²-4ac>0 É REDUZIDA SE |√Δ -2|a||<b <√Δ.

SEJA r(a, b) = r, O MENOR INTEIRO TAL QUE r= b (mod 2a) E PARA UMA FORMA QUADRÁTICA f=(a, b, c), A TRANSFORMAÇÃO ρ(a, b, c)=(c, r(-b, c), [(r²(-b, c)-Δ)/(4c)]).
EXISTE UM TEOREMA QUE GARANTE QUE APÓS UM NÚMERO FINITO DE PASSOS A TRANSFORMAÇÃO ρ SEMPRE PRODUZ UMA FORMA QUADRÁTICA REDUZIDA, ALÉM DISSO DE f FOR REDUZIDA PARA
QUALQUER n INTEIRO SUFICIENTEMENTE GRANDE (ρ^n)f.

O NÚMERO DE ORBITAS LEVANDO EM CONTA A TRANSFORMAÇÃO ρ DEFINE O NÚMERO DE CLASSE REDUZIDO h+(Δ) (O GRUPO DE CLASSES DE IDEAIS REDUZIDO LEVA EM COMSIDERAÇÃO IMERSÕES DE UM CORPO ALGÉBRICO NO CONJUNTO DOS NÚMEROS REAIS). IDENTIFICANDO AS FORMAS (a, b, c) COM (-a, b, -c) É POSSÍVEL COMPUTAR O NÚMERO DE CLASSE h(D).

ALGORITMOS MAIS EFICIENTES (SUBEXPONENCIAIS) PARA COMPUTAR h(D) PENVOLVEM A COMPUTAÇÃO DE REGULADORES E UNIDADES FUNDAMENTAIS Q(√d).

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Class_number_formula
                          https://en.wikipedia.org/wiki/Ideal_class_group
                          https://en.wikipedia.org/wiki/Narrow_class_group

*/

//****************************************************************************************************************************************************************
//CABEÇALHO
#ifndef CLASS_NUMBER_QUADRATIC_FIELD_POSITIVE_DISCRIMINANT_H
#define CLASS_NUMBER_QUADRATIC_FIELD_POSITIVE_DISCRIMINANT_H
#include"class_number2.h"//As dependências necessárias estão inclusas aqui
#include<stdlib.h>

//****************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool positive_discriminat_checker(int64_t[]);
void reduce_quadratic_form_positive_discriminant(int64_t[]);
int64_t class_number_positive_discriminant(int64_t);
int64_t narrow_class_number_positive_discriminant(int64_t);

//****************************************************************************************************************************************************************
//FUNÇÕES
//Função que checa se uma forma quadrática de discriminante positivo está reduzida 
bool positive_discriminat_checker(int64_t quadratic_form[]){
//Variáveis  locais
int64_t a=quadratic_form[0], b=quadratic_form[1], c=quadratic_form[2];
int64_t discriminant=((b*b)-(4*a*c));

//Restrição a formas de discriminante positivo
assert(discriminant>0);

//Resultado
int64_t tester=llabs(sqrt(discriminant)-(2*a));
if(tester>=b || b>=sqrt(discriminant))
return false;
else
return true;
                                                           };

//Função que reduz uma forma quadrática de discriminante positivo
void reduce_quadratic_form_positive_discriminant(int64_t quadratic_form[]){
//Caso trivial: a forma já está na sua forma reduzida
if(positive_discriminat_checker(quadratic_form)==true)
return;

//Variáveis  locais
int64_t a=quadratic_form[0], b=quadratic_form[1], c=quadratic_form[2];
int64_t a_, b_, c_, r, positive_a;
int64_t discriminant=((b*b)-(4*a*c));
bool is_reduced;

//Restrição a formas de discriminante positivo
assert(discriminant>0);

//Procedimento
reduction:
//Ajuste de variáveis 
positive_a=llabs(a);

//Aplicando a transformação ρ
a_=c;

r=b;
while(true){
//Condições que checam valor de r
if(positive_a>sqrt(discriminant)){
if(r>(-1)*positive_a && r<=positive_a)
break;
                                 };

if(positive_a<sqrt(discriminant)){
if(r>(sqrt(discriminant)-(2*positive_a)) && r<sqrt(discriminant))
break;
                                 };

//Ajuste de variáveis
r+=(2*a);
           };
b_=r;
c_=round(((1.0*r*r)-discriminant)/(4*c));

//Teste se a  forma quadrática está reduzida ou não
quadratic_form[0]=a_;
quadratic_form[1]=b_;
quadratic_form[2]=c_;

if(positive_discriminat_checker(quadratic_form)==true)
return;
else{
a=quadratic_form[0];
b=quadratic_form[1];
c=quadratic_form[2];
goto reduction;
    };
                                                                          };

//Função que calcula o número de classe reduzido para um corpo algébrico cujo discriminante é positivo
int64_t narrow_class_number_positive_discriminant(int64_t d){
//Variáveis locais
int64_t a, b, c;
int64_t root=sqrt(d), tester;
int64_t h=0;

//Procedimento
//Loop principal
for(b=(d%2); b<root; b+=2){
for(a=((-1)*root)+1; a<root; a++){
tester=llabs(root-(2*llabs(a)));
if(b>tester && (llabs((b*b)-d)%llabs(4*a))==0)
h++;
                                 };
                         };

//Resultado
return h/2;
                                                            };

//Função que calcula o número de classe reduzido para um corpo algébrico cujo discriminante é positivo
int64_t class_number_positive_discriminant(int64_t d){
return narrow_class_number_positive_discriminant(d)/2;
                                                     };


//****************************************************************************************************************************************************************
//FIM DO HEADER
#endif
