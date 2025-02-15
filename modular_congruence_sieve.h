//VAMOS CRIAR UM PROGRAMA QUE USA RELAÇÕES DE CONGRUÊNCIA PARA FILTRAR NÚMEROS INTEIROS DE 64 BITS USANDO RELAÇÕES DE CONGRUÊNCIA

/*

VÁRIOS ALGORITMOS EM TEORIA DOS NÚMEROS REQUER A SELEÇÃO DE VALORES INTEIROS EM UM INTERVALO BASEADO EM
RELAÇÕES DE CONGRUÊNCIA DO TIPO a = b (mod p) COMO É NO CASO DO ALGORITMO DE GAUSS PARA FATORAR NÚMEROS
INTEIROS.

O ALGORITMO APRESENTADO AQUI PODE SER EFICIENTEMENTE IMPLEMENTADO USANDO-SE DETERMINADOS DISPOSITIVOS 
ELETROMECÂNICOS CAPAZES DE DETECTAR RELAÇÕES DE CONGRUÊNCIA BASEADOS EM PROPRIEDADES FÍSICAS
MENSURÁVEIS DOS DISPOSITIVOS OPERADOS. EQUIPAMENTOS MAIS MODERNOS SÃO CAPAZES DE CHECAR DE 10^8 A 10^9
RELAÇÕES POR SEGUNDO.

PARA MAIORES INFORMAÇÕES: The Joy Of Factoring by S. Wagstaff


*/



//*******************************************************************************************************************
//CABEÇALHO 
#ifndef MODULAR_CONGRUENCE_SIEVE_H
#define MODULAR_CONGRUENCE_SIEVE_H
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>


//*******************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void congruence_sieve_interval(int64_t[], int64_t[], int64_t, int64_t, int64_t);

//*******************************************************************************************************************
//FUNÇÕES
//Função que filtra números inteiros em um intervalo usando uma relação de congruência
/*
  NOTA: O presente algoritmo pode ser usado múltiplas vezes para refinar um intervalo
        de candidatos a resultado de um problema mais sofisticado.
*/
void congruence_sieve_interval(int64_t sieve_interval[], int64_t residue_classes[], int64_t moduli,
                               int64_t interval_size, int64_t residue_class_size){

  //Variáveis locais
  int64_t ap;
  bool good_moduli;

  //Procedimentos
    //Loop principal sobre os elementos do intervalo
    for(int64_t i=0; i<interval_size; ++i){

      //Restrição a valores já descartados em uma prévia execução do algoritmo
      if(sieve_interval[i]==0) continue;

      //Ajuste de variáveis
      good_moduli=false;
      ap=(sieve_interval[i]%moduli);

      //Loop sobre as classes residuais
      for(int64_t j=0; j<residue_class_size; ++j){
        if(ap==residue_classes[j]){
          good_moduli=true;
          break;
        };
      };

      //Checando se o valor atual satisfaz pelo menos uma da relações de congruência
      if(good_moduli==false) sieve_interval[i]=0;

    };//Fim do loop principal


};

//*******************************************************************************************************************
//FIM DO HEADER
#endif


