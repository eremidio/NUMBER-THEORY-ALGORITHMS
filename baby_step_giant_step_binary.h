//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO BABY-STEP-GIANT-STEP USANDO BUSCA BINÁRIA

/*
PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blame/main/baby_step_giant_step.hpp

*/

//********************************************************************************************************************************
//CABEÇALHO
#ifndef BABY_STEP_GIANT_STEP_BINARY_H
#define BABY_STEP_GIANT_STEP_BINARY_H
#include"mod_bin_exponentiation128.h"
#include<math.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>

//********************************************************************************************************************************
//ESTRUTURA USADA NO ALGORITMO
struct log_map{
    int64_t index;
    int64_t value;
};

//********************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void swap(int64_t, int64_t, struct log_map[]);
void quicksort_ascending(struct log_map[],int64_t, int64_t);
int64_t binary_search(struct log_map[], int64_t, int64_t, int64_t);


//********************************************************************************************************************************
//FUNÇÕES
//Função que troca dois elementos em um array
void swap(int64_t i, int64_t j, struct log_map log_array[]){
    //Variáveis locais
    struct log_map temp;

    //Procedimento
    //Trocando os elementos do array
    temp=log_array[i];
    log_array[i]=log_array[j];
    log_array[j]=temp;
}

//Função que implementa o algoritmo quicksort para ordenar um array de 64-bits em ordem crescente
void quicksort_ascending(struct log_map log_array[], int64_t low, int64_t high){
    //Caso base: o array contém apenas 1 elemento
    if(low>=high) return;

    //Variáveis locais
    int64_t i, last;

    //Procedimentos
    //Movendo o elemento da partição
    swap(low, ((low+high)/2), log_array);
    last=low;

    //Organizando uma subpartição da lista
    for(int64_t i=(low+1); i<=high; ++i){
        if(log_array[i].value<log_array[low].value)
            swap(++last, i, log_array);
    }

    //Retornando o elemento pivotal a sua posição original
    swap(low, last, log_array);

    //Execução recursiva do algoritmo: a lista é particionada em dois subarrays
    quicksort_ascending(log_array, low, (last-1));
    quicksort_ascending(log_array, (last+1), high);
}

//Função que implementa a busca binária em um array de struct log_map
int64_t binary_search(struct log_map log_array[], int64_t low, int64_t high, int64_t key){

    //Loop principal
    while (low <= high){
        int64_t mid = low + (high - low) / 2;
        // Se o elemento estiver presente no meio
        if (log_array[mid].value == key)
            return mid;
        // Se o elemento for maior, ignore a metade esquerda
        if (log_array[mid].value < key)
            low = mid + 1;
        // Se o elemento for menor, ignore a metade direita
        else
            high = mid - 1;
    }
    // Se o elemento não estiver presente no array
    return -1;
}

//Função que implementa o algoritmo de Baby-Step-Giant_Step para computar logaritmos discretos usando buscas binárias
int64_t baby_step_giant_step_binary(int64_t a, int64_t c, int64_t m){
    //Variáveis locais
    int64_t n=ceil(sqrt(m)); //n^(1/2))
    int64_t i, j;
    struct log_map* power_in=NULL;
    int64_t array_size=0;
    int64_t result=0;

    //Procedimentos
    //Pré-computando valores de a^(in) (mod m) e colocando seus elementos em ordem crescente
    for(i=0; i<=n; ++i){
        array_size++;
        power_in = (struct log_map*)realloc(power_in, array_size*sizeof(struct log_map));
        int64_t value1 = mod_bin_pow(a, (i*n), m);
        power_in[array_size-1].value=value1;
        power_in[array_size-1].index=i;
    }

    quicksort_ascending(power_in, 0, (array_size-1));

    //Loop principal buscando por valores que satisfazem a relação a^(in)= c(a^j) (mod m)
    for(j=0; j<n; ++j){
        int64_t value2=c*mod_bin_pow(a, j, m)%m;
        int64_t index = binary_search(power_in, 0, array_size-1, value2);
        if (index != -1){
            result=power_in[index].index*n-j;
            goto end;
        }
    }

    //Limpando o cachê de memória e retornando o resultado
    end:
    if(power_in) free(power_in);
    return result;
}

//********************************************************************************************************************************
//FIM DO HEADER
#endif
