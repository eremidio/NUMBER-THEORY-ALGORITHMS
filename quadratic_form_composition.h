//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE COMPOSIÇÃO DE FORMAS QUADRÁTICA REDUZIDAS

/*
DADO DUAS FORMAS QUADRÁTICAS BINÁRIAS f(x,y)=a1x²+b1xy+c1y² E g(x,y)=a2x²+b2xy+c2y² DE MESMO DETERMINANTE, É POSSÍVEL COMBINÁ-LAS DE MODO A OBTER UMA NOVA FORMA
QUADRÁTICA s(x,y)=a3x²+b3xy+c3y². UMA FORMA QUADRÁTICA É DITA PRIMITIVA SE mmc(a, b, c)=1. A COMPOSIÇÃO DE FORMAS QUADRÁTICAS PRIMITIVAS É ASSOCIATIVA POSSUI ELEMENTOS
INVERSOS DE FORMA QUE O CONJUNTO DE FORMAS QUADRÁTICAS PRMITIVAS DE DISCRIMINANTE NEGATIVO FORMAM UM GRUPO DENOTADO POR cl(D). NOCASO DE CORPOS ALGÉBRICOS QQUADRÁTICOS
IMAGINÁRIOS DE DISCRIMINANTE FUNDAMENTAL ESTE GRUPO É ISOMÓRFICO AO GRUPO DE CLASSES DE IDEAIS (QUOCIENTE DO GRUPO DE IDEAIS FRACIONÁRIOS MÓDULO IDEAIS PRINCIPAIS). PARA
FORMAS QUADRÁTICAS DE DISCRIMINANTE POSITIVO ESTE GRUPO É ISOMÓRFICO AO CHAMADO GRUPO DE CLASSE REDUZIDO.

O ESTUDO DA ESTRUTURA DO GRUPO cl(D) FORNECE INFORMAÇÕES IMPORTANTES SOBRE O GRUPO DE CLASSES DE IDEAIS DE UM CORPO ALGÉBRICO. SENDO h(D) O NÚMERO DE CLASSE DE UM CORPO
ALGÉBRICO h(D) ESTÁ DIRETAMENTE RELACIONADO AO GRUPO cl(D). ALGORITMOS ENVOLVENDO GRUPOS DE CLASSES IDEAIS EM CORPOS ALGÉBRICOS QUADRÁTICOS USAM A COMPOSIÇÃO DE FORMAS 
QUADRÁTICAS.

FORMAS QUADRÁTICAS REDUZIDAS QUE SÃO SEU PRÓPRIO INVERSO MULTIPLICATIVO SOB A OPERAÇÃO DE COMPOSIÇÃO DE FORMAS QUADRÁTICAS SÃO CHAMADAS DE FORMAS AMBÍGUAS. USANDO AS 
CHAMADAS FORMAS PRIMAS f(p)={p, b, (b²-D)/(4p)} E UM RESULTADO ACERCA DA NATUREZA DE FORMAS AMBÍGUAS EM cl(D) É POSSÍVEL ELABORAR UM EFICIENTE DO PONTO DE VISTA TEÓRICO
MÉTODO DE FATORAÇÃO (O ALGORITMO DE SCHNORR-SEYSEN-LENSTRA UM APRIMORAMENTO EM RELAÇÃO AO ALGORITMO DE SHANKS QUE USA FORMAS AMBÍGUAS). ESTE ALGORITMO EMBORA SEJA
ASSINTOTICAMENTE RÁPIDO E USE UM ESPAÇO POLINOMIAL, ELE NÃO É USADO PARA FINS PRÁTICOS, POIS AS OPERAÇÕES REQUERIDAS ENVOLVENDO FORMAS QUADRÁTICAS SÃO COMPUTACIONALMENTE
DISPENDIOSAS E O ALGORITMO TEM COMPLEXIDADE EXPONENCIAL PARA CERTOS VALORES.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Integer_factorization#Rigorous_running_time
                          https://en.wikipedia.org/wiki/Ideal_class_group
*/ 

//******************************************************************************************************************************************************************
//CABEÇALHO
#if !defined QUADRATIC_FORMS_COMPOSITION_H
#define QUADRATIC_FORMS_COMPOSITION_H
#include"quadratic_form_reduction.h"//Inclui as dependência necessárias
#include<math.h>

//******************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void extended_euclidean_algorithm(int64_t, int64_t, int64_t*, int64_t*, int64_t*);
void quadratic_form_composition(int64_t[], int64_t [], int64_t[]);

//******************************************************************************************************************************************************************
//FUNÇÕES 
//Algoritmo extendido de Euclides para computar o mmc de dois inteiros mmc(a,b) e oscoeficientes da identidade de Bézout ax+by=mmc(a,b)
void extended_euclidean_algorithm(int64_t a, int64_t b, int64_t* gcd, int64_t* x , int64_t* y){
//Variáveis locais
int64_t r0,r1, x0, x1, y0, y1, r2, x2, y2;
//Procedimentos 
//Ajuste de variáveis
r0=a;
r1=b;
r2=1;
x0=1;
x1=0;
y0=0;
y1=1;
//Calculando os valores finais coeficientes recursivamente

while(r2>0){
int64_t quotient= r0/r1;

r2=r0-quotient*r1;
x2=x0-quotient*x1;
y2=y0-quotient*y1;
//Atualizando variáveis para a próxima iteração
if(r2>0){
r0=r1;
r1=r2;
x0=x1;
x1=x2;
y0=y1;
y1=y2;
        };

            };

//Resultado
(*gcd)=r1;
(*x)=x1;
(*y)=y1;
                                                                                              };

//Algoritmo que computa a operação de composição de duas formas quadráticas primitivas de dicriminantes iguais
void quadratic_form_composition(int64_t quadratic_form1[], int64_t quadratic_form2[], int64_t result[]){
//Variáveis locais
int64_t a1=quadratic_form1[0], b1=quadratic_form1[1], c1=quadratic_form1[2];
int64_t a2=quadratic_form2[0], b2=quadratic_form2[1], c2=quadratic_form2[2];
double a3, b3, c3;
int64_t h, g, u1, v1, u2, v2, u, v, w;

//Restrição a formas de discriminante iguais
assert(((b1*b1)-(4*a1*c1))==((b2*b2)-(4*a2*c2)));

//Procedimentos
//Computando os coeficientes intermediários usados no algoritmo
extended_euclidean_algorithm(a1, a2, &h, &u1, &v1);
extended_euclidean_algorithm(h, ((b1+b2)/2), &g, &u2, &v2);

u=u2*u1;
v=u2*v1;
w=v2;

a3=((a1*a2)/(g*g));
b3=(b2+((2*a2)/g)*( ((b1-b2)/2)*v) -(c2*w));
c3=(((b3*b3)-g)/(4*a3));

//Resultado
result[0]=round(a3);
result[1]=round(b3);
result[2]=round(c3);
                                                                                                       };


//******************************************************************************************************************************************************************
//FIM DO HEADER
#endif
