//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO BABY_STEP_GIANT_STEP PARA CALCULAR LOGARITMOS DISCRETOS

/*
DADO INTEIROS a, b, c TAL QUE a^b = c O LOGARITMO DE c NA BASE a É DEFINIDO COMO log_a(c)=b.
TAL DEFINIÇÃO ESTABELECE UM HOMOMORFISMO ENTRE O GRUPO DOS INTEIROS COM A OPERAÇÃO DE ADIÇÃO E UM GRUPO G QUALQUER GERADO POR
UM CERTO ELEMENTO g (ISTO É ELEMENTOS DESTE GRUPO SÃO DA FORMA g^k=g*g*...*g). SE G FOR INFINITO TAL RELAÇÃO É UM ISOMORFISMO,
CASO CONTRÁRIO É UM ISOMORFISMO A MENOS DE UMA RELAÇÃO DE CONGRUÊNCIA MÓDULO |G| (|G| É A ORDEM DO GRUPO, NÚMEROS DE ELEMENTOS
DO GRUPO).

O ALGORITMO BABY_STEP_GIANT_STEP USA A SEGUINTE ABORDAGEM PARA CALCULAR LOGARITMOS DISCRETOS: SEJA k TAL QUE b^k=c (mod m)
ESCRITO NA FORMA k=in-j, COM i, j = 0, ..., m^(1/2). NESTA SITUAÇÃO TEMOS b^(in-j)=c (mod m) DONDE b^(in)= c(b^j) (mod m),
PRÉ-COMPUTANDO VALORES DE b^(in) E b^j, PODE-SE CHECAR RAPIDAMENTE QUAIS VALORES DE i, j SATISFAZEM ESTA RELAÇÃO E O VALOR DO
EXPOENTE k É FACILMENTE RECUPERADO. PARA OTIMIZAR ESTE ALGORITMO OS VALORES PRÉ-COMPUTADOS SÃO ALOCADOS EM UMA HASH TABLE.

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
//DECLARAÇÃO DE FUNÇÕES
int64_t baby_step_giant_step(int64_t, int64_t, int64_t);


//****************************************************************************************************************************
//FUNÇÕES
//Função que calcula um logaritmo discreto dado uma base, o logaritmando e um elemento de congruência
int64_t baby_step_giant_step(int64_t a, int64_t c, int64_t m) {

   //Variáveis locais
   int64_t n = std::ceil(std::sqrt(m));
   int64_t i, j;
   std::unordered_map<int64_t, int64_t> power_in;


  //Procedimentos
    //Pré-computando valores de a^(in) (mod m)
    for(i = 0; i < n; ++i) {
        int64_t value1 = mod_bin_pow(a, i * n, m);
        power_in[value1] = i;
    };

    //Iterando sobre os valores hash para calcular i,j satisfazendo a relação b^(in)= c(b^j) (mod m)
    for(j = 0; j < n; ++j) {

        int64_t value2 = c * mod_bin_pow(a, j, m) % m;
        auto it = power_in.find(value2);

        if (it != power_in.end()) {
            i = it->second;
            return i * n - j;
                                  };
    }

    // Resultado em caso de falha
    return -1;
}



//****************************************************************************************************************************
//FIM DO HEADER
#endif
