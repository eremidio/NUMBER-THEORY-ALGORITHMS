//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO mertens_function_sieving.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o mertens_function_sieving mertens_function_sieving.c -lm -O2



//Cabeçalho
#include"mertens_function_sieving.h"



//Função principal
int main(){

  //Variáveis locais
  uint64_t n=100000000, mobius_bound=floor(n/3.0)+2;

  //Procedimentos
    //Preenchendo um buffer de primos
    fill_prime_buffer();    
    
    //Computando um array com a função de Möbius
    struct mertens_pair* mobius_array=generate_mobius_array(mobius_bound);

   // printf("Lista de μ(n) usadas no cálculo: \n");
   // for(uint64_t i=0; i<=n; ++i) printf("μ(%lu)=%d, ", i, mobius_array[i].mu_n);
   // printf("...\n");


    //Computando a função de Mertens M(n)
    printf("M(100): %li\n", mertens_function_sieving(100, mobius_array));
    printf("M(1000): %li\n", mertens_function_sieving(1000, mobius_array));
    printf("M(10000): %li\n", mertens_function_sieving(10000, mobius_array));
    printf("M(100000): %li\n", mertens_function_sieving(100000, mobius_array));
    printf("M(1000000): %li\n", mertens_function_sieving(1000000, mobius_array));
    printf("M(10000000): %li\n", mertens_function_sieving(10000000, mobius_array));
    printf("M(100000000): %li\n", mertens_function_sieving(100000000, mobius_array));

    //Limpando o cachê de memória
    if(mobius_array) free(mobius_array); mobius_array=NULL;
  

  //Finalizando a aplicação
  return 0;

}
