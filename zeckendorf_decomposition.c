//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO zeckendorf_decomposition.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o zeckendorf_decomposition zeckendorf_decomposition.c -lm -O2


//Cabeçalho
#include"zeckendorf_decomposition.h"


//Função principal
int main(){

  //Variáveis locais
  __int128_t fib_mul;
  uint64_t a, b;


  //Procedimentos
    //Preenchendo um buffer dos números de Fibonnaci
    fill_fibonacci_buffer();

/*    for(int i=0; i<185; ++i){
      printf("F(%i)= ", i);
      printf128(fibonacci_buffer[i]);
    };
*/

    //Recebendo input usuário
    printf("[Inteiro] a: ");
    if(scanf("%lu", &a)!=1) return 0;

    printf("[Inteiro] b: ");
    if(scanf("%lu", &b)!=1) return 0; 

    //Calculando a decomposição de Zeckendorf do números em questão
    int* a_fib_array=zeckendorf_decomposition(a);
    int* b_fib_array=zeckendorf_decomposition(b);
    int a_fib_size=sizeof(a_fib_array)/sizeof(a_fib_array[0]);
    int b_fib_size=sizeof(b_fib_array)/sizeof(b_fib_array[0]);
   
    
    printf("%lu= ", a);
    for(int i=0; i<a_fib_size; ++i) printf("F(%i)+", a_fib_array[i]);
    printf("...\n");

    printf("%lu= ", b);
    for(int i=0; i<b_fib_size; ++i) printf("F(%i)+", b_fib_array[i]);
    printf("...\n");


    //Calculando o produto de Fibonacci
    fib_mul=fibonacci_multiplication(a_fib_array, b_fib_array, a_fib_size, b_fib_size);
    printf("a°b = "); printf128(fib_mul);


    //Limpando o cachê de memória
    if(a_fib_array) free(a_fib_array); a_fib_array=NULL;
    if(b_fib_array) free(b_fib_array); b_fib_array=NULL;


  //Finalizando a aplicação
  return 0;

}
