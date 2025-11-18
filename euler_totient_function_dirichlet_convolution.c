//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO euler_totient_function_dirichlet_convolution.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o euler_totient_function_dirichlet_convolution euler_totient_function_dirichlet_convolution.c -O2


//Cabeçalho
#include"euler_totient_function_dirichlet_convolution.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int32_t n;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    //Calculando a função de Möbius no intervalo {1,2,...,n}
    int8_t* mobius_array = compute_mobius_function(n);
    int32_t* euler_phi_array = compute_euler_totient_function_dirichlet_convolution(n, mobius_array);

    for(int32_t i=1; i<=n; ++i) printf("φ(%i)=%i, ", i, euler_phi_array[i]);
    printf("...\n");


    //Limpando o cachê de memória
    if(mobius_array) free(mobius_array); mobius_array=NULL;
    if(euler_phi_array) free(euler_phi_array); euler_phi_array=NULL;


  //Finalizando a aplicação
  return 0;

}


