//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA VERSÃO SIMPLIFICADA DO ALGORITMO DE GAUSS PARA FATORAR NÚMEROS INTEIROS DE  ATÉ 64 BITS


/*
O ALGORITMO DE GAUSS É UMA APLICAÇÃO DA LEI DA RECIPROCIDADE QUADRÁTICA AO PROBLEMA DE COMPUTAR FATORES PRIMOS DE NÚMEROS INTEIROS. O ALGORITMO SE BASEIA NO SEGUINTE
FATO SEJA n=pq UM  NÚMERO COMPOSTO E p UM FATOR PRIMO DE n, x²=a (mod n), ENTÃO NECESSARIAMENTE x²=a (mod p) (TAL AFIRMAÇÃO É VERDADEIRA PARA QUALQUER FATOR PRIMO DE n).
ENTÃO SE OBTERMOS CLASSES DE RESÍDUOS QUADRÁTICOS MÓDULO n, PODEMOS DE MANEIRA EFICIENTE COMPUTAR FATORES PRIMOS DE n. LEIS ESTATÍSTICAS ACERCA DA DISTRIBUIÇÃO DE PRIMOS
AFIRMAM QUE PARA CADA CLASSE RESÍDUAL A CERCA DE 50% DOS PRIMOS NÃO SÃO RESÍDUOS QUADRÁTICOS MÓDULO UM PRIMO. ENTÃO CÁLCULANDO k RESÍDUOS QUADRÁTICOS MÓDULO O NÚMERO A 
SER FATORADO REDUZ-SE A LISTA DE EVENTUAIS DIVISORES POR UM FATOR DE 2^k.

NOTEMOS QUE x²=a (mod n), ENTÃO x²-a=kn, PARA ALGUM INTEIRO k, ENTÃO TOMANDO VALORES DA ORDEM DE (kn)^(1/2) PARA PEQUENOS k, E USANDO O FATO QUE PRODUTOS DE QUADRADOS RESIDUAIS MÓDULOS UM INTEIRO FIXO TAMBÉM PRODUZEM QUADRADOS RESIDUAIS MÓDULO UM INTEIRO, PODEMOS COMPUTAR FACILMENTE PEQUENOS VALORES DE a E COM ISSO OBTER INFORMAÇÕES
ACERCA DE POSSÍVEIS DIVISORES DE n POR MEIO DE RELAÇÕES p=l (mod k) COM k INTEIRO. COMBINANDO ALGEBRICAMENTE RELAÇÕES PARA p, É POSSÍVEL CALCULAR A FORMA DOS FATORES DE
UM NÚMERO COMPOSTO. PARA MUITAS CLASSES RESIDUAIS MÓDULO n A MANIPULAÇÃO ALGÉBRICA FINAL É RELATIVAMENTE COMPLICADA. PARA UM NÚMERO REDUZIDO DE CLASSES RESIDUAIS TAIS
COMPUTAÇÕES PODEM SER FEITAS MANUALMENTE.

USAREMOS UMA ABORDAGEM MAIS SIMPLES BASEADO NO SEGUINTE ESQUEMA QUE USA PRIMOS INFERIORES A 20, A SABER {2,3,5,7,11,13,17,19,23,29}. CALCULAMOS UM ELEMENTO p DESTA
LISTA DE PRIMOS TAL QUE O SÍMBOLO DE LEGENDRE (n|p)=1, TAL RELAÇÃO FORNECE UMA LISTA DE POSŚIVEIS DIVISORES p DE n DA FORMA p= l (mod k) QUE PODEM SER TESTADOS. COM UMA
ESCOLHA ADEQUADA PODEMOS REDUZIR A  LISTA DE  POSSÍVEIS DIVISORES A SEREM TESTADOS. USANDO UM LISTA DE PRIMOS MAIOR É O POSSÍVEL OBTER UMA MAIOR NÚMERO DE RELAÇÕES DE
CONGRUÊNCIA SATISFEITA POR POSSÍVEIS DIVISORES DE UM NÚMERO COMPOSTO, PORÉM O NÚMERO DE CHECAGENS RAPIDAMENTE CRESCE DE MODO QUE OTIMIZAÇÕES SIMPLES DO TIPO CONSIDERAR POSSÍVEIS DIVISORES DE FORMAS 6k+1, 6k-1 OU 30k+7, 30k+11, 30k+13, 30k+17, 30k+19, 30k+23, 30k+29, 30k+31 SE TORNA MAIS EFICAZES.


PARA MAIORES INFORMAÇÕES: Prime Numbers And Computer Method For Factorization by Hans Riesel


*/



//*******************************************************************************************************************************************************************
//CABEÇALHO
#if !defined GAUSS_FACTORIZATION_METHOD_H
#define GAUSS_FACTORIZATION_METHOD_H
#include"legendre_symbol.h"
#include<math.h>
#include<stdio.h>


//*******************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void residue2_test(uint64_t*, uint64_t);
void residue3_test(uint64_t*, uint64_t);
void residue5_test(uint64_t*, uint64_t);
void residue7_test(uint64_t*, uint64_t);
void residue11_test(uint64_t*, uint64_t);
void residue13_test(uint64_t*, uint64_t);
void residue17_test(uint64_t*, uint64_t);
void residue19_test(uint64_t*, uint64_t);
void residue23_test(uint64_t*, uint64_t);
void residue29_test(uint64_t*, uint64_t);

void gauss_factorization_method(uint64_t);

//*******************************************************************************************************************************************************************
//FUNÇÕES

//-------------------
//Função que implementa o teste de possíveis divisores da classes residual x²=2 (mod n)

void residue2_test(uint64_t* number, uint64_t root){
//Variáveis locais
uint64_t N=(*number);
uint64_t divisor1, divisor2;
uint64_t k, l=1;

//Procedimentos 
//Loop principal
for(k=1;;++k){
divisor1=(8*k)+1;
divisor2=(8*k)-1;

if(divisor2>root)
return;

if((N%divisor1)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor1);
N/=divisor1;
(*number)=N;
return;
                   };

if((N%divisor2)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor2);
N/=divisor2;
(*number)=N;
return;
                   };
             };
                                                   };

//-------------------
//Função que implementa o teste de possíveis divisores da classes residual x²=3 (mod n)

void residue3_test(uint64_t* number, uint64_t root){
//Variáveis locais
uint64_t N=(*number);
uint64_t divisor1, divisor2;
uint64_t k, l=1;

//Procedimentos 
//Loop principal
for(k=1;;++k){
divisor1=(12*k)+1;
divisor2=(12*k)-1;

if(divisor2>root)
return;

if((N%divisor1)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor1);
N/=divisor1;
(*number)=N;
return;
                   };

if((N%divisor2)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor2);
N/=divisor2;
(*number)=N;
return;
                   };
             };
                                                   };

//-------------------
//Função que implementa o teste de possíveis divisores da classes residual x²=5 (mod n)

void residue5_test(uint64_t* number, uint64_t root){
//Variáveis locais
uint64_t N=(*number);
uint64_t divisor1, divisor2;
uint64_t k, l=1;

//Procedimentos 
//Loop principal
for(k=1;;++k){
divisor1=(10*k)+1;
divisor2=(10*k)-1;

if(divisor2>root)
return;

if((N%divisor1)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor1);
N/=divisor1;
(*number)=N;
return;
                   };

if((N%divisor2)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor2);
N/=divisor2;
(*number)=N;
return;
                   };
             };
                                                   };

//-------------------
//Função que implementa o teste de possíveis divisores da classes residual x²=7 (mod n)

void residue7_test(uint64_t* number, uint64_t root){

//Variáveis locais
uint64_t N=(*number);
uint64_t divisor1, divisor2;
uint64_t l[3]={1,3,9};
uint64_t k, i;

//Procedimentos
//Loop principal
for(k=1;;++k){
for(i=0; i<3; ++i){


divisor1=(28*k)+l[i];
divisor2=(28*k)-l[i];

if(divisor2>root)
return;

if((N%divisor1)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor1);
N/=divisor1;
(*number)=N;
return;
                   };

if((N%divisor2)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor2);
N/=divisor2;
(*number)=N;
return;
                   };

                  };
             };

                                                   };

//-------------------
//Função que implementa o teste de possíveis divisores da classes residual x²=11 (mod n)

void residue11_test(uint64_t* number, uint64_t root){

//Variáveis locais
uint64_t N=(*number);
uint64_t divisor1, divisor2;
uint64_t l[5]={1,5,7,9,19};
uint64_t k, i;

//Procedimentos
//Loop principal
for(k=1;;++k){
for(i=0; i<5; ++i){


divisor1=(44*k)+l[i];
divisor2=(44*k)-l[i];

if(divisor2>root)
return;

if((N%divisor1)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor1);
N/=divisor1;
(*number)=N;
return;
                   };

if((N%divisor2)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor2);
N/=divisor2;
(*number)=N;
return;
                   };

                  };
             };

                                                    };

//-------------------
//Função que implementa o teste de possíveis divisores da classes residual x²=13 (mod n)

void residue13_test(uint64_t* number, uint64_t root){

//Variáveis locais
uint64_t N=(*number);
uint64_t divisor1, divisor2;
uint64_t l[3]={1,3,9};
uint64_t k, i;

//Procedimentos
//Loop principal
for(k=1;;++k){
for(i=0; i<3; ++i){


divisor1=(26*k)+l[i];
divisor2=(26*k)-l[i];

if(divisor2>root)
return;

if((N%divisor1)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor1);
N/=divisor1;
(*number)=N;
return;
                   };

if((N%divisor2)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor2);
N/=divisor2;
(*number)=N;
return;
                   };

                  };
             };

                                                    };

//-------------------
//Função que implementa o teste de possíveis divisores da classes residual x²=17 (mod n)

void residue17_test(uint64_t* number, uint64_t root){

//Variáveis locais
uint64_t N=(*number);
uint64_t divisor1, divisor2;
uint64_t l[4]={1,9,13,15};
uint64_t k, i;

//Procedimentos
//Loop principal
for(k=1;;++k){
for(i=0; i<4; ++i){


divisor1=(34*k)+l[i];
divisor2=(34*k)-l[i];

if(divisor2>root)
return;

if((N%divisor1)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor1);
N/=divisor1;
(*number)=N;
return;
                   };

if((N%divisor2)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor2);
N/=divisor2;
(*number)=N;
return;
                   };

                  };
             };

                                                    };

//-------------------
//Função que implementa o teste de possíveis divisores da classes residual x²=19 (mod n)

void residue19_test(uint64_t* number, uint64_t root){

//Variáveis locais
uint64_t N=(*number);
uint64_t divisor1, divisor2;
uint64_t l[9]={1,3,5,9,15,17,25,27,31};
uint64_t k, i;

//Procedimentos
//Loop principal
for(k=1;;++k){
for(i=0; i<9; ++i){


divisor1=(76*k)+l[i];
divisor2=(76*k)-l[i];

if(divisor2>root)
return;

if((N%divisor1)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor1);
N/=divisor1;
(*number)=N;
return;
                   };

if((N%divisor2)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor2);
N/=divisor2;
(*number)=N;
return;
                   };

                  };
             };

                                                   };

//-------------------
//Função que implementa o teste de possíveis divisores da classes residual x²=23 (mod n)

void residue23_test(uint64_t* number, uint64_t root){

//Variáveis locais
uint64_t N=(*number);
uint64_t divisor1, divisor2;
uint64_t l[11]={1,7,9,11,13,15,19,25,29,41,43};
uint64_t k, i;

//Procedimentos
//Loop principal
for(k=1;;++k){
for(i=0; i<11; ++i){


divisor1=(92*k)+l[i];
divisor2=(92*k)-l[i];

if(divisor2>root)
return;

if((N%divisor1)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor1);
N/=divisor1;
(*number)=N;
return;
                   };

if((N%divisor2)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor2);
N/=divisor2;
(*number)=N;
return;
                   };

                   };
             };

                                                    };

//-------------------
//Função que implementa o teste de possíveis divisores da classes residual x²=29 (mod n)

void residue29_test(uint64_t* number, uint64_t root){

//Variáveis locais
uint64_t N=(*number);
uint64_t divisor1, divisor2;
uint64_t l[7]={1,5,7,9,13,23,25};
uint64_t k, i;

//Procedimentos
//Loop principal
for(k=1;;++k){
for(i=0; i<7; ++i){


divisor1=(58*k)+l[i];
divisor2=(58*k)-l[i];

if(divisor2>root)
return;

if((N%divisor1)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor1);
N/=divisor1;
(*number)=N;
return;
                   };

if((N%divisor2)==0){
printf("Fator de %lu encontrado: %lu\n", N, divisor2);
N/=divisor2;
(*number)=N;
return;
                   };

                  };
             };

                                                    };


//-------------------
//Função que implementa uma versão simplificada do algoritmo de Gauss para fatorar números inteiros
void gauss_factorization_method(uint64_t number){
//Variáveis locais
int tester;
uint64_t current=number;
const uint64_t root=sqrt(number);
uint64_t prime_seed[10]={2,3,5,7,11,13,17,19,23,29};

//Procedimento
//Loop principal: testes sobre classes residuais de primos menores que 30
while(true){

//29
tester= legendre(number, 29);

if(tester==0){
printf("Fator de %lu encontrado: 29\n", number);
printf("Cofator: %lu\n", (number/29));
return;
             };

if(tester==1){
residue29_test(&number, root);

//Obtendo fatorações não triviais
if(current==number)
goto step23;

printf("Cofator: %lu\n", number);
return;
             };

//23
step23:

tester= legendre(number, 23);

if(tester==0){
printf("Fator de %lu encontrado: 23\n", number);
printf("Cofator: %lu\n", (number/23));
return;
             };

if(tester==1){
residue23_test(&number, root);

//Obtendo fatorações não triviais
if(current==number)
goto step19;

printf("Cofator: %lu\n", number);
return;
             };


//19
step19:

tester= legendre(number, root);

if(tester==0){
printf("Fator de %lu encontrado: 19\n", number);
printf("Cofator: %lu\n", (number/19));
return;
             };

if(tester==1){
residue19_test(&number, 1);

//Obtendo fatorações não triviais
if(current==number)
goto step17;

printf("Cofator: %lu\n", number);
return;
             };

//17
step17:

tester= legendre(number, 17);

if(tester==0){
printf("Fator de %lu encontrado: 17\n", number);
printf("Cofator: %lu\n", (number/17));
return;
             };

if(tester==1){
residue17_test(&number, root);

//Obtendo fatorações não triviais
if(current==number)
goto step13;

printf("Cofator: %lu\n", number);
return;
             };

//13
step13:

tester= legendre(number, 13);

if(tester==0){
printf("Fator de %lu encontrado: 13\n", number);
printf("Cofator: %lu\n", (number/13));
return;
             };

if(tester==1){
residue13_test(&number, root);

//Obtendo fatorações não triviais
if(current==number)
goto step11;

printf("Cofator: %lu\n", number);
return;
             };

//11
step11:

tester= legendre(number, 11);

if(tester==0){
printf("Fator de %lu encontrado: 11\n", number);
printf("Cofator: %lu\n", (number/11));
return;
             };

if(tester==1){
residue11_test(&number, root);

//Obtendo fatorações não triviais
if(current==number)
goto step7;

printf("Cofator: %lu\n", number);
return;
             };


//7
step7:

tester= legendre(number, 7);

if(tester==0){
printf("Fator de %lu encontrado: 7\n", number);
printf("Cofator: %lu\n", (number/7));
return;
             };

if(tester==1){
residue7_test(&number, root);

//Obtendo fatorações não triviais
if(current==number)
goto step5;

printf("Cofator: %lu\n", number);
return;
             };


//5
step5:

tester= legendre(number, 5);

if(tester==0){
printf("Fator de %lu encontrado: 5\n", number);
printf("Cofator: %lu\n", (number/5));
return;
             };

if(tester==1){
residue5_test(&number, root);

//Obtendo fatorações não triviais
if(current==number)
goto step5;

printf("Cofator: %lu\n", number);
return;
             };


//3
step3:

tester= legendre(number, 3);

if(tester==0){
printf("Fator de %lu encontrado: 3\n", number);
printf("Cofator: %lu\n", (number/3));
return;
             };

if(tester==1){
residue3_test(&number, root);

//Obtendo fatorações não triviais
if(current==number)
goto step2;

printf("Cofator: %lu\n", number);
return;
             };

//2
step2:

tester= legendre(number, 2);

if(tester==0){
printf("Fator de %lu encontrado: 2\n", number);
printf("Cofator: %lu\n", (number/2));
return;
             };

if(tester==1){
residue2_test(&number, root);
printf("Cofator: %lu\n", number);
return;
             };


           };
                                                };

//*******************************************************************************************************************************************************************
//FIM DO HEADER
#endif
