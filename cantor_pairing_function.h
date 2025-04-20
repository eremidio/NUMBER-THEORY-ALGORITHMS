//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA A FUNÇÃO DE PAREAMENTO DE CANTOR PARA INTEIROS DE 64 BITS

/*

UMA FUNÇÃO DE PAREAMENTO É UMA FUNÇÃO BIJETIVA F:AxA-> A; F(a, b)=c, QUE ASSOCIA A CADA PAR DE ELEMENTOS DE UM
CONJUNTO A, UM ÚNICO ELEMENTO DESTE CONJUNTO. POR SER UMA BIJEÇÃO A FUNÇÃO F É INVERTÍVEL, ISTO É, EXISTE A
TRANSFORMAÇÃO INVERSA F⁻¹: A->AxA F⁻¹(c)=(a, b).

FUNÇÕES DE PAREAMENTO SÃO EXTREMAMENTE IMPORTANTES EM MATEMÁTICA, TENDO MUITAS APLICAÇÕES EM TEORIA DE NÚMEROS,
ANÁLISE COMBINATÓRIA, TEORIA DOS CONJUNTOS E EM ÁREAS APLICADAS COMO A CRIPTOGRAFIA.

A FUNÇÃO DE PAREAMENTO DE CANTOR É DEFINIDA SOBRE O CONJUNTO DOS NÚMEROS NATURAIS PELA RELAÇÃO 
π(a,b)={(a+b+1)(a+b)}/2+b. TAL FUNÇÃO É MONOTÔNICA CRESCENTE PARA CADA UM DOS ARGUMENTOS E PODE SER FACILMENTE
INVERTIDA.

UM EXEMPLO DE APLICAÇÃO DESTA FUNÇÃO É NA DEMONSTRAÇÃO DA ENUMERABILIDADE DOS CONJUNTOS DOS RACIONAIS. SEGUNDO
O TEOREMA DE FUETER-PÓLYA, ESTA É A ÚNICA FUNÇÃO DE PAREAMENTO QUADRÁTICA. APLICAÇÕES CORRENTES INCLUEM A
COMPRESSÃO DE DADOS DE FORMA EFICIENTE, CÁLCULO DE CHAVES EM HASH TABLES, ENTRE OUTRAS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Pairing_function#Definition
                          https://pipme.github.io/posts/2020-04-25-cantor-pairing/
                          https://practicaldev-herokuapp-com.global.ssl.fastly.net/creuserr/cantor-pairing-for-string-compression-1534

*/ 


//***************************************************************************************************************
//CABEÇALHO
#ifndef CANTOR_PAIRING_FUNCTION_H
#define CANTOR_PAIRING_FUNCTION_H
#include"int128.h"
#include<math.h>


//***************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
__int128_t cantor_paring_function(int64_t, int64_t);
void inverse_cantor_paring_function(__int128_t, int64_t*, int64_t*);


//***************************************************************************************************************
//FUNÇÕES
//Função que implementa a função de pareamento de Cantor
__int128_t cantor_paring_function(int64_t a, int64_t b){


  //Variáveis locais
  __int128_t sum=(a+b);

  //Resultado
  return ((sum+1)*sum)/2+b;
};


//Função que implementa a rotina inversa da função de pareamento de Cantor
void inverse_cantor_paring_function(__int128_t z, int64_t* x, int64_t* y){

  //Variáveis locais
  double root=sqrt(8.0*z+1.0);
  int64_t w = floor((root-1)/2.0);
  __int128_t t =((w*w)+w)/2;
  int64_t y_=z-t, x_=w-y_;
  
  //Resultado
  (*x)=x_; (*y)=y_;

};


//***************************************************************************************************************
//FIM DO HEADER
#endif
