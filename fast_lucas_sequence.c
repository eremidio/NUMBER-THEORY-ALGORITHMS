//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO fast_lucas_sequence.h
//COMPILAR ESTE PROGRAMA COM OS COMANDO: gcc -o fast_lucas_sequence fast_lucas_sequence.c 


//Cabeçalho
#include"fast_lucas_sequence.h"
#include"int128.h"


//Função principal
int main(){

  //Variáveis locais
  int64_t P, Q, n;
  __int128_t V, U;

  //Procedimentos
    //Recebendo input do usuário

    //Calculando números de Mersenne usando sequências de Lucas com P=3 e Q=2
    P=3, Q=2;
    for(int64_t i=1; i<=126; ++i){
      fast_lucas_sequence(P, Q, i, &U, &V);
      printf("n: %li, M(n)=2^n-1: ", i);
      printf128(U);
    }


    //Testando a primalidade de 19
    P=5, Q=(-1);
    fast_modular_lucas_sequence(P, Q, 20, 19, &U, &V);

    printf("P=5, Q=(-1), U(20) mod 19: ");
    printf128(U);

  //Finalizando a aplicação
  return 0;

}
