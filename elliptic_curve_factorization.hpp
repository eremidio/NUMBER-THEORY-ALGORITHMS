//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE CURVAS ELIPTICAS PARA FATORAR NÚMEROS INTEIROS  

/*
O MÉTODO DE FATORAÇÃO USANDO CURVAS ELÍPTICAS USA O FATO QUE EM CERTOS TIPOS DE CURVAS UMA OPERAÇÃO GEOMÉTRICA DE
ADIÇÃO DE PONTOS E MULTIPLICAÇÃO DE UM PONTO POR UM ESCALAR DEFINE UMA ESTRUTURA QUE É UM GRUPO (ESTRUTURA ALGÉBRICA).
A IDEIA FUNDAMENTAL É CONSIDERAR CURVAS NA FORMA (NORMAL REDUZIDA) DE WEIERTRASS y²=x³+ax+b, COM a E b REAIS; SOBRE UM CORPO
FINITO DO PRIMEIRO TIPO (INTEIROS COM AS OPERAÇÕES USUAIS USANDO ARITMÉTICA MODULAR).

NESTE CONTEXTO A CURVA EM QUESTÃO PASSA A TER UM NÚMERO FINITO DE ELEMENTOS, INCLUINDO UM PONTO NO INFINITO, DENOTADO POR o.

NESTA SITUAÇÃO É POSSÍVEL OBTER UMA SITUAÇÃO NA QUAL A MULTIPLICAÇÃO DE PONTOS POR UM ESCALAR EVENTUALMENTE IRÁ ATINGIR O PONTO NO INFINITO o. NESTE CÁLCULO OPERAÇÕES ENVOLVENDO mdc DE DOIS INTEIROS SÃO PERFORMADOS E QUANDO PONTO o FOR ATINGINDPO O
CÁLCULO DO mdc EVENTUALMENTE IRÁ FORNECER UM FATOR NÃO TRIVIAL DO NÚMERO A SER FATORADO.

ESTE ALGORITMO É UMA VARIANTE DO MÉTODO DE POLLARD RHO (p-1).

PARA MAIORES INFORMAÇÕES: https://medium.com/@gaelfoppolo/elliptic-curve-cryptography-ecc-6af6142b0dd1
https://en.wikipedia.org/wiki/Lenstra_elliptic-curve_factorization
https://zafirr31.github.io/posts/lenstra-elliptic-curve-method-of-factorization/


*/ 

//***************************************************************************************************************************
//CABEÇALHO
#ifndef ELLIPTIC_CURVE_METHOD_H
#define ELLIPTIC_CURVE_METHOD_H
#include"int128.h"
#include<stdint.h>
#include<iostream>
#include<random>

//CONSTANTES GLOBAIS
#define MAX_TRIALS 50000 //Variável para se restringir o número de tentativas

//***************************************************************************************************************************
//FUNÇÕES AUXILIARES
//Função que implementa o algoritmo de Euclides
__int128_t euclides_algorithm(__int128_t a, __int128_t b){
if(b==0)
return a;
else
return euclides_algorithm(b, a%b);
                                                        };

//Função que calcula o inverso modular de um número inteiro a (mod n) usando o algoritmo extendido de euclides
__int128_t  modular_inverse(__int128_t  a, __int128_t  n){
//Variáveis locais
__int128_t  r0,r1, x0, x1, r2, x2;
//Procedimentos 
//Ajuste de variáveis
r0=a;
r1=n;
r2=1;
x0=1;
x1=0;

//Calculando os valores finais coeficientes recursivamente
while(r2>0){
__int128_t  quotient= r0/r1;

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

//Função usada para se gerar um número inteiro aleatório da ordem 64 bits 
__int128_t  generate_random_number(__int128_t  number){
//Variáveis locais
__int128_t  result;
__int128_t  limit;

//Procedimentos
//Ajuste de variáveis
else if(number>1e32)
limit=number/1e25;
else if(number>1e24)
limit=number/1e18;
else if(number>1e16)
limit=number/1e8;
else
limit=number;


//Ajuste da distribuição de números aleatórios
std::random_device generator_x;
std::mt19937 gen(generator_x());
std::uniform_int_distribution<__int128_t> elliptic_distribution(1, limit);

//Resultado
result=elliptic_distribution(generator_x);
return result;
                                              };

//***************************************************************************************************************************
//CLASSE 
//Classe do algoritmo de fatoração usando curvas elípticas
class elliptic_curve_method{
public:
//Membros da classe
__int128_t number;//Número a ser fatorado
__int128_t x0, y0;//Coordenadas do ponto inicial da curva elíptica
__int128_t xp, yp, xq, yq, xr, yr, slope;//Coordenadas de pontos na curva elíptica usados no cálculo
__int128_t a, b;//Parâmetros que definem a curva usada
int64_t B;//Pârametro que define a profundidade do algoritmo na busca de pontos na curva elíptica
__int128_t selection;//Número inteiro não congruente modulo o número a ser fatorado que serve de detecção de fatores não triviais
__int128_t factor1, factor2;//Fatores calculados usando este algoritmo
int64_t number_trial;//Função que controla o número de testagens até o algoritmo encontrar um fator não trivial
bool restart;//Variável para se reiniciar o teste usando uma outra curva

//Métodos da classe
void run();//Função principal
void setup();//Função que recebe input do usuário
void set_new_curve();//Função que reajusta a equação da curva para novos testes
void pointwise_addition();//Função que executa a adição de pontos em uma curva elíptica
void point_scalar_multiplication(int64_t);//Função que executa a multiplição de pontos por um escalar em uma curva elíptica
                          };

//***************************************************************************************************************************
//MÉTODOS DA CLASSE
//Função principal
void elliptic_curve_method::run(){
//Ajuste de variáveis
number_trial=1;
selection=0;
factor1=0;
factor2=0;
restart=false;
setup();

//Loop principal
mainloop:
//Limitando o número de testes
if(number_trial>(MAX_TRIALS+1)){
std::cout<<"Teste não encontrou fatores primos do número em questão!\n";
return;
                               };

//Loop
for(int64_t k=2; k<B; ++k){
point_scalar_multiplication(k);

//Reiniciando o loop
if(restart==true)
break;

//Fator não trivial encontrado
if(selection>1 && selection<number)
break;

//Ajustando os pontos na curva para a próxima iteração
xp=xr; xq=xr;
yp=yr; yq=yr;
                          };

//Redefinindo uma nova curva
if(restart==true){
set_new_curve();
goto mainloop;
                 };

//Fatores não triviais encontrados
if(selection>1 && selection<number){
factor1=selection;
factor2=number/factor1;
std::cout<<"Fatores encontrados: \n";
printf128(factor1);
printf128(factor2);
std::cout<<"Número de curvas usadas no cálculo: "<< number_trial<<"\n";
                                   };

//Reinicializando o loop com uma nova curva caso fatores não tenham sio encontrados
if(factor1==0){
set_new_curve();
goto mainloop;
              };
                                };

//Função que recebe input do usuário para ajuste inicial do algoritmo
void elliptic_curve_method::setup(){
//Variáveis locais
char number_string1[40];
char number_string2[40];
char number_string3[40];
char number_string4[40];

//Procedimentos recebendo input do usuário

std::cout<<"Digite o número a ser fatorado: ";
scanf("%s", number_string1);
number=scanf128(number_string1);

std::cout<<"Digite o valor inicial da coordenada x0 de um ponto na curva: ";
scanf("%s", number_string2);
x0=scanf128(number_string2);

std::cout<<"Digite o valor inicial da coordenada y0 de um ponto na curva: ";
scanf("%s", number_string3);
y0=scanf128(number_string3);

std::cout<<"Digite o valor inicial do parâmetro a que define a curva a ser testada: ";
scanf("%s", number_string4);
a=scanf128(number_string4);

std::cout<<"Digite o uma fator de 2 a 250 que determina a profundidade da busca a ser realizada por fatores primos: ";
std::cin>>B;


//O parâmetro b  é calculado usando-se esses parâmetros
b= ((y0*y0)- (x0*x0*x0)-(a*x0))%number;
//Ajustando o primeiro ponto da curva
xp=x0; xq=x0;
yp=y0; yq=y0;

//TESTE1,  USE UM // APÓS O MESMO
//std::cout<<"TESTE1\n";
//std::cout<< b<<"\n";
                                   };

//Função que reajusta a equação da curva para novos testes
void elliptic_curve_method::set_new_curve(){
//Ajuste da variável que conta o número de tentativas
number_trial++;
restart=false;

//Reajustando os coeficientes que definem a curva elíptica
a=generate_random_number(number)%number;
x0=generate_random_number(number)%number;
y0=generate_random_number(number)%number;
b= ((y0*y0)- (x0*x0*x0)-(a*x0))%number;

//Ajustando o primeiro ponto da curva
xp=x0; xq=x0;
yp=y0; yq=y0;
                                           };


//Função que executa a adição de pontos em uma curva elíptica
void elliptic_curve_method::pointwise_addition(){

//Caso 1: P=Q, ambos dos pontos possuem as mesmas coordenadas
if(xp==xq && yp==yq){
//Restrição
//Restrição
if(yp==0){
restart=true;
return;
         };

//Calculo da inclinação da curva, uma checagem é executada para verificar se um ponto não invertível foi encontrado
if(euclides_algorithm((2*yp), number)!=1){
selection=euclides_algorithm(2*yp, number);
return;
                                         };

slope=((3*xp*xp+a)*modular_inverse(2*yp, number))%number;

//Calculo das coordenadas do novo ponto gerado
xr=((slope*slope)-(2*xp))%number;
yr=((slope*(xp-xr))-yp)%number;

                    };

//Caso 2: P/=Q, pontos possuem diferentes coordenadas
if(xp!=xq || yp!=yq){

//Restrição
if(xp==xq){
restart=true;
return;
          };

//Calculo da inclinação da curva, uma checagem é executada para verificar se um ponto não invertível foi encontrado
if(euclides_algorithm((xp-xq), number)!=1){
selection=euclides_algorithm((xp-xq), number);
return;
                                          };

slope=((yp-yq)*modular_inverse((xp-xq), number))%number;

//Calculo das coordenadas do novo ponto gerado
xr=((slope*slope)-xp-xq)%number;
yr=((slope*(xp-xr))-yp)%number;

                    };

                                                };

//Função que executa a multiplição de pontos por um escalar em uma curva elíptica
void elliptic_curve_method::point_scalar_multiplication(int64_t n){
//Variáveis locais
int64_t i=1;

//Caso trivial: n=2
if(n==2){
//Ajuste de variáveis
pointwise_addition();
if(selection>1 && selection<number)
return;
        };

//Caso geral geral
while(i<=n){
//Primeira iteração
if(i==2){
pointwise_addition();
if(restart==true)
return;
if(selection>1 && selection<number)
return;
        };
//Demais iterações
if(i>2){
//Ajuste de variáveis
xp=xr; yp=yr;
pointwise_addition();
if(restart==true)
return;
if(selection>1 && selection<number)
return;
        };

//Ajuste do contador
++i;
           };
                                                                  };

//***************************************************************************************************************************
//FIM DO HEADER
#endif
