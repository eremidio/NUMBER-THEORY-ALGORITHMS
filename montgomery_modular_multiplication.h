//VAMOS IMPLEMENTAR UM PROGRAMA QUE COMPUTA O ALGORITMO DA ARITMÉTICA MODULAR DE MONTGOMERY 

/*
O ALGORITMO DE MONTOGOMERY É UM EFICIENTE ALGORITMO USADO PARA IMPLEMENTAR ARITMÉTICA MODULAR. DADO a (mod N) E b (mod N) O ALGORITMO DE MONTGOMERY NOS PERMITE CALCULAR
DE FORMA EFICIENTE ab (mod N). O ALGORITMO FAZ USO DAS CHAMADAS FORMAS DE MONTGOMERY E NOS CÁLCULOS EMPREGA UM VALOR R TAL QUE mmc(N, R)=1, NOS CÁLCULOS INTERMEDIÁRIOS.
A IDEIA É QUE A DIVISÃO POR R SEJA FACILMENTE COMPUTADA (PODEMOS TOMAR R=2^k COM k INTEIRO POR EXEMPLO). ADIÇÃO E SUBTRAÇÃO PERMANECEM IDÊNTICOS, PORÉM MULTIPLICAÇÃO
REQUER O CÁLCULO DE FATORES MULTIPLICATIVOS R' E N' TAL QUE AS  RELAÇÕES [a (mod N)][b (mod N)] = ab (mod N) SEJAM PRESERVADAS.

TIPICAMENTE O ALGORITMO EXIGEQUE UM INPUT SEJA ESCRITO EM FORMA DE MONTGOMERY E O RESULTADO FINAL SEJA RECONVERTIDO PARA A REPRESENTAÇÃO USUAL, PORÉM AO EVITAR O CÁLCULO
DE DIVISÕES QUE EXIGEM COMPLEXAS MANIPULAÇÕES BITS NO CÁLCULO DE DÍGITOS DECIMAIS E AFINS, O ALGORITMO PERFOMA OPERAÇÕES mod N DE MANEIRA MUITO EFICIENTE. EM PARTICULAR
O ALGORITMO É EXTREMAMENTE A APLICAÇÕES QUANDO N É SUFICIENTEMENTE GRANDE COMO É O CASO DE ALGORITMOS ENVOLVIDOS EM CRIPTOGRAFIA, NOS  QUAIS AS CONVERSÕES ENVOLVENDO 
FORMAS DEMONTGOMERY SÓ SÃO NECESSÁRIAS AO INÍCIO E FIM DOS CÁLCULOS.

VAMOS IMPLEMENTAR A VARIANTE MAIS SIMPLES DO ALGORITMO. PARA INTEIROS DE PRECISÃO MÚLTIPLA QUE CONTÉM CENTENAS OU MILHARES DE BITS TAIS QUAIS OS USADOS EM CRIPTOGRAFIA O
ALGORITMO É UM POUCO MAIS SOFISTICADO.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Montgomery_modular_multiplication#Modular_arithmetic

*/

//********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef MONTGOMERY_MODULAR_MULTIPLICATION_H
#define MONTGOMERY_MODULAR_MULTIPLICATION_H
#include"gcd_euclides_fast.h"
#include"mod_bin_exponentiation.h"
#include<assert.h>
#include<stdio.h>

//********************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t montgomery_form(int64_t, int64_t, int64_t);
int64_t calculate_n_factor(int64_t, int64_t);
int64_t montgomery_reduction(int64_t, int64_t, int64_t);
int64_t mod_mul_montgomery(int64_t, int64_t, int64_t, int64_t);

//********************************************************************************************************************************************************************
//FUNÇÕES
//Função que determina a forma montgomery aR mod N, para um inteiro a
int64_t montgomery_form(int64_t a, int64_t R, int64_t N){
//Restrição
assert(binary_gcd(R,N)==1);

//Resultado
return ((a*R)%N); 
                                                        };

//Função que determina um parâmetro N' tal que N(N')=(R-1) mod R
int64_t calculate_n_factor(int64_t N, int64_t R){
//Variáveis locais
int64_t i, result;

//Procedimentos
for(i=1; i<R/2; ++i){
if(mul_mod(i, N, R)==(R-1)){
result=i;
break;
                           };

if(mul_mod((R-i), N, R)==(R-1)){
result=(R-i);
break;
                               };
                    };

//Resultado
return result;
                                               };

//Função que determina uma redução de Montgomery
int64_t montgomery_reduction(int64_t N, int64_t R, int64_t T){
//Restrições 
assert(binary_gcd(R,N)==1);

//Variáveis locais
int64_t N_=calculate_n_factor(N, R);
int64_t t, m;

//Procedimentos
//Ajuste de variáveis
m=((T%R)*N_)%R;
t=(T+(m*N))/R;

//Resultado
if(t>=N)
return (t-N);
else
return t;
                                                             };

//Função que calcula uma expressão do  tipo a(mod N)*b(mod N)=a*b(mod N) usando a redução de Montgomery
int64_t mod_mul_montgomery(int64_t a, int64_t b, int64_t N, int64_t R){
//Variáveis locais
int64_t am=montgomery_form(a, R, N);
int64_t bm=montgomery_form(b, R, N);
int64_t T=(am*bm)%N;
int64_t S=montgomery_reduction(N, R, T);

//Resultado
if(R>N){
if(S<N)
return S;
else
return (S-N);
       }
else{
if(S<N)
return (S-R);
else
return (S-N-R);
    };
                                                                      };


//********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
