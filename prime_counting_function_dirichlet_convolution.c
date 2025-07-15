//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO prime_counting_function_dirichlet_convolution.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o prime_counting_function_dirichlet_convolution prime_counting_function_dirichlet_convolution.c -lm -O3


//Cabeçalho
#include"prime_counting_function_dirichlet_convolution.h"
#include<stdio.h>



//Função principal 
int main(){

  //Variáveis locais
  int32_t* prime_omega_array=generate_prime_omega_function_array(100000000);
  int8_t* mobius_array=compute_mobius_function(100000000); 

  
  //Procedimentos
    //Computando a função de contagem de primos π(x) usando convoluções de Dirichlet
    printf("π(10)=%i\n", prime_counting_function_dirichlet_convolution(10, prime_omega_array, mobius_array));
    printf("π(100)=%i\n", prime_counting_function_dirichlet_convolution(100, prime_omega_array, mobius_array));
    printf("π(1000)=%i\n", prime_counting_function_dirichlet_convolution(1000, prime_omega_array, mobius_array));
    printf("π(10000)=%i\n", prime_counting_function_dirichlet_convolution(10000, prime_omega_array, mobius_array));
    printf("π(100000)=%i\n", prime_counting_function_dirichlet_convolution(100000, prime_omega_array, mobius_array));
    printf("π(1000000)=%i\n", prime_counting_function_dirichlet_convolution(1000000, prime_omega_array, mobius_array));
    printf("π(10000000)=%i\n", prime_counting_function_dirichlet_convolution(10000000, prime_omega_array, mobius_array));
    printf("π(100000000)=%i\n", prime_counting_function_dirichlet_convolution(100000000, prime_omega_array, mobius_array));


    //Limpando o cachê de memória
    if(prime_omega_array) free(prime_omega_array); prime_omega_array=NULL;
    if(mobius_array) free(mobius_array); mobius_array=NULL;


  //Finalizando a aplicação
  return 0;

}
