//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE SHANKS PARA FATORAR NÚMEROS INTEIROS USANDO IDEAIS DE GRUPOS DE CLASSE EM CORPOS ALGÉBRICOS NÚMERICOS

/*
USANDO IDEAIS DE GRUPOS DE CLASSES EM CORPOS ALGÉBRICOS NÚMERICOS, É POSSÍVEL FATORAR NÚMEROS INTEIROS. DE FATO SENDO f(x,y)=ax²+bxy+cy², UMA FORMA QUADRÁTICA
(REPRESENTADO POR UMA TRIPLA f=(a, b, c)) DE DISCRIMINANTE Δ=b²-4ac, DEFINIMOS e=(1, 0, Δ) COMO A UNIDADE RELATIVA A OPERAÇÃO DE COMPOSIÇÃO DE FORMA QUADRÁTICAS.
f=(a, b, c) É UMA FORMA AMBÍGUA SE f FOR EQUIVALENTE A SUA INVERSA g=(a, -b, c) A MENOS DE UMA TRANSFORMAÇÃO LINEAR. 

PARA FORMAS AMBÍGUAS TRÊS CASOS SÃO POSSÍVEIS: [1] SE b=0, ENTÃO Δ=-4ac; [2] SE a=b, ENTÃO Δ=b(b-4c); [3] SE a=c, ENTÃO Δ=(b-2a)(b+2a). SEJA n UM NÚMERO A SER FATORADO
ENTÃO DEFINIMOS O DISCRIMINANTE FUNDAMENTAL Δ = (-n) SE n=3 (mod 4) OU Δ = (-4n) NO CASO GERAL. O PROBLEMA DE FATORAR UM NÚMERO INTEIRO É ENTÃO REDUZIDO A COMPUTAR 
FORMAS AMBÍGUAS. 

A ORDEM DO GRUPO DE FORMAS QUADRÁTICAS É IDENTIFICADO COM O NÚMERO DE CLASSE h(-Δ) DE UM CORPO ALGÉBRICO QUADRÁTICO Q(√-Δ). NESTE PROGRAMA USAREMOS A REGRA DE COMPOSIÇÃO DIRICHLET, VÁLIDAS APENAS EM CERTOS CASOS, PORÉM FACILMENTE COMPUTÁVEL.

PARA MAIORES REFERÊNCIAS: A Course In Computational Algebraic Number Theory by Henri Cohen
                          Primes of the Form x² + ny² : Fermat, Class Field Theory, and Complex Multiplication by D. A. Cox

*/


//******************************************************************************************************************************************************************
//CABEÇALHO
#ifndef SHANKS_CLASS_GROUP_FACTORIZATION_H
#define SHANKS_CLASS_GROUP_FACTORIZATION_H
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include<assert.h>
#include<math.h>
#include<time.h>

//CONSTANTES GLOBAIS
#define MAX_TRIALS 500

//******************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t euclides_algorithm(int64_t, int64_t);
int64_t triple_euclides_algorithm(int64_t, int64_t, int64_t);
int64_t generate_fundamental_discriminant(int64_t);
int64_t class_number(int64_t);
void generate_random_form(int64_t[], int64_t);
bool dirichlet_quadratic_form_composition(int64_t[], int64_t[], int64_t[]);
bool factorization_test(int64_t, int64_t[]);
bool quadratic_form_power(int64_t, int64_t[], int64_t[]);
void shanks_class_group_factorization(int64_t);

//******************************************************************************************************************************************************************
//FUNÇÕES
//Função que computa o mmc de dois números inteiros
int64_t euclides_algorithm(int64_t a, int64_t b){
if(b==0)
return a;
else
return euclides_algorithm(b, (a%b));
                                                };

//Função que computa o mmc de três números inteiros
int64_t triple_euclides_algorithm(int64_t a, int64_t b, int64_t c){
//Variáveis locais
int64_t two_gcd=euclides_algorithm(a, b);

//Resultado
if(two_gcd==1)
return 1;
else
euclides_algorithm(two_gcd, c);
                                                                  };

//Função que determina o discriminante fundamental associado a um inteiro
int64_t generate_fundamental_discriminant(int64_t n){
//Resultado
if((n%4)==3)
return (-1)*n;
else
return (-4)*n;
                                                    };

//Função que computa o número de classe associado a um discriminante fundamental mediante a contagem de formas quadráticas reduzidas de discriminante negativo
/*
NOTA: Este procedimento é razoável para discriminantes de até 10^10, para discriminantes maiores o algoritmo aqui descrito é computacionalmente dispendioso.
Métodos mais eficientes devem ser empregados para computar o número de classe.
*/
int64_t class_number(int64_t n){
//Variáveis locais
int64_t d=generate_fundamental_discriminant(n);
int64_t abs_d=(-1)*d;
int64_t B=floor(sqrt(abs_d/3.0));
int64_t a, b, c;
int64_t h=0;

//Procedimentos
//Ajuste de variáveis 
b=(abs_d%2);

//TESTE USE UM // APÓS O MESMO
//printf("b=%li\n", b);
//printf("|D|=%li\n", abs_d);

//Loop principal:contagem de formas reduzidas
for(; b<=B; b+=2){
//Inicializando variáveis
a=b;
if(a<=1)
a=1;

//Loop secundário sobre possiveis valores de a
for(; a<=B; a++){
c=round(((b*b)+abs_d)/4.0);

if((a*a)<c){
if((c%a)==0){
if(a==b || (a*a)==c ||b==0)
h++;
else
h+=2;
            };
           };
                };
                 };



//Resultado 
return h;
                               };

//Função que gera uma forma quadrática
void generate_random_form(int64_t quadratic_form[], int64_t discriminant){
//Semente para geração de números aleatórios
srand(time(NULL));

//Variáveis locais
double c;
int64_t a, b;
int64_t B=sqrt((llabs(discriminant)/3));

//Procedimentos
rerun:
//Definindo os parâmetros a, b
a=2+rand()%B;
b=1+rand()%a;

//Definindo o parâmetro c
c=(b*b-discriminant)/(4.0*a);

while(true){
if(floor(c)==ceil(c))
break;
else
b--;
c=(b*b-discriminant)/(4.0*a);
          };

//Resultado 
quadratic_form[0]=a;
quadratic_form[1]=b;
quadratic_form[2]=round(c);
                                                                        };


//Função que implementa o algoritmo de Dirichlet de composição de duas formas quadráticas
bool dirichlet_quadratic_form_composition(int64_t result[], int64_t quadratic_form1[], int64_t quadratic_form2[]){
//Variáveis locais
int64_t a1=quadratic_form1[0], b1=quadratic_form1[1], c1=quadratic_form1[2];
int64_t a2=quadratic_form2[0], b2=quadratic_form2[1], c2=quadratic_form2[2];
int64_t discriminant=((b1*b1)-(4*a1*c1));
int64_t a3, b3, c3, B=1;

//Restrições
//As formas quadráticas devem ter o mesmo discriminante
if(discriminant!=((b2*b2)-(4*a2*c2)))
return false;
if(triple_euclides_algorithm(a1, a2, ((b1+b2)/2))>1)
return false;

//Cálculo do parâmetro B
while((B%(2*a1))!=b1)
B++;

while(true){
if((B%(2*a2))==b2 && ((B*B)%(4*a1*a2))==discriminant)
break;
else
B+=(2*a1);
           };

//Cálculo do resultado
result[0]=(a1*a2);
result[1]=B;
result[2]=(((B*B)-discriminant)/(4*result[0]));

return true;
                                                                                                                 };

//Função que determina se uma fatoração foi obtida por meio de uma forma quadrática ambígua
bool factorization_test(int64_t n, int64_t quadratic_form[]){
//Testes que determinam se uma forma quadrática retorna uma fatoração não trivial
if(quadratic_form[1]==0){
printf("Fatores de %li: %li e %li\n", n, quadratic_form[0], quadratic_form[2]);
return true;
                        };

if(quadratic_form[0]==quadratic_form[1]){
int64_t a=quadratic_form[0], b=quadratic_form[1], c=quadratic_form[2];
if((b%2)==0){
printf("Fatores de %li: %li e %li\n", n, (b/2), ((2*c)-(b/2)));
return true;
            }
else{
printf("Fatores de %li: %li e %li\n", n, b, ((4*c)-b));
return true;
    };
                                        };

if(quadratic_form[0]==quadratic_form[2]){
int64_t a=quadratic_form[0], b=quadratic_form[1], c=quadratic_form[2];
if((b%2)==0){
printf("Fatores de %li: %li e %li\n", n, ((b/2)+a), (a-(b/2)));
return true;
            }
else{
printf("Fatores de %li: %li e %li\n", n, ((2*a)-b), (b+(2*a)));
return true;
    };
                                        };

//Resultado em caso de erro
return false;
                                                            };

//Função que eleva uma forma quadrática f=(a, b, c) a um expoente inteiro k
bool quadratic_form_power(int64_t exponent, int64_t result[], int64_t quadratic_form[]){
//Variáveis locais
int64_t quadratic_form_product[3], temp[3];
int64_t power=2;
bool stop;

//Procedimento
//Casos triviais
if(exponent==1){
result[0]=quadratic_form[0]; result[1]=quadratic_form[1]; result[2]=quadratic_form[2]; 
return true;
               };

//k=2
stop=dirichlet_quadratic_form_composition(result, quadratic_form, quadratic_form);
if(stop==true && exponent==2)
return true;

if(stop==false)
return false;

//Caso geral: k>2
//Atualizando variáveis
quadratic_form_product[0]=result[0];
quadratic_form_product[1]=result[1];
quadratic_form_product[2]=result[2];

//Loop principal
while(power<exponent){
//Computando a composição de formas quadráticas
stop=dirichlet_quadratic_form_composition(temp, quadratic_form_product, quadratic_form);

if(stop==false)
return false;

//Atualizando variáveis para a próxima iteração
quadratic_form_product[0]=temp[0];
quadratic_form_product[1]=temp[1];
quadratic_form_product[2]=temp[2];
power++;
                     };

//Resultado
result[0]=temp[0];
result[1]=temp[1];
result[2]=temp[2];
return true;
                                                                                       };


//Função que implementa o algoritmo de Shanks para fatorar números inteiros
void shanks_class_group_factorization(int64_t n){
//Variáveis locais
int64_t d=generate_fundamental_discriminant(n);
int64_t h=class_number(n);
int64_t t=0, q, m, power2=1;
int64_t random_quadratic_form[3], ambiguous_form[3];
bool test1, test2;
int64_t trials=0;

//Procedimentos
//Computando os parâmetros t e q usados no algoritmo
if(h==1){
q=1;
t=0;
        };

while((h%2)==0){
h/=2;
t++;
               };
q=h;

//Gerando uma forma quadrática aleatória
restart_1:
generate_random_form(random_quadratic_form, d);

test2=factorization_test(n, random_quadratic_form);
if(test2==true)
return;

//Testando se g=f^q retorna uma fatoração de não trivial
test1=quadratic_form_power(q, ambiguous_form, random_quadratic_form);
if(test1==false)
goto restart_1;

test2=factorization_test(n, ambiguous_form);

if(test2==true)
return;
else{
if(q==1 && t==0){
trials++;
if(trials>MAX_TRIALS){
printf("O algoritmo não foi capaz de encontrar fatores primos do número em questão.\n");
return;
                     };

goto restart_1;
                };

    };

//Etapa 2 do algoritmo: testando se para algum no intervalo 1,... t; g^(2^m) retorna uma fatoração não trivial
//Restrição
if(t==0)
goto restart_1;

//Atualizando variáveis
random_quadratic_form[0]=ambiguous_form[0];
random_quadratic_form[1]=ambiguous_form[1];
random_quadratic_form[2]=ambiguous_form[2];

//Loop principal
for(m=1; m<t; m++){
power2*=2;
test1=quadratic_form_power(power2, ambiguous_form, random_quadratic_form);
test2=factorization_test(n, ambiguous_form);
if(test2==true)
return;
                  };

//Reinicializando o algoritmo
trials++;
if(trials>MAX_TRIALS){
printf("O algoritmo não foi capaz de encontrar fatores primos do número em questão.\n");
return;
                     };
goto restart_1;

                                                };

//******************************************************************************************************************************************************************
//FIM DO HEADER
#endif
