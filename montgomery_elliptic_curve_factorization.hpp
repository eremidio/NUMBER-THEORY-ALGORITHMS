//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA A VARIANTE DE MONTGOMERY DO MÉTODO DE FATORAÇÃO VIA CURVAS ELÍPTICAS
/*
O MÉTODO DE MONTGOMERY É UMA VARIAÇÃO DO MÉTODO ORIGINAL DE FATORAÇÃO VIA CURVAS ELÍPTICAS PROPOSTOPOR H. LENSTRA QUE USA AS CHAMADAS CURVAS DE MONTOGOMERY
gy²=x³+Cx²+x (mod p). ASSIM COMO NO ALGORITMO ORIGINAL PONTOS SOBRE A CURVA FORMAM UM GRUPO ABELIANO COM AS OPERAÇÕES GEOMÉTRICAS DE ADIÇÃO DE PONTOS E MULTIPLICAÇÃO
POR UM ESCALAR.

ESTE ALGORITMO TEM A VANTAGEM DE NÃO REQUERER O CÁLCULO DE INVERSOS MODULARES USANDO-SE O ALGORITMO DE EUCLIDES EXTENDIDO COMO NO ALGORITMO ORIGINAL, ALÉM DE
POSSIBILITAR A EXECUÇÃO DE UM SEGUNDO ESTÁGIO NO ALGORITMO QUE EMPREGA DOIS NÚMEROS B1 E B2 PARA CONTROLAR O INTERVALO DE BUSCA POR FATORES PRIMOS (FATORES NÃO TRIVIAIS
SÃO ENCONTRADOS SE A ORDEM DO SUBGRUPO E(p) DE PONTOS EM CURVAS FOR SUAVE EM RELAÇÃO A ESTE PARÂMETROS, O TEOREMA DE HASSE ESTIMA QUE A ORDEM #E(p) ESTÁ NO INTERVALO
(p+1)-2√p, ..., (p+1)+2√p). A ESCOLHA DE PARAMETRIZAÇÕES ADEQUADAS GARANTE QUE #E(p) É SUAVE EM RELAÇÃO AOS PARÂMETROS B1 E B2.

PARA MAIORES INFORMAÇÕES:
https://dspace.mit.edu/bitstream/handle/1721.1/97521/18-783-spring-2013/contents/lecture-notes/MIT18_783S13_lec12.pdf
https://eprint.iacr.org/2017/212.pdf
https://members.loria.fr/PZimmermann/papers/40760525.pdf
https://members.loria.fr/PZimmermann/records/ecm/params.html
https://en.wikipedia.org/wiki/Lenstra_elliptic-curve_factorization
https://www.rieselprime.de/ziki/Elliptic_curve_method#Step_2

*/

//********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef MONTGOMERY_ELLPITIC_CURVE_FACTORIZATION_H
#define MONTGOMERY_ELLPITIC_CURVE_FACTORIZATION_H
#include"montgomery_elliptic_curve_factorization_auxiliary_functions.hpp"
#include<random>
#include<string>
#include<iostream>

//CONSTANTES GLOBAIS
#define MAX_CURVES 10000

//Parâmetros otimos para fatores de até 50 dígitos decimais
uint64_t B1_table[8]={2000, 11000, 50000, 250000, 1000000, 3000000, 11000000, 43000000};
int digits_table[8]= {15, 20, 25, 30, 35, 40, 45, 50};


//********************************************************************************************************************************************************************
//CLASSE DO ALGORITMO
class elliptic_curve_method{
public:
//Membros da classe
int512_t number;//Número a ser fatorado
std::string number_string;//Número a ser fatorado
uint64_t B1, B2, B;//Variável usada na escolha de profundidade de busca por um número primo
int512_t factor1, factor2, selection;//Fatores primos encontrados
int64_t sigma_parameter;//Variável de seleção do ponto inicial usado nas curvas
int512_t C;//Parâmetro que define a curva usada no algoritmo
uint64_t curve_number;//Função que determina o número de curva testadas no algoritmo

std::vector<uint64_t> prime_buffer_B1;//Buffer de números primos usados no algoritmo

int auto_setup;//Função usada para iniciar o estágio 2 do algoritmo
int512_t up, vp, x0, z0, xp, zp;//Coordenadas das curvas usadas no cálculo no estágio 1 do algoritmo
int512_t prime_power;//Variável usada para definir o fator multiplicativo no cálculo de pontos sobre a curva elíptica

int512_t xq, zq, xc, zc, x7, z7, x11, z11, x13, z13, x30, z30;//Coordenadas das curvas usadas no cálculo no estágio 2 do algoritmo
int512_t g, gt, h, ht, multiplier;//Variáveis usadas no cálculo no estágio 2 do algoritmo


//Construtores e destruidores
elliptic_curve_method(){ };
~elliptic_curve_method(){ };

//Métodos da classe
void run();//Função principal do algoritmo
void setup();//Função que recebe input do usuário e ajusta variáveis usadas no algoritmo
void set_new_curve();//Função que reajusta a equação da curva para novos testes
void first_stage();//Função que implementa o estágio 1 do algoritmo
void second_stage();//Função que implementa o estágio 2 do algoritmo
void calculate_factors();//Função que calcula fatores primos dos números a ser fatorado
void print_result();//Função que exibe o resultado da execução do algoritmo
                           };

//********************************************************************************************************************************************************************
//MÉTODOS DA CLASSE
//Função principal da classe
void elliptic_curve_method::run(){
//Etapa 1: configurando variáveis usadas no algoritmo
step1:
setup();

//Etapa 2: executando o estágio 1 do algoritmo
step2:
first_stage();
if(selection>1 && selection!=number)
goto step4;

//Etapa 3: executando o estágio 2 do algoritmo
step3:
second_stage();

//Etapa 4: calculando fatores primos
step4:
if(selection>1 && selection!=number){
calculate_factors();
print_result();
return;
                                    };

//Etapa 5: Encerrando o algortimo caso um fator não tenha sido encontrado no estágio 2 do algoritmo
step5:
set_new_curve();
curve_number++;
if(curve_number<=MAX_CURVES)
goto step2;
else{
std::cout<<"O algoritmo não encontrou fatores primos do número em questão\n";
return;
    };

                                 };

//Função que recebe input do usuário
void elliptic_curve_method::setup(){
//Recebendo input do usuário
std::cout<<"Número a ser fatorado: ";
std::cin>> number_string;
int512_t temp1(number_string);
number =temp1;


std::cout<<"Fator de profundidade usado na busca por fatores primos: ";
std::cin>>B1;

std::cout<<"Fator σ que define a curva e ponto na curva a ser usada no cálculo: ";
std::cin>>sigma_parameter;

//Cálculos de outros parâmetros
//Fator de profundidade usado na busca no estágio 2 do algoritmo
B2=B1*100000000;
B=B2;
while((B%30)!=0)
B--;

//Parâmetros que definem o ponto da inicial curva
while(std::abs(sigma_parameter)==1 || sigma_parameter==0 || sigma_parameter==5)
sigma_parameter=generate_random_number();

up=((sigma_parameter*sigma_parameter)-5);
vp=4*sigma_parameter;

x0=((up%number)*(up%number)*(up%number))%number;
z0=((vp%number)*(vp%number)*(vp%number))%number;

//Parâmetro que define a curva
C= ((( (vp-up)*(vp-up)*(vp-up)*((3*up)+vp) ) /(4*up*up*up*vp))-2) ;

//Preenchendo o buffer de primos usados no estágio 1 do algoritmo
fill_prime_buffer(prime_buffer_B1, B1);

//Outros ajustes de parâmetros
factor1=0;
factor2=0;
selection=0;
prime_power=0;
auto_setup=0;
curve_number=1;
g=1;
gt=1;
h=1;
ht=1;
multiplier=1;

//TESTES USE UM // APÓS O TESTE
//std::cout<<number<<'\n';
//for(auto x:prime_buffer_B1)
//std::cout<<x<<" ";
//std::cout<<'\n';

//std::cout<<"Curva:\n";
//std::cout<<x0<<'\n';
//std::cout<<y0<<'\n';
//std::cout<<C<<'\n';
                                   };

//Função que reajusta a equação da curva para novos testes
void elliptic_curve_method::set_new_curve(){
//Parâmetros que definem o ponto da inicial curva
sigma_parameter=generate_random_number();
while(std::abs(sigma_parameter)==1 || sigma_parameter==0 || sigma_parameter==5)
sigma_parameter=generate_random_number();

up=((sigma_parameter*sigma_parameter)-5);
vp=4*sigma_parameter;

x0=((up%number)*(up%number)*(up%number))%number;
z0=((vp%number)*(vp%number)*(vp%number))%number;

if(auto_setup>0){
xq=x0;
zq=z0;
                };

//Parâmetro que define a curva
C= ((( (vp-up)*(vp-up)*(vp-up)*((3*up)+vp) ) /(4*up*up*up*vp))-2) ;
                                           };



//Função que calcula fatores primos dos números a ser fatorado
void elliptic_curve_method::calculate_factors(){
if(selection>1)
factor1=selection;
factor2=number/factor1;
                                               };

//Função que exibe o resultado da execução do algoritmo
void elliptic_curve_method::print_result(){
std::cout<<"\nRelatório de execução do algoritmo:\n";
std::cout<<"Curva usada para encontrar o fator: gy²=x³+("<<C<<")x²+x (mod "<<number<<")\n";
std::cout<<"σ: "<<sigma_parameter<<'\n';
std::cout<<"Número de curvas testadas: "<<curve_number<<'\n';
std::cout<<"B1: "<<B1<<'\n';
std::cout<<"B2: "<<B2<<'\n';
std::cout<<"Número a ser fatorado: "<<number<<'\n';
std::cout<<"Fator encontrado: "<<factor1<<'\n';
std::cout<<"Restante: "<<factor2<<'\n';

                                          };

//Função que implementa o estágio 1 do algoritmo
void elliptic_curve_method::first_stage(){
//Ajuste de variáveis
curve_number++;
auto_setup=0;

//Loop principal
for(auto x: prime_buffer_B1){
prime_power=x;

while(prime_power<B1){
pointwise_scalar_multiplication(xp, zp, x0, z0, prime_power, C, number);
selection=euclides_algorithm(zp, number);
if(selection>1)
return;
else
prime_power=prime_power*x;
                     };
                            };
                                         };

//Função que implementa o estágio 2 do algoritmo
/*
NOTA: A abordagem mais eficiente que emprega o algoritmo baby step-giant step é excessivamente pesado para um desktop simples. Usaremos uma abordagem simples
recalculando os pontos na curva partir do último ponto gerado no estágio 1 do algoritmo.
*/
void elliptic_curve_method::second_stage(){
//Ajuste de variáveis
xq=xp;
zq=zp;
auto_setup=1;
g=1;
gt=1;
h=1;
ht=1;
multiplier=B;

//Calculando o valor das coordenadas dos pontos [B]P, [7]Q, [11]Q, [13]Q 
pointwise_scalar_multiplication(xc, zc, x0, z0, B, C, number);
selection=euclides_algorithm(zc, number);
if(selection>1){
std::cout<<"Fator encontrado no estágio 2 do algoritmo.\n";
return;
               };
pointwise_scalar_multiplication(x7, z7, xq, zq, 7, C, number);
selection=euclides_algorithm(z7, number);
if(selection>1){
std::cout<<"Fator encontrado no estágio 2 do algoritmo.\n";
return;
               };
pointwise_scalar_multiplication(x11, z11, xq, zq, 11, C, number);
selection=euclides_algorithm(z11, number);
if(selection>1){
std::cout<<"Fator encontrado no estágio 2 do algoritmo.\n";
return;
               };

pointwise_scalar_multiplication(x13, z13, xq, zq, 13, C, number);
selection=euclides_algorithm(z13, number);
if(selection>1){
std::cout<<"Fator encontrado no estágio 2 do algoritmo.\n";
return;
               };

gt=((gt%number)*((xc-xq)%number))%number;
if(gt!=0)
g=gt;
else
gt=g;

gt=((gt%number)*((xc-x7)%number))%number;
if(gt!=0)
g=gt;
else
gt=g;

gt=((gt%number)*((xc-x11)%number))%number;

if(gt!=0)
g=gt;
else
gt=g;

gt=((gt%number)*((xc-x13)%number))%number;

if(gt!=0)
g=gt;
else
gt=g;


//Loop principal sobre o intervalo {B, B+30, ..., B+30k<B2}
while(multiplier<B2){
multiplier+=30;
pointwise_scalar_multiplication(x30, z30, xq, zq, multiplier, C, number);

if((multiplier%1500)==0){

selection=euclides_algorithm(z30, number);
if(selection>1){
std::cout<<"Fator encontrado no estágio 2 do algoritmo.\n";
return;
               };
                        };

gt=((gt%number)*((x30-xq)%number))%number;
if(gt!=0)
g=gt;
else
gt=g;

gt=((gt%number)*((x30-x7)%number))%number;
if(gt!=0)
g=gt;
else
gt=g;

gt=((gt%number)*((x30-x11)%number))%number;

if(gt!=0)
g=gt;
else
gt=g;

gt=((gt%number)*((x30-x13)%number))%number;

if(gt!=0)
g=gt;
else
gt=g;

ht=((x30%number)*(z30%number))%number;

if(ht!=0)
h=ht;
else
ht=h;

                    };

//Testando se um fator primo foi encontrado no segundo estágio do algoritmo 
selection=euclides_algorithm(g, number);
if(selection>1){
std::cout<<"Fator encontrado no estágio 2 do algoritmo.\n";
return;
               };

selection=euclides_algorithm(h, number);
if(selection>1){
std::cout<<"Fator encontrado no estágio 2 do algoritmo.\n";
return;
               };


                                          };

//********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
