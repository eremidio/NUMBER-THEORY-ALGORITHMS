//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO goldbach_conjecture.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o goldbach_conjecture goldbach_conjecture.c -O2


//Cabeçalho
#include"goldbach_conjecture.h"

//Função principal
int main(){


  //Variáveis locais
  int32_t n, gn;


  //Procedimento
    //Recebendo input do usuário e alocando um array de números primos
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    bool* prime_array = fill_prime_buffer(n);
    
  
    //Testando a conjectura de Goldbach
    for(int32_t i=4; i<=n; i+=2){
      gn=compute_golbach_partition(i, prime_array, Yes); //Use 'No' para obter apenas a função de partição de Goldbach
      printf("g(%i)=%i\n", i, gn);
    };    

    //Limpeza do cachê de memória
    if(prime_array) free(prime_array); prime_array=NULL;


  //Finalizando a aplicação
  return 0;

}

