//VAMOS UM CRIAR PROGRAMA QUE IMPLEMENTA ROTINAS EFICIENTES PARA O CÁLCULO DAS SEQUÊNCIAS DE LUCAS

/*
SEQUÊNCIAS DE LUCAS SÃO EXTREMAMENTE IMPORTANTES MMATEMÁTICAS, EM PARTICULAR EM TEORIA DE NÚMEROS. 
USAREMOS UM ALGORITMO LIGEIRAMENTE MAIS RÁPIDO DO QUE AS TÉCNICAS USUAIS PARA COMPUTAR SEQUÊNCIA DE LUCAS.

LINK PARA O ARTIGO ORIGINAL: https://file.scirp.org/pdf/IJCNS20101200011_90376712.pdf

*/

//********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef LUCAS_SEQUENCE_H
#define LUCAS_SEQUENCE_H
#include<stdint.h>
#include<inttypes.h>
#include<math.h>

//********************************************************************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
void lucas_sequence(__int128_t*, __int128_t*, int64_t, int64_t, int64_t);

//********************************************************************************************************************************************************************
//FUNÇÕES
//Funções que implementa o cálculo da sequêcia de Lucas
void lucas_sequence(__int128_t* Uk, __int128_t* Vk, int64_t k, int64_t P, int64_t Q){
__int128_t vl=2, vh=P;
__int128_t ql=1, qh=1;
int bits=log2(k)+1;
int8_t bit_digits[bits];
int i, j;

//Procedimentos
//Cálculos dos bits do número em questão
for(i=(bits-1); i>=0; --i){
if(k&1)
bit_digits[i]=1;
else
bit_digits[i]=0;

//Atualizando variáveis para a próxima iteração
k>>=1;
                          };

//Loop principal
for(j=(bits-1); j>=0; j--){
ql*=qh;

if(bit_digits[j]==1){
qh=ql*Q;
vl=((vh*vl)-(P*ql));
vh=((vh*vh)-(2*qh));
                    }
else{
ql=qh;
vh=((vh*vl)-(P*ql));
vl=((vl*vl)-(2*qh));
    };
                          };

//Resultado
(*Vk)=vl;
(*Uk)=(((2*vh)-(P*vl))/((P*P)-(4*Q)));
                                                                                    };

//********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
