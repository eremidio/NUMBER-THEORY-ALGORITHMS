//VAMOS CRIAR UM PROGRAMA QUE COMPUTA O NÚMERO DE CLASSE DE UM CORPO ALGÉBRICO QUADRÁTICO IMAGINÁRIO COM DISCRIMINANTE NEGATIVO USANDO FORMAS QUADRÁTICAS REDUZIDAS

/*
O CÁLCULO DO NÚMERO DE CLASSE PARA UM CORPO ALGÉBRICO QUALQUER EM SUA FORMULAÇÃO GERAL É EXTREMAMENTE COMPILACADA. ENVOLVENDO COMPLEXAS RELAÇÕES FUNCIONAIS ENVOLVENDO A
FUNÇÃO ZETA DE DEDEKIND. 

PARA CORPOS QUADRÁTICOS IMAGINÁRIOS Q(√-n) COM n RAZOAVELMENTE PEQUENO (n<10^9) UMA POSSISIBILIDADE É CONTABILIZAR O NÚMERO DE FORMAS QUADRÁTICAS REDUTÍVEIS COM
DISCRIMINANTE -n, PARA ax²+bxy+cy², O DISCRIMINANTE É DADO POR: Δ=b²-4ac.

UMA FORMA QUADRÁTICA É DITA SER REDUTÍVEL SE A SEGUINTE RELAÇÃO FOR SATISFEITA: |b|≲ a ≲ c. SE UMA DESTA RELAÇÕES FOR UMA IGUALDADE ENTÃO b ≳ 0.

*/

//*********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef CLASS_NUMBER_QUADRATIC_FIELD_REDUCED_QUADRATIC_FORMS_H
#define CLASS_NUMBER_QUADRATIC_FIELD_REDUCED_QUADRATIC_FORMS_H
#include"class_number.h"//As dependências necessárias estão inclusas aqui
#include<math.h>

//*********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t class_number_negative_discriminant2(int64_t);
int64_t two_gcd(int64_t, int64_t);
int64_t triple_gcd(int64_t, int64_t, int64_t);
int64_t class_number_negative_discriminant3(int64_t);

//*********************************************************************************************************************************************************************
//FUNÇÕES
//Função que calcula o número de classe para aum corpo algébrico númerico cujo discriminante é fundamental
int64_t class_number_negative_discriminant2(int64_t d){
//Restrição
if(is_fundamental_discriminant(d)==false)
return (-1);

//Variáveis locais
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

//Função que calcula algoritmo de Euclides para dois ou mais argumentos
int64_t two_gcd(int64_t a, int64_t b){
if(b==0)
return a;
else
return two_gcd(b, a%b);
                                     };

int64_t triple_gcd(int64_t a, int64_t b, int64_t c){
return two_gcd(two_gcd(a, b), c);
                                                   };

//Função que calcula o número de classe para aum corpo algébrico númerico cujo discriminante não é fundamental
/*
NOTA: Para este cálculo existe uma fórmula relacionando h(d) com h(d0) onde d=d0.f²; onde d0 sendo um discriminante fundamental.
A fórmula explicita é:

h(d)/w(d) = [h(d0)/w(d0)]f Π{1-(d0|p)/p}, na qual o produtório é tomado sobre todos os primos p que dividem o fator multiplicativo f.
w(d) é a função substitution_number definida no noheader class_number.h que calcula o número de substituições que deixam uma forma quadrática invariante.
Esta fórmula fornce um resultado preciso.
*/

int64_t class_number_negative_discriminant3(int64_t d){
//Restrição
if(is_fundamental_discriminant(d)==true)
return (-1);

//Variáveis locais
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
if((c%a)==0 && triple_gcd(a, b, (c/a))==1){
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

//*********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
