//VAMOS CRIARUM PROGRAMA QUE IMPLEMENTA ROTINAS PARA O CÁLCULO DE ALGUMAS FORMAS MODULARES

/*
O CHAMADO GRUPO MODULAR  CONSISTE NO CONJUNTO DE MATRIZES DO TIPO G= GL²(Z)/± I = |a b| COM det(G)= ad-bc = 1, I=|1 0| É A MATRIZ IDENTIDADE E a, b, c, d SÃO INTEIROS.
                                                                                  |c d|                          |0 1|

ESTE GRUPO É GERADO PELAS MATRIZES S = |0 -1| T = |1 1|.
                                       |1  0|     |0 1|

DADO g EM G ESTE GRUPO AGE SOBRE UM ELEMENTO z NO SEMIPLANO SUPERIOR DO ESPAÇO DOS NÚMEROS COMPLEXOS (DENOTADO POR H) QUE CONSISTE EM NÚMEROS COMPLEXOS DA FORMA
z=a+bi(COM b>0) POR MEIO DA RELAÇÃO: gz=(az+b)/(cz+d). EM PARTICULAR Sz=(-1)/z E Tz=(z+1). DE GRANDE INTERESSE É A AÇÃO DESTE GRUPO NO SUBCONJUNTO FUNDAMENTAL DE H
DENOTADO POR D QUE CONSISTE EM NÚMEROS COMPLEXOS EM H COM |z|≳1 |Re(z)|≲(1/2).

FUNÇÕES MODULARES FRACAS DE GRAU 2k COM k INTEIROS SÃO FUNÇÕES DE ARGUMENTOS COMPLEXOS QUE SATISFAZEM A SEGUINTE RELAÇÃO FUNCIONAL (SOB AÇÃO DO GRUPO MODULAR G):
f(z)=f(z+1)(PERIODICIDADE EM RELAÇÃO A TRANSLAÇÕES NO EIXO REAL), f((-1)/z)=(z^(2k))f(z), f((az+b)/(cz+d))[(cz+d)^(2k)] = f(z). POR CONTA DA PERIODICIDADE FUNÇÕES
MODULARES PODEM SER EXPANDIDAS EM SÉRIES DE FOURIER.

SE ALÉM DAS CONDIÇÕES ACIMA A FUNÇÃO f FOR HOLOMÓRFICA EM TODO SEU DOMÍNIO INCLUINDO UM PONTO NO INFINITO (f(∞) É LIMITADO) ENTÃO A FUNÇÃO É CHAMADA DE FORMA MODULAR DE
GRAU 2k. SE f(∞)=0 ENTÃO f É CHAMADA DE FUNÇÃO MODULAR DE CÚSPIDE.

FUNÇÕES MODULARES OCORREM NATURALMENTE NA TEORIA DE CURVAS ELÍPTICAS E DESEMPENHAM UM PAPEL IMPORTANTE EM ALGORITMOS COMO O TESTE DE PRIMALIDADE DE CURVAS ELÍPTICAS (UM
DOS MAIS EFICIENTES ALGORITMOS PARA TESTAR A PRIMALIDADE DE GRANDES NÚMEROS INTEIROS). ESTA CLASSE DE FUNÇÕES TAMBÉM SÃO DE GRANDE INTERESSE TEÓRICO, POR EXEMPLO NA
DEMONSTRAÇÃO DO ÚLTIMO TEOREMA DE FERMAT ELAS DESEMEPANHAM UM PAPEL MUITO IMPORTANTE.

PARA MAIORES INFORMAÇÕES:
https://en.wikipedia.org/wiki/Modular_form
https://en.wikipedia.org/wiki/Eisenstein_series
https://en.wikipedia.org/wiki/Weierstrass_elliptic_function#Modular_discriminant
https://en.wikipedia.org/wiki/Dedekind_eta_function
https://en.wikipedia.org/wiki/Nome_(mathematics)#
https://en.wikipedia.org/wiki/Theta_function#Auxiliary_functions
https://en.wikipedia.org/wiki/J-invariant#Expressions_in_terms_of_theta_functions

*/


//********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef MODULAR_FORMS_H
#define MODULAR_FORMS_H
#include"complexification.hpp"
#include"complex_numbers.hpp"
#include"riemann_zeta.hpp"
#include<cmath>
#include<assert.h>
#include<stdint.h>

//********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
complex<double> eisenstein_series(complex<double>, complex<double>, int64_t);
complex<double> eisenstein_series(complex<double>, int64_t);
complex<double> normalized_eisenstein_series(complex<double>, int64_t);
complex<double> modular_discriminant(complex<double>);
complex<double> dedekind_eta_function(complex<double>);
complex<double> j_invariant(complex<double>);
complex<double> weierstrass_rho_function(complex<double>, complex<double>, complex<double>);
complex<double> jacobi_theta_function(complex<double>, complex<double>);


//********************************************************************************************************************************************************************
//FUNÇÕES
//Funções que implementam as séries de Einsenstein G(k, z) e G(k, ω1, ω2) usaremos uma malha de 2000x2000 pontos no cálculo
complex<double> eisenstein_series(complex<double> omega1, complex<double> omega2, int64_t k){
//Restrição
complex<double> quotient=omega1/omega2;
assert(quotient.imag>0);
assert((omega1.real/omega2.real)!=(omega1.imag/omega2.imag));
assert(k%2==0 && k>=2);

//Variáveis locais
complex<double> m, n;
complex<double> result(0.0, 0.0), parcel;
int64_t lattice_points=2000;
int64_t i, j;

//Procedimentos
for(i=(-1)*lattice_points; i<(lattice_points+1); i++){
for(j=(-1)*lattice_points; j<(lattice_points+1); j++){
//Excluindo a origem
if(i==0 && j==0)
continue;

//Computando os termos da soma
m=complexification(i);
n=complexification(j);
parcel=((m*omega1)+(n*omega2)).pow(k);
parcel=parcel.inv();
result = result+parcel;
                                                     };
                                                     };
//Resultados
result.real/=(lattice_points*lattice_points);
result.imag/=(lattice_points*lattice_points);
return result;
                                                                                            };


complex<double> eisenstein_series(complex<double> z, int64_t k){
//Restrições
assert(z.imag>0);
assert(k%2==0 && k>=2);

//Variáveis locais
complex<double> m, n;
complex<double> result(0.0, 0.0), parcel;
int64_t lattice_points=2000;
int64_t i, j;

//Procedimentos
for(i=(-1)*lattice_points; i<(lattice_points+1); i++){
for(j=(-1)*lattice_points; j<(lattice_points+1); j++){
//Excluindo a origem
if(i==0 && j==0)
continue;

//Computando os termos da soma
m=complexification(i);
n=complexification(j);
parcel=((m*z)+n).pow(k);
parcel=parcel.inv();
result = result+parcel;
                                                     };
                                                     };
//Resultados
result.real/=(lattice_points*lattice_points);
result.imag/=(lattice_points*lattice_points);
return result;
                                                               };

complex<double> normalized_eisenstein_series(complex<double> z, int64_t k){
//Variáveis locais
double k_=static_cast<double>(k);
complex<double> result = eisenstein_series(z, k);

//Resultado
result.real/=(2*riemann_zeta_function(k_));
result.imag/=(2*riemann_zeta_function(k_));
return result;
                                                                          };

//Função que implementa a função (Δ) discriminante modular
complex<double> modular_discriminant(complex<double> z){
//Variáveis locais
complex<double>sixty=complexification(60.0);
complex<double>one_hunrdred_fourty=complexification(140.0);
complex<double>twenty_seven=complexification(27.0);
complex<double>g2=sixty*eisenstein_series(z, 4);
complex<double>g3=one_hunrdred_fourty*eisenstein_series(z, 6);

//Resultado
return (g2*g2)-twenty_seven*(g3*g3*g3);
                                                       };

//Função que implementa a função (η) eta de Dedekind
complex<double> dedekind_eta_function(complex<double> z){
//Variáveis locais
constexpr double pi=4*std::atan(1.0);
complex<double>power_pi= (complexification(2*pi)).pow(12);

//Resultado
return (modular_discriminant(z)/power_pi).pow(1.0/24.0);
                                                        };

//Função que implementa a função invariante j
complex<double> j_invariant(complex<double> z){
//Variáveis locais
complex<double> sixty=complexification(60.0);
complex<double> constant_factor=complexification(1728.0);
complex<double>g2=sixty*eisenstein_series(z, 4);

//Resultado
return (constant_factor*g2*g2*g2)/modular_discriminant(z);
                                              };

//Função que implementa a função (ρ) rho de Weierstrass
complex<double> weierstrass_rho_function(complex<double>z, complex<double>omega1, complex<double>omega2){
//Restrição
complex<double> quotient=omega1/omega2;
assert(quotient.imag>0);
assert((omega1.real/omega2.real)!=(omega1.imag/omega2.imag));

//Variáveis locais
complex<double>m, n, parcel, lattice, sum(0.0,0.0);
int64_t lattice_points=1000;
int64_t i, j;

//Procedimentos
//Cálculo do termo da soma
for(i=(-1)*lattice_points; i<(lattice_points+1); i++){
for(j=(-1)*lattice_points; j<(lattice_points+1); j++){
//Excluindo a origem
if(i==0 && j==0)
continue;

//Computando os termos da soma
m=complexification(i);
n=complexification(j);
lattice=((m*omega1)+(n*omega2));

//Excluindo os polos
if(lattice.real== z.real && lattice.imag== z.imag)
continue;

parcel = ((z-lattice).pow(2)).inv()-(lattice.pow(2)).inv();

                                                     };
                                                     };

sum.real/=(lattice_points*lattice_points);
sum.imag/=(lattice_points*lattice_points);

//Resultado
return (z.pow(2)).inv()+sum;
                                                                                                        };
//Função que implementa função theta de Jacobi (Θ_00 ou simplesmente Θ)
//Usaremos a função complex_int_pow definida no header
/*

NOTA:Algumas funções auxiliares Θ_01, Θ_10 e Θ_11 podem ser definidas támbem, para diferenças na notação ver artigo:
https://en.wikipedia.org/wiki/Jacobi_theta_functions_(notational_variations) 
Aqui definimos apenas a função Θ_00 as demais funções auxiliares podem ser definidas a partir desta.
Existem generalizações para outros corpos numéricos como o conjunto dos inteiros gaussianos.

*/
complex<double> jacobi_theta_function(complex<double> z, complex<double> tau){
//Variáveis locais
constexpr double pi = 4*std::atan(1.0);
complex<double> exponent;
complex<double> unit(0, 1.0);
complex<double> parcel, sum(0.0,0.0);
int64_t n=2000, i;

//Procedimentos
for(i=(-1)*n; i<(n+1); ++i){
exponent = (unit*complexification(pi*i*i)*tau)+(unit*complexification(2*pi*i)*z);
parcel.real=std::cos(exponent.imag)*std::exp(exponent.real);
parcel.imag=std::sin(exponent.imag)*std::exp(exponent.real);
sum=sum+parcel;
                           };
//Resultado
return sum;
                                                                             };



//********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
