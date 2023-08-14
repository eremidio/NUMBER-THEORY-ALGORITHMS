//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO BABY_STEP_GIANT_STEP PARA CALCULAR LOGARITMOS DISCRETOS

/*
DADO INTEIROS a, b, c TAL QUE a^b = c O LOGARITMO DE c NA BASE a É DEFINIDO COMO log_a(c)=b.
TAL DEFINIÇÃO ESTABELECE UM HOMEOMORFISMO ENTRE O GRUPO DOS INTEIROS COM A OPERAÇÃO DE ADIÇÃO E UM GRUPO G QUALQUER GERADO POR
UM CERTO ELEMENTO g (ISTO É ELEMENTOS DESTE GRUPO SÃO DA FORMA g^k=g*g*...*g). SE G FOR INFINITO TAL RELAÇÃO É UM ISOMORFISMO,
CASO CONTRÁRIO É UM ISOMORFISMO A MENOS DE UMA RELAÇÃO DE CONGRUÊNCIA MÓDULO |G| (|G| É A ORDEM DO GRUPO, NÚMEROS DE ELEMENTOS
DO GRUPO).

LOGARITMOS DISCRETOS PODE SER COMPUTADOS USANDO-SE MULTIPLICAÇÃO ATÉ SE OBTER A RELAÇÃO DE CONGRUÊNCIA DESEJADA. O ALGORITMO
DENOMINADO BABY_STEP_GIANT_STEP USA A SEGUINTE ABORDAGEM ESCREVEMOS k (b^k=c (mod m)) COMO k=in-j, COM i,j=0, ..., m^(1/2).
NESTA SITUAÇÃO TEMOS b^(in-j)=c (mod m) DONDE b^(in)= c(b^j) (mod m), PRÉ-COMPUTANDO VALORES DE b^(in) E b^j, PODE-SE CHECAR
RAPIDAMENTE QUAIS VALORES DE i, j SATISFAZEM ESTA RELAÇÃO  E OVALOR DO EXPOENTE k É FACILMENTE RECUPERADO. PARA OTIMIZAR ESTE
ALGORITMO PODEMOS ALOCAR OS VALORES PRÉ COMPUTADOS EM UMA HASH TABLE.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Discrete_logarithm
                          https://en.wikipedia.org/wiki/Baby-step_giant-step
                          https://www.geeksforgeeks.org/discrete-logarithm-find-integer-k-ak-congruent-modulo-b/

*/

//****************************************************************************************************************************
//CABEÇALHO
#ifndef BABY_STEP_GIANT_STEP_H
#define BABY_STEP_GIANT_STEP_H
#include<unordered_map>
#include<cmath>
#include"mod_bin_exponentiation.h"
#include<inttypes.h>

//****************************************************************************************************************************
//FUNÇÕES
//Função que calcula um logaritmo discreto dado uma base, o logaritmando e um elemento de congruência
int64_t discrete_logarithm(int64_t a, int64_t c, int64_t m){
//Variáveis locais
std::unordered_map<int64_t, int64_t> power_in;
std::unordered_map<int64_t, int64_t>::iterator it1;

int64_t n=std::ceil(std::sqrt(m));//Limitante superior;
int64_t i, j, k;//Resultado 

//Procedimento
//Pré-computando valores de a^(in)/ a^j (mod m)
for(int64_t i=0; i<n; ++i)
power_in.insert({i, mod_pow(a, (i*n), m)});

//Iterando sobre os valores anteriores para calcula o valor do logaritmo
for(it1=power_in.begin(); it1!=power_in.end(); ++it1){
for(j=0;j<n;++j){
if((it1->second%m)==((c*mod_pow(a, j, m))%m)){
i=it1->first;
return ((i*n)-j);
                                             };
                };
                                                     };
return (-1);

                                                           };



//****************************************************************************************************************************
//FIM DO HEADER
#endif
