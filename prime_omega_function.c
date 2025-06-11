//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO HEADER prime_omega_function.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o prime_omega_function prime_omega_function.c -lm -O2



//Cabeçalho
#include"prime_omega_function.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int32_t n;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    //Calculando a função ω(n) intervalo {1,2,...,n}
    int32_t* prime_omega_function_array=generate_prime_omega_function_array(n);

    for(int32_t i=1; i<=n; ++i) printf("ω(%i)=%i, ", i, prime_omega_function_array[i]);
    printf("...\n");


    //Limpando o cachê de memória
    if(prime_omega_function_array) free(prime_omega_function_array);
    prime_omega_function_array=NULL;


  //Finalizando a aplicação
  return 0;

}

