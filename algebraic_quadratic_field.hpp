//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA A CLASSE DOS CORPOS ALGÉBRICOS QUADRÁTICOS PARA DISCRIMINANTES DE ATÉ 64 BITS (~10^18) E ALGUNS ALGORITMOS SIMPLES RELACIONADOS

/*
CORPOS ALGÉBRICOS QUADRÁTICOS Q(√d) SÃO FORMADOS POR ELEMENTOS DO TIPO z=a+b(√d), ONDE d É UM INTEIRO QUE NÃO É UM QUADRADO PERFEITO. CORPOS ALGÉBRICOS QUADRÁTICOS SÃO
EXTENSÕES DE CORPOS NÚMERICOS ORDENADOS COMO OS REAIS, RACIONAIS E SÃO DE GRANDE IMPORTÂNCIA PARA DIVERSAS ÁREAS DA MATEMÁTICA COMO ÁLGEBRA ABSTRATA EM QUE SÃO USADOS
PARA DEMONSTRAR O TEOREMA DE ABEL, TEORIA DOS NÚMEROS NA QUAL SÃO FERRAMENTAS ONIPRESENTES EM UMA GRANDE VARIEDADE DE ALGORITMOS, ANÁLISE DE FUNÇÕES DE VARIÁVEIS
COMPLEXAS (NO CORPO DOS NÚMEROS COMPLEXOS d =(-1) E √d=i, ONDE i É A UNIDADE IMAGINÁRIA).

AS OPERAÇÕES ARITMÉTICAS USUAIS PARA DOIS INTEIROS z=a+b(√d) E z'=u+v(√d) SÃO DEFINIDOS PELAS REGRAS TÍPICAS DAS OPERAÇÕES COM NÚMEROS COMPLEXOS:
z+z'=(a+u)+(b+v)(√d)
z-z'=(a-u)+(b-v)(√d)
z.z'=(au+bvd)+(av+bu)(√d)
z/z'=[1/(u²-v²d)][(au-bvd)+(bu-av)(√d)]

UM NÚMERO z EM Q(√d) É DITO SER UM INTEIRO SE ELE FOR UMA SOLUÇÃO DE UMA EQUAÇÃO DO SEGUNDO GRAU z²+pz+q=0, COM p, q RACIONAIS. A CLASSE DE INTEIROS EM Q(√d) INCLUI
NÚMEROS DA FORMA z=r+s√d SE d=2,3 (mod 4) OU z=r+s(-1+√d)/2 SE d= 1 (mod 4).

PARA z=r+s(√d) SEU CONJUGADO É DENOTADO POR z=a-b(√d) E A SUA NORMA É DEFINIDA COMO N(z)=z.z* OU MAIS EXPLICITAMENTE N(z)=r²-s²d SE d=2,3 (mod 4) OU 
N(z)=r²-rs-s²[(d-1)/4] SE d= 1 (mod 4). A NORMA É UMA FUNÇÃO MULTIPLICATIVA, DADO DOIS NÚMEROS z E z' EM Q(√d) ENTÃO N(z'z)=N(z')N(z). SE PARA UM DADO z, N(z)=1, ENTÃO 
z É DITO SER UMA UNIDADE NO ANEL DE INTEIROS EM Q(√d). DOIS NÚMEROS SÃO DITOS ESTAR ASSOCIADOS SE O QUOCIENTE DE UM PELO OUTRO FOR UMA UNIDADE. A ARITMÉTICA MODULAR 
USUAL DE INTEIROS PODE SER APLICADA PARA ELEMENTOS EM Q(√d) (ELA É EMPREGADA, EXEMPLO NO ALGORITMO DE CIPOLLA).

EM ALGUNS CORPOS QUADRÁTICOS (ANÉIS DE INTEIROS) CONCEITOS ELEMENTARES DA TEORIA DE NÚMEROS PODEM SER EXTENDIDOS COMO O CONCEITOS DE NÚMEROS PRIMOS, DECOMPOSIÇÃO DE
EM FATORES PRIMOS. EXEMPLOS BÁSICOS INCLUEM OS CHAMADOS INTEIROS GAUSSIANOS E OS INTEIROS DE EISENSTEIN. PORÉM, PARA CORPOS QUADRÁTICOS GERAIS ESSA SITUAÇÃO SE TORNA 
MAIS COMPLEXA. DOMÍNIOS DE FATORAÇÃO ÚNICA POSSUEM NÚMERO DE CLASSE h(d)=1. PARA d<0, h(d)=1, APENAS PARA d = -3, -4, -7, -8, -11, -12, -16, -19, -27 -28, -43,-63,
-163. O CONJUNTO DOS CORPOS QUADRÁTICOS É ISOMÓRFICO AO CONJUNTO DE FORMAS BINÁRIAS QUADRÁTICAS cl(d), FUNÇÕES f(x, y)=ax²+bxy+cy² COM OPERAÇÃO DE COMPOSIÇÃO BEM
DEFINIDA QUE O TORNA UM GRUPO, TAL ISOMORISMO É AMPLAMENTE EM VÁRIOS ALGORITMOS EM TEORIA DE NÚMEROS ALGÉBRICA COMPUTACIONAL. O NÚMERO DE CLASSE CORRESPONDE A ORDEM DO
GRUPO |cl(d)|.

ALGUNS ANÉIS DE INTEIROS EM CORPOS ALGÉBRICOS QUADRÁTICOS COMO OS INTEIROS DE EISENSTEIN E O INTEIROS KLEINIANOS SÃO DOMÍNIOS DE FATORAÇÃO ÚNICA, ISTO É, h(d)=1.

O PEQUENO TEOREMA DE FERMAT PODE SER GENERALIZADO PARA Q(√d) DA SEGUINTE FORMA: SEJA z UM ELEMENTO NO ANEL DE INTEIROS ALGÉBRICOS O(√d) EM Q(√d) E p UM PRIMO ÍMPAR NO
ANEL DOS INTEIROS RACIONAIS ENTÃO SE (d|p)=1 (SÍMBOLO DE LEGENDRE) TÊM-SE QUE z^p =z (mod p), SE (d|p)=(-1) TÊM-SE QUE z^p =z* (mod p) OU z^(p+1) = N(z) (mod p).

DEFINIÇÕES ESTABELECIDAS EM Q(√d) PODEM SER GENERALIZADAS PARA CORPOS ALGÉBRICOS DE ORDEM SUPERIORES Q(d^(1/n)) COM n>2. PORÉM A ARITMÉTICA NESTES CASOS É BEM MAIS COMPLICADA. CORPOS ALGÉBRICOS DE ORDEM SUPERIOR, PORÉM SÃO DE GRANDE INTERESSE COMPUTACIONAL APARECENDO EM ALGORITMOS COMO A PENEIRA DE CORPOS NÚMERICOS ALGÉBRICOS, O
MAIS EFICIENTE ALGORITMO (CLÁSSICO) PARA FATORAR NÚMEROS INTEIROS.

PARA MAIORES REFERÊNCIAS: https://en.wikipedia.org/wiki/Algebraic_number_field
                          https://en.wikipedia.org/wiki/Dirichlet_L-function
                          https://en.wikipedia.org/wiki/Quadratic_integer
                          https://en.wikipedia.org/wiki/Quadratic_field
                          https://en.wikipedia.org/wiki/Class_number_problem
                          Prime Numbers And Computer Methods For Factorization by Hans Riesel

*/


//**********************************************************************************************************************************************
//CABEÇALHO
#ifndef ALGEBRAIC_QUADRATIC_FIELD_H
#define ALGEBRAIC_QUADRATIC_FIELD_H
#include<iostream>
#include<string>
#include<sstream>
#include<cmath>
#include<cassert>
#include<type_traits>

//**********************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
bool is_perfect_square(T);

template<typename T>
bool is_square_free_integer(T);

//**********************************************************************************************************************************************
//FUNÇÕES
//Função que detecta se um inteiro possui fatores primos repetidos
bool is_square_free_integer(int64_t x64){
//Restrição a inteiros positivos
if(x64<0)
x64*=(-1);

//Variáveis locais
int64_t root=static_cast<int64_t>(std::sqrt(x64));
int64_t divisors[8]={7,11,13,17,19,23,29,31};
int64_t i, j, tester;

//Procedimentos
//Fatores 2,3,5
if((x64%4)==0 || (x64%9)==0 || (x64%25)==0)
return false;

//Loop principal
for(i=0;;++i){


for(j=0; j<8; ++j){
tester=(30*i)+divisors[j];

if((x64%(tester*tester))==0)
return false;

if(tester>root)
return true;
                  };


             };

//Erro
return false;
                                        };


//**********************************************************************************************************************************************
//CLASSE DE CORPOS ALGÉBRICOS QUADRÁTICOS
template<typename T>
class algebraic_quadratic_field{
public:
//------------------------------------
//MEMBROS
int64_t d;//Discriminante
T a;
T b;

//------------------------------------
//CONSTRUTORES E DESTRUIDORES
algebraic_quadratic_field(){
d=0; a=0; b=0;
                           };

algebraic_quadratic_field(int64_t x){
d=x;
a=0; b=0;

//Restrição
assert(is_square_free_integer(d));

                                    };

algebraic_quadratic_field(T x, T y, int64_t z){
d=z;
a=x;
b=y;

//Restrição
assert(is_square_free_integer(d));
                                              };


~algebraic_quadratic_field(){ };


//------------------------------------
//MÉTODOS  DA CLASSE
std::string algebraic();
void set();
T norm();
algebraic_quadratic_field<T> conjugate();


algebraic_quadratic_field<T> operator+(algebraic_quadratic_field<T>);
algebraic_quadratic_field<T> operator-(algebraic_quadratic_field<T>);
algebraic_quadratic_field<T> operator*(algebraic_quadratic_field<T>);
algebraic_quadratic_field<T> operator/(algebraic_quadratic_field<T>);

                               };


//**********************************************************************************************************************************************
// MÉTODOS DA CLASSE DE CORPOS ALGÉBRICOS QUADRÁTICOS

//Função que escreve um inteiro algébrico como uma string
template<typename T>
std::string algebraic_quadratic_field<T>::algebraic(){
//Variáveis locais
std::string algebraic_number_string="";

//Procedimentos
algebraic_number_string+=std::to_string(a);

if(b>0)
algebraic_number_string+="+";

algebraic_number_string+=std::to_string(b);

algebraic_number_string+="(√";
algebraic_number_string+=std::to_string(d);
algebraic_number_string+=")";

//Resultados
return algebraic_number_string;
                                                     };


//Função que define os coeficientes de um número algébrico
template<typename T>
void algebraic_quadratic_field<T>::set(){
if(d==0){
std::cout<<"a+b(√d) --> valor do discriminante d: ";
std::cin>>d;

assert(is_square_free_integer(d));
        };

std::cout<<"a+b(√d) --> valor do coeficiente a: ";
std::cin>>a;
std::cout<<"a+b(√d) --> valor do coeficiente b: ";
std::cin>>b;
                                        };

//Função que calcula a  norma de um número algébrico
template<typename T>
T algebraic_quadratic_field<T>::norm(){

//Caso 1: d>0
if(d>0){

if((d%4)==2 || (d%4)==3)
return ((a*a)-(b*b*d));

else if((d%4)==1)
return ((a*a)-(b*a) -(((d-1)/4)*b*b));

       };


//Caso 2: d<0
if(d<0){

//Variável local
int64_t d_=(-1)*d;

//Resultado

if((d_%4)==2 || (d_%4)==1)
return ((a*a)-(b*b*d));

else if((d_%4)==3)
return ((a*a)-(b*a) -(((d-1)/4)*b*b));
       };


//Erro
return 0;
                                      };


//Função que retorna o conjugado de número algébrico
template<typename T>
algebraic_quadratic_field<T> algebraic_quadratic_field<T>::conjugate(){

//Variáveis locais
algebraic_quadratic_field<T> result;

//Procedimentos
result.a=a;
result.b=b*(-1);
result.d=d;


//Resultado
return result;
                                                                      };



//Soma de números algébricos
template<typename T>
algebraic_quadratic_field<T> algebraic_quadratic_field<T>::operator+(algebraic_quadratic_field<T> z1){
//Restrição
assert(d==z1.d);

//Variáveis locais
algebraic_quadratic_field<T> result;

//Procedimentos
result.d=d;
result.a=a+z1.a;
result.b=b+z1.b;

//Resultado
return result;
                                                                                                     };




//Subtração de números algébricos
template<typename T>
algebraic_quadratic_field<T> algebraic_quadratic_field<T>::operator-(algebraic_quadratic_field<T> z1){
//Restrição
assert(d==z1.d);

//Variáveis locais
algebraic_quadratic_field<T> result;

//Procedimentos
result.d=d;
result.a=a-z1.a;
result.b=b-z1.b;

//Resultado
return result;
                                                                                                      };


//Multiplicação de números algébricos
template<typename T>
algebraic_quadratic_field<T> algebraic_quadratic_field<T>::operator*(algebraic_quadratic_field<T> z1){
//Restrição
assert(d==z1.d);

//Variáveis locais
algebraic_quadratic_field<T> result;

//Procedimentos
result.d=d;
result.a=(a*z1.a)+(d*b*z1.b);
result.b=(a*z1.b)+(b*z1.a);

//Resultado
return result;

                                                                                                     };


//Divisão de números algébricos
template<typename T>
algebraic_quadratic_field<T> algebraic_quadratic_field<T>::operator/(algebraic_quadratic_field<T> z1){
//Restrição
assert(d==z1.d);

//Variáveis locais
algebraic_quadratic_field<T> result;
T quadratic_norm=((z1.a*z1.a)-(d*z1.b*z1.b));

//Procedimentos
result.d=d;

result.a=(a*z1.a)-(d*b*z1.b);
result.a/=quadratic_norm;

result.b=(b*z1.a)-(a*z1.b);
result.b/=quadratic_norm;


//Resultado
return result;

                                                                                                     };

//**********************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES AUXILIARES
template<typename T>
bool is_unity(algebraic_quadratic_field<T>);

template<typename T>
bool is_associated(algebraic_quadratic_field<T>, algebraic_quadratic_field<T>);

template<typename T, typename U>
algebraic_quadratic_field<T> quadratic_pow(algebraic_quadratic_field<T>, U);

//**********************************************************************************************************************************************
//FUNÇÕES AUXILIARES

//Função que determina se um número algébrico é uma unidade (possui norma 1)
template<typename T>
bool is_unity(algebraic_quadratic_field<T> z){
//Variáveis locais
int64_t unit_norm= static_cast<int64_t>(z.norm());

//Resultado
if(unit_norm==1 || (-1)*unit_norm==1)
return true;
else
return false;
                                             };

//Função que determina se o quociente de dois números algébricos é uma unidade
template<typename T>
bool is_associated(algebraic_quadratic_field<T> z1, algebraic_quadratic_field<T> z2){
//Variáveis locais
algebraic_quadratic_field<T> quotient=z1/z2;

//Resultado
if(is_unity(quotient)==true)
return true;
else
return false;

                                                                                    };


//Função que eleva um número algébrico a uma potência inteira racional
template<typename T, typename U>
algebraic_quadratic_field<T> quadratic_pow(algebraic_quadratic_field<T> z, U power){
//Restrição a expoentes inteiro racionais
static_assert(std::is_integral<U>::value==true);

//Variáveis locais

algebraic_quadratic_field<T> result(1,0, z.d), temp;


//Procedimentos
//Loop principal
while(power>0){

//Testando os bits do expoente
if(power&1)
result=result*z;

//Atualizando variáveis para a próxima iteração
z=z*z;
power>>=1;
              };

//Resultado
return result;
                                                                                   };


//**********************************************************************************************************************************************
//FIM DO HEADER
#endif
