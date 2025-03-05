//VAMOS CRIAR UM PROGRAMA PARA  TESTAR AS ROTINAS CRIADAS NO ARQUIVO ramanujan_gamma_function_approximantion.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o ramanujan_gamma_function_approximation ramanujan_gamma_function_approximation.c -lm


//Cabeçalho
#include"ramanujan_gamma_function_approximation.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t n=1; //5!


  //Procedimentos
    //Computando valores da função fatorial n!=Γ(n+1)
    for(int i=1; i<=16; ++i){
      n*=i;
      printf("[Fatorial] %i!=%li\n", i, n);
      printf("[Aproximação de Ramanujan] %i!=%.9Lf\n", i, factorial_function_ramanujan_approximation(i));

    }


  printf("\n[Aproximação de Ramanujan] π: %Lf\n", ((16.0/9.0)*gamma_function_ramanujan_approximation(1.5)*gamma_function_ramanujan_approximation(1.5)));



  //Finalizando a aplicação
  return 0;

}
