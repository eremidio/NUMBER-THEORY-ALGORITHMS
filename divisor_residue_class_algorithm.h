//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE CÁLCULO DE DIVISORES DE UM INTEIRO A MENOS DE UMA CONGRUÊNCIA 

/*
SEJAM r, s, n INTEIROS TAIS QUE r<s<n, O ALGORITMO DE LENSTRA PARA DIVISORES EM CLASSES RESIDUAIS RETORNA OS DIVISORES d QUE SATISFAZEM A RELAÇÃO: d= r (mod s). ESTE
ALGORITMO É PARTICULARMENTE ÚTIL COMO SUBROTINA EM OUTROS ALGORITMOS MAIS SOFISTICADOS COMO O TESTE DE PRIMALIDADE APR-CL E O TESTE DE PRIMALIDADES (n+1) E (n²-1)
GENERALIZADO.

O ALGORITMO FUNDAMENTA-SE-SE NO ALGORITMO DE EUCLIDES EXTENDIDO. CADEIAS EUCLIDIANAS a(i), b(i), c(i) COM CONDIÇÕES INICIAIS DETERMINADAS A MENOS DE ALGUMAS RELAÇÕES DE
CONGRUÊNCIA SÃO CÁLCULADAS E OS POSSÍVEIS VALORES DESTA SEQUÊNCIA DEVEM SATISFAZER UM SISTEMA DE EQUAÇÕES LINEARES ENVOLVENDO OS VALORES DE r, s, n, a(i), b(i), c(i).
OS VALORES DE x, y INTEIROS POSITIVOS OBTIDOS NA SOLUÇÃO DESTE SISTEMA SÃO DIVISORES DE n SATISFAZENDO A RELAÇÃO d = r (mod s).

PARA MAIORES REFERÊNCIAS: Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance
                          A Course In Computational Algebraic Number Theory by Henri Cohen

*/


//***************************************************************************************************************************************
//CABEÇALHO
#ifndef DIVISOR_RESIDUE_CLASS_ALGORITHM_H
#define DIVISOR_RESIDUE_CLASS_ALGORITHM_H
#include<stdint.h>
#include<inttypes.h>
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>


//***************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t gcd(int64_t, int64_t);
int64_t modular_inverse(int64_t, int64_t);
void quadratic_system_equation_solver(int64_t*, int64_t, int64_t, int64_t, int64_t, int64_t, int64_t, int64_t);
void divisors_residue_class_algorithm(int64_t, int64_t, int64_t);

//***************************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides para o cálculo do mdc de dois inteiros
int64_t gcd(int64_t a, int64_t b){
if(b==0)
return a;
else
return gcd(b, (a%b));
                                 };

//Função que calcula o inverso modular de um número inteiro a (mod n) usando o algoritmo extendido de Euclides
int64_t  modular_inverse(int64_t a, int64_t n){
//Variáveis locais
int64_t  r0,r1, x0, x1, r2, x2;
//Procedimentos 
//Ajuste de variáveis
r0=a;
r1=n;
r2=1;
x0=1;
x1=0;

//Calculando os valores finais dos coeficientes recursivamente
while(r2>0){
int64_t quotient= floor(r0/r1);

r2=r0-quotient*r1;
x2=x0-quotient*x1;

//Atualizando variáveis para a próxima iteração
if(r2>0){
r0=r1;
r1=r2;
x0=x1;
x1=x2;
        };
            };

//Resultado
if(x1<0)
return(x1+n);
else
return x1;
                                              };

//Função que resolve um sistema de equações do segundo grau: ax+by=c, (xs+r)(ys+r')=n 
void quadratic_system_equation_solver(int64_t* divisor, int64_t a, int64_t b, int64_t c, int64_t s, int64_t r, int64_t r_, int64_t n){
//Variáveis locais
int64_t* x_list=NULL;
int64_t* y_list=NULL;
int64_t counter=0;
int64_t limitant=1, difference;

//Procedimentos
//1ª etapa: resolução da equação ax+by=c
//Ajuste de variáveis
while((limitant*a)<c)
limitant++;
limitant--;

//Calculando valores de x, y satidfazendo a relação acima
for(int64_t i=limitant; i>0; --i){
difference=(c-(i*a))%b;

if(difference==0){
counter++;
x_list=(int64_t*)realloc(x_list, counter*sizeof(int64_t));
y_list=(int64_t*)realloc(y_list, counter*sizeof(int64_t));

x_list[counter-1]=i;
y_list[counter-1]=((c-(i*a))/b);
                 };
                                 };

//TESTE USE UM// APÓS O MESMO
//printf("c: %li\n", c);
//printf("b: %li\n", b);
//printf("a: %li\n", a);
//printf("r: %li\n", r);
//printf("s: %li\n", s);
//printf("r': %li\n", r_);
//printf("Lista de possíveis soluções de ax+by=c, (xs+r)(ys+r')=n :\n");
//printf("x: ");
//for(int64_t k1=0; k1<counter; k1++)
//printf("%li, ", x_list[k1]);
//printf("\n");
//printf("y: ");
//for(int64_t k2=0; k2<counter; k2++)
//printf("%li, ", y_list[k2]);
//printf("\n");



//Verificando se os valores obtidos na etapa anterior satisfaz a equação (xs+r)(ys+r')=n 
for(int64_t j=0; j<counter; j++){
if( (((x_list[j]*s)+r)*((y_list[j]*s)+r_))==n){
(*divisor)=((x_list[j]*s)+r);

//TESTE USE UM// APÓS O MESMO
//printf("Divisor encontrado: %li\n", (*divisor));

break;
                                              };
                                };

//Limpando o cachê de memória
free(x_list);
free(y_list);
                                                                                                                                     };

//Algoritmo que calcula divisores d de um inteiro n satisfazendo a relação de congruência d = r (mod s), com r<s<n
void divisors_residue_class_algorithm(int64_t r, int64_t s, int64_t n){
//Restrições
if(gcd(r, s)>1 || r>=s){
printf("O algoritmo não se aplica aos parâmetros definidos.\n");
return;
                       };

//Variáveis locais
int64_t a0, b0, c0, a1, b1, c1, a2, b2, c2;
int64_t c;
int64_t r0, r1;
int64_t t=0, i;
int64_t divisors, divisors_counter=0;
int64_t * a_list=NULL;
int64_t * b_list=NULL;
int64_t * c_list=NULL;
int64_t * divisors_list=NULL;

//Procedimentos
//Ajuste de variáveis
r0=modular_inverse(r, s);
r1=(n*r0)%s;
a0=s;
a1=(r0*r1)%s;
b0=0;
b1=1;
c0=0;
c1=(((n*r0)-(r*a1))/s)%s;

//Cálculo das cadeias Euclidianas usadas no algoritmo
while(true){
t++;
int64_t quotient=floor(a0*1.0/a1);

a2=a0-quotient*a1;
b2=b0-quotient*b1;
c2=c0-quotient*c1;

a_list=(int64_t*)realloc(a_list, t*sizeof(int64_t));
a_list[t-1]=a2;
b_list=(int64_t*)realloc(b_list, t*sizeof(int64_t));
b_list[t-1]=b2;
c_list=(int64_t*)realloc(c_list, t*sizeof(int64_t));
c_list[t-1]=c2;

//Fim do loop
if(a2==0)
break;

//Atualizando variáveis para a proxima iteração
a0=a1;
a1=a2;
b0=b1;
b1=b2;
c0=c1;
c1=c2;
           };

//Cálculo de possíveis divisores de n satisfazendo d= r (mod s)
for(i=0; i<t; ++i){
c=(c_list[i]%s);


if((i%2)==0 && (c<=((-1)*s) || c>=s))
continue;
if((i%2)==1 && (c<=(2*a_list[i]*b_list[i]) || c>=((a_list[i]*b_list[i])+floor(n/(1.0*s*s)))))
continue;

if(c<0)
c+=s;

quadratic_system_equation_solver(&divisors, a_list[i], b_list[i], c, s, r, r1, n);

if((n%divisors)==0){
divisors_counter++;
divisors_list=(int64_t*)realloc(divisors_list, divisors_counter*sizeof(int64_t));
divisors_list[divisors_counter-1]=divisors;
                   };

                  };


//Exibindo o resultado da execução do algoritmo
if(divisors_counter==0)
printf("Não foram encontrados divisores de %li congruentes %li módulo %li.\n", n, r, s);
else{
printf("Lista de divisores de %li congruentes %li módulo %li:\n", n, r, s);
for(int64_t i=0; i<divisors_counter; ++i)
printf("%li\n", divisors_list[i]);
    };


//Limpando o cachê de memória
end:
free(a_list);
free(b_list);
free(c_list);
free(divisors_list);
                                                                      };




//***************************************************************************************************************************************
//FIM DO HEADER 
#endif
