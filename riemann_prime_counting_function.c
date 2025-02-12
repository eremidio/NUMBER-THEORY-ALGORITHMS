//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO riemann_prime_counting_function.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o riemann_prime_counting_function riemann_prime_counting_function.c -lm


//Cabeçalho
#include"riemann_prime_counting_function.h"
#include<stdio.h>



//Função principal
int main(){

  //Variáveis locais
  uint64_t prime_list_size;
  uint64_t* prime_list =NULL;

  //Procedimentos
    //Lendo a lista de primos  até 10^7 alocadas no arquivo 'prime_table.txt'
    prime_list=read_prime_table("prime_table.txt", prime_list, &prime_list_size);

    //Computando a função Π(x) para x<100
    printf("Valores de Π(x) para x≲100:\n");

    for(int i=1; i<=100; ++i){
      printf("Π(%d) = %lf, ",i, riemann_pi_weight_function(i, prime_list));
    };
    printf("...\n\n");


    //Computando a função Ri(x)
    printf("Função de contagem de primos de Riemann para 10^6≲ x ≲10^12:\n");
    printf("Ri(1000000)=%lf\n", riemann_prime_counting_function(1000000));
    printf("Ri(10000000)=%lf\n",  riemann_prime_counting_function(10000000));
    printf("Ri(100000000)=%lf\n", riemann_prime_counting_function(100000000));
    printf("Ri(1000000000)=%lf\n",  riemann_prime_counting_function(1000000000));
    printf("Ri(10000000000)=%lf\n", riemann_prime_counting_function(10000000000));
    printf("Ri(100000000000)=%lf\n",  riemann_prime_counting_function(100000000000));
    printf("Ri(1000000000000)=%lf\n", riemann_prime_counting_function(1000000000000));

    //Limpando o cachê de memória
    if(prime_list) free(prime_list); prime_list=NULL;

  //Finalizando a aplicação
  return 0;

}
