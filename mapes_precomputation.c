//VAMOS CRIARUM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO mapes_precomputation.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o mapes_precomputation mapes_precomputation.c



//Cabeçalho
#include"mapes_precomputation.h"


//Função principal
int main(){

  //Carregando valores pré-computados da função φ(m, n)
  mapes_precomputation();

  //Teste
  /*
     VER: Prime Numbers And Computer Methods For Factorization, by Hans Riesel,
     na página 15 para ver a tabela a ser reproduzida aqui.
  */
  for(int i=0; i<1000; ++i) printf("φ(%d, 15)=%li\n", i, mapes15[i]);
   


  //Finalizando a aplicação
  return 0;

}


