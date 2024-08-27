//VAMOS CRIAR UM PROGRAMA QUE COMPUTA RAÍZES QUADRADAS MODULARES USANDO SEQUÊNCIAS DE LUCAS

/*
O SEGUINTE ALGORITMO É ÚTIL PARA COMPUTAR RAÍZES QUADRADAS A MENOS DE UMA RELAÇÃO DE CONGRUÊNCIA:
DADOS h E n INTEIROS, p PRIMO TAIS QUE D=h²-4n É TAL QUE (d|p)=(-1) ((|) DENOTA O SÍMBOLO DE
JACOBI), ENTÃO A SOLUÇÃO DA EQUAÇÃO x²=n (mod p) É DADA POR x=[V((p+1)/2)]/2 (mod p). V DENOTA 
UMA SEQUÊNCIA DE LUCAS DO SEGUNDO TIPO.

PARA MAIORES INFORMAÇÕES: Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance


*/

//************************************************************************************************************
//CABEÇALHO
#ifndef LUCAS_SEQUENCE_MODULAR_SQUARE_ROOT_H
#define LUCAS_SEQUENCE_MODULAR_SQUARE_ROOT_H
#include<math.h>
#include"fast_lucas_sequence.h"
#include"jacobi_symbol.h"
#include"mod_bin_exponentiation128.h"


//************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void parameter_selection(int64_t*, int64_t, int64_t);
int64_t ls_modular_square_root(int64_t, int64_t);

//************************************************************************************************************
//FUNÇÕES
//Função que define o parâmetro h usado no algoritmo tal que D=h²-4n (D|p)=1
void parameter_selection(int64_t* h, int64_t n, int64_t prime){

  //Variáveis locais
  int64_t i, D;

  //Procedimentos
    //Loop principal
    for(i=(sqrt(n<<2)+1); i<n; ++i){
      D=(i*i)-(n<<2);
      if(jacobi(D, prime)==(-1)) break;
  
    }

  //Resultado
  (*h)=i;


};


//Função que calcula soluções da equação x²=n(mod p)
int64_t ls_modular_square_root(int64_t n, int64_t prime){

  //Restrição: n deve ser uma classe residual quadrática módulo um primo
  if(mod_bin_pow(n, ((prime-1)>>1), prime)!=1)
    return 0;

  //Variáveis locais
  __int128_t u, v;
  int64_t h, result;

  //Procedimentos
    //Seleção dos paÂmetros da sequência de Lucas
    parameter_selection(&h, n, prime);

    //Computando o (p+1)-ésimo termo da sequência mod
    fast_lucas_sequence(h, n, ((prime+1)>>1), &u, &v);


    //Ajuste fino do resultado
    result= (v>>1)%prime;
    while((result*result)%prime!=n) result++;

  //Resultado
  return result;

};


//************************************************************************************************************
//FIM DO HEADER
#endif
