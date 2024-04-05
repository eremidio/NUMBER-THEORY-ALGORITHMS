//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DA PENEIRA HIPERBÓLICA PARA OTIMIZAR ALGORITMOS EXPONENCIAIS USADOS NA FATORAÇÃO DE NÚMEROS 

/*
USANDO TÉCNICAS DA TEORIA DOS CRIVOS (PENEIRAS) É POSSÍVEL REDUZIR A COMPLEXIDADE E OTIMIZAR A EXECUÇÃO DE DIVERSOS ALGORITMOS EM TEORIA DOS NÚMEROS PARA RESOLVER
PROBLEMAS COMO A DECOMPOSIÇÃO DE INTEIROS EM FATORES PRIMOS E O PROBLEMA DO LOGARITMO DISCRETO.

SEJA n  UM INTEIRO TAL QUE n=pq, COM p, q PRIMOS E p<q. p,q SÃO SOLUÇÕES DA EQUAÇÃO n=xy (mod m), COM m INTEIRO COPRIMO COM n. DENOTANDO Z/nZ O CONJUNTO DOS INTEIROS
A MENOS DE UMA CONGRUÊNCIA MÓDULO n, DEFINIMOS OS CONJUNTOS DENOMINADOS HIPÉRBOLAS MODULARES COMO h(m,n)={(x,y) ∈ Z/nZ: n= xy mod(m), mdc(m,n)=1}. O NÚMERO DE PARES EM 
h(m,n) É φ(m), ONDE φ É A FUNÇÃO TOTIENTE DE EULER. PARA OBTER INFORMAÇÕES SOBRE OS FATORES DE n CONSIDERAMOS OS CONJUNTO l(m,n)={={x+y(mod m): (x,y) ∈ h(m,n)}. É
POSSÍVEL MOSTRAR QUE PARA m PRIMO l(m,n) CONTÉM CERCA DE METADES DAS CLASSES RESIDUAIS MÓDULO m. PARA m  IGUAL AO PRODUTO DE PEQUENOS NÚMEROS PRIMOS l(m,n) CONTÉM
UM PERCENTUAL PEQUENO DE CLASSES RESIDUAIS MÓDULO m. TAL FATO PERMITE OBTER INFORMAÇÕES SOBRE S=(p+q) A SOMA DOS FATORES PRIMOS DE n. TAL INFORMAÇÃO NOS PERMITE 
OTIMIZAR ALGORITMOS PARA FATORAR n.

NO PRESENTE PROGRAMA VAMOS IMPLEMENTAR UMA VARIANTE SIMPLES DO ALGORITMO DE FERMAT USANDO ESSA OTIMIZAÇÃO (UMA VARIANTE MAIS ROBUSTA USANDO DOIS LIMITES B1 E B2 ESTÁ 
DISPONÍVEL NO ARTIGO, ESTA VARIANTE POSSUI MELHOR TEMPO DEEXECUÇÃO  PORÉM USA MAIS ESPAÇO).
NO ALGORITMO É MAIS ADEQUADO O USO DE BIBLIOTECAS OU LINGUAGENS COM INTEIROS DE PRECISÃO ARBITRÁRIA,  USAREMOS INTEIROS DE 128 BITS NO CÁLCULO PARA EVITAR OVERFLOW.

PARA MAIORES REFERÊNCIAS: https://arxiv.org/pdf/2205.10074.pdf


*/



//***********************************************************************************************************************************************
//CABEÇALHO
#ifndef HYPERBOLIC_SIEVE_FERMAT_FACTORIZATION_ALGORITHM_H
#define HYPERBOLIC_SIEVE_FERMAT_FACTORIZATION_ALGORITHM_H
#include"int128.h"
#include"sqrt128.h"
#include"mod_bin_exponentiation128.h"
#include<stdint.h>
#include<vector>
#include<iostream>
#include<random>


//***********************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
__int128_t modular_inverse(__int128_t, __int128_t );
std::vector<__int128_t> optimal_chinese_remainder_theorem(std::vector<__int128_t>&, std::vector<std::vector<__int128_t>>&, std::vector<__int128_t>&);
__int128_t generate_random_number(__int128_t);
__int128_t gcd128(__int128_t, __int128_t);
__int128_t legendre_symbol(__int128_t, __int128_t);
std::vector<__int128_t> generate_lnrk_set(__int128_t, __int128_t, __int128_t);
void hyperbolic_fermat_factorization(__int128_t, __int128_t);

//***********************************************************************************************************************************************
//FUNÇÕES
//Função que calcula o inverso modular de um número inteiro a (mod n) usando o algoritmo extendido de Euclides
__int128_t modular_inverse(__int128_t a, __int128_t n){
//Variáveis locais
__int128_t r0,r1, x0, x1, r2, x2;
//Procedimentos 
//Ajuste de variáveis
r0=a;
r1=n;
r2=1;
x0=1;
x1=0;

//Calculando os valores finais dos coeficientes recursivamente
while(r2>0){
__int128_t quotient= r0/r1;

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


//Função que implementa uma variante do teorema do resíduos chinês que computa um conjunto X={x(i)=a(i) mod m(i)}, para i=0,1,2,3,....
/*
NOTA: mi denota valores m(i) coprimos, A(i) são conjuntos de valores inteiros residuos módulo m(i) e k(i) são os tamanhos dos conjuntos A(i)
*/
std::vector<__int128_t> optimal_chinese_remainder_theorem(std::vector<__int128_t>& mi, std::vector<std::vector<__int128_t>>& Ai, std::vector<__int128_t>& kappa){
//Variáveis locais
__int128_t M=1, A_size=1, x, u;
std::vector<__int128_t> Mi;
std::vector<__int128_t> A_set;
std::vector<std::vector<__int128_t>> delta;
std::vector<int64_t> r;
int d=kappa.size();


//Procedimentos
//Computando os parâmetros M e A_size usados no algoritmo
for(auto congruent:mi)
M*=congruent;

for(auto set_size:kappa)
A_size*=set_size;

//Pré-computação:computando os valores de Mi={M/m(i)} [ (M/m(i)⁻¹) mod m(i)]
for(int i1=0; i1<d; i1++){

r.push_back(0);
__int128_t temp0=M/mi[i1];
Mi.push_back((temp0*modular_inverse(temp0, mi[i1]))%M);

                         };

//Pré computando as distâncias Δ entre os (l+1)-ésimos e l-ésimos elementos do i-ésimo conjunto
for(int i2=0; i2<d; i2++){
std::vector<__int128_t> temp;

temp.push_back(((Ai[i2][0]-Ai[i2][kappa[i2]-1])*Mi[i2])%M);

for(auto l=1; l<(kappa[i2]-2);l++)
temp.push_back(((Ai[i2][l]-Ai[i2][l-1])*Mi[i2])%M);

delta.push_back(temp);

                         };


//Calculando elementos do conjunto A final
//1º elemento
x=0;

for(int i3=0; i3<d; i3++)
x+=((Ai[i3][0])*Mi[i3])%M;

A_set.push_back(x);

//Demais elementos
for(__int128_t i4=1; i4<A_size; i4++){

r[1]=r[1]+1;
u=1;

while(r[u]==0){
u++;
r[u]=(r[u]+1)%kappa[u];
              };


for(__int128_t i5=1; i5<=u; i5++)
x+=delta[i5][r[i5]];

                                     };

//Resultado
return A_set;

                                                                                                                                                                };



//Função que gera um inteiro aleatório de 128 bits
__int128_t generate_random_number(__int128_t limit){

//Variáveis locais
__int128_t result;


//Procedimentos
//Ajuste da distribuição de números aleatórios
std::random_device generator_x;
std::mt19937 gen(generator_x());
std::uniform_int_distribution<__int128_t> elliptic_distribution(1, limit);

//Resultado
result=elliptic_distribution(generator_x);
return result;
                                                   };




//Função que implementa o algoritmo de Euclides para inteiros de 128 bits
__int128_t gcd128(__int128_t a, __int128_t b){

if(b==0)
return a;
else
return gcd128(b, (a%b));
                                             };


//Função que calcula o símbolo de Legendre usando exponenciação binária e o critério de Euler
__int128_t legendre_symbol(__int128_t a, __int128_t p){
return mod_bin_pow(a, ((p-1)/2), p);
                                                      }; 

//Função que gera um conjunto de valores que satisfazem relações de reciprocidade quadrática
std::vector<__int128_t> generate_lnrk_set(__int128_t N, __int128_t m, __int128_t k){
//Variáveis locais
std::vector<__int128_t> result;
__int128_t x, abs_discriminant, discriminant, tester;

//Loop principal
for(x=1; x<m; ++x){

discriminant=(x*x)-(4*k*N);

if(discriminant<0){
abs_discriminant=(-1)*discriminant;
abs_discriminant%=m;
tester=(m-abs_discriminant);

if(legendre_symbol(tester, m)==1)
result.push_back(x);

                  }

else{
tester=(discriminant%m);

if(legendre_symbol(tester, m)==1)
result.push_back(x);
    };


                  };

//Resultado
return result;
                                                                                   };


//Função que implementa uma versão optimizada do algoritmo de Fermat usando uma peneira hiperbólica
void hyperbolic_fermat_factorization(__int128_t number, __int128_t bound){
//Variáveis locais
int prime_seed[25]={2,3,5,7,11,13,17,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
__int128_t m=1, a=1, b=1, L, k, y, y_squared;
__int128_t factor=0;
std::vector<__int128_t> L_r_size;
std::vector<std::vector<__int128_t>> L_r;
std::vector<__int128_t> remainder_set;
std::vector<__int128_t> L_Nrk;
std::vector<__int128_t> L_m;


//Procedimentos
//Computado o parâmetro m usado no algoritmo
for(auto prime:prime_seed){
m*=prime;
if(prime>bound)
break;

if(prime>bound)
break;
                          };


//Teste 1: detectando a ocorrência de pequenos fatores primos
factor=gcd128(number, m);
if(factor>1){
printf("Fatores encontrados: ");
printf128(factor);
printf128((number/factor));
return;
            };

//Gerando números aleatórios a, b  tais que mdc(ab, mN)=1
while(1){
a=generate_random_number(number);
b=generate_random_number(number);

if(gcd128((a*b), (m*number))==1)
break;
        };

//Cálculo dos parâmetros L, k
L=sqrt128(2*a*b*number);
k=(a*b)%m;

//Teste 2: checando se L,k possuem fatores em comum com o número a ser fatorado
factor=gcd128(number, L);

if(factor>1){
printf("Fatores encontrados: ");
printf128(factor);
printf128((number/factor));
return;
            };

factor=gcd128(number, k);

if(factor>1){
printf("Fatores encontrados: ");
printf128(factor);
printf128((number/factor));
return;
            };


//Gerando um conjunto de potenciais classes residuais da soma de fatores primos do número a ser fatorado
for(auto r: prime_seed){

if((m%r)==0){

L_Nrk=generate_lnrk_set(number, r, k);
remainder_set.push_back(r);

std::vector<__int128_t> temp_set;

for(auto element:L_Nrk){
if(element<L)
temp_set.push_back(((m-(L-element))%m));
else
temp_set.push_back(((element-L)%m));
                       };

L_r.push_back(temp_set);
L_r_size.push_back(temp_set.size());

            };



                           };




L_m=optimal_chinese_remainder_theorem(remainder_set, L_r, L_r_size);

//Cálculo de possiveis fatores primos
for(auto m:L_m){
y_squared=((m+L)*(m+L))-(4*a*b);
y=sqrt(y_squared);

if((y*y)==(((m+L)*(m+L))-(4*a*b))){

factor=gcd128((m+L-y), number);

if(factor>1){
printf("Fatores encontrados: ");
printf128(factor);
printf128((number/factor));
return;
            };

                                  };

               };



//Caso o algoritmo não encontre um fator primo 
printf("Limite usado é muito pequeno.\n");
                                                                         };


//***********************************************************************************************************************************************
//FIM DO HEADER
#endif

