//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO sundaram_sieve.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o sundaram_sieve sundaram_sieve.c -lm -O2

//Cabeçalho
#include"sundaram_sieve.h"


//Função principal
int main(){

  //Variáveis  locais
  int64_t n;


  //Procedimentos
    //Recebendo input do9 usuário
    printf("[Inteiro] n: ");
    if(scanf("%li", &n)!=1) return 0;

    //Calculando números primos usando a peneira de Sundaram    
    sundaram_sieve(n);


  //Finalizando a aplicação
  return 0;

}

