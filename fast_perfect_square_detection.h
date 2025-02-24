//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ROTINAS PARA RÁPIDA DETECÇÃO DE QUADRADOS PERFEITOS USANDO ARITMÉTICA MODULAR

/*

PODEMOS USAR O SEGUINTE RESULTADO DA ARITMÉTICA MODULAR PARA DETECTAR RAPIDAMENTE QUADRADOS PEFEITOS:
SE n=i² E r=j² SÃO QUADRADOS PEEFEITOS, ENTÃO s = n (mod r) É UM QUADRADO PERFEITO TAMBÉM.

TAL FATO PODE SER USADO PARA RÁPIDA DETECÇÃO DE QUADRADOS PERFEITOS USANDO PEQUENAS CLASSES RESIDUAIS,
POR EXEMPLO, SE r=16, ENTÃO s=0,1,4,9.


*/



//******************************************************************************************************************
//CABEÇALHO
#ifndef PERFECT_SQUARE_DETECTION_H
#define PERFECT_SQUARE_DETECTION_H
#include"sqrt128.h"
#include<stdbool.h>
#include<math.h>


//CONSTANTES GLOBAIS
const int quadratic_residues_mod16[16]={1,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0};

//******************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool perfect_square_detection_64bits(uint64_t, uint64_t*);
bool perfect_square_detection_128bits(__int128_t, __int128_t*);


//******************************************************************************************************************
//FUNÇÕES
//Função para deteccção de quadrados perfeitos de inteiros de 64 bits
bool perfect_square_detection_64bits(uint64_t n, uint64_t* root){

  //Variáveis locais
  int is_square=quadratic_residues_mod16[n&15];


  //Procedimentos
    //Teste 1: checando a condição s = n (mod 16)={0,1,4,9}
    if(is_square==0) return false;
  
    //Teste 2: calculando raízes quadradas
    uint64_t r=sqrt(n);
    if((r*r)==n){
      (*root)=r;
      return true;
    }

  //Resultado em caso de falhas
  return false;

};

//Função para detecção de quadrados perfeitos de inteiros de 128 bits
bool perfect_square_detection_128bits(__int128_t n, __int128_t* root){

  //Variáveis locais
  int is_square=quadratic_residues_mod16[n&15];


  //Procedimentos
    //Teste 1: checando a condição s = n (mod 16)={0,1,4,9}
    if(is_square==0) return false;
  
    //Teste 2: calculando raízes quadradas
    __int128_t r=sqrt128(n);
    if((r*r)==n){
      (*root)=r;
      return true;
    }

  //Resultado em caso de falhas
  return false;

};

//******************************************************************************************************************
//FIM DO HEADER
#endif
