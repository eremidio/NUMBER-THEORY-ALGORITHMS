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
                          https://members.loria.fr/PZimmermann/records/ecm/params.html

*/ 

//***************************************************************************************************************************
//CABEÇALHO
#ifndef ELLIPTIC_CURVE_METHOD_H
#define ELLIPTIC_CURVE_METHOD_H
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/cstdint.hpp>
#include<string>
#include<stdint.h>
#include<iostream>
#include<random>
using namespace boost::multiprecision;

//CONSTANTES GLOBAIS
#define MAX_TRIALS 60000 //Variável para se restringir o número de tentativas

//***************************************************************************************************************************
//FUNÇÕES AUXILIARES
//Função que calcula o inverso modular de um número inteiro a (mod n) usando o algoritmo extendido de euclides
int512_t  modular_inverse(int512_t  a, int512_t n, int512_t& gcd){
//Variáveis locais
int512_t  r0,r1, x0, x1, r2, x2;
//Procedimentos 
//Ajuste de variáveis
r0=a;
r1=n;
r2=1;
x0=1;
x1=0;

//Calculando os valores finais coeficientes recursivamente
while(r2>0){
int512_t quotient= r0/r1;

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
gcd=r1;//MMC

if(x1<0)
return(x1+n);
else
return x1;
                                                                 };

//Função usada para se gerar um número inteiro aleatório da ordem 64 bits 
int512_t  generate_random_number(int512_t  number){
//Variáveis locais
__int128_t  limit=1e7;
int512_t result;
//Procedimentos
//Ajuste da distribuição de números aleatórios
std::random_device generator_x;
std::mt19937 gen(generator_x());
std::uniform_int_distribution<__int128_t> elliptic_distribution(1, limit);

//Resultado
result=elliptic_distribution(generator_x);
return (result*result)%number;
                                              };

//***************************************************************************************************************************
//CLASSE 
//Classe do algoritmo de fatoração usando curvas elípticas
class elliptic_curve_method{
public:
//Membros da classe
int512_t number;//Número a ser fatorado
int512_t x0, y0;//Coordenadas do ponto inicial da curva elíptica
int512_t xp, yp, xq, yq, xr, yr, slope;//Coordenadas de pontos na curva elíptica usados no cálculo
int512_t a, b;//Parâmetros que definem a curva usada
int64_t B;//Pârametro que define a profundidade do algoritmo na busca de pontos na curva elíptica
int512_t selection;//Número inteiro não congruente modulo o número a ser fatorado que serve de detecção de fatores não triviais
int512_t discriminant;//Discriminant da curva elíptica
int512_t factor1, factor2;//Fatores calculados usando este algoritmo
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

//Teste do discriminante da curva
curve_selection:
discriminant=(4*a*a*a)-(27*b*b);
int512_t temp=modular_inverse(discriminant, number, selection);
if(selection>1 && selection<number)
goto end;

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
end:
if(selection>1 && selection<number){
factor1=selection;
factor2=number/factor1;
std::cout<<"\nRelatório de execução do algoritmo:\n";
std::cout<<"Curva usada para encontrar o fator: y²=x³+("<<a<<")x+("<<b<<")  (mod "<<number<<")\n";
std::cout<<"Fatores encontrados: \n";
std::cout<<factor1<<'\n';
std::cout<<factor2<<'\n';
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
std::string number_string1;
std::string number_string2;
std::string number_string3;
std::string number_string4;

//Procedimentos recebendo input do usuário

std::cout<<"Digite o número a ser fatorado: ";
std::cin>>number_string1;
int512_t temp1(number_string1);
number=temp1;

std::cout<<"Digite o valor inicial da coordenada x0 de um ponto na curva: ";
std::cin>>number_string2;
int512_t temp2(number_string2);
x0=temp2;

std::cout<<"Digite o valor inicial da coordenada y0 de um ponto na curva: ";
std::cin>>number_string3;
int512_t temp3(number_string3);
y0=temp3;

std::cout<<"Digite o valor inicial do parâmetro a que define a curva a ser testada: ";
std::cin>>number_string4;
int512_t temp4(number_string4);
a=temp4;

std::cout<<"Digite um fator de 2 a 25000000 que determina a profundidade da busca a ser realizada por fatores primos: ";
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
slope=((3*xp*xp+a)*modular_inverse(2*yp, number, selection))%number;

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
slope=((yp-yq)*modular_inverse((xp-xq), number, selection))%number;

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
