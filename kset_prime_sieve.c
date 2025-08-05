//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO kset_prime_sieve.h
//COMPILAR ESTEPROGRAMA COM O COMANDO: gcc -o kset_prime_sieve kset_prime_sieve.c -lm -O2


//Cabeçalho
#include"kset_prime_sieve.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int32_t m;


  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] m: ");
    if(scanf("%i", &m)!=1) return 0;

    //Gerando uma lista de números
    size_t p_size=0;
    int32_t* prime_array=kset_prime_sieve(m, &p_size);

    for(int32_t i=0;  i<p_size; ++i) printf("%i, ", prime_array[i]);
    printf("...\n");

    //Limpando o cachê de memória
    if(prime_array) free(prime_array); prime_array=NULL;


  //Finalizando a aplicação
  return 0;

}
